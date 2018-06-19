package erfa.automata;

import java.util.ArrayList;
import java.util.TreeSet;

public class Symbols extends TreeSet<Character> {
	private static final long serialVersionUID = -2739754664611746333L;
	private boolean first = true;
	@Override
	public String toString() {
		ArrayList<Character> chars = new ArrayList<>(this);
		int size = chars.size();
		String string = new String();
		for(int i = 0; i < size; i++) {
			if(isSequenceable(chars.get(i))) {
				char start = chars.get(i);
				int j = i;
				int k = i + 1;
				while(k < size && chars.get(k) - chars.get(j) == 1) {
					j++;
					k++;
				}
				char end = chars.get(j);
				string += comma();
				if(end - start >= 2) {
					string += start + "-" + end;
				}
				else if(end - start == 1) {
					string += start + comma() + end;
				}
				else if(end - start == 0) {
					string += start;
				}
				i = j;
			}
			else {
				string += comma() + chars.get(i);
			}
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
