DIR_SRC := src
CC := gcc
l := lex
y := yacc
LEX_TEMP := lex.yy.c
YACC_TEMP := cx.tab.c
TARGET := ../CX_Compiler/CX_Compiler/cx

LEX_SOURCES := $(wildcard $(DIR_SRC)/*.l)
YACC_SOURCES := $(wildcard $(DIR_SRC)/*.y)

all: prog run

prog:
	$(y) -dv $(YACC_SOURCES)
	$(l) $(LEX_SOURCES)
	$(CC) $(LEX_TEMP) $(YACC_TEMP) -o $(TARGET)

run:
	$(TARGET) -c -t -s ./test/const.in

hl:
	$(l) -o ./highlight/lex.yy.c ./highlight/highlight.l
	$(CC) ./highlight/lex.yy.c -o ../CX_Compiler/CX_Compiler/hl