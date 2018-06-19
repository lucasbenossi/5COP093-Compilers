package erfa.automata;

import java.util.HashMap;
import java.util.LinkedHashSet;
import java.util.LinkedList;
import java.util.List;

import erfa.output.Dot;
import erfa.output.Table;

public class NFA {
	public int states;
	public LinkedList<Transition> transitions;
	public LinkedHashSet<Integer> finals;
	public HashMap<Integer, String> tokens;
	public HashMap<String, Integer> priority;
	private int counter;
	
	public NFA() {
		this.states = 1;
		this.transitions = new LinkedList<>();
		this.finals = new LinkedHashSet<>();
		this.tokens = new HashMap<>();
		this.priority = new HashMap<>();
		this.counter = 0;
	}
	
	public void insertRNFA(RegexNFA rnfa) {
		int offset = this.states;
		this.transitions.add(new Transition(0, offset));
		for(Transition t : rnfa.transitions) {
			this.transitions.add(new Transition(t.from + offset, t.to + offset, t.symbol));
		}
		this.finals.add(rnfa.qf + offset);
		this.tokens.put(rnfa.qf + offset, rnfa.token);
		this.priority.put(rnfa.token, counter);
		counter++;
		this.states += rnfa.states;
	}
	
	public void insertRNFAs(List<RegexNFA> rnfas, List<String> tokens) {
		for (RegexNFA rnfa : rnfas) {
			this.insertRNFA(rnfa);
		}
	}
	
	public void toDot(Dot dot) {
		Table table = new Table(transitions);
		dot.start();
		for(int qf : this.finals) {
			dot.printFinal(qf, this.tokens.get(qf));
		}
		table.toDot(dot);
		dot.end();
	}
}
