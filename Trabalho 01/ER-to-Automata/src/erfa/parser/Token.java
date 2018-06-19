package erfa.parser;

import erfa.utils.SetExp;

public interface Token {
	public static class TokenSymbol implements Token {
		public char symbol;
		public TokenSymbol(char symbol) {
			this.symbol = symbol;
		}
		public String toString() {
			return Character.toString(this.symbol);
		}
	}
	
	public static class TokenSetExp implements Token {
		public SetExp setExp;
		public TokenSetExp(SetExp setExp) {
			this.setExp = setExp;
		}
		public String toString() {
			return this.setExp.toString();
		}
	}

	public static class TokenString implements Token {
		public String string;
		public TokenString(String string) {
			this.string = string;
		}
		public String toString() {
			return this.string;
		}
	}

	public static class TokenOperator implements Token {
		private OperatorType type;
		public TokenOperator(char operator) {
			switch(operator) {
			case '*':
				this.type = OperatorType.KLEENE_STAR;
				break;
			case '+':
				this.type = OperatorType.KLEENE_PLUS;
				break;
			case '.':
				this.type = OperatorType.CONCAT;
				break;
			case '|':
				this.type = OperatorType.UNION;
				break;
			case '(':
				this.type = OperatorType.LEFT_PAREN;
				break;
			case ')':
				this.type = OperatorType.RIGHT_PAREN;
				break;
			}
		}
		public boolean isKleeneStar() {
			return this.type.equals(OperatorType.KLEENE_STAR);
		}
		public boolean isKleenePlus() {
			return this.type.equals(OperatorType.KLEENE_PLUS);
		}
		public boolean isConcat() {
			return this.type.equals(OperatorType.CONCAT);
		}
		public boolean isUnion() {
			return this.type.equals(OperatorType.UNION);
		}
		public boolean isLeftParen() {
			return this.type.equals(OperatorType.LEFT_PAREN);
		}
		public boolean isRightParen() {
			return this.type.equals(OperatorType.RIGHT_PAREN);
		}
		public String toString() {
			return this.type.toString();
		}
		private enum OperatorType{
			KLEENE_STAR, KLEENE_PLUS, CONCAT, UNION, LEFT_PAREN, RIGHT_PAREN;
		}
	}
}
