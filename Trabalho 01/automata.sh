#!/bin/bash

CP="/home/lucas/Files/Git/5COP093-Compilers/Trabalho 01/ER-to-Automata/bin/"

java -cp "$CP" erfa.main.Main; dot -Tpdf -o pdf.pdf dot.dot