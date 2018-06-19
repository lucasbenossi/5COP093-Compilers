package erfa.automata;

public class Thompson {
	public static RegexNFA kleene(RegexNFA automata) {
		RegexNFA result = new RegexNFA(automata.states + 2);
		int offset = 1;
		result.insertEpsilonTransition(0, offset);
		result.insertEpsilonTransition(0, result.qf);
		result.insertTransitions(automata, offset);
		result.insertEpsilonTransition(automata.qf + offset, result.qf);
		result.insertEpsilonTransition(automata.qf + offset, offset);
		return result;
	}
	public static RegexNFA concat(RegexNFA lhs, RegexNFA rhs) {
		RegexNFA result = new RegexNFA(lhs.states + rhs.states - 1);
		int offset = 0;
		result.insertTransitions(lhs, offset);
		offset = lhs.states - 1;
		result.insertTransitions(rhs, offset);
		return result;
	}
	public static RegexNFA union(RegexNFA lhs, RegexNFA rhs) {
		RegexNFA result = new RegexNFA(lhs.states + rhs.states + 2);
		int offset = 1;
		result.insertEpsilonTransition(0, offset);
		result.insertTransitions(lhs, offset);
		result.insertEpsilonTransition(lhs.qf + offset, result.qf);
		offset += lhs.states;
		result.insertEpsilonTransition(0, offset);
		result.insertTransitions(rhs, offset);
		result.insertEpsilonTransition(rhs.qf + offset, result.qf);
		return result;
	}
}
