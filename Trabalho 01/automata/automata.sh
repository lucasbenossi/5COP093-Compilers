#!/bin/bash

CP="../ER-to-Automata/bin/"

java -cp "$CP" erfa.main.Main tokens.txt

dot -Tpdf -o pdf.pdf dot.dot