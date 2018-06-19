package erfa.output;

import java.util.LinkedHashMap;
import java.util.List;

import erfa.automata.Transition;

public class Table extends LinkedHashMap<Integer, LinkedHashMap<Integer, Symbols>> {
	private static final long serialVersionUID = 7349934723666284819L;
	
	public Table(List<Transition> transitions) {
		super();
		for(Transition t : transitions) {
			LinkedHashMap<Integer, Symbols> map = this.get(t.from);
			if(map == null) {
				map = new LinkedHashMap<>();
				this.put(t.from, map);
			}
			Symbols symbols = map.get(t.to);
			if(symbols == null) {
				symbols = new Symbols();
				map.put(t.to, symbols);
			}
			symbols.add(translateChar(t.symbol));
		}
	}
	
	public void toDot(Dot dot) {
		for(int from : this.keySet()) {
			LinkedHashMap<Integer, Symbols> map2 = this.get(from);
			for(int to : map2.keySet()) {
				Symbols symbols = map2.get(to);
				dot.printTransition(from, to, symbols.toString());
			}
		}
	}
	public void toCCode(CCode c) {
		for(int from : this.keySet()) {
			LinkedHashMap<Integer, Symbols> map2 = this.get(from);
			for(int to : map2.keySet()) {
				List<Symbol> list = map2.get(to).toSymbolList();
				for(Symbol s : list) {
					if(s.interval) {
						c.printTransition(from, to, s.start, s.end);
					}
					else {
						c.printTransition(from, to, s.symbol);
					}
				}
			}
		}
	}
	
	private static char translateChar(char c) {
		if(c == '\0') {
			return 'ε';
		}
		return c;
	}
}
