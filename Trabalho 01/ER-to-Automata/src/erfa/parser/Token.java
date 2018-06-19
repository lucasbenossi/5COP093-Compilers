package erfa.parser;

import erfa.utils.CharSet;

public interface Token {
	public static class TokenSymbol implements Token {
		public char symbol;
		public TokenSymbol(char symbol) {
			this.symbol = symbol;
		}
	}
	
	public static class TokenCharSet implements Token {
		public CharSet charSet;
		public TokenCharSet(CharSet charSet) {
			this.charSet = charSet;
		}
	}

	public static class TokenString implements Token {
		public String string;
		public TokenString(String string) {
			this.string = string;
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
		private enum OperatorType{
			KLEENE_STAR, KLEENE_PLUS, CONCAT, UNION;
		}
	}
}
