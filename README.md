# CX_Compiler
A Compiler for CX language based on Lex &amp; Yacc, final project of Compilation principle (ECNU)

## Release
You can download Release version (with GUI) with this link: https://github.com/Nemotte/CX_Compiler/releases/tag/GUI_ver

## Introduction
This repo only contains lexer, parser and interpreter.

## Environment
You need to install:
```
Make, GCC
Windows: Flex & Bison
Linux: Lex & Yacc
```

## Usage
Modify these codes in `Makefile`:
```diff
- TARGET := ../CX_Compiler/CX_Compiler/cx
+ TARGET := cx

- $(TARGET) -c -t -s ./test/const.in
+ $(TARGET) [-c] [-t] [-s] [your_testfile_path]

- $(CC) ./highlight/lex.yy.c -o ../CX_Compiler/CX_Compiler/hl
+ $(CC) ./highlight/lex.yy.c -o hl
```

Then use `make prog` to get executable compiler file `cx.exe` (`cx` in Linux Sys).
Use `make run` to test ur file.
Or you can use `make` to do all above.

Use `make hl` to get executable syntax highlight file `hl.exe` (`hl` in Linux Sys) for GUI.