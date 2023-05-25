%{
	#include <stdio.h>
    #include <stdlib.h>

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
[ ]	        {fprintf(yyout, "&nbsp;");}
[\t]        {fprintf(yyout, "&nbsp;&nbsp;&nbsp;&nbsp;");}
[\n]	    {fprintf(yyout, "<br>");}

"true"		{fprintf(yyout,"<font color=\"#4169E1\">true</font>");}
"false"		{fprintf(yyout,"<font color=\"#4169E1\">false</font>");}

"int"		{fprintf(yyout,"<font color=\"#4169E1\">int</font>");}
"bool"		{fprintf(yyout,"<font color=\"#4169E1\">bool</font>");}
"if"		{fprintf(yyout,"<font color=\"#DA70D6\">if</font>");}
"else"		{fprintf(yyout,"<font color=\"#DA70D6\">else</font>");}
"while"		{fprintf(yyout,"<font color=\"#DA70D6\">while</font>");}
"write"		{fprintf(yyout,"<font color=\"#F0E68C\">write</font>");}
"read"		{fprintf(yyout,"<font color=\"#F0E68C\">read</font>");}

"+"         {fprintf(yyout,"+");}
"-"         {fprintf(yyout,"-");}
"*"         {fprintf(yyout,"*");}
"/"         {fprintf(yyout,"/");}
"<"         {fprintf(yyout,"&lt;");}
"<="        {fprintf(yyout,"&lt;=");}
">"         {fprintf(yyout,"&gt;");}
">="        {fprintf(yyout,"&gt;=");}
"=="        {fprintf(yyout,"==");}
"!="        {fprintf(yyout,"!=");}
"="         {fprintf(yyout,"=");}
"||"        {fprintf(yyout,"||");}
"&&"        {fprintf(yyout,"&&");}
"!"         {fprintf(yyout,"!");}
";"         {fprintf(yyout,";");}
"("         {fprintf(yyout,"<font color=\"#FFD700\">(</font>");}
")"         {fprintf(yyout,"<font color=\"#FFD700\">)</font>");}
"{"         {fprintf(yyout,"<font color=\"#FFD700\">{</font>");}
"}"         {fprintf(yyout,"<font color=\"#FFD700\">}</font>");}
"/*"        {fprintf(yyout,"<font color=\"#1FC227\">");comment();fprintf(yyout,"</font>");}

","			{fprintf(yyout,",");}
":"			{fprintf(yyout,":");}

"repeat"	{fprintf(yyout,"<font color=\"#DA70D6\">repeat</font>");}
"until"		{fprintf(yyout,"<font color=\"#DA70D6\">until</font>");}

"%"			{fprintf(yyout,"&#37;");}
"^"			{fprintf(yyout,"^");}
"odd"		{fprintf(yyout,"<font color=\"#F0E68C\">odd</font>");}
"++"		{fprintf(yyout,"++");}
"--"		{fprintf(yyout,"--");}

"case"		{fprintf(yyout,"<font color=\"#DA70D6\">case</font>");}
"switch"	{fprintf(yyout,"<font color=\"#DA70D6\">switch</font>");}
"default"	{fprintf(yyout,"<font color=\"#DA70D6\">default</font>");}

"const"		{fprintf(yyout,"<font color=\"#4169E1\">const</font>");}

"break"		{fprintf(yyout,"<font color=\"#DA70D6\">break</font>");}
"exit"		{fprintf(yyout,"<font color=\"#DA70D6\">exit</font>");}
"continue"	{fprintf(yyout,"<font color=\"#DA70D6\">continue</font>");}

"for"		{fprintf(yyout,"<font color=\"#DA70D6\">for</font>");}
"do"		{fprintf(yyout,"<font color=\"#DA70D6\">do</font>");}

"procedure" {fprintf(yyout,"<font color=\"#4169E1\">procedure</font>");}
"call"		{fprintf(yyout,"<font color=\"#DA70D6\">call</font>");}


{ID}  	 	{
				fprintf(yyout, "%s", yytext);
			}

{NUM}   	{
				fprintf(yyout, "<font color=\"#CCFF99\">%s</font>", yytext);
			}

{CHAR} 		{
				fprintf(yyout, "%s", yytext);
			}


.       	{
				fprintf(yyout, "%s", yytext);
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
	fprintf(yyout, "/*", ch);
	while(1){
		while ((ch = input()) != '*' && ch != 0) {
			fprintf(yyout, "%c", ch);
        }
		fprintf(yyout, "*", ch);
		if ((ch_out = input()) != '/' && ch_out != 0) 
			fprintf(yyout, "%c", ch);
		else{
			fprintf(yyout, "/", ch);
			break;
		}
	}
}

int main(int argc, char *argv[]){
    if ((yyin = fopen(argv[argc - 1], "r")) == NULL) {
        printf("Cann't open file according to given filename.\n");
		exit(0);
    }
    yyout = fopen("fhighlight.txt", "w");
    yylex();
    return 0;
}