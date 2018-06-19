package erfa.main;

import java.io.File;
import java.io.IOException;
import java.io.PrintStream;
import java.util.Scanner;

import erfa.automata.DFA;
import erfa.automata.NFA;
import erfa.automata.RegexNFA;

public class Main {
	public static void main(String[] argv) {
		try {
			PrintStream dot = new PrintStream("/home/lucas/Desktop/dot.dot");
			
			NFA nfa = new NFA();
			
			Scanner scan = new Scanner(new File("/home/lucas/Files/Git/5COP093-Compilers/Trabalho 01/tokens.txt"));
			while(scan.hasNextLine()) {
				String line = scan.nextLine();
				String[] parts = line.split(" ");
				nfa.insertRNFA(RegexNFA.compile(parts[0], parts[1]));
			}
			scan.close();
			
//			RegexNFA rnfa = RegexNFA.compile("[abcdefghijklnopqrstuvwyz0123456789]*", "TOKEN");
//			nfa.insertRNFA(rnfa);
			
			DFA dfa = new DFA(nfa);
			
			dfa.toDot(dot);
			
			dot.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
