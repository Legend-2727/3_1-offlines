%{
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
#include <cmath>
#include "2005042_SymbolTable.h"
#define BUCKET_SIZE 11
using namespace std;

int yylex(void);
int yyparse(void);

extern FILE *yyin;
extern int line_count;
extern int error_count;
ofstream parsetree_out, error_out;
ofstream logout;
SymbolTable *symbolTable;
ScopeTable *scopetable;
void yyerror(string s)
{
    logout<<"Error at line no "<<line_count<<": syntax error"<<'\n';
	error_count++;
}

void free_s(SymbolInfo *s) {
    if (s != nullptr) {
        delete s;
		s=nullptr;
    }
}

void printInLog(string rule) {
	logout<< rule << " \n";
}
void insertAll(string type,SymbolInfo *sm){
	Parameter *temp=sm->getParameterList();
	while(temp!=NULL){
		symbolTable->insert(temp->getName(),type,"",line_count,error_out);
		temp=temp->getNext();
	}
}
void insertParameters(SymbolInfo *sm){
	cout<<"here\n";
	Parameter *temp=sm->getParameterList();
	while(temp!=NULL){
		symbolTable->insert(temp->getName(),temp->getType(),"",line_count,error_out);
		temp=temp->getNext();
	}
}
void printInParseTree(SymbolInfo *root,int height){
	for(int i=0;i<height;i++){
		parsetree_out<<" ";
	}
	//cout<<"eikhane\n";
	parsetree_out<<root->getRule()<<"\t";
	if(root->getEndLine()!=-1){
		parsetree_out<<"<Line: "<<root->getStartLine()<<"-"<<root->getEndLine()<<">\n";
	}
	else{
		parsetree_out<<"<Line: "<<root->getStartLine()<<">\n";
	}
	SymbolInfo *temp=root->getChild();
	while(temp!=NULL){
		printInParseTree(temp,height+1);
		temp=temp->getNext();
	}
}

void printError(string type,string state,string location,int lc){
	error_out<<"Line# "<<lc<<":"<<type<<" at "<<state<<" of "<<location<<"\n";
}
%}

%define parse.error verbose


%union {
    SymbolInfo *symbolInfo;
}
/* %destructor {
    free_s($$);
} <symbolInfo> */

%right <symbolInfo> ASSIGNOP
%left <symbolInfo> LOGICOP
%left  <symbolInfo> RELOP
%left  <symbolInfo> ADDOP
%left  <symbolInfo> MULOP
%right <symbolInfo> NOT
%right <symbolInfo> INCOP DECOP
%left <symbolInfo> RPAREN
%left <symbolInfo> ELSE
//%nonassoc LOWER_THAN_ELSE
%token <symbolInfo> IF FOR WHILE RETURN PRINTLN 
%token <symbolInfo> LPAREN LCURL RCURL LTHIRD RTHIRD COMMA SEMICOLON INT FLOAT VOID
%token <symbolInfo> CONST_INT CONST_FLOAT ID
%type <symbolInfo> start program unit var_declaration func_declaration func_definition type_specifier parameter_list compound_statement statements declaration_list statement expression expression_statement logic_expression rel_expression simple_expression term unary_expression factor variable argument_list arguments




%%

start : program
	{
		SymbolInfo *temp=new SymbolInfo("Root","Start");
		temp->setRule("start : program");
		temp->addChild($1);
		$$ = temp;
		printInLog(temp->getRule());
		cout<<"p\n";
		printInParseTree($$,0);
		//free_s($$);
		cout<<"he\n";
	}
	;

program : program unit{
		SymbolInfo *temp=new SymbolInfo("Node","program");
		temp->setRule("program : program unit");
		temp->addChild($1);
		temp->addChild($2);
		$$ = temp;
		printInLog(temp->getRule());
	}
	| unit{
		SymbolInfo *temp=new SymbolInfo("Node","program");
		temp->setRule("program : unit");
		temp->addChild($1);
		$$ = temp;
		printInLog(temp->getRule());
	}
	;
	
unit : var_declaration{
			SymbolInfo *temp=new SymbolInfo("Node","unit");
			temp->setRule("unit : var_declaration");
			// cout<<"here................\n";
			// cout<<$1->getStartLine()<<$1->getEndLine()<<'\n';
			// cout<<temp->getStartLine()<<temp->getEndLine()<<'\n';
			temp->addChild($1);
			//cout<<temp->getStartLine()<<endl;
			$$ = temp;
			printInLog(temp->getRule());
		}
     | func_declaration{
		SymbolInfo *temp=new SymbolInfo("Node","unit");
		temp->setRule("unit : func_declaration");
		temp->addChild($1);
		$$ = temp;
		printInLog(temp->getRule());
	 }
     | func_definition{
		SymbolInfo* temp= new SymbolInfo("Node","unit");
		temp->setRule("unit : func_declaration");
		temp->addChild($1);
		$$=temp;
		printInLog(temp->getRule());
	 }
	 |error{
		SymbolInfo* temp= new SymbolInfo("Node","unit");
		temp->setRule("unit : error");
		//temp->addChild($1);
		$$=temp;
		printInLog(temp->getRule());
	 }
     ;
     
func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON{
			//cout<<"here\n";
			SymbolInfo *temp=new SymbolInfo($2->getName(),"func_declaration");
			temp->setRule("func_declaration :  type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
			temp->addChild($1);
			temp->addChild($2);
			temp->addChild($3);
			temp->addChild($4);
			temp->addChild($5);
			temp->addChild($6);
			if($4->getName()=="error"){
				printError("Syntax error","parameter list","function declaration",line_count);
			}
			temp->addParameterList($4->getParameterList());
			temp->setReturnType($1->getDataType());
			//symbolTable->insert($2->getName(),"FUNCTION",$1->getDataType(),line_count,error_out);
			$$ = temp;
			//symbolTable->insert()
			printInLog(temp->getRule());
		}
		| type_specifier ID LPAREN RPAREN SEMICOLON{
			SymbolInfo *temp=new SymbolInfo($2->getName(),"func_declaration");
			temp->setRule("func_declaration :  type_specifier ID LPAREN RPAREN SEMICOLON");
			temp->addChild($1);
			temp->addChild($2);
			temp->addChild($3);
			temp->addChild($4);
			temp->addChild($5);
			temp->setReturnType($1->getDataType());
			//symbolTable->insert($2->getName(),"FUNCTION",$1->getDataType(),line_count,error_out);
			$$ = temp;
			printInLog(temp->getRule());
		}
		;
func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement{
					SymbolInfo *temp=new SymbolInfo($2->getName(),"func_definition");
					temp->setRule("func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement");
					temp->addChild($1);
					temp->addChild($2);
					temp->addChild($3);
					temp->addChild($4);
					temp->addChild($5);
					temp->addChild($6);
					temp->setReturnType($1->getDataType());
					if($4->getName()=="error"){
						printError("Syntax error","parameter list","function definition",$4->getStartLine());
					}
					//symbolTable->insert($2->getName(),"FUNCTION",$1->getDataType(),line_count,error_out);
					$$=temp;
					printInLog(temp->getRule());
				}

		| type_specifier ID LPAREN RPAREN compound_statement{
					SymbolInfo *temp=new SymbolInfo($2->getName(),"func_definition");
					temp->setRule("func_definition : type_specifier ID LPAREN RPAREN compound_statement");
					temp->addChild($1);
					temp->addChild($2);
					temp->addChild($3);
					temp->addChild($4);
					temp->addChild($5);
					cout<<"here"<<line_count<<"\n";
					temp->setReturnType($1->getDataType());
					//symbolTable->insert($2->getName(),"FUNCTION",$1->getDataType(),line_count,error_out);
					//symbolTable->enterScope();
					//insertAll($1->getDataType(),$5);
					//symbolTable->printAllScope(logout);
					//symbolTable->exitScope();
					$$=temp;
					printInLog(temp->getRule());
				}
 		;				


parameter_list  : parameter_list COMMA type_specifier ID{
			SymbolInfo *temp = new SymbolInfo("Node","parameter_list");
			temp->setRule("parameter_list : parameter_list COMMA type_specifier ID");
			temp->addChild($1);
			temp->addChild($2);
			temp->addChild($3);
			temp->addChild($4);
			temp->addParameterList($1->getParameterList());
			Parameter *p=new Parameter($4->getName(),$3->getType());
			temp->addParameterList(p);
			//func_parameters=temp;
			//logout<<"here\n";
			$$ = temp;
			printInLog(temp->getRule());
		}
		| parameter_list COMMA type_specifier{
			SymbolInfo *temp = new SymbolInfo("Node","parameter_list");
			temp->setRule("parameter_list : parameter_list COMMA type_specifier");
			temp->addChild($1);
			temp->addChild($2);
			temp->addChild($3);
			temp->addParameterList($1->getParameterList());
			Parameter *p=new Parameter($3->getName(),$3->getType());
			temp->addParameterList(p);
			//func_parameters=temp;
			$$ = temp;
			printInLog(temp->getRule());
		}
 		| type_specifier ID{
			SymbolInfo *temp = new SymbolInfo("Node","parameter_list");
			temp->setRule("parameter_list : type_specifier ID");
			temp->addChild($1);
			temp->addChild($2);
			Parameter *p=new Parameter($2->getName(),$1->getType());
			temp->addParameterList(p);
			$$ = temp;
			//func_parameters=temp;
			printInLog(temp->getRule());
		}
		| type_specifier{
			SymbolInfo *temp = new SymbolInfo("Node","parameter_list");
			temp->setRule("parameter_list : type_specifier");
			temp->addChild($1);
			Parameter *p=new Parameter($1->getName(),$1->getType());
			temp->addParameterList(p);
			$$ = temp;
			//func_parameters=temp;
			printInLog(temp->getRule());
		}
		| error{
			yyclearin;
			SymbolInfo *temp=new SymbolInfo("error","parameter_list",line_count);
			temp->setRule("parameter_list : error");
			$$=temp;
		}
 		;

compound_statement : LCURL statements RCURL{
				SymbolInfo *temp = new SymbolInfo("Leaf","compound_statement");
				temp->setRule("compound_statement : LCURL statements RCURL");
				temp->addChild($1);
				temp->addChild($2);
				temp->addChild($3);
				$$ = temp;
				// symbolTable->copyScope(scopetable,logout);
				//scopetable=new ScopeTable(BUCKET_SIZE,NULL);
				printInLog(temp->getRule());
				symbolTable->printAllScope(logout);
				symbolTable->exitScope();
			}
 		    | LCURL RCURL{
				SymbolInfo *temp = new SymbolInfo("Leaf","compound_statement");
				//symbolTable->enterScope();
				symbolTable->insert("NN","INT","",line_count,logout);
				temp->setRule("compound_statement : LCURL RCURL");
				temp->addChild($1);
				temp->addChild($2);
				$$ = temp;
				printInLog(temp->getRule());
				symbolTable->printAllScope(logout);
				symbolTable->exitScope();
			}
 		    ;
 		    
var_declaration : type_specifier declaration_list SEMICOLON{
				SymbolInfo *temp=new SymbolInfo("Node","var_declaration",$1->getType());
				temp->setRule("var_declaration : type_specifier declaration_list SEMICOLON");
				temp->addChild($1);
				temp->addChild($2);
				temp->addChild($3);
				insertAll($1->getDataType(),$2);
				$$ = temp;
				printInLog(temp->getRule());
			}
			|type_specifier declaration_list error SEMICOLON{
				SymbolInfo *temp=new SymbolInfo("error","var_declaration");
				temp->setRule("var_declaration : type_specifier declaration");
				$$=temp;
				printError("Syntax","declaration list","var_declaration",line_count);
			}
 		 ;
 		 
type_specifier	: INT{
					$$=new SymbolInfo("Node","type_specifier","int");
					$$->setRule("type_specifier	: INT");
					$$->addChild($1);
					printInLog($$->getRule());
				}
 				| FLOAT{
					$$=new SymbolInfo("Node","type_specifier","float");
					$$->setRule("type_specifier	: FLOAT");
					$$->addChild($1);
					printInLog($$->getRule());
				}
 				| VOID{
					$$=new SymbolInfo("Node","type_specifier","VOID");
					$$->setRule("type_specifier	: VOID");
					$$->addChild($1);
					printInLog($$->getRule());
				}
 				;
 		
declaration_list : declaration_list COMMA ID{
							SymbolInfo *temp=new SymbolInfo("Node","declaration_list");
							temp->setRule("declaration_list : declaration_list COMMA ID");
							temp->addParameterList($1->getParameterList());
							Parameter *p=new Parameter($3->getName(),$3->getType());
							temp->addParameterList(p);
							//cout<<$3->getName()<<endl;
							//temp->printParameter(logout);
							temp->addChild($1);
							temp->addChild($2);
							temp->addChild($3);
							$$=temp;
							printInLog($$->getRule());
						}
 		  | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD{
				SymbolInfo *temp=new SymbolInfo("Node","declaration_list");
				temp->setRule("declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
				temp->addParameterList($1->getParameterList());
				Parameter *p=new Parameter($3->getName(),$3->getType());
				temp->addParameterList(p);
				temp->addChild($1);
				temp->addChild($2);
				temp->addChild($3);
				temp->addChild($4);
				temp->addChild($5);
				temp->addChild($6);
				$$=temp;
				printInLog($$->getRule());
		  }
 		  | ID{
				SymbolInfo *temp=new SymbolInfo("Node","declaration_list");
				//logout<<$1->getName()<<'\n';
				Parameter *p=new Parameter($1->getName(),$1->getType());
				temp->addParameterList(p);
				//logout<<"here\n";
				temp->addChild($1);
				$$=temp;
				$$->setRule("declaration_list : ID");
				printInLog($$->getRule());
		  }
 		  | ID LTHIRD CONST_INT RTHIRD{
				SymbolInfo *s=new SymbolInfo("Node","declaration_list");
				Parameter *temp=new Parameter($1->getName(),$1->getType());
				s->addParameterList(temp);
				s->setRule("declaration_list : ID LTHIRD CONST_INT RTHIRD");
				s->addChild($1);
				s->addChild($2);
				s->addChild($3);
				s->addChild($4);
				$$=s;
				printInLog(s->getRule());
		  }
		  /* |error{
			yyclearin;	 
		  } */
 		  ;
 		  
statements : statement{
			SymbolInfo *temp=new SymbolInfo("Node","statements");
			temp->setRule("statements : statement");
			temp->addChild($1);
			$$=temp;
			printInLog(temp->getRule());
		}
	   | statements statement{
			SymbolInfo *temp=new SymbolInfo("Node","statements");
			temp->setRule("statements : statements statement");
			temp->addChild($1);
			temp->addChild($2);
			$$=temp;
			printInLog(temp->getRule());
		}
	   ;
	   
statement : var_declaration{
				SymbolInfo *temp=new SymbolInfo("Node","statement");
				temp->setRule("statement: var_declaration");
				temp->addChild($1);
				$$=temp;
				printInLog(temp->getRule());
			}
	  | expression_statement{
				SymbolInfo *temp=new SymbolInfo("Node","statement");
				temp->setRule("statement: expression_statement");
				temp->addChild($1);
				$$=temp;
				printInLog(temp->getRule());
			}
	  | compound_statement{
				SymbolInfo *temp=new SymbolInfo("Node","statement");
				temp->setRule("statement: compound_statement");
				temp->addChild($1);
				$$=temp;
				printInLog(temp->getRule());
			}
	  | FOR LPAREN expression_statement expression_statement expression RPAREN statement{
				SymbolInfo *temp=new SymbolInfo("Node","statement");
				temp->setRule("statement: FOR LPAREN expression_statement expression_statement expression RPAREN statement");
				temp->addChild($1);
				temp->addChild($2);
				temp->addChild($3);
				temp->addChild($4);
				temp->addChild($5);
				temp->addChild($6);
				temp->addChild($7);
				$$=temp;
				printInLog(temp->getRule());
		}
	  | IF LPAREN expression RPAREN statement{
				SymbolInfo *temp=new SymbolInfo("Node","statement");
				temp->setRule("statement: IF LPAREN expression RPAREN statement");
				temp->addChild($1);
				temp->addChild($2);
				temp->addChild($3);
				temp->addChild($4);
				temp->addChild($5);
				$$=temp;
				printInLog(temp->getRule());
		}
	  | IF LPAREN expression RPAREN statement ELSE statement{
				SymbolInfo *temp=new SymbolInfo("Node","statement");
				temp->setRule("statement: IF LPAREN expression RPAREN statement ELSE statement");
				temp->addChild($1);
				temp->addChild($2);
				temp->addChild($3);
				temp->addChild($4);
				temp->addChild($5);
				temp->addChild($6);
				temp->addChild($7);
				$$=temp;
				printInLog(temp->getRule());
		}
	  | WHILE LPAREN expression RPAREN statement{
				SymbolInfo *temp=new SymbolInfo("Node","statement");
				temp->setRule("statement: WHILE LPAREN expression RPAREN statement");
				temp->addChild($1);
				temp->addChild($2);
				temp->addChild($3);
				temp->addChild($4);
				temp->addChild($5);
				$$=temp;
				printInLog(temp->getRule());
		}
	  | PRINTLN LPAREN ID RPAREN SEMICOLON{
				SymbolInfo *temp=new SymbolInfo("Node","statement");
				temp->setRule("statement: PRINTLN LPAREN ID RPAREN SEMICOLON");
				temp->addChild($1);
				temp->addChild($2);
				temp->addChild($3);
				temp->addChild($4);
				temp->addChild($5);
				$$=temp;
				printInLog(temp->getRule());
		}
	  | RETURN expression SEMICOLON{
				SymbolInfo *temp=new SymbolInfo("Node","statement");
				temp->setRule("statement: RETURN expression SEMICOLON");
				temp->addChild($1);
				temp->addChild($2);
				temp->addChild($3);
				$$=temp;
				printInLog(temp->getRule());
		}
	  ;
	  
expression_statement 	: SEMICOLON{
				SymbolInfo *temp=new SymbolInfo("Leaf","expression_statement");
				temp->setRule("expression_statement : SEMICOLON");
				temp->addChild($1);
				$$=temp;
				printInLog(temp->getRule());
			}			
			| expression SEMICOLON {
				SymbolInfo *temp=new SymbolInfo("Leaf","expression_statement");
				temp->setRule("expression_statement : expression SEMICOLON");
				temp->addChild($1);
				temp->addChild($2);
				$$=temp;
				printInLog(temp->getRule());
			}
			;
	  
variable : ID {
			SymbolInfo *temp=new SymbolInfo($1->getName(),"variable");
			temp->setRule("variable : ID");
			temp->addChild($1);
			$$=temp;
			printInLog(temp->getRule());
			symbolTable->lookup($1->getName(),line_count,error_out);
		}		
	 | ID LTHIRD expression RTHIRD {
			SymbolInfo *temp=new SymbolInfo($1->getName(),"variable","array");
			temp->setRule("variable : ID LTHIRD expression RTHIRD");
			temp->addChild($1);
			temp->addChild($2);
			temp->addChild($3);
			temp->addChild($4);
			$$=temp;
			printInLog(temp->getRule());
			if($3->getName()=="error"){
				printError("Invalid index","expression","array declaration",line_count);
			}
			symbolTable->lookup($1->getName(),line_count,error_out);
		}
	 ;
 expression : logic_expression{
			SymbolInfo *temp=new SymbolInfo("Node","expression");
			temp->setRule("expression : logic_expression");
			temp->addChild($1);
			$$=temp;
			printInLog(temp->getRule());
		 }
	   | variable ASSIGNOP logic_expression{
			SymbolInfo *temp=new SymbolInfo("Node","expression");
			temp->setRule("expression : variable ASSIGNOP logic_expression");
			temp->addChild($1);
			temp->addChild($2);
			temp->addChild($3);
			$$=temp;
			printInLog(temp->getRule());
		 }
		| error{
			yyclearin;
			SymbolInfo *temp=new SymbolInfo("error","expression");
			temp->setRule("expression : error");
			$$=temp;
		}	
	   ;
			
logic_expression : rel_expression{
			SymbolInfo *temp=new SymbolInfo("Node","logic_expression");
			temp->setRule("logic_expression : rel_expression");
			temp->addChild($1);
			$$=temp;
			printInLog(temp->getRule());
		 }
		 | rel_expression LOGICOP rel_expression {
			SymbolInfo *temp=new SymbolInfo("Node","logic_expression");
			temp->setRule("logic_expression : rel_expression LOGICOP rel_expression");
			temp->addChild($1);
			temp->addChild($2);
			temp->addChild($3);
			$$=temp;
			printInLog(temp->getRule());
		 }	
		 ;
			
rel_expression	: simple_expression {
			SymbolInfo *temp=new SymbolInfo("Node","simple_expression");
			temp->setRule("rel_expression : simple_expression");
			temp->addChild($1);
			$$=temp;
			printInLog(temp->getRule());
		}
		| simple_expression RELOP simple_expression	{
			SymbolInfo *temp=new SymbolInfo("Node","simple_expression");
			temp->setRule("rel_expression : simple_expression RELOP simple_expression");
			temp->addChild($1);
			temp->addChild($2);
			temp->addChild($3);
			$$=temp;
			printInLog(temp->getRule());
		}
		;
				
simple_expression : term {
			SymbolInfo *temp= new SymbolInfo("Node","simple_expression");
			temp->setRule("simple_expression : term");
			temp->addChild($1);
			$$ = temp;
			printInLog(temp->getRule());
		  }
		  | simple_expression ADDOP term {
			SymbolInfo *temp= new SymbolInfo("Node","simple_expression");
			temp->setRule("simple_expression : simple_expression ADDOP term");
			temp->addChild($1);
			temp->addChild($2);
			temp->addChild($3);
			$$ = temp;
			printInLog(temp->getRule());
		  }
		  ;
					
term :	unary_expression{
		SymbolInfo *temp=new SymbolInfo("Node","term");
		temp->setRule("term : unary_expression");
		temp->addChild($1);
		$$=temp;
		printInLog(temp->getRule());
	}
     |  term MULOP unary_expression{
		SymbolInfo *temp=new SymbolInfo("Node","term");
		temp->setRule("term : term MULOP unary_expression");
		temp->addChild($1);
		temp->addChild($2);
		temp->addChild($3);
		$$=temp;
		printInLog(temp->getRule());
	 }
     ;

unary_expression : ADDOP unary_expression{
			SymbolInfo *temp=new SymbolInfo("Node","unary_expression");
			temp->setRule("unary_expression : ADDOP unary_expression");
			temp->addChild($1);
			temp->addChild($2);
			$$=temp;
			printInLog(temp->getRule());
		 }  
		 | NOT unary_expression {
			SymbolInfo *temp=new SymbolInfo("Node","unary_expression");
			temp->setRule("unary_expression : NOT unary_expression");
			temp->addChild($1);
			temp->addChild($2);
			$$=temp;
			printInLog(temp->getRule());
		 }
		 | factor {
			SymbolInfo *temp=new SymbolInfo("Node","unary_expression");
			temp->setRule("unary_expression : factor");
			temp->addChild($1);
			$$=temp;
			printInLog(temp->getRule());
		 }
		 ;
	
factor	: variable {
		SymbolInfo *temp=new SymbolInfo("Node","factor");	
		temp->setRule("factor : variable");
		temp->addChild($1);
		$$=temp;
		printInLog(temp->getRule());
	}
	| ID LPAREN argument_list RPAREN{
		SymbolInfo *temp=new SymbolInfo("Node","factor");	
		temp->setRule("factor : ID LPAREN argument_list RPAREN");
		temp->addChild($1);
		temp->addChild($2);
		temp->addChild($3);
		temp->addChild($4);
		$$ = temp;
		printInLog(temp->getRule());
	}
	| LPAREN expression RPAREN{
		SymbolInfo *temp=new SymbolInfo("Node","factor");	
		temp->setRule("factor : LPAREN expression RPAREN")	;
		temp->addChild($1);
		temp->addChild($2);
		temp->addChild($3);
		$$ = temp;
		printInLog(temp->getRule());
	}
	| CONST_INT {
		SymbolInfo *temp=new SymbolInfo("Node","factor");	
		temp->setRule("factor : CONST_INT")	;
		temp->addChild($1);
		$$ = temp;
		printInLog(temp->getRule());
	}
	| CONST_FLOAT{
		SymbolInfo *temp=new SymbolInfo("Node","factor");	
		temp->setRule("factor : CONST_FLOAT")	;
		temp->addChild($1);
		$$ = temp;
		printInLog(temp->getRule());
	}
	| variable INCOP{
		SymbolInfo *temp = new SymbolInfo("Node", "factor");
		temp->setRule("factor : variable INCOP");
		temp->addChild($1);
		temp->addChild($2);
		$$=temp;
		printInLog(temp->getRule());
	}
	| variable DECOP{
		SymbolInfo *temp = new SymbolInfo("Node", "factor");
		temp->setRule("factor : variable DECOP");
		temp->addChild($1);
		temp->addChild($2);
		$$=temp;
		printInLog(temp->getRule());
	}
	;
	
argument_list : arguments{
				SymbolInfo *temp=new SymbolInfo("Leaf","argument_list");
				temp->setRule("argument_list: arguments");
				temp->addChild($1);
				$$=temp;
				printInLog(temp->getRule());
			  }
			  |{
				SymbolInfo *temp=new SymbolInfo("Leaf","argument_list",line_count);
				temp->setEndLine(line_count);
				temp->setRule("argument_list: ");
				$$=temp;
				printInLog(temp->getRule());
				
			  }
			  |error{
				yyclearin;
				SymbolInfo *temp=new SymbolInfo("error","argument_list");
				temp->setRule("argument_list : error");
				$$=temp;

			  }
			  ;
	
arguments : arguments COMMA logic_expression{
			SymbolInfo *temp = new SymbolInfo("Node","arguments");
			temp->setRule("arguments : arguments COMMA logic_expression");
			temp->addChild($1);
			temp->addChild($2);
			temp->addChild($3);
			$$=temp;
			printInLog(temp->getRule());
		  }
	      | logic_expression{
			SymbolInfo *temp = new SymbolInfo("Node","arguments");
			temp->setRule("arguments : logic_expression");
			temp->addChild($1);
			$$=temp;
			printInLog(temp->getRule());
		  }
	      ;
 

%%
int main(int argc,char *argv[])
{
	FILE *fp;
	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}
	symbolTable=new SymbolTable(BUCKET_SIZE);
	parsetree_out.open("2005042_parseTree.txt");
	logout.open("2005042_log.txt");
	error_out.open("2005042_error.txt");
	scopetable=new ScopeTable(BUCKET_SIZE,NULL);
	yyin=fp;
	yyparse();
	cout<<"hello\n";
	//symbolTable->printAllScope(logout);
	delete symbolTable; 
	
	logout<< "Total Lines: " << line_count << '\n';
	logout<< "Total Errors: " << error_count << '\n';
	fclose(fp);
	parsetree_out.close();
	error_out.close();
	logout.close();
	return 0;
}

