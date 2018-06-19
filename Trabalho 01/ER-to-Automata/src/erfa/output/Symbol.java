package erfa.output;

public class Symbol {
	public char symbol, start, end;
	public boolean interval = false;
	
	public Symbol(char symbol) {
		this.symbol = symbol;
		this.start = '\0';
		this.end = '\0';
		this.interval = false;
	}
	public Symbol(char start, char end) {
		this.symbol = '\0';
		this.start = start;
		this.end = end;
		this.interval = true;
	}
	@Override
	public String toString() {
		String string = new String();
		if(this.interval) {
			string += start + "-" + end;
		}
		else if(symbol == '"') {
			string += "\\" + symbol;
		}
		else if(symbol == ' ') {
			string += "(space)";
		}
		else if(symbol == '\t') {
			string += "TAB";
		}
		else if(symbol == '\n') {
			string += "NL";
		}
		else if(symbol == '\r') {
			string += "CR";
		}
		else {
			string += symbol;
		}
		return string;
	}
}
