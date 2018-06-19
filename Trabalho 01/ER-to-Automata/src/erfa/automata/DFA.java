package erfa.automata;

import java.io.PrintStream;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedHashMap;
import java.util.LinkedHashSet;
import java.util.LinkedList;
import java.util.TreeMap;
import java.util.TreeSet;

public class DFA {
	public int states;
	public LinkedList<Transition> transitions;
	public LinkedHashSet<Integer> finals;
	public HashMap<Integer, String> tokens;
	
	private Symbols alphabet;
	private NFATable nfaTable;
	
	public DFA(NFA nfa) {
		this.transitions = new LinkedList<>();
		this.finals = new LinkedHashSet<>();
		this.tokens = new HashMap<>();
		
		this.alphabet = new Symbols();
		for(Transition t : nfa.transitions) {
			alphabet.add(t.symbol);
		}
	
		this.nfaTable = new NFATable(nfa.states);
		for(Transition t : nfa.transitions) {
			nfaTable.put(t);
		}
		
		alphabet.remove('\0');
		
		LinkedList<StateSet> todo = new LinkedList<>();
		HashSet<StateSet> done = new HashSet<>();
		StateSetMap states = new StateSetMap();

		StateSet q0 = new StateSet();
		q0.add(0);
		q0 = q0.epsilon();
		todo.add(q0);
		states.put(q0);
		
		while(!todo.isEmpty()) {
			StateSet from = todo.remove();
			if(done.contains(from)) {
				continue;
			}
			done.add(from);
			for(char symbol : alphabet) {
				StateSet to = new StateSet();
				for(int state : from) {
					to.addAll(nfaTable.get(state).get(symbol).epsilon());
				}
				if(to.size() > 0) {
					todo.add(to);
					states.put(to);
					transitions.add(new Transition(states.get(from), states.get(to), symbol));
				}
			}
		}
		
		for(StateSet state : states.keySet()) {
			int q = states.get(state);
			for(int i : state) {
				if(nfa.finals.contains(i)) {
					finals.add(q);
					String proposedToken = nfa.tokens.get(i);
					String currentToken = this.tokens.get(q);
					if(currentToken == null || nfa.priority.get(proposedToken) < nfa.priority.get(currentToken)) {
						this.tokens.put(q, proposedToken);
					}
				}
			}
		}
		
		this.states = states.size();
	}
	
	public void toDot(PrintStream out) {
		Dot dot = new Dot(out);
		dot.start();
		for(int qf : this.finals) {
			dot.printFinal(qf, this.tokens.get(qf));
		}
		dot.printTransition(this.transitions);
		dot.end();
	}
	
	private class NFATable extends HashMap<Integer, TreeMap<Character, StateSet>> {
		private static final long serialVersionUID = -5210114328616677151L;
		public NFATable(int states) {
			super();
			for(int i = 0; i < states; i++) {
				TreeMap<Character, StateSet> state = new TreeMap<>();
				for(char symbol : alphabet) {
					state.put(symbol, new StateSet());
				}
				this.put(i, state);
			}
		}
		public void put(Transition t) {
			this.get(t.from).get(t.symbol).add(t.to);
		}
	}
	private class StateSet extends TreeSet<Integer> {
		private static final long serialVersionUID = 5963420611280408964L;
		public StateSet epsilon() {
			StateSet result = new StateSet();
			result.addAll(this);
			int size;
			do {
				size = result.size();
				StateSet aux = new StateSet();
				for(int state : result) {
					aux.addAll(nfaTable.get(state).get('\0'));
				}
				result.addAll(aux);
			} while(result.size() != size);
			return result;
		}
	}
	private class StateSetMap extends LinkedHashMap<StateSet, Integer> {
		private static final long serialVersionUID = 6424798434558917240L;
		private int q = 0;
		public void put(StateSet states) {
			if(!this.containsKey(states)) {
				this.put(states, q);
				q++;
			}
		}
	}
}
