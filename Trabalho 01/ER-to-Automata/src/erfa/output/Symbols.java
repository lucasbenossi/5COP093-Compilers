package erfa.output;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.TreeSet;

public class Symbols extends TreeSet<Character> {
	private static final long serialVersionUID = -2739754664611746333L;
	private boolean first;
	public List<Symbol> toSymbolList(){
		List<Symbol> list = new LinkedList<>();
		ArrayList<Character> chars = new ArrayList<>(this);
		int size = chars.size();
		for(int i = 0; i < size; i++) {
			if(isSequenceable(chars.get(i))) {
				char start = chars.get(i);
				int j = i;
				int k = i + 1;
				while(k < size && chars.get(k) - chars.get(j) == 1 && isSequenceable(chars.get(k))) {
					j++;
					k++;
				}
				char end = chars.get(j);
				if(end - start >= 2) {
					list.add(new Symbol(start, end));
				}
				else if(end - start == 1) {
					list.add(new Symbol(start));
					list.add(new Symbol(end));
				}
				else if(end - start == 0) {
					list.add(new Symbol(start));
				}
				i = j;
			}
			else {
				list.add(new Symbol(chars.get(i)));
			}
		}
		return list;
	}
	@Override
	public String toString() {
		List<Symbol> list = this.toSymbolList();
		String string = new String();
		this.first = true;
		for(Symbol symbol : list) {
			string += comma() + symbol.toString();
		}
		return string;
	}
	private boolean isSequenceable(int c) {
		if(c >= 'a' && c <= 'z') {
			return true;
		}
		if(c >= 'A' && c <= 'Z') {
			return true;
		}
		if(c >= '0' && c <= '9') {
			return true;
		}
		return false;
	}
	private String comma() {
		if(this.first) {
			this.first = false;
			return "";
		}
		else {
			return ", ";
		}
	}
}
