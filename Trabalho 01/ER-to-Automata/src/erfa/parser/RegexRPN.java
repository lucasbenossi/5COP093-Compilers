package erfa.parser;

import java.util.LinkedList;
import java.util.Stack;

import erfa.automata.RegexNFA;
import erfa.automata.Thompson;
import erfa.parser.Token.*;

public class RegexRPN {
	private LinkedList<Token> tokens;
	
	public RegexRPN(LinkedList<Token> tokens) {
		this.tokens = tokens;
	}
	
	public RegexNFA result() {
		Stack<RegexNFA> stack = new Stack<>();
		
		for(Token token : tokens) {
			if(token instanceof TokenSymbol) {
				TokenSymbol tokenSymbol = (TokenSymbol) token;
				RegexNFA nfa = new RegexNFA(tokenSymbol.symbol);
				stack.push(nfa);
			}
			else if(token instanceof TokenString) {
				TokenString tokenString = (TokenString) token;
				RegexNFA nfa = new RegexNFA(tokenString.string);
				stack.push(nfa);
			}
			else if(token instanceof TokenSetExp) {
				TokenSetExp tokenCharSet = (TokenSetExp) token;
				RegexNFA nfa = new RegexNFA(tokenCharSet.setExp);
				stack.push(nfa);
			}
			else if(token instanceof TokenOperator) {
				TokenOperator tokenOp = (TokenOperator) token;
				if(tokenOp.isKleeneStar()) {
					RegexNFA nfa = stack.pop();
					stack.push(Thompson.kleene(nfa));
				}
				else if(tokenOp.isKleenePlus()) {
					RegexNFA nfa = stack.pop();
					stack.push(Thompson.concat(nfa, Thompson.kleene(nfa)));
				}
				else if(tokenOp.isConcat()) {
					RegexNFA rhs = stack.pop();
					RegexNFA lhs = stack.pop();
					stack.push(Thompson.concat(lhs, rhs));
				}
				else if(tokenOp.isUnion()) {
					RegexNFA rhs = stack.pop();
					RegexNFA lhs = stack.pop();
					stack.push(Thompson.union(lhs, rhs));
				}
			}
		}
		
		return stack.pop();
	}
}
