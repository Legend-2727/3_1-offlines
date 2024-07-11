%option noyywrap
%x STRING_STATE
%x SINGLE_LINE_COMMENT_STATE
%x MULTILINE_COMMENT_STATE
%x INDENT_CHECK_STATE
%{
    #include <string>
    #include "2005042_SymbolTable.h"
    #define BUCKET_SIZE 10 

    ofstream logout;
    ofstream tokenout;
    int line_count=1;
    int error_count=0;
    int warning_count=0;
    int indentation_count=0;
    SymbolTable symbolTable(BUCKET_SIZE);
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
    void printInToken(string name,string type){
        tokenout<<"<"<<name<<", "<<type<<">"<<endl;
    }
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
        printInToken(keyWord,key);
        printInLog(key,keyWord);
    }
    void printInt(string key){
        printInToken("CONST_INT",key);
        printInLog(key,"CONST_INT");
    }
    void printFloat(string key){
        printInToken("CONST_FLOAT",key);
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
            printInToken("CONST_CHAR",res);
            printInLog(res,"CONST_CHAR");
        }
        else if(text.size()==3){
            if(text[1]=='\\'){
                showError(UNFINISHED_CONST_CHAR,text);
            }
            res+=text[1];
            printInToken("CONST_CHAR",res);
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
        printInToken(token,text);
        printInLog(text,token);
    }
    void setIdentifier(string id){
	    printInLog(id,"ID");
        printInToken("ID",id);
	    bool success = symbolTable.insert(yytext, "ID", logout);
	    if (success) symbolTable.printAllScope(logout);
    }
    void printString(string res,string main_string){
        for(int i=0;i<res.size();i++){
            if(main_string[i]=='\n')
            {
                printInLog(main_string,"MULTI LINE STRING");
                printInToken("MULTI LINE STRING",res);
                return;
            }
        }
        printInLog(main_string,"SINGLE LINE STRING");
        printInToken("SINGLE LINE STRING",res);
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
{WHITESPACE} 			{}
{NLINE}+({WHITESPACE}|{NLINE})*     { 
                                        checkIndent(yytext);
                                    }
{NLINE}+({WHITESPACE}|{NLINE})*"}"  { 
                                        indentation_count--;
                                        indentation_count=max(indentation_count,0);
                                        string temp1=yytext;
                                        temp1.pop_back();
                                        checkIndent(temp1);
                                        printOperatorPunc("RCURL","}");
                                        symbolTable.exitScope();
                                        
                                        
                                    }

"if"	    |
"for"	    |
"do"		|
"int"		|
"float"		|
"void"		|
"switch"	|
"default"	|
"else"		|
"while"		|
"break"		|
"char"		|
"double"	|
"return"	|
"case"      |
"continue"	{ printKeyword(yytext); }

{INTEGER}   {printInt(yytext);}
{FLOAT}     {printFloat(yytext);}
{TOO_DECIMAL}   {showError(TOO_DECIMAL,yytext);}
{ILL_FORMED}   {showError(ILL_FORMED,yytext);}
{IDENTIFIER}    {
                    setIdentifier(yytext);
                }

{INVALID_ID}    {
                    showError(INVALID_ID_SUFFIX_NUM_PREFIX,yytext);
                }

"+"|"-"		            { printOperatorPunc("ADDOP",yytext); }
"*"|"/"|"%"	            { printOperatorPunc("MULOP",yytext); }
"++"|"--"	            { printOperatorPunc("INCOP",yytext); }
"<"|"<="|">"|">="|"=="|"!="			{ printOperatorPunc("RELOP",yytext); }
"="			            { printOperatorPunc("ASSIGNOP",yytext); }
"&&"|"||"	            { printOperatorPunc("LOGICOP",yytext); }
"&"|"|"|"^"|"<<"|">>"	{ printOperatorPunc("BITOP",yytext); }
"!"						{ printOperatorPunc("NOT",yytext); }
"("						{ printOperatorPunc("LPAREN",yytext); }
")"						{ printOperatorPunc("RPAREN",yytext); }
"{"						{
                            printOperatorPunc("LCURL",yytext); 
                            symbolTable.enterScope(); 
                            indentation_count++;     
                        }
"}"						{ 
                            printOperatorPunc("RCURL",yytext); 
                            symbolTable.exitScope();
                            indentation_count--;
                            indentation_count=max(indentation_count,0);
                        }
"["						{ printOperatorPunc("LSQUARE",yytext); }
"]"						{ printOperatorPunc("RSQUARE",yytext); }
","						{ printOperatorPunc("COMMA",yytext); }
";"						{ printOperatorPunc("SEMICOLON",yytext); }

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
                                            cur_string="/*"+cur_string+"*/";
                                            printMultiLineComment(cur_string);
                                            cur_string="";
                                            BEGIN INITIAL;
                                        }
<<EOF>> {return 0;}
.       {showError(UNRECOGNIZED_CHAR,yytext);}
%%
int main(int argc,char *argv[]){
	
	if(argc!=2){
		printf("Please provide input file name and try again\n");
		return 0;
	}
	
	FILE *fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("Cannot open specified file\n");
		return 0;
	}
	
    logout.open("2005042_log.txt");
    tokenout.open("2005042_token.txt");
	yyin = fin;
	yylex();
    //cout
    symbolTable.printAllScope(logout);
    logout << "Total lines: " << line_count << endl;
	logout << "Total errors: " << error_count << endl;
    logout << "Total warnings: "<<warning_count<<endl;
	fclose(yyin);
    logout.close();
    tokenout.close();
	return 0;
}