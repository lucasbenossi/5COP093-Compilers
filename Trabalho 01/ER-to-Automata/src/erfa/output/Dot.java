package erfa.output;

import java.io.PrintStream;

public class Dot {
	private PrintStream out;
	
	public Dot(PrintStream out) {
		this.out = out;
	}
	
	public void start() {
		out.println("digraph \"Automata\" {");
		out.println("\tnode [shape=circle];");
		out.println("\trankdir=LR;");
	}
	public void printFinal(int qf, String token) {
		out.printf("\tq%d [shape=doublecircle, xlabel=\"%s\"];\n", qf, token);
	}
	public void printTransition(int from, int to, String symbols) {
		out.printf("\tq%d -> q%d [label=\"%s\"];\n", from, to, symbols);
	}
	public void end() {
		out.println("}");
	}
}
