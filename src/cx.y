%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <malloc.h>
    #include <memory.h>
    #include <string.h>
    #include <stdbool.h>

    #define txmax 100       // 符号表容量
    #define al 10           // 标识符最大长度
    #define amax 2048       // 地址上界
    #define levmax 3        // 最大允许过程嵌套声明层数
    #define cxmax 200       // 最多的虚拟机代码数
    #define stacksize 500   // 运行时数据栈元素最多为500个

    // 符号表中的类型
    enum object{
        constant,
        variable,
        procedure,
    };

    // 变量类型
    enum vartype {
        inttype,
        booltype,
        chartype
    };

    // 符号表结构
    struct tablestruct{
        char name[al];      // 名字
        enum object kind;   // 类型
        enum vartype type;  // 变量类型
        int val;            // 数值
        int level;          // 所处层
        int adr;            // 地址
        int size;           // 需要分配的数据空间
    };
    struct tablestruct table[txmax];

    // 虚拟机代码指令
    enum fct{
        lit, opr, lod, sto, cal, pint, jmp, jpc, jpe, ext, blo, fre,
    };

    // 虚拟机代码结构
    struct instruction{
        enum fct f;         // 虚拟机代码指令
        int l;              // 引用层与声明层的层次差
        int a;              // 根据f的不同而不同
    };
    struct instruction code[cxmax];

    int tx;
    int cx;
    int px;
    int lev;
    int proctable[3];
    char id[al];
    int leveltable[5];
    int num;
    bool listswitch;
    bool tableswitch;
    bool stackswitch;
    bool interpretswitch;
    int p;
    int b;
    int t;

    FILE* fin;
    FILE* ftable;
    FILE* fcode;
    FILE* foutput;
    FILE* fresult;
    FILE* fstack;
    char fname[al];
    int err;
    int switchaddr;
    extern int line;

    char varType[10];

    void init();
    void enter(enum vartype t, enum object k);
    int position(char* s);
    void setdx(int n);
    void gen(enum fct x, int y, int z);
    void listall();
    void displaytable();
    void interpret();
    int base(int l, int *s, int b);
    
    int yylex();
    int yyerror(const char *s);
    void redirectInput(FILE *fin);

    int hasProc;

    #define YYERROR_VERBOSE 1
%}


%union {
    char *ident;
    int number;
}


%token INT BOOL IF ELSE WHILE WRITE READ CALL PROC
%token PLUS MINUS TIMES SLASH LES LEQ GTR GEQ EQL NEQ BECOMES COMMA
%token OR AND NOT SEMICOLON LPAREN RPAREN LBRACE RBRACE SYM_TRUE SYM_FALSE
%token REPEAT UNTIL XOR CASE SWITCH DEFAULT BREAK COLON CONST
%token EXIT CONTINUE FOR DO MOD ODD SELFADD SELFMINUS
%token <ident> IDENT
%token <number> NUMBER
%token <ident> CHARACTER

%type <number> ident forbexpr abasic aselfaddorminus
%type <number> decls decl varlist vardef
%type <number> elsestm get_cx get_table_addr casestms casestm defaultstm
%type <number> aterm afactor aexpr idornum trueorfalse

%nonassoc IFX
%nonassoc ELSE

%%

program:
    block
    ;

block:
    LBRACE{
        $<number>$ = cx;
        gen(jmp, 0, 1);
    }
    decls{
        setdx($3);
        code[$<number>2].a = cx;
        gen(pint, 0, $3 + 3);
    }
    procdecls
    stmts
    RBRACE{
        gen(opr, 0, 0);
    }
	;

decls:
    decls decl 
    {
        $$ = $1 + $2;
    }
    |
    {
        $$ = 0;
    }
    ;

decl: 
    type varlist SEMICOLON
    {
        $$ = $2;
    }
    | type varlist  
    {
        $$ = $2;         
        yyerror("Miss SEMICOLON");  //错误处理，变量声明缺少结尾分号
    }
    | CONST type IDENT BECOMES NUMBER SEMICOLON{
        strcpy(id, $3);
        if (!strcmp(varType, "int")) 
            enter(inttype, constant); 
        else if(!strcmp(varType, "bool"))
            enter(booltype, constant);
        else if(!strcmp(varType, "char"))
            enter(chartype, constant);

        int tmp = position($3);
        
        if (table[tmp].type == inttype)
            table[tmp].val = $5;
        else{
            char *str1 = "Symbol \"";
            char *str2 = "\" type should be int";
            char *str = (char *) malloc(strlen(str1) + strlen(str2) + strlen(table[tmp].name));
            strcpy(str, str1); 
            strcat(str, table[tmp].name);
            strcat(str, str2);
            yyerror(str);
        }
    }
    | CONST type IDENT BECOMES trueorfalse SEMICOLON{
        strcpy(id, $3);
        if (!strcmp(varType, "int")) 
            enter(inttype, constant); 
        else if(!strcmp(varType, "bool"))
            enter(booltype, constant);
        else if(!strcmp(varType, "char"))
            enter(chartype, constant);
        
        int tmp = position($3);

        if (table[tmp].type == booltype)
            table[tmp].val = $5;
        else{
            char *str1 = "Symbol \"";
            char *str2 = "\" type should be bool";
            char *str = (char *) malloc(strlen(str1) + strlen(str2) + strlen(table[tmp].name));
            strcpy(str, str1); 
            strcat(str, table[tmp].name);
            strcat(str, str2);
            yyerror(str);
        }
    }
    | error SEMICOLON
    ;

type:
    INT
    {
        strcpy(varType, "int");
    }
    | BOOL
    {
        strcpy(varType, "bool");
    }
    ;

varlist: 
    vardef 
    {
        $$ = $1;
    }
    | varlist COMMA vardef 
    {
        $$ = $1 + $3;
    }
    | error {/*错误处理*/} SEMICOLON
    ;

vardef: 
    IDENT 
    {
        strcpy(id, $1);
        if (!strcmp(varType, "int")) 
            enter(inttype, variable); 
        else if(!strcmp(varType, "bool"))
            enter(booltype, variable);
        else if(!strcmp(varType, "char"))
            enter(chartype, variable);
        $$ = 1;
    }
    | error SEMICOLON
    ;


procdecls:
    |
    procdecls procdecl
    ;

procdecl:
    PROC IDENT LPAREN RPAREN get_cx
    {
        hasProc = 1;
        gen(jmp, 0, 0);
        strcpy(id, $2);
        enter(-1, procedure);
    }
    procbody get_cx{
        code[$5].a = $8;
    }
    ;

procbody:
    LBRACE
    inc_level
    {
        leveltable[lev] = tx;
    }
    get_table_addr
    decls
    {
        setdx($5);
        table[$4].adr = cx;
        table[$4].size = $5 + 3;
        gen(pint, 0, $5 + 3);
        if(hasProc)
            displaytable();
    }
    stmts
    {
        gen(opr, 0, 0);
    }
    RBRACE
    {
        tx = leveltable[lev];
    }
    dec_level
    ;


stmts:
    stmts stm
    |
    ;

stm:
    ident BECOMES aexpr SEMICOLON
    {
        if ($1 == 0)
            yyerror("Symbol does not exist");
        else if (table[$1].kind == variable && table[$1].type == inttype)
            gen(sto, lev - table[$1].level, table[$1].adr);
        else{
            char *str1 = "Symbol \"";
            char *str2 = "\" should be a variable and type should be int";
            char *str = (char *) malloc(strlen(str1) + strlen(str2) + strlen(table[$1].name));
            strcpy(str, str1); 
            strcat(str, table[$1].name);
            strcat(str, str2);
            yyerror(str);
        }
    }
    | ident BECOMES trueorfalse SEMICOLON
    {
        if ($1 == 0)
            yyerror("Symbol does not exist");
        else if (table[$1].kind == variable && table[$1].type == booltype) 
            gen(sto, lev - table[$1].level, table[$1].adr);
        else{
            char *str1 = "Symbol \"";
            char *str2 = "\" should be a variable and type should be bool";
            char *str = (char *) malloc(strlen(str1) + strlen(str2) + strlen(table[$1].name));
            strcpy(str, str1); 
            strcat(str, table[$1].name);
            strcat(str, str2);
            yyerror(str);
        }
    }
    | READ ident 
    {
        if (table[$2].kind == variable && table[$2].type == inttype) {
            gen(opr, 0, 16);
            gen(sto, lev - table[$2].level, table[$2].adr);
        }
        else {
            yyerror("Can only read int variable");
        }
    } SEMICOLON
    | WRITE aexpr{
        gen(opr, 0, 14);
        gen(opr, 0, 15);
    } SEMICOLON
    | IF LPAREN bexpr RPAREN get_cx{
        gen(jpc, 0, 0);
    } stm elsestm{
        code[$5].a = $8;
    }
    | WHILE get_cx LPAREN bexpr RPAREN get_cx{
        gen(jpc, 0, 0);
    } stm {
        gen(jmp, 0, $2);
        code[$6].a = cx;
    }
    | REPEAT get_cx stm UNTIL LPAREN bexpr RPAREN get_cx SEMICOLON{
        gen(jpc, 0, $2);
    }
    | DO get_cx stm get_cx WHILE LPAREN bexpr get_cx{
        gen(jpe, 0, $2);
    } RPAREN SEMICOLON
    | switchstm
    | FOR LPAREN fordecl get_cx forbexpr{
        if ($5 == 1)
            gen(lit, 0, 1);
    } SEMICOLON get_cx{
        gen(jpe, 0, 0);
        gen(jmp, 0, 0);
    } get_cx forstm RPAREN{
        gen(jmp, 0, $4);
    } get_cx stm{
        gen(jmp, 0, $10);
        code[$8].a = $14;
        code[$8 + 1].a = cx;
    }
    | EXIT NUMBER SEMICOLON{
        gen(ext, 0, 0);
    }
    | aselfaddorminus SEMICOLON
    | blockstm
    | callstm
    | error {/*错误处理*/} SEMICOLON 
    ;

callstm:
    CALL ident SEMICOLON
    {
        if ($2 == 0)
            yyerror("Call symbol does not exist");
        else if (table[$2].kind != procedure)
            yyerror("Call symbol should be a procedure");
        else
            gen(cal, lev - table[$2].level, table[$2].adr);    
    }
    ;

blockstm:
    LBRACE
    inc_level
    {
        proctable[lev] = tx;
        gen(blo, 0, 0);
    }
    decls
    {
        setdx($4);
        gen(pint, 0, $4 + 3);
    }
    stmts
    {
        gen(fre, 0, 0);
    }
    RBRACE
    {
        tx = proctable[lev];
    }
    dec_level;
    ;

fordecl:
    | 
    ident BECOMES aexpr SEMICOLON{
        if ($1 == 0)
            yyerror("Symbol does not exist");
        else if (table[$1].kind == variable && table[$1].type == inttype)
            gen(sto, lev - table[$1].level, table[$1].adr);
        else{
            char *str1 = "Symbol \"";
            char *str2 = "\" should be a variable and type should be int";
            char *str = (char *) malloc(strlen(str1) + strlen(str2) + strlen(table[$1].name));
            strcpy(str, str1); 
            strcat(str, table[$1].name);
            strcat(str, str2);
            yyerror(str);
        }
    }
    | ident BECOMES bexpr SEMICOLON{
        if ($1 == 0)
            yyerror("Symbol does not exist");
        else if (table[$1].kind == variable && table[$1].type == booltype) 
            gen(sto, lev - table[$1].level, table[$1].adr);
        else{
            char *str1 = "Symbol \"";
            char *str2 = "\" should be a variable and type should be bool";
            char *str = (char *) malloc(strlen(str1) + strlen(str2) + strlen(table[$1].name));
            strcpy(str, str1); 
            strcat(str, table[$1].name);
            strcat(str, str2);
            yyerror(str);
        }
    }
    ;

forstm:
    |
    aexpr
    ;

forbexpr:
    {
        $$ = 1; 
    }
    |
    bexpr{
        $$ = 0; 
    }
    ;

elsestm:
    %prec IFX
    {
        $$ = cx;
    }
    | ELSE get_cx{
        gen(jmp, 0, 0); //满足if条件的直接jmp走
    }
    stm{
        $$ = $2 + 1; //jmp的后一条指令位置
        code[$2].a = cx; //回填，满足if条件的跳到哪里
    }
    ;

switchstm:
    SWITCH get_cx{
        gen(jpc, 0, 0);
        switchaddr = $2;
    } LPAREN aexpr RPAREN LBRACE casestms defaultstm RBRACE{
        code[$2].a = cx;
    }
    ;

casestms:
    |
    casestms casestm
    ;

casestm:
    CASE aexpr get_cx{
        gen(jmp, 0, 0);
    } COLON stm{
        gen(lit, 0, 0);
        gen(jmp, 0, switchaddr);
        code[$3].a = cx;
        gen(opr, 0, 24);
        gen(jpc, 0, $3+1);
    }
    ;

defaultstm:
    DEFAULT COLON get_cx stm{
        $$ = $3;
        // code[$3].a = cx;
        gen(jpc, 0, $3);
    }
    ;

/* 布尔表达式 */
bexpr:
    bexpr OR bterm {
        gen(opr, 0, 22);
    }
    | bterm
    ;

bterm:
    bterm AND bfactor {
        gen(opr, 0, 21);
    }
    | bfactor
    ;

bfactor:
    ident 
    { 
        if ($1 == 0)
            yyerror("Symbol does not exist");
        else if (table[$1].kind == variable)
            gen(lod, lev - table[$1].level, table[$1].adr);
        else if (table[$1].kind == constant)
            gen(lit, 0, table[$1].val);
    }   
    | trueorfalse
    | NOT bfactor {
        gen(opr, 0, 20);
    }
    | LPAREN bexpr RPAREN 
    | ODD LPAREN idornum RPAREN{
        gen(opr, 0, 6);
    }
    | rel
    ;

rel:
    idornum EQL aexpr {
        gen(opr, 0, 8);
    }
    | idornum NEQ aexpr {
        gen(opr, 0, 9);
    }
    | idornum LES aexpr {
        gen(opr, 0, 10);
    }
    | idornum LEQ aexpr {
        gen(opr, 0, 13);
    }
    | idornum GTR aexpr {
        gen(opr, 0, 12);
    }
    | idornum GEQ aexpr {
        gen(opr, 0, 11);
    }
    ;

idornum:
    ident
    { 
        if ($1 == 0)
            yyerror("Symbol does not exist");
        else if (table[$1].kind == procedure)
            yyerror("Symbol should not be a procedure");
        else if (table[$1].kind == constant) {
            $$ = 0;
            gen(lit, 0, table[$1].val);
        }
        else if (table[$1].kind == variable && table[$1].type == inttype) {
            $$ = 0; 
            gen(lod, lev - table[$1].level, table[$1].adr);
        }
        else if (table[$1].kind == variable && table[$1].type == booltype) {
            $$ = 0; 
            gen(lod, lev - table[$1].level, table[$1].adr);
        }
    }   
    | NUMBER 
    {
        $$ = 0;
        gen(lit, 0, $1);
    }
    ;

trueorfalse:
    SYM_TRUE{
        gen(lit, 0, 1);
        $$ = 1;
    }
    |
    SYM_FALSE{
        gen(lit, 0, 0);
        $$ = 0;
    }
    ;


/* 算术表达式 */
aexpr: 
    PLUS aterm {
        $$ = 0;
    }
    | MINUS aterm {
        $$ = 0;
        gen(opr, 0, 1);
    }
    | aterm {
        $$ = $1;
    }
    | aexpr PLUS aterm{
        $$ = 0;
        gen(opr, 0, 2);
    }
    | aexpr MINUS aterm{
        $$ = 0;
        gen(opr, 0, 3);
    }
    ;

/* 项 */
aterm: 
    afactor{
        $$ = $1;
    }
    | aterm TIMES afactor{
        $$ = 0;
        gen(opr, 0, 4);
    }
    | aterm SLASH afactor{
        $$ = 0;
        gen(opr, 0, 5);
    }  
    | aterm MOD afactor{
        $$ = 0;
        gen(opr, 0, 18);
    }
    ;

/* 因子 */
afactor: 
    abasic{
        $$ = $1;
    }
    | afactor XOR abasic{
        $$ = 0;
        gen(opr, 0, 19);
    }
    ;

abasic:
    idornum{
        $$ = $1;
    }
    | LPAREN aexpr RPAREN{
        $$ = 0;
    }
    | aselfaddorminus{
        $$ = $1;
    }
    ;

aselfaddorminus:
    ident SELFADD{ 
        if ($1 == 0)
            yyerror("Symbol does not exist");
        else if (table[$1].kind == constant) 
            yyerror("Constant cannot selfadd");
        else if (table[$1].kind == variable && table[$1].type != inttype) 
            yyerror("Only int variable can selfadd");
        else if (table[$1].kind == variable && table[$1].type == inttype) {
            gen(lod, lev - table[$1].level, table[$1].adr);
            gen(lit, 0, 1);
            gen(opr, 0, 2);
            gen(sto, lev - table[$1].level, table[$1].adr);
        }
        $$ = $1;
    }
    | ident SELFMINUS{ 
        if ($1 == 0)
            yyerror("Symbol does not exist");
        else if (table[$1].kind == constant) 
            yyerror("Constant cannot selfadd");
        else if (table[$1].kind == variable && table[$1].type != inttype) 
            yyerror("Only int variable can selfadd");
        else if (table[$1].kind == variable && table[$1].type == inttype) {
            gen(lod, lev - table[$1].level, table[$1].adr);
            gen(lit, 0, 1);
            gen(opr, 0, 3);
            gen(sto, lev - table[$1].level, table[$1].adr);
        }
        $$ = $1;
    }
    ;

ident: 
    IDENT 
    {
        $$ = position($1); 
    }
    ;

get_cx:
    {
        $$ = cx;
    }
    ;

get_table_addr:
    {
        $$ = tx;
    } 
    ;

inc_level:
    {
        lev++;               
        if (lev > levmax)   /* 嵌套层数过多 */
            yyerror("Lev is too big");    
    }
    ;

dec_level:
    {
        lev--;
    }
    ;
    
%%

int yyerror(char const *str){
    err = err + 1;
	extern char *yytext;
	fprintf(stdout, "parser error near line %d \"%s\", %s.\n", line, yytext, str);
    fprintf(foutput, "parser error near line %d \"%s\", %s.\n", line, yytext, str);
	return 0;
}

void init(){
    tx = 0;
    cx = 0;
    lev = 0;   
    proctable[0] = 0;
    num = 0;
    err = 0;
    hasProc = 0;
}

void enter(enum vartype t, enum object k){
    tx = tx + 1;
    strcpy(table[tx].name, id);
    table[tx].kind = k;
    table[tx].type = t;
    table[tx].level = lev;
}

int position(char *s){
    int i;
    strcpy(table[0].name, s);
    i = tx;
    while(strcmp(table[i].name, s) != 0)
        i--;
    return i;
}

/* 为本层变量分配相对地址，从3开始分配 */
void setdx(int n) {
    int i;
    for (i = 1; i <= n; i++) {
        table[tx - i + 1].adr = n - i + 3;
    }
}

/* 生成虚拟机代码 */
void gen(enum fct x, int y, int z) {
    if (cx >= cxmax) {
        printf("Program is too long!\n"); /* 生成的虚拟机代码程序过长 */
        exit(1);
    }
    if (z >= amax) {
        printf("Displacement address is too big!\n"); /* 地址偏移越界 */
        exit(1);
    }
    code[cx].f = x;
    code[cx].l = y;
    code[cx].a = z;
    cx++;
}

/* 输出所有目标代码  */
void listall() {
    int i;
    char name[][5] = {
        {"lit"}, {"opr"}, {"lod"}, {"sto"}, {"cal"}, {"pint"}, 
        {"jmp"}, {"jpc"}, {"jpe"}, {"ext"}, {"blo"}, {"fre"}
    };
    if (listswitch) {
        for (i = 0; i < cx; i++) {
            printf("%d %s %d %d\n", i, name[code[i].f], code[i].l, code[i].a);
            fprintf(fcode,"%d %s %d %d\n", i, name[code[i].f], code[i].l, code[i].a);
        }
        printf("\n");
    }
}

/* 输出符号表 */
void displaytable() {
    int i;
    if (tableswitch) {
        for (i = 1; i <= tx; i++) {
            switch (table[i].kind)
            {
            case constant:
                printf("    %d const %s ", i, table[i].name);
                printf("val=%d type=%d \n", table[i].val, table[i].type);
                fprintf(ftable, "    %d const %s ", i, table[i].name);
                fprintf(ftable, "val=%d type=%d \n", table[i].val, table[i].type);
                break;
            case variable:
                printf("    %d var   %s ", i, table[i].name);
                printf("lev=%d addr=%d type=%d \n", table[i].level, table[i].adr,  table[i].type);
                fprintf(ftable, "    %d var   %s ", i, table[i].name);
                fprintf(ftable, "lev=%d addr=%d type=%d \n", table[i].level, table[i].adr, table[i].type);
                break;
            case procedure:
                printf("    %d proc  %s ", i, table[i].name);
                printf("lev=%d addr=%d size=%d\n", table[i].level, table[i].adr, table[i].size);
                fprintf(ftable,"    %d proc  %s ", i, table[i].name);
                fprintf(ftable,"lev=%d addr=%d size=%d\n", table[i].level, table[i].adr, table[i].size);
                break;
            }
        }
        printf("\n");
        fprintf(ftable, "\n");
    }
}

void printstack(FILE* f, int t, int p, int *s) {
    int i;
    if (stackswitch) {
        fprintf(f, "pcode %2d: |", p);
        for (i = 1; i <= t; i++)
            fprintf(f, " %2d |", s[i]);
        fprintf(f, "%s", "\n");
    }
}

/* 解释程序 */
void interpret() {
	int p = 0; /* 指令指针 */
    int b = 1; /* 指令基址 */
    int t = 0; /* 栈顶指针 */
    struct instruction i; /* 存放当前指令 */
    int s[stacksize]; /* 栈 */

	printf("Start CX interpret\n");
 	fprintf(fresult,"Start CX interpret\n");
	s[0] = 0;
	s[1] = 0;
	s[2] = 0;
	s[3] = 0;
	do {
		i = code[p];  /* 读当前指令 */
        p = p + 1;
        switch (i.f)
        {
        case lit: /* 将常量a的值取到栈顶 */
            t = t + 1;
            s[t] = i.a;
            printstack(fstack, t, p, s);
            break;
        case opr: /* 数学、逻辑运算 */
            switch(i.a) {
            case 0:  /* 函数调用结束后返回 */
                t = b - 1;
                p = s[t + 3];
                b = s[t + 2];
                break;
            case 1: /* 栈顶元素取反 */
                s[t] = -s[t];
                break;
            case 2: /* 次栈顶项加上栈顶项，退两个栈元素，相加值进栈 */
                t = t - 1;
                s[t] = s[t] + s[t + 1];
                break;
            case 3:/* 次栈顶项减去栈顶项 */
                t = t - 1;
                s[t] = s[t] - s[t + 1];
                break;
            case 4:/* 次栈顶项乘以栈顶项 */
                t = t - 1;
                s[t] = s[t] * s[t + 1];
                break;
            case 5:/* 次栈顶项除以栈顶项 */
                t = t - 1;
                s[t] = s[t] / s[t + 1];
                break;
            case 6:/* 栈顶元素的奇偶判断 */
                s[t] = s[t] % 2;
                break;
            case 8:/* 次栈顶项与栈顶项是否相等 */
                t = t - 1;
                s[t] = (s[t] == s[t + 1]);
                break;
            case 9:/* 次栈顶项与栈顶项是否不等 */
                t = t - 1;
                s[t] = (s[t] != s[t + 1]);
                break;
            case 10:/* 次栈顶项是否小于栈顶项 */
                t = t - 1;
                s[t] = (s[t] < s[t + 1]);
                break;
            case 11:/* 次栈顶项是否大于等于栈顶项 */
                t = t - 1;
                s[t] = (s[t] >= s[t + 1]);
                break;
            case 12:/* 次栈顶项是否大于栈顶项 */
                t = t - 1;
                s[t] = (s[t] > s[t + 1]);
                break;
            case 13: /* 次栈顶项是否小于等于栈顶项 */
                t = t - 1;
                s[t] = (s[t] <= s[t + 1]);
                break;
            case 14:/* 栈顶值输出 */
                printf("%d", s[t]);
                fprintf(fresult, "%d", s[t]);
                t = t - 1;
                break;
            case 15:/* 输出换行符 */
                printf("\n");
                fprintf(fresult,"\n");
                break;
            case 16:/* 读入一个数置于栈顶 */
                t = t + 1;
                printf("input a number: ");
                fprintf(fresult, "input a number: ");
                scanf("%d", &(s[t]));
                getchar();
                fprintf(fresult, "%d\n", s[t]);           
                break;
            case 17:/* 读入一个字符置于栈顶 */
            {
                char ch;
                t = t + 1;
                printf("input a character: ");
                fprintf(fresult, "input a character: ");
                scanf("%c", &ch);
                getchar();
                s[t] = ch;
                fprintf(fresult, "%c\n", s[t]);           
                break;
            }
            case 18:/* 次栈顶项求余栈顶项 */ 
                t = t - 1;
                s[t] = s[t] % s[t + 1];
                break;
            case 19:/* 次栈顶项异或栈顶项 */
                t = t - 1;
                s[t] = s[t] ^ s[t + 1];
                break;
            case 20:/* 栈顶的值取not */
                s[t] = !s[t];
                break;
            case 21:/* 次栈顶项and栈顶项 */
                t = t - 1;
                s[t] = s[t] && s[t + 1];
                break;
            case 22:/* 次栈顶项or栈顶项 */
                t = t - 1;
                s[t] = s[t] || s[t + 1];
                break;
            case 23:/* 栈顶字符输出 */
                printf("%c", s[t]);
                fprintf(fresult, "%c", s[t]);
                t = t - 1;
                break;
            case 24:/* switch用 次栈顶项与栈顶项是否不等 */
                s[t] = (s[t] != s[t - 1]);
                break;
            }
            printstack(fstack, t, p, s);
            break;	
        case lod: /* 取相对当前过程的数据基地址为a的内存的值到栈顶 */
            t = t + 1;
            s[t] = s[base(i.l, s, b) + i.a];
            printstack(fstack, t, p, s);            
            break;
        case sto: /* 栈顶的值存到相对当前过程的数据基地址为a的内存 */
            s[base(i.l, s, b) + i.a] = s[t];
            t = t - 1;
            printstack(fstack, t, p, s);
            break;
        case cal: /* 调用子过程 */
            s[t + 1] = base(i.l, s, b); /* 将父过程基地址入栈，即建立静态链 */
            s[t + 2] = b; /* 将本过程基地址入栈，即建立动态链 */
            s[t + 3] = p; /* 将当前指令指针入栈，即保存返回地址 */
            b = t + 1;  /* 改变基地址指针值为新过程的基地址 */
            p = i.a;  /* 跳转 */
            printstack(fstack, t, p, s);
            break;
        case pint: /* 在数据栈中为被调用的过程开辟a个单元的数据区 */
            t = t + i.a;
            printstack(fstack, t, p, s);
            break;
        case jmp: /* 直接跳转 */
            p = i.a;
            printstack(fstack, t, p, s);
            break;
        case jpc: /* 如果栈顶等于0条件跳转 */
            if (s[t] == 0)
                p = i.a;
            t = t - 1;
            printstack(fstack, t, p, s);
            break;
        case jpe: /* 如果栈顶等于1条件跳转 */
            if (s[t]) 
                p = i.a;
            t = t - 1;
            printstack(fstack, t, p, s);
            break;
        case ext:
            p = 0;
            printstack(fstack, t, p, s);
            break;
        case blo: //不改变p
            s[t + 1] = base(i.l, s, b);
            s[t + 2] = b;
            b = t + 1;
            printstack(fstack, t, p, s);
            break;
        case fre: //不改变p
            t = b - 1;
            b = s[t + 2];
            printstack(fstack, t, p, s);
            break;
        }
    } while (p != 0);
    printf("End CX interpret\n");
    fprintf(fresult, "End CX interpret\n");
}

/* 解释程序 */
void interpret_once(int q) {
    struct instruction i; /* 存放当前指令 */
    int s[stacksize]; /* 栈 */

    FILE* fqresult;
    FILE* fqstack;

    FILE* fqcode;

    char tmp[3];
    itoa(q, tmp, 10);
    

    char* qresult1 = "./interpret/fqresult_";
    char* q2 = ".txt";
    
    char *qs = (char *) malloc(strlen(qresult1) + strlen(tmp) + strlen(q2));

    strcpy(qs, qresult1);
    strcat(qs, tmp);
    strcat(qs, q2);

    char* qstack1 = "./interpret/fqstack_";
    char *qstack = (char *) malloc(strlen(qstack1) + strlen(tmp) + strlen(q2));

    strcpy(qstack, qstack1);
    strcat(qstack, tmp);
    strcat(qstack, q2);

    char* qcode1 = "./interpret/fqcode_";
    char *qcode = (char *) malloc(strlen(qcode1) + strlen(tmp) + strlen(q2)+1);

    strcpy(qcode, qcode1);
    strcat(qcode, tmp);
    strcat(qcode, q2);


    if ((fqresult = fopen(qs, "w")) == NULL) {
        printf("Can't open qresult once file!\n");
        exit(1);
    }

    if ((fqstack = fopen(qstack, "w")) == NULL) {
        printf("Can't open qstack once file!\n");
        exit(1);
    }

    if ((fqcode = fopen(qcode, "w")) == NULL) {
        printf("Can't open qcode once file!\n");
        exit(1);
    }

	s[0] = 0;
	s[1] = 0;
	s[2] = 0;
	s[3] = 0;
		i = code[p];  /* 读当前指令 */
        char name[][5] = {
            {"lit"}, {"opr"}, {"lod"}, {"sto"}, {"cal"}, {"pint"}, 
            {"jmp"}, {"jpc"}, {"jpe"}, {"ext"}, {"blo"}, {"fre"}
        };
        fprintf(fqcode,"%d %s %d %d\n", q+1, name[i.f], i.l, i.a);
        fclose(fqcode);
        p = p + 1;
        switch (i.f)
        {
        case lit: /* 将常量a的值取到栈顶 */
            t = t + 1;
            s[t] = i.a;
            printstack(fqstack, t, p, s);
            break;
        case opr: /* 数学、逻辑运算 */
            switch(i.a) {
            case 0:  /* 函数调用结束后返回 */
                t = b - 1;
                p = s[t + 3];
                b = s[t + 2];
                break;
            case 1: /* 栈顶元素取反 */
                s[t] = -s[t];
                break;
            case 2: /* 次栈顶项加上栈顶项，退两个栈元素，相加值进栈 */
                t = t - 1;
                s[t] = s[t] + s[t + 1];
                break;
            case 3:/* 次栈顶项减去栈顶项 */
                t = t - 1;
                s[t] = s[t] - s[t + 1];
                break;
            case 4:/* 次栈顶项乘以栈顶项 */
                t = t - 1;
                s[t] = s[t] * s[t + 1];
                break;
            case 5:/* 次栈顶项除以栈顶项 */
                t = t - 1;
                s[t] = s[t] / s[t + 1];
                break;
            case 6:/* 栈顶元素的奇偶判断 */
                s[t] = s[t] % 2;
                break;
            case 8:/* 次栈顶项与栈顶项是否相等 */
                t = t - 1;
                s[t] = (s[t] == s[t + 1]);
                break;
            case 9:/* 次栈顶项与栈顶项是否不等 */
                t = t - 1;
                s[t] = (s[t] != s[t + 1]);
                break;
            case 10:/* 次栈顶项是否小于栈顶项 */
                t = t - 1;
                s[t] = (s[t] < s[t + 1]);
                break;
            case 11:/* 次栈顶项是否大于等于栈顶项 */
                t = t - 1;
                s[t] = (s[t] >= s[t + 1]);
                break;
            case 12:/* 次栈顶项是否大于栈顶项 */
                t = t - 1;
                s[t] = (s[t] > s[t + 1]);
                break;
            case 13: /* 次栈顶项是否小于等于栈顶项 */
                t = t - 1;
                s[t] = (s[t] <= s[t + 1]);
                break;
            case 14:/* 栈顶值输出 */
                printf("%d", s[t]);
                fprintf(fqresult, "%d", s[t]);
                t = t - 1;
                break;
            case 15:/* 输出换行符 */
                printf("\n");
                fprintf(fqresult,"\n");
                break;
            case 16:/* 读入一个数置于栈顶 */
                t = t + 1;
                printf("input a number: ");
                fprintf(fqresult, "input a number: ");
                scanf("%d", &(s[t]));
                getchar();
                fprintf(fqresult, "%d\n", s[t]);           
                break;
            case 17:/* 读入一个字符置于栈顶 */
            {
                char ch;
                t = t + 1;
                printf("input a character: ");
                fprintf(fqresult, "input a character: ");
                scanf("%c", &ch);
                getchar();
                s[t] = ch;
                fprintf(fqresult, "%c\n", s[t]);           
                break;
            }
            case 18:/* 次栈顶项求余栈顶项 */ 
                t = t - 1;
                s[t] = s[t] % s[t + 1];
                break;
            case 19:/* 次栈顶项异或栈顶项 */
                t = t - 1;
                s[t] = s[t] ^ s[t + 1];
                break;
            case 20:/* 栈顶的值取not */
                s[t] = !s[t];
                break;
            case 21:/* 次栈顶项and栈顶项 */
                t = t - 1;
                s[t] = s[t] && s[t + 1];
                break;
            case 22:/* 次栈顶项or栈顶项 */
                t = t - 1;
                s[t] = s[t] || s[t + 1];
                break;
            case 23:/* 栈顶字符输出 */
                printf("%c", s[t]);
                fprintf(fqresult, "%c", s[t]);
                t = t - 1;
                break;
            case 24:/* switch用 次栈顶项与栈顶项是否不等 */
                s[t] = (s[t] != s[t - 1]);
                break;
            }
            printstack(fqstack, t, p, s);
            break;	
        case lod: /* 取相对当前过程的数据基地址为a的内存的值到栈顶 */
            t = t + 1;
            s[t] = s[base(i.l, s, b) + i.a];
            printstack(fqstack, t, p, s);            
            break;
        case sto: /* 栈顶的值存到相对当前过程的数据基地址为a的内存 */
            s[base(i.l, s, b) + i.a] = s[t];
            t = t - 1;
            printstack(fqstack, t, p, s);
            break;
        case cal: /* 调用子过程 */
            s[t + 1] = base(i.l, s, b); /* 将父过程基地址入栈，即建立静态链 */
            s[t + 2] = b; /* 将本过程基地址入栈，即建立动态链 */
            s[t + 3] = p; /* 将当前指令指针入栈，即保存返回地址 */
            b = t + 1;  /* 改变基地址指针值为新过程的基地址 */
            p = i.a;  /* 跳转 */
            printstack(fqstack, t, p, s);
            break;
        case pint: /* 在数据栈中为被调用的过程开辟a个单元的数据区 */
            t = t + i.a;
            printstack(fqstack, t, p, s);
            break;
        case jmp: /* 直接跳转 */
            p = i.a;
            printstack(fqstack, t, p, s);
            break;
        case jpc: /* 如果栈顶等于0条件跳转 */
            if (s[t] == 0)
                p = i.a;
            t = t - 1;
            printstack(fqstack, t, p, s);
            break;
        case jpe: /* 如果栈顶等于1条件跳转 */
            if (s[t]) 
                p = i.a;
            t = t - 1;
            printstack(fqstack, t, p, s);
            break;
        case ext:
            p = 0;
            printstack(fqstack, t, p, s);
            break;
        case blo: //不改变p
            s[t + 1] = base(i.l, s, b);
            s[t + 2] = b;
            b = t + 1;
            printstack(fqstack, t, p, s);
            break;
        case fre: //不改变p
            t = b - 1;
            b = s[t + 2];
            printstack(fqstack, t, p, s);
            break;
        }
    fclose(fqresult);
    fclose(fqstack);
}


/* 通过过程基址求上ｌ层过程的基址 */
int base(int l, int s[], int b) {
    int b1 = b;
    while (l > 0) {
        b1 = s[b1];
        l = l - 1;
    }
    return b1;
}

int main(int argc, char *argv[])
{
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-c") == 0) {  /* 是否输出虚拟机代码 */
                listswitch = true;
            } else if (strcmp(argv[i], "-t") == 0) {  /* 是否输出符号表 */
                tableswitch = true;
            } else if (strcmp(argv[i], "-s") == 0) {  /* 是否输出栈信息 */
                stackswitch = true;
            } else if (strcmp(argv[i], "-i") == 0) {  /* 是否输出单步调试信息 */
                interpretswitch = true;
            }
        }
    }
    if ((fin = fopen(argv[argc - 1], "r")) == NULL) {
        printf("Cann't open file according to given filename.\n");
		exit(0);
    }
    if ((foutput = fopen("foutput.txt", "w")) == NULL) {
        printf("Can't open the output file!\n");
        exit(0);
    }
    if ((ftable = fopen("ftable.txt", "w")) == NULL) {
        printf("Can't open ftable.txt file!\n");
        exit(0);
    }

	redirectInput(fin);
    init();
	err=0;
	yyparse();

    if ((fcode = fopen("fcode.txt", "w")) == NULL) {
        printf("Can't open fcode.txt file!\n");
        exit(1);
    }
    if ((fresult = fopen("fresult.txt", "w")) == NULL) {
        printf("Can't open fresult.txt file!\n");
        exit(1);
    }
    if ((fstack = fopen("fstack.txt", "w")) == NULL) {
        printf("Can't open fresult.txt file!\n");
        exit(1);
    }

	if(err==0){
        printf("===Parsing success!===\n\n");
        fprintf(foutput, "===Parsing success!===\n");

        listall();  /* 输出所有代码 */
        fclose(fcode);
        if(!hasProc)
            displaytable();
        if(interpretswitch){
            p = 0; /* 指令指针 */
            b = 1; /* 指令基址 */
            t = 0; /* 栈顶指针 */
            int q = 0;
            do{
                interpret_once(q);
                q++;
            }while(p!=0);
        }
        else
            interpret();  /* 调用解释执行程序 */
        fclose(fresult);
        fclose(fstack);
	}
	else{
        if(err == 1)
	 	    printf("%d error in cx program.\n", err);
        else
            printf("%d errors in cx program.\n", err);
	}
	fclose(ftable);
    fclose(foutput);
    fclose(fin);
	return 0;
}