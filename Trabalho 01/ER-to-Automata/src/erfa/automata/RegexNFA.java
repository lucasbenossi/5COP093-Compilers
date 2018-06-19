package erfa.automata;

import java.io.PrintStream;
import java.util.LinkedList;

import erfa.parser.RegexRPN;
import erfa.parser.ShuntingYard;
import erfa.utils.CharSet;

public class RegexNFA {
	public int states, qf;
	public LinkedList<Transition> transitions;
	public String token;
	
	public static RegexNFA compile(String regex, String token) {
		RegexNFA rnfa = new RegexRPN(new ShuntingYard(regex).parse()).result();
		rnfa.token = token;
		return rnfa;
	}
	
	public RegexNFA(int states) {
		this.states = states;
		this.qf = states - 1;
		this.transitions = new LinkedList<>();
		this.token = "";
	}
	public RegexNFA(char symbol) {
		this(2);
		this.insertTransition(0, 1, symbol);
	}
	public RegexNFA(String string) {
		this(string.length() + 1);
		for(int i = 0; i < string.length(); i++) {
			this.insertTransition(i, i+1, string.charAt(i));
		}
	}
	public RegexNFA(CharSet set) {
		this(2);
		for(char c : set) {
			this.insertTransition(0, 1, c);
		}
	}
	
	public void insertTransition(int from, int to, char symbol) {
		this.transitions.add(new Transition(from, to, symbol));
	}
	public void insertEpsilonTransition(int from, int to) {
		this.transitions.add(new Transition(from, to));
	}
	public void insertTransitions(RegexNFA automata, int offset) {
		for(Transition t : automata.transitions) {
			this.insertTransition(t.from + offset, t.to + offset, t.symbol);
		}
	}
	public void toDot(PrintStream out) {
		Dot dot = new Dot(out);
		dot.start();
		dot.printFinal(this.qf, this.token);
		dot.printTransition(this.transitions);
		dot.end();
	}
}
