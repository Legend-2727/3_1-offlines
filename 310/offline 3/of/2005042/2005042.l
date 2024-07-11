%option noyywrap
%{
    #include <iostream>
    #include <fstream>
    #include <sstream>
    #include <cstdio>
    #include <cstdlib>
    #include <string>
    #include "2005042_SymbolTable.h"
    #include "y.tab.h"

    using namespace std;
    #define BUCKET_SIZE 10

    extern YYSTYPE yylval;
    extern ofstream logout;
    //void yyerror(char *);
    extern SymbolTable* symbolTable;
    int line_count=1;
    int error_count=0;
    int warning_count=0;
    int indentation_count=0;
    string cur_string="";
    string main_string="";
    string indent_check="";
    enum errors{
        MULTICHAR,EMPTYCHAR,UNFINISHED_CONST_CHAR,TOO_DECIMAL,
        UNFINISHED_STRING,UNFINISHED_COMMENT,INVALID_ID_SUFFIX_NUM_PREFIX,
        UNRECOGNIZED_CHAR,ILL_FORMED
    };
    void showError(errors e,string text){
        error_count++;
        logout <<"Error at line# "<<line_count<<": ";
        if(e==MULTICHAR){
            logout<<"MULTICHAR_CONST_CHAR "<<text<<'\n';
        }
        else if(e==EMPTYCHAR){
            logout<<"EMPTY_CONST_CHAR "<<text<<'\n';
        }
        else if (e == UNFINISHED_CONST_CHAR) {
		    logout << "UNFINISHED_CONST_CHAR " << text << '\n';
	    }
	else if (e == UNRECOGNIZED_CHAR) {
		logout << "UNRECOGNIZED_CHAR " << text << '\n';
	}
        else if (e == TOO_DECIMAL) {
            logout << "TOO_MANY_DECIMAL_POINTS " << text << '\n';
        }
        else if (e == ILL_FORMED) {
            logout << "ILLFORMED_NUMBER " << text <<'\n';
        }
        else if (e == INVALID_ID_SUFFIX_NUM_PREFIX) {
            logout << "INVALID_ID_SUFFIX_NUM_PREFIX " << text << '\n';
        }
        else if (e == UNFINISHED_STRING) {
            logout << "UNFINISHED_STRING " << text << '\n';
        }
        else if (e == UNFINISHED_COMMENT) {
            logout << "UNFINISHED_COMMENT " << text << '\n';
        }
    }
    // void printInToken(string name,string type){
    //     tokenout<<"<"<<name<<", "<<type<<">"<<endl;
    // }
    void printInLog(string lexe,string type){
        int lines=0;
        for(int i=0;i<lexe.size();i++){
            if(lexe[i]=='\n'){
                lines++;
            }
        }
        logout << "Line# " << line_count-lines << ": Token <"<<type<<"> Lexeme "
        << lexe << " found" << endl;
    }
    void printKeyword(string key){
        string keyWord="";
        for(auto ch:key){
            keyWord.push_back(toupper(ch));
        }
        //printInToken(keyWord,key);
        printInLog(key,keyWord);
    }
    void printInt(string key){
        //printInToken("CONST_INT",key);
        printInLog(key,"CONST_INT");
    }
    void printFloat(string key){
        //printInToken("CONST_FLOAT",key);
        printInLog(key,"CONST_FLOAT");
    }
    char toSpecialChar(char c) {
	    if (c == 'n') return '\n';
	    else if (c == 't') return '\t';
	    else if (c == 'a') return '\a';
	    else if (c == 'f') return '\f';
	    else if (c == 'b') return '\b';
	    else if (c == 'v') return '\v';
	    else if (c == 'r') return '\r';
	    else if (c == '0') return '\0';
	    else return c;
    }
    void printChar(string text){
        string res = "";
        if(text.size()==4 && text[1]=='\\'){
            res+=toSpecialChar(text[2]);
            //printInToken("CONST_CHAR",res);
            printInLog(res,"CONST_CHAR");
        }
        else if(text.size()==3){
            if(text[1]=='\\'){
                showError(UNFINISHED_CONST_CHAR,text);
            }
            res+=text[1];
            //printInToken("CONST_CHAR",res);
            printInLog(res,"CONST_CHAR");
        }
        else if(text.size()<=2){
            showError(EMPTYCHAR,text);
        }
        else{
            showError(MULTICHAR,text);
        }
    }
    // void unfinishedChar(string text){
    //     int i=1;
    //     string res="";
    //     while(i<text.length())
    //     {
    //         if(res[i]!='\\' || i==text.length()-1){
    //             res+=text[i];
    //         }
    //         else{
    //             char cc = toSpecialChar(text[i + 1]);
    //             if (cc == text[i + 1]) {
    //                 res += text.substr(i, 2);
    //             }
    //             else {
    //                 res += cc;
    //             }
    //             i++;
    //         }
    //     }
    //     showError(UNFINISHED_CONST_CHAR,res);
    // }
    void printOperatorPunc(string token,string text) {
        //printInToken(token,text);
        printInLog(text,token);
    }
    // void setIdentifier(string id){
	//     // printInLog(id,"ID");
    //     //printInToken("ID",id);
	//     bool success = symbolTable.insert(yytext, "ID", logout);
	//     if (success) symbolTable.printAllScope(logout);
    // }
    void printString(string res,string main_string){
        for(int i=0;i<res.size();i++){
            if(main_string[i]=='\n')
            {
                printInLog(main_string,"MULTI LINE STRING");
                //printInToken("MULTI LINE STRING",res);
                return;
            }
        }
        printInLog(main_string,"SINGLE LINE STRING");
        //printInToken("SINGLE LINE STRING",res);
    }
    void printComment(string com){
        printInLog(com,"SINGLE LINE COMMENT");
    }
    void printMultiLineComment(string com){
        printInLog(com,"MULTI LINE COMMENT");
    }
    void checkIndent(string text){
        int tabCount=0;
        int spaceCount=0;
        int last_index=0;
        for(int i=0;i<text.size();i++){
            if(text[i]=='\n'){
                line_count++;
                last_index=i;
            }
        }
        //cout<<text<<"ind2\n";
        for(int i=last_index+1;i<text.size();i++){
            if(text[i]=='\t'){
                tabCount++;
            }
            else if(text[i]==' '){
                logout<<"Line# "<<line_count<<": Warning, tab required but got space.\n";
                warning_count++;
                return;
            }
            else if(text[i]=='\v'){
                logout<<"Line# "<<line_count<<": Warning, tab required but got another whitespace.\n";
                warning_count++;
                return;
            }
        }
        //cout<<tabCount;
        if(tabCount!=indentation_count){
            logout<<"Line# "<<line_count<<": warning, "<<indentation_count
            <<" of tabs needed but got "<<tabCount<<" tabs.\n";
            warning_count++;
        }
    }
%}

WHITESPACE[ \t\f\r\v]
LETTER[a-zA-Z]
DIGIT[0-9]
SIGN [+-]?
INTEGER {DIGIT}+
FLOAT {DIGIT}*\.?{DIGIT}+([eE]{SIGN}?{DIGIT}+)?
CHAR_LIT[\'\"nta\\frbv0]
CHAR ((\\{CHAR_LIT})|([^\\\'\n\r]))
TOO_DECIMAL ({DIGIT}*\.({DIGIT}*\.)*{DIGIT}+)
ILL_FORMED  ({DIGIT}*\.?{DIGIT}+([eE]{SIGN}?{DIGIT}*\.{DIGIT}+))
IDENTIFIER ({LETTER}|_)(({DIGIT}|{LETTER}|_)*)
INVALID_ID ({DIGIT})(({DIGIT}|{LETTER}|_)*)
NLINE ((\r)?\n)

%%
<<EOF>> {cout<<"ended\n"; return 0;}
{WHITESPACE}+ 			{}
{NLINE}                 {line_count++;}

"if"	    {
                printKeyword(yytext); 
                SymbolInfo* temp=new SymbolInfo(yytext,"KEYWORD",line_count,"IF");
                yylval.symbolInfo=temp;
                return IF;
            }
"for"	    {
                printKeyword(yytext); 
                SymbolInfo* temp=new SymbolInfo(yytext,"KEYWORD",line_count,"FOR");
                yylval.symbolInfo=temp;
                return FOR;
            }
"int"		{
                printKeyword(yytext); 
                SymbolInfo* temp=new SymbolInfo(yytext,"KEYWORD",line_count,"INT");
                yylval.symbolInfo=temp;
                return INT;
            }
"float"		{
                printKeyword(yytext); 
                SymbolInfo* temp=new SymbolInfo(yytext,"KEYWORD",line_count,"FLOAT");
                yylval.symbolInfo=temp;
                return FLOAT;
            }
"void"		{
                printKeyword(yytext); 
                SymbolInfo* temp=new SymbolInfo(yytext,"KEYWORD",line_count,"VOID");
                yylval.symbolInfo=temp;
                return VOID;
            }
"else"		{
                printKeyword(yytext); 
                SymbolInfo* temp=new SymbolInfo(yytext,"KEYWORD",line_count,"ELSE");
                yylval.symbolInfo=temp;
                return ELSE;
            }
"while"		{
                printKeyword(yytext); 
                SymbolInfo* temp=new SymbolInfo(yytext,"KEYWORD",line_count,"WHILE");
                yylval.symbolInfo=temp;
                return WHILE;
            }
"return"	{
                printKeyword(yytext); 
                SymbolInfo* temp=new SymbolInfo(yytext,"KEYWORD",line_count,"RETURN");
                yylval.symbolInfo=temp;
                return RETURN;
            }

{INTEGER}   {
                printInt(yytext);
                SymbolInfo* temp=new SymbolInfo(yytext,"CONST_INT",line_count,"int");
                yylval.symbolInfo=temp;
                return CONST_INT;
            }
{FLOAT}     {
                printFloat(yytext);
                SymbolInfo* temp=new SymbolInfo(yytext,"CONST_FLOAT",line_count,"float");
                yylval.symbolInfo =temp; 
                return CONST_FLOAT;
            }
{TOO_DECIMAL}   {showError(TOO_DECIMAL,yytext);}
{ILL_FORMED}   {showError(ILL_FORMED,yytext);}
{IDENTIFIER}    {
                    // setIdentifier(yytext);
                    printInLog(yytext,"ID");
                    SymbolInfo* temp=new SymbolInfo(yytext,"ID",line_count);
                    yylval.symbolInfo=temp;
                    return ID;
                }

{INVALID_ID}    {
                    showError(INVALID_ID_SUFFIX_NUM_PREFIX,yytext);
                }

"+"|"-"		            { 
                            printOperatorPunc("ADDOP",yytext); 
                            SymbolInfo* temp=new SymbolInfo(yytext,"ADDOP",line_count);
                            yylval.symbolInfo=temp;
                            return ADDOP;
                        }
"*"|"/"|"%"	            { 
                            printOperatorPunc("MULOP",yytext); 
                            SymbolInfo* temp=new SymbolInfo(yytext,"MULOP",line_count);
                            yylval.symbolInfo=temp;
                            return MULOP;
                        }
"++"|"--"	            { 
                            printOperatorPunc("INCOP",yytext); 
                            SymbolInfo* temp=new SymbolInfo(yytext,"INCOP",line_count);
                            yylval.symbolInfo=temp;
                            return INCOP;
                        }
"<"|"<="|">"|">="|"=="|"!="			{ 
                                        printOperatorPunc("RELOP",yytext); 
                                        SymbolInfo* temp=new SymbolInfo(yytext,"RELOP",line_count);
                                        yylval.symbolInfo=temp;
                                        return RELOP;
                                    }
"="			            { 
                            printOperatorPunc("ASSIGNOP",yytext); 
                            SymbolInfo* temp=new SymbolInfo(yytext,"ASSIGNOP",line_count);
                            yylval.symbolInfo=temp;
                            return ASSIGNOP;
                        }
"&&"|"||"	            { 
                            printOperatorPunc("LOGICOP",yytext); 
                            SymbolInfo* temp=new SymbolInfo(yytext,"LOGICOP",line_count);
                            yylval.symbolInfo=temp;
                            return LOGICOP;
                        }
"!"						{ 
                            printOperatorPunc("NOTOP",yytext); 
                            SymbolInfo* temp=new SymbolInfo(yytext,"NOTOP",line_count);
                            yylval.symbolInfo=temp;
                            return NOT;
                        }
"("						{ 
                            printOperatorPunc("LPAREN",yytext); 
                            SymbolInfo* temp=new SymbolInfo(yytext,"LPAREN",line_count);
                            yylval.symbolInfo=temp;
                            return LPAREN;
                        }
")"						{ 
                            printOperatorPunc("RPAREN",yytext); 
                            SymbolInfo* temp=new SymbolInfo(yytext,"RPAREN",line_count);
                            yylval.symbolInfo=temp;
                            return RPAREN;
                        }
"{"						{
                            printOperatorPunc("LCURL",yytext); 
                            SymbolInfo* temp=new SymbolInfo(yytext,"LCURL",line_count);
                            yylval.symbolInfo=temp;
                            symbolTable->enterScope();
                            indentation_count++;     
                            return LCURL;
                        }
"}"						{ 
                            printOperatorPunc("RCURL",yytext); 
                            SymbolInfo* temp=new SymbolInfo(yytext,"RCURL",line_count);
                            yylval.symbolInfo=temp;
                            indentation_count--;
                            indentation_count=max(indentation_count,0);
                            return RCURL;
                        }
"["						{ 
                            printOperatorPunc("LTHIRD",yytext); 
                            SymbolInfo* temp=new SymbolInfo(yytext,"LTHIRD",line_count);
                            yylval.symbolInfo=temp;
                            return LTHIRD;
                        }
"]"						{ 
                            printOperatorPunc("RTHIRD",yytext); 
                            SymbolInfo* temp=new SymbolInfo(yytext,"RTHIRD",line_count);
                            yylval.symbolInfo=temp;
                            return RTHIRD;
                        }
","						{ 
                            printOperatorPunc("COMMA",yytext); 
                            SymbolInfo* temp=new SymbolInfo(yytext,"COMMA",line_count);
                            yylval.symbolInfo=temp;
                            return COMMA;
                        }
";"						{ 
                            printOperatorPunc("SEMICOLON",yytext); 
                            SymbolInfo* temp=new SymbolInfo(yytext,"SEMICOLON",line_count);
                            yylval.symbolInfo=temp;
                            return SEMICOLON;
                        }


.       {showError(UNRECOGNIZED_CHAR,yytext);error_count++;}
%%
/* {NLINE}+({WHITESPACE}|{NLINE})*     { 
                                        checkIndent(yytext);
                                    }
{NLINE}+({WHITESPACE}|{NLINE})*"}"  { 
                                        indentation_count--;
                                        indentation_count=max(indentation_count,0);
                                        string temp1=yytext;
                                        temp1.pop_back();
                                        checkIndent(temp1);
                                        printOperatorPunc("RCURL","}");
                                        //symbolTable->exitScope();
                                    } 
\"                      {
                            cur_string="";
                            main_string="";
                            BEGIN STRING_STATE;
                        }
\/\/                    {
                            cur_string="";
                            main_string="";
                            BEGIN SINGLE_LINE_COMMENT_STATE;
                        }
\/\*                    {
                            cur_string="";
                            main_string="";
                            BEGIN MULTILINE_COMMENT_STATE;
                        }
\'{CHAR}*\'     {
                    printChar(yytext);
                }
\'{CHAR}?       {
                    if(yytext[yyleng-1]=='\n'){
                        line_count++;
                        string temp=yytext;
                        showError(UNFINISHED_CONST_CHAR,temp.substr(0,yyleng-1));
                    }
                    else{
                        showError(UNFINISHED_CONST_CHAR,yytext);
                    }
                }


<STRING_STATE>\\{CHAR_LIT}      {
                                    cur_string+=toSpecialChar(yytext[yyleng-1]);
                                    main_string+="\\";
                                    main_string+=yytext[yyleng-1];
                                } 
<STRING_STATE>\\{NLINE}         {
                                    //cur_string+='';
                                    main_string+="\\\n";
                                    line_count++;
                                }
<STRING_STATE>{NLINE}           {
                                    main_string="\""+main_string;
                                    showError(UNFINISHED_STRING,main_string);
                                    line_count++;
                                    main_string="";
                                    cur_string="";
                                    BEGIN INITIAL;
                                } 
<STRING_STATE><<EOF>>           {
                                    main_string="\""+main_string;
                                    showError(UNFINISHED_STRING,main_string);
                                    main_string="";
                                    cur_string="";
                                    BEGIN INITIAL;
                                }                  
<STRING_STATE>\"                {
                                    string res=cur_string;
                                    main_string="\""+main_string+"\"";
                                    printString(res,main_string);
                                    cur_string="";
                                    main_string="";
                                    BEGIN INITIAL;
                                }
<STRING_STATE>.                 {
                                    cur_string+=yytext;
                                    main_string+=yytext;
                                }
<SINGLE_LINE_COMMENT_STATE>\\{NLINE}    {cur_string+="\\\n";line_count++;}
<SINGLE_LINE_COMMENT_STATE>{NLINE}      {
                                            cur_string="//"+cur_string;
                                            printComment(cur_string);
                                            cur_string="";
                                            line_count++; 
                                            BEGIN INITIAL;   
                                        }
<SINGLE_LINE_COMMENT_STATE><<EOF>>      {
                                            cur_string="\""+cur_string+"\"";
                                            printComment(cur_string);
                                            cur_string="";
                                            line_count++; 
                                            BEGIN INITIAL;   
                                        }                                        
<SINGLE_LINE_COMMENT_STATE>.            {cur_string+=yytext;}
<MULTILINE_COMMENT_STATE><<EOF>>        {
                                            cur_string="/*"+cur_string;
                                            showError(UNFINISHED_COMMENT,cur_string);
                                            cur_string="";
                                            BEGIN INITIAL;
                                        }
<MULTILINE_COMMENT_STATE>{NLINE}        {line_count++;cur_string+='\n';}
<MULTILINE_COMMENT_STATE>.              {cur_string+=yytext;}
<MULTILINE_COMMENT_STATE>\*\/           {
                                            cur_string="/*"+cur_string+"*";
                                            printMultiLineComment(cur_string);
                                            cur_string="";
                                            BEGIN INITIAL;
                                        }

        */