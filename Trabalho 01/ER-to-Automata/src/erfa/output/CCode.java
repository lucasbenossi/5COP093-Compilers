package erfa.output;

import java.io.PrintStream;

public class CCode {
	private PrintStream out;
	
	public CCode(PrintStream out) {
		this.out = out;
	}
	
	public void printStates(int states) {
		out.printf("static const int STATES = %d;\n", states);
	}
	public void printFinal(int qf) {
		out.printf("set_final(%d);\n", qf);
	}
	public void printFinal(int qf, String token) {
		printFinal(qf);
		out.printf("set_token(%d, %s);\n", qf, token);
	}
	public void printTransition(int from, int to, char symbol) {
		out.printf("set_transition(%d, '%c', %d);\n", from, symbol, to);
	}
	public void printTransition(int from, int to, char start, char end) {
		out.printf("for(char i = '%c'; i <= '%c'; i++) set_transition(%d, i, %d);\n", start, end, from, to);
	}
}
