package erfa.automata;

import java.io.PrintStream;
import java.util.LinkedHashMap;
import java.util.List;

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
	public void printTransition(List<Transition> transitions) {
		LinkedHashMap<Integer, LinkedHashMap<Integer, Symbols>> map1 = new LinkedHashMap<>();
		for(Transition t : transitions) {
			LinkedHashMap<Integer, Symbols> map2 = map1.get(t.from);
			if(map2 == null) {
				map2 = new LinkedHashMap<>();
				map1.put(t.from, map2);
			}
			Symbols symbols = map2.get(t.to);
			if(symbols == null) {
				symbols = new Symbols();
				map2.put(t.to, symbols);
			}
			symbols.add(translateChar(t.symbol));
		}
		for(int from : map1.keySet()) {
			LinkedHashMap<Integer, Symbols> map2 = map1.get(from);
			for(int to : map2.keySet()) {
				Symbols symbols = map2.get(to);
				out.printf("\tq%d -> q%d [label=\"%s\"];\n", from, to, symbols.toString());
			}
		}
	}
	public void end() {
		out.println("}");
	}
	
	private static char translateChar(char c) {
		if(c == '\0') {
			return 'ε';
		}
		return c;
	}
}
