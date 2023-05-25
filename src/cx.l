%{
	#include <stdio.h>
	#include "cx.tab.h"

	int line = 1;
	int yywrap();
	void yyerror(char *);
	char msg[100];
	void comment();
%}

SPACE		 ([ \t\n])+
ID			 [A-Za-z][A-Za-z0-9]*
NUM			 ([1-9][0-9]*)|0
CHAR         '[A-Za-z]'

%%
[ \t]	    {;}
[\n]	    {line++;}

"true"		{return SYM_TRUE;}
"false"		{return SYM_FALSE;}

"int"		{return INT;}
"bool"		{return BOOL;}
"if"		{return IF;}
"else"		{return ELSE;}
"while"		{return WHILE;}
"write"		{return WRITE;}
"read"		{return READ;}

"+"         {return PLUS;}
"-"         {return MINUS;}
"*"         {return TIMES;}
"/"         {return SLASH;}
"<"         {return LES;}
"<="        {return LEQ;}
">"         {return GTR;}
">="        {return GEQ;}
"=="        {return EQL;}
"!="        {return NEQ;}
"="         {return BECOMES;}
"||"        {return OR;}
"&&"        {return AND;}
"!"         {return NOT;}
";"         {return SEMICOLON;}
"("         {return LPAREN;}
")"         {return RPAREN;}
"{"         {return LBRACE;}
"}"         {return RBRACE;}
"/*"        {comment();}

","			{return COMMA;}
":"			{return COLON;}

"repeat"	{return REPEAT;}
"until"		{return UNTIL;}

"%"			{return MOD;}
"^"			{return XOR;}
"odd"		{return ODD;}
"++"		{return SELFADD;}
"--"		{return SELFMINUS;}

"case"		{return CASE;}
"switch"	{return SWITCH;}
"default"	{return DEFAULT;}

"const"		{return CONST;}

"break"		{return BREAK;}
"exit"		{return EXIT;}
"continue"	{return CONTINUE;}

"for"		{return FOR;}
"do"		{return DO;}

"procedure" {return PROC;}
"call"		{return CALL;}


{ID}  	 	{
				yylval.ident = (char *)malloc(strlen(yytext) + 1);
				strcpy(yylval.ident, yytext);
				return IDENT;
			}

{NUM}   	{
				yylval.number = atoi(yytext);
				return NUMBER;
			}

{CHAR} 		{
				yylval.ident = (char *)malloc(strlen(yytext) + 1);
				strcpy(yylval.ident, yytext);
				return CHARACTER;
			}


.       	{
				sprintf(msg, "error: unexpected character %s.", yytext);
				yyerror(msg);
			}

%%

void redirectInput(FILE *input) {
	yyin = input;
}

int yywrap() {
    return 1;
}

void comment() {
    char ch, ch_out;
	while(1){
		while ((ch = input()) != '*' && ch != 0) 
			if (ch == '\n') {line++;}
		if ((ch_out = input()) != '/' && ch_out != 0) 
			unput(ch_out);
		else
			break;
	}
}