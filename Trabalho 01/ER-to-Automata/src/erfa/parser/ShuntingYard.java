package erfa.parser;

import java.util.LinkedList;
import java.util.Stack;

import erfa.parser.Token.*;
import erfa.utils.CharSet;
import erfa.utils.StringIterator;

public class ShuntingYard {
	private StringIterator input;
	private LinkedList<Token> output;
	private Stack<Character> operators;
	private boolean first;
	
	public ShuntingYard(String input) {
		this.input = new StringIterator(input);
		this.output = new LinkedList<>();
		this.operators = new Stack<>();
		this.first = true;
	}
	
	public LinkedList<Token> parse(){
		char c = getNext();
		while(c != '\0') {
			if(isSymbol(c)) {
				pushDotOperator();
				putSymbol(c);
			}
			else if(isLeftSqBracket(c)) {
				pushDotOperator();
				String set = new String();
				set += '[';
				c = getNext();
				while(!isRightSqBracket(c)) {
					set += c;
					c = getNext();
				}
				set += ']';
				putCharSet(new CharSet(set));
			}
			else if(isQuote(c)){
				pushDotOperator();
				String string = new String();
				c = getNext();
				while(!isQuote(c)) {
					string += c;
					c = getNext();
				}
				putString(string);
			}
			else if(isOperator(c)) {
				pushOperator(c);
				if(c == '|' || c == '.') {
					first = true;
				}
			}
			else if(isLeftBracket(c)) {
				pushDotOperator();
				operators.push(c);
				first = true;
			}
			else if(isRightBracket(c)) {
				while(!isLeftBracket(operators.peek())) {
					popOperator();
				}
				operators.pop();
				first = false;
			}
			c = getNext();
		}
		while(operators.size() > 0) {
			popOperator();
		}
		return output;
	}
	
	private void pushOperator(char operator){
		while (!operators.isEmpty() 
				&& !isLeftBracket(operators.peek())
				&& getPrecedence(operators.peek()) > getPrecedence(operator)) {
			popOperator();
		}
		operators.push(operator);
	}
	private void pushDotOperator() {
		if(first) {
			first = false;
		}
		else {
			pushOperator('.');
		}
	}
	private void popOperator() {
		output.add(new TokenOperator(operators.pop()));
	}
	private void putString(String string) {
		output.add(new TokenString(string));
	}
	private void putSymbol(char symbol) {
		output.add(new TokenSymbol(symbol));
	}
	private void putCharSet(CharSet set) {
		output.add(new TokenCharSet(set));
	}
	
	private char getNext() {
		return input.next();
	}

	private boolean isOperator(char c){
		return c == '*' || c == '|' || c == '.' || c == '+';
	}
	private boolean isLeftBracket(char c){
		return c == '(';
	}
	private boolean isRightBracket(char c){
		return c == ')';
	}
	private boolean isLeftSqBracket(char c){
		return c == '[';
	}
	private boolean isRightSqBracket(char c){
		return c == ']';
	}
	private boolean isQuote(char c){
		return c == '"';
	}
	private boolean isSymbol(char c){
		return !isOperator(c) &&
		!isLeftBracket(c) && !isRightBracket(c) &&
		!isLeftSqBracket(c) && !isRightSqBracket(c) &&
		!isQuote(c);
	}
	private int getPrecedence(char c){
		if(c == '*' || c == '+'){
			return 3;
		}
		if(c == '.'){
			return 2;
		}
		if(c == '|'){
			return 1;
		}
		return 0;
	}
}
