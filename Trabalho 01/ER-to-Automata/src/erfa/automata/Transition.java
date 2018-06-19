package erfa.automata;

public class Transition {
	public int from, to;
	public char symbol;
	
	public Transition(int from, int to) {
		this.from = from;
		this.to = to;
		this.symbol = '\0';
	}
	public Transition(int from, int to, char symbol) {
		this(from, to);
		this.symbol = symbol;
	}
}