#!/bin/bash
flex tokenizer.l
bison parser.y -d
gcc lex.yy.c parser.tab.c -lfl -w
./a.out
