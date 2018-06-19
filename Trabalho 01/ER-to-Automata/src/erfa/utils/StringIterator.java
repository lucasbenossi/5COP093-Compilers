package erfa.utils;

public class StringIterator {
	String string;
	int pos, length;
	
	public StringIterator(String string) {
		this.string = string;
		this.pos = 0;
		this.length = string.length();
	}
	
	public char next() {
		char c = '\0';
		if(this.pos < this.length) {
			c = this.string.charAt(this.pos);
			this.pos++;
		}
		return c;
	}
}
