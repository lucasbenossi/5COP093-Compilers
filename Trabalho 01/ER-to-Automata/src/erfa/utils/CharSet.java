package erfa.utils;

import java.util.Iterator;
import java.util.LinkedList;

public class CharSet implements Iterable<Character>{
	private LinkedList<Character> symbols;
	
	public CharSet(String string) {
		this.symbols = new LinkedList<>();
		StringIterator input = new StringIterator(string);
		input.next();
		char current = input.next();
		char next = input.next();
		while(current != ']') {
			if(next == '-') {
				char start = current;
				current = input.next();
				next = input.next();
				char end = current;
				for(char c = start; c <= end; c++) {
					symbols.add(c);
				}
			}
			else {
				symbols.add(current);
			}
			current = next;
			next = input.next();
		}
	}

	@Override
	public Iterator<Character> iterator() {
		return this.symbols.iterator();
	}
	@Override
	public String toString() {
		String string = new String();
		for(char c : symbols) {
			string += c + " ";
		}
		return string.trim();
	}
}
