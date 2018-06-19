package erfa.parser;

import java.util.LinkedList;
import java.util.Stack;

import erfa.parser.Token.*;
import erfa.utils.SetExp;
import erfa.utils.StringIterator;

public class ShuntingYard {
	private StringIterator input;
	private LinkedList<Token> output;
	private Stack<TokenOperator> operators;
	private boolean first;
	
	public ShuntingYard(String input) {
		this.input = new StringIterator(input);
		this.output = new LinkedList<>();
		this.operators = new Stack<>();
		this.first = true;
	}
	
	public LinkedList<Token> parse(){
		Token token = getNext();
		while(token != null) {
			if(token instanceof TokenSymbol) {
				pushConcatOperator();
				putToken(token);
			}
			else if(token instanceof TokenSetExp) {
				pushConcatOperator();
				putToken(token);
			}
			else if(token instanceof TokenString){
				pushConcatOperator();
				putToken(token);
			}
			else if(token instanceof TokenOperator) {
				TokenOperator operator = (TokenOperator) token;
				if(operator.isLeftParen()) {
					pushConcatOperator();
					operators.push(operator);
					first = true;
				}
				else if(operator.isRightParen()) {
					while(!operators.peek().isLeftParen()) {
						popOperator();
					}
					operators.pop();
					first = false;
				}
				else {
					pushOperator(operator);
					if(operator.isUnion()) {
						first = true;
					}
				}
			}
			token = getNext();
		}
		while(operators.size() > 0) {
			popOperator();
		}
		return output;
	}
	
	private void pushOperator(TokenOperator operator){
		while (!operators.isEmpty() 
				&& !operators.peek().isLeftParen()
				&& getPrecedence(operators.peek()) > getPrecedence(operator)) {
			popOperator();
		}
		operators.push(operator);
	}
	private void pushConcatOperator() {
		if(first) {
			first = false;
		}
		else {
			pushOperator(new TokenOperator('.'));
		}
	}
	private void popOperator() {
		output.add(operators.pop());
	}
	private void putToken(Token token) {
		output.add(token);
	}
	
	private Token getNext() {
		char c = input.next();
		Token token = null;
		if(c == '\0') {
			token = null;
		}
		else if(isSymbol(c)) {
			token = new Token.TokenSymbol(c);
		}
		else if(isLeftBracket(c)) {
			String set = new String();
			set += '[';
			c = input.next();
			while(!isRightBracket(c)) {
				set += c;
				c = input.next();
			}
			set += ']';
			token = new Token.TokenSetExp(new SetExp(set));
		}
		else if(isQuote(c)){
			String string = new String();
			c = input.next();
			while(!isQuote(c)) {
				string += c;
				c = input.next();
			}
			token = new Token.TokenString(string);
		}
		else if(isOperator(c)) {
			token = new Token.TokenOperator(c);
		}
		else if(isDot(c)) {
			token = new Token.TokenSetExp(new SetExp());
		}
		return token;
	}

	private boolean isOperator(char c){
		return c == '*' || c == '+' || c == '|' || c == '(' || c == ')';
	}
	private boolean isDot(char c) {
		return c == '.';
	}
	private boolean isLeftBracket(char c){
		return c == '[';
	}
	private boolean isRightBracket(char c){
		return c == ']';
	}
	private boolean isQuote(char c){
		return c == '"';
	}
	private boolean isSymbol(char c){
		return !isOperator(c) && !isDot(c) &&
		!isLeftBracket(c) && !isRightBracket(c) &&
		!isQuote(c);
	}
	private int getPrecedence(TokenOperator token){
		if(token.isKleeneStar() || token.isKleenePlus()){
			return 3;
		}
		if(token.isConcat()) {
			return 2;
		}
		if(token.isUnion()){
			return 1;
		}
		return 0;
	}
}
