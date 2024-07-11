#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<sstream>
#include "2005042_SymbolTable.h"
//#include "dbg.h"
using namespace std;

bool global=true;
bool codeStarted=false;
bool isMain=false;
int variable_count=0;
int argument_count=0;
int block_count=0;
int setEnd=0;
map<string,int>  localMap;
map<string,int> argumentMap;
void handleLogicExpress(ofstream &out,SymbolInfo *info);
void handleExpress(ofstream &out,SymbolInfo *node);
void handleStatements(ofstream &out,SymbolInfo *node);


void printInitial(ofstream &out){
    out<<".MODEL SMALL\n";
    out<<".STACK 1000H\n";
    out<<".Data\n";
    out<<"\tCR EQU 0DH\n";
    out<<"\tLF EQU 0AH\n";
    out<<"\tnumber DB \"00000$\"\n";
}

void handleArguments(ofstream &out,SymbolInfo *node) {
    if(node==NULL) return;
    if(node->getRule()=="arguments : arguments COMMA logic_expression"){
        handleLogicExpress(out, node->getChild()->getNext()->getNext());
        handleArguments(out, node->getChild());
    }
    else{
        handleLogicExpress(out, node->getChild());
    }
}
void handleLeftLvar(ofstream &out,SymbolInfo *node){
    if(node->getRule()=="variable : ID"){
        string id = node->getChild()->getName();
        out<<"\tPOP AX \n";
        if(localMap[id]!=0){
            out<<"\tMOV [BP - "<<localMap[id]*2<<"],AX\n";
        }
        else if(argumentMap[id]!=0)
        {
            out<<"\tMOV [BP + "<<argumentMap[id]*2+2<<"],AX\n";
        }
        else{
            out<<"\tMOV "<<id<<",AX\n";
        }
    }
    else{
        string id = node->getChild()->getName();
        handleExpress(out, node->getChild()->getNext()->getNext());
        if(localMap[id]!=0){
            out<<"\tPOP AX \n";
            out<<"\tMOV BX,2\n";
            out<<"\tMUL BX\n";
            out<<"\tADD AX,"<<localMap[id]*2<<"\n";
            out<<"\tMOV BX,BP\n";
            out<<"\tSUB BP,AX\n";
            out<<"\tPOP AX \n";
            out<<"\tMOV [BP],AX\n";
            out<<"\tMOV BP,BX\n";
        }
        // else if(argumentMap[id]!=0)
        // {
        //     out<<"\tPOP AX \n";
        //     out<<"\tMOV BX,2\n";
        //     out<<"\tMUL BX\n";
        //     out<<"\tADD AX,"<<argumentMap[id]*2<<"\n";
        //     out<<"\tMOV BX,BP\n";
        //     out<<"\tSUB BP,AX\n";
        //     out<<"\tPOP AX \n";
        //     out<<"\tMOV [BP],AX\n";
        //     out<<"\tMOV BP,BX\n";
        // }
        else{
            out<<"\tPOP AX\n";
            out<<"\tLEA SI,"<<id<<'\n';
            out<<"\tMOV BX,2\n";
            out<<"\tMUL BX\n";
            out<<"\tADD SI,AX\n";
            out<<"\tPOP AX\n";
            out<<"\tMOV [SI],AX\n";
        }
    }
}
void handleRightVar(ofstream &out,SymbolInfo *node){
    if(node->getRule()=="variable : ID"){
        string id = node->getChild()->getName();
        if(localMap[id]!=0){
            out<<"\tMOV AX, [BP - "<<localMap[id]*2<<"]\n";
            out<<"\tPUSH AX\n";
        }
        else if(argumentMap[id]!=0)
        {
            out<<"\tMOV AX, [BP + "<<argumentMap[id]*2+2<<"]\n";
            out<<"\tPUSH AX\n";
        }
        else{
            out<<"\tMOV AX, "<<id<<"\n";
            out<<"\tPUSH AX\n";
        }
    }
    else{
        string id = node->getChild()->getName();
        handleExpress(out, node->getChild()->getNext()->getNext());
        if(localMap[id]!=0){
            out<<"\tPOP AX \n";
            out<<"\tMOV BX,2\n";
            out<<"\tMUL BX\n";
            out<<"\tADD AX,"<<localMap[id]*2<<"\n";
            out<<"\tMOV BX,BP\n";
            out<<"\tSUB BP,AX\n";
            out<<"\tMOV AX,[BP]\n";
            out<<"\tPUSH AX \n";
            out<<"\tMOV BP,BX\n";
        }
        // else if(argumentMap[id]!=0)
        // {
        //     out<<"\tPOP AX \n";
        //     out<<"\tMOV BX,2\n";
        //     out<<"\tMUL BX\n";
        //     out<<"\tADD AX,"<<argumentMap[id]*2<<"\n";
        //     out<<"\tMOV BX,BP\n";
        //     out<<"\tSUB BP,AX\n";
        //     out<<"\tPOP AX \n";
        //     out<<"\tMOV [BP],AX\n";
        //     out<<"\tMOV BP,BX\n";
        // }
        else{
            out<<"\tPOP AX\n";
            out<<"\tLEA SI,"<<id<<'\n';
            out<<"\tMOV BX,2\n";
            out<<"\tMUL BX\n";
            out<<"\tADD SI,AX\n";
            out<<"\tMOV AX,[SI]\n";
            out<<"\tPUSH AX\n";
        }
    }
}
void handleFactor(ofstream &out,SymbolInfo *node){
    if(node->getRule()=="factor : CONST_INT"){
        SymbolInfo *temp=node->getChild();
        string val = temp->getName();
        out<<"\tMOV AX,"<<val<<"\n\t;Line No: "<<temp->getStartLine()<<"\n";
        out<<"\tPUSH AX\n";
    }
    else if(node->getRule()=="factor : variable"){
        handleRightVar(out,node->getChild());
    }
    else if(node->getRule()=="factor : variable INCOP"){
        handleRightVar(out,node->getChild());
        string id = node->getChild()->getName();
        if(localMap[id]!=0){
            out<<"\tMOV AX, [BP - "<<localMap[id]*2<<"]\n";
            out<<"\tINC AX\n";
            out<<"\tMOV [BP - "<<localMap[id]*2<<"],AX\n";
        }
        else if(argumentMap[id]!=0)
        {
            out<<"\tMOV AX, [BP + "<<argumentMap[id]*2+2<<"]\n";
            out<<"\tINC AX\n";
            out<<"\tMOV [BP + "<<argumentMap[id]*2+2<<"],AX\n";
        }
        else{
            out<<"\tMOV AX, "<<id<<"\n";
            out<<"\tINC AX\n";
            out<<"\tMOV "<<id<<",AX\n";
        }
    }
    else if(node->getRule()=="factor : variable DECOP"){
        handleRightVar(out,node->getChild());
        string id = node->getChild()->getName();
        if(localMap[id]!=0){
            out<<"\tMOV AX, [BP - "<<localMap[id]*2<<"]\n";
            out<<"\tDEC AX\n";
            out<<"\tMOV [BP - "<<localMap[id]*2<<"],AX\n";
        }
        else if(argumentMap[id]!=0)
        {
            out<<"\tMOV AX, [BP + "<<argumentMap[id]*2+2<<"]\n";
            out<<"\tDEC AX\n";
            out<<"\tMOV [BP + "<<argumentMap[id]*2+2<<"],AX\n";
        }
        else{
            out<<"\tMOV AX,"<<id<<"\n";
            out<<"\tDEC AX\n";
            out<<"\tMOV "<<id<<",AX\n";
        }
    }
    else if(node->getRule()=="factor : LPAREN expression RPAREN"){
        handleExpress(out,node->getChild()->getNext());
    }
    else if(node->getRule()=="factor : ID LPAREN argument_list RPAREN"){
        //cout<<"func e\n";
        SymbolInfo *func=node->getChild();
        SymbolInfo *argumentList = func->getNext()->getNext();
        SymbolInfo *temp=argumentList->getChild();
        handleArguments(out,temp);
        
        if(func->getName()=="println")
        {
            out<<"\tCALL print_output\n";
            out<<"\tCALL new_line\n";
            out<<"\tPOP AX\n";
        }
        else{
            out<<"\tCALL  "<<func->getName()<<" \n";
        }
        out<<"\tPUSH AX\n";
    }
}
void handleUnaryExpress(ofstream &out,SymbolInfo *node){
    if(node->getRule()=="unary_expression : factor"){
        handleFactor(out,node->getChild());
    }
    else if(node->getRule()=="unary_expression : ADDOP unary_expression"){
        handleUnaryExpress(out,node->getChild()->getNext());
        SymbolInfo *oper=node->getChild();
        if(oper->getName()=="-"){
            out<<"\tPOP AX\n";
            out<<"\tNEG AX\n";
            out<<"\tPUSH AX\n";
        }
    }
    else if(node->getRule()=="unary_expression : NOT unary_expression"){
        handleUnaryExpress(out,node->getChild()->getNext());
            out<<"\tPOP AX\n";
            out<<"\tNOT AX\n";
            out<<"\tPUSH AX\n";
    }
}
void evaluateTerm(ofstream &out,SymbolInfo *node){
    if(node->getRule()=="term : unary_expression"){
        handleUnaryExpress(out,node->getChild());
    }
    else{
        SymbolInfo *child1=node->getChild();
        SymbolInfo *oper = child1->getNext();
        SymbolInfo *child2= oper->getNext();
        evaluateTerm(out,child1);
        handleUnaryExpress(out,child2);
        if(oper->getName()=="*"){
            out<<"\tPOP CX\n";
            out<<"\tPOP AX\n";
            out<<"\tCWD\n";
            out<<"\tIMUL CX\n";
            out<<"\tPUSH AX\n";
        }
        else if(oper->getName()=="/"){
            out<<"\tPOP CX\n";
            out<<"\tPOP AX\n";
            out<<"\tCWD\n";
            out<<"\tIDIV CX\n";
            out<<"\tPUSH AX\n";
        }
        else{
            out<<"\tPOP CX\n";
            out<<"\tPOP AX\n";
            out<<"\tCWD\n";
            out<<"\tIDIV CX\n";
            out<<"\tPUSH DX\n";
        }
    }
}
void handleSimpleExpress(ofstream &out,SymbolInfo *node){
    if(node->getRule()=="simple_expression : term"){
        evaluateTerm(out,node->getChild());
    }
    else{
        SymbolInfo *child1=node->getChild();
        SymbolInfo *oper = child1->getNext();
        SymbolInfo *child2= oper->getNext();
        handleSimpleExpress(out,child1);
        evaluateTerm(out,child2);
        if(oper->getName()=="+"){
            out<<"\tPOP BX\n";
            out<<"\tPOP AX\n";
            out<<"\tADD AX,BX\n";
            out<<"\tPUSH AX\n";
        }
        else if(oper->getName()=="-"){
            out<<"\tPOP BX\n";
            out<<"\tPOP AX\n";
            out<<"\tSUB AX,BX\n";
            out<<"\tPUSH AX\n";
        }
    }
}
void handleRelExpress(ofstream &out,SymbolInfo *node){
    if(node->getRule()=="rel_expression : simple_expression"){
        handleSimpleExpress(out, node->getChild());
    }
    else{
        SymbolInfo *child1=node->getChild();
        SymbolInfo *oper = child1->getNext();
        SymbolInfo *child2= oper->getNext();
        handleSimpleExpress(out,child1);
        handleSimpleExpress(out,child2);
        string opName=oper->getName();
        string command;
        if(opName=="=="){
            command="JE ";
        }
        else if(opName=="<="){
            command="JLE ";
        }
        else if(opName==">="){
            command="JGE ";
        }
        else if(opName=="<"){
            command="JL ";
        }
        else if(opName==">"){
            command="JG ";
        }
        else if(opName=="!="){
            command="JNE ";
        }
        block_count++;
        out<<"\tPOP AX\n";
        out<<"\tMOV BX,AX\n";
        out<<"\tPOP AX\n";
        out<<"\tCMP AX,BX\n";
        out<<"\t"<<command<<" Label"<<block_count<<"\n";
        out<<"\tMOV AX,0\n";
        out<<"\tPUSH AX\n";
        out<<"\tJMP EndLabel"<<block_count<<'\n';
        out<<"Label"<<block_count<<":\n";
        out<<"\tMOV AX,1\n";
        out<<"\tPUSH AX\n";
        out<<"EndLabel"<<block_count<<":\n";
    }
}
void handleLogicExpress(ofstream& out,SymbolInfo *node) {
    if(node->getRule()=="logic_expression : rel_expression"){
        handleRelExpress(out, node->getChild());
    }
    else{
        SymbolInfo *child1=node->getChild();
        SymbolInfo *oper = child1->getNext();
        SymbolInfo *child2= oper->getNext();
        handleRelExpress(out,child1);
        handleRelExpress(out,child2);
        string  opName=oper->getName();
        string command;
        if (opName == "||") {
            out<<"\tPOP AX\n";
            out<<"\tCMP AX,1\n";
            out<<"\tJGE Label"<<++block_count<<":\n";
            out<<"\tPOP AX\n";
            out<<"\tCMP AX,1\n";
            out<<"\tJL Label"<<++block_count<<":\n";
            out<<"Label"<<block_count-1<<":\n";
            out<<"\tMOV AX,1\n";
            out<<"\tPUSH AX\n";
            out<<"\tJMP EndLabel"<<block_count<<"\n";
            out<<"Label"<<block_count<<":\n";
            out<<"\tMOV AX,0\n";
            out<<"\tPUSH AX\n";
            out<<"EndLabel"<<block_count<<":\n";
        }
        else if (opName == "&&") {
            out<<"\tPOP AX\n";
            out<<"\tCMP AX,1\n";
            out<<"\tJL Label"<<++block_count<<":\n";
            out<<"\tPOP AX\n";
            out<<"\tCMP AX,1\n";
            out<<"\tJGE Label"<<++block_count<<":\n";
            out<<"Label"<<block_count-1<<":\n";
            out<<"\tMOV AX,0\n";
            out<<"\tPUSH AX\n";
            out<<"\tJMP EndLabel"<<block_count<<"\n";
            out<<"Label"<<block_count<<":\n";
            out<<"\tMOV AX,1\n";
            out<<"\tPUSH AX\n";
            out<<"EndLabel"<<block_count<<":\n";
        }
    }
}
void handleExpress(ofstream &out,SymbolInfo* node) {
    //cout<<"hs\n";
    if(node->getRule()=="expression : logic_expression"){ 
        handleLogicExpress(out,node->getChild());
    }else {
        SymbolInfo *var=node->getChild();
        SymbolInfo *oper = var->getNext();
        SymbolInfo *child= oper->getNext();
        handleLogicExpress(out,child);
        handleLeftLvar(out,var);
        out<<"\tPUSH AX\n";
    }
}
void handleLocalVar(ofstream &out,SymbolInfo *node){
    cout<<node->getRule()<<endl;
    SymbolInfo *list=node->getChild()->getNext();
    Parameter *temp=list->getParameterList();
    while(temp!=NULL){
        if(temp->isArray()!=1){
            variable_count++;
            out<< "\t"<<"SUB SP,"<<2<<"\n";
            localMap[temp->getName()] = variable_count;
            temp=temp->getNext();
        }
        else{
            variable_count++;
            out<<"\tSUB SP,"<<temp->getArraySize()*2<<'\n';
            localMap[temp->getName()]=variable_count;
            variable_count+=(temp->getArraySize()-1);
            temp=temp->getNext();
        }
    }
    return;
}
void handleSingleStatement(ofstream &out,SymbolInfo *node){
    //cout<<node->getRule()<<endl;
    if(node->getRule()=="statement : var_declaration"){
        handleLocalVar(out,node->getChild());
    }
    else if(node->getRule()=="statement : expression_statement"){
        SymbolInfo *child=node->getChild();
        if(child->getRule()=="expression_statement : expression SEMICOLON"){
            handleExpress(out,child->getChild());
            out<<"\tPOP AX\n";
        }
    }
    else if(node->getRule()=="statement : compound_statement")
    {
        SymbolInfo *child=node->getChild();
        if(child->getRule()=="compound_statement : LCURL statements RCURL"){
            handleStatements(out,child->getChild()->getNext());
        }
    }
    else if(node->getRule()=="statement : IF LPAREN expression RPAREN statement")
    {
        SymbolInfo *express=node->getChild()->getNext()->getNext();
        SymbolInfo *statement=express->getNext()->getNext();
        handleExpress(out,express);
        out<<"\tPOP AX\n";
        out<<"\tCMP AX,1\n";
        int t=++block_count;
        out<<"\tJL END_IF"<<t<<'\n';
        handleSingleStatement(out,statement);
        out<<"END_IF"<<t<<":\n";
    }
    else if(node->getRule()=="statement : IF LPAREN expression RPAREN statement ELSE statement")
    {
        cout<<"if e\n";
        SymbolInfo *express1=node->getChild()->getNext()->getNext();
        SymbolInfo *statement1=express1->getNext()->getNext();
        SymbolInfo *statement2=statement1->getNext()->getNext();
        handleExpress(out,express1);
        out<<"\tPOP AX\n";
        out<<"\tCMP AX,1\n";
        int t=++block_count;
        out<<"\tJL END_IF"<<t<<'\n';
        handleSingleStatement(out,statement1);
        out<<"JMP END_ELSE"<<t<<'\n';
        out<<"END_IF"<<t<<":\n";
        handleSingleStatement(out,statement2);
        out<<"END_ELSE"<<t<<":\n";
    }
    else if(node->getRule()=="statement : WHILE LPAREN expression RPAREN statement")
    {
        //cout<<"while\n";
        SymbolInfo *expression=node->getChild()->getNext()->getNext();
        SymbolInfo *statement=expression->getNext()->getNext();
        int t = ++block_count;
        out<<"WHILE_START"<<t<<":\n";
        handleExpress(out,expression);
        out<<"\tPOP AX\n";
        out<<"\tCMP AX,1\n";
        out<<"\tJL END_WHILE"<<t<<'\n';
        handleSingleStatement(out,statement);
        out<<"\tJMP WHILE_START"<<t<<'\n';
        out<<"END_WHILE"<<t<<":\n";
    }
    else if(node->getRule()=="statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement")
    {
        
        SymbolInfo *expression_state=node->getChild()->getNext()->getNext();
        out<<"FOR_LOOP"<<++block_count<<":\n";
        out<<"\t;initialization\n";
        int t = block_count;
        if(expression_state->getRule()=="expression_statement : expression SEMICOLON"){
            cout<<"while\n";
            handleExpress(out,expression_state->getChild());
            out<<"\tPOP AX\n";
        }

        SymbolInfo *expression_state2=expression_state->getNext();
        out<<"LOOP_START"<<t<<":\n";
        if(expression_state2->getRule()=="expression_statement : expression SEMICOLON"){
            handleExpress(out,expression_state2->getChild());
        }
        SymbolInfo *statement=expression_state2->getNext()->getNext()->getNext();
        out<<"\t;validity check\n";
        out<<"\tPOP AX\n";
        out<<"\tCMP AX,1\n";
        out<<"\tJL LOOP_END"<<t<<'\n';
        handleSingleStatement(out,statement);
        out<<"\t;inc or dec\n";
        handleExpress(out,expression_state2->getNext());
        out<<"\tPOP AX\n";
        out<<"\tJMP LOOP_START"<<t<<'\n';
        out<<"LOOP_END"<<t<<":\n";
    }
    
    else if(node->getRule()=="statement : RETURN expression SEMICOLON" && !isMain){
        cout<<"ret\n";
        out<<"\t;return\n";
        handleExpress(out,node->getChild()->getNext());
        out<<"\tPOP AX\n";
        out<<"\tJMP END_FUNC"<<setEnd<<"\n";
    }
}
void handleStatements(ofstream &out,SymbolInfo *node){
    if(node==NULL) return;
    if(node->getRule()=="statements : statement"){
        out<<"\n\t;Line no: "<<node->getChild()->getStartLine()<<'\n';
        handleSingleStatement(out,node->getChild());
    }
    else{
        handleStatements(out,node->getChild());
        out<<"\n\t;Line no: "<<node->getChild()->getStartLine()<<'\n'; //error
        handleSingleStatement(out,node->getChild()->getNext());
    }
}
void traverse(ofstream &out,SymbolInfo *node){
    if(node==NULL) return;
    if(node->getType()=="statements")
    {
        //cout<<"stt\n";
        handleStatements(out,node);
        return;
    }
    //cout<<"paise\n";
    // if(node->getType()=="declaration_list"){
    //     Parameter *temp=node->getParameterList();
    //     while(temp!=NULL){
    //         variable_count++;
    //         out<< "\t"<<"SUB SP,"<<2<<"\n";
    //         localMap[temp->getName()] =variable_count;
    //         temp=temp->getNext();
    //     }
    //     return;
    // }
    SymbolInfo *temp=node;
    temp=temp->getChild();
    while(temp!=NULL)
    {
        traverse(out,temp);
        temp=temp->getNext();
    }
}
void handleVarDeclaration(ofstream &out,SymbolInfo* node){
    if (global) {
        Parameter *temp=node->getParameterList();
        while(temp!=NULL){
            //cout<<temp->isArray()<<endl;
            //cout<<"eita size "<<temp->getArraySize()<<endl;
            if(temp->isArray()==0){
                out<< "\t"<<temp->getName()<<" DW 1 DUP (0000H)\n";
            }
            else{
                out<< "\t"<<temp->getName()<<" DW "<<temp->getArraySize()<<" DUP (0000H)\n";
            }
            temp=temp->getNext();
        }
    }
}
void handleFunction(ofstream &out,SymbolInfo* node,string name){
    out<<"\tPUSH BP\n";
    out<<"\tMOV BP,SP\n";
    //cout<<node->getRule()<<endl;
    SymbolInfo *argumentList=node->getChild()->getNext()->getNext()->getNext();
    if(argumentList->getType()=="parameter_list"){
        Parameter *temp=argumentList->getParameterList();
        while(temp!=NULL){
            argumentMap[temp->getName()]=++argument_count;
            temp=temp->getNext();
        }
    }
    SymbolInfo *temp=node;
    traverse(out,temp);
}
void handleFuncDefinition(ofstream &out,SymbolInfo* node){
    if(!codeStarted){
        codeStarted=true;
        out<<".CODE\n";
    }
    setEnd=++setEnd;
    out<<node->getName()<<" PROC\n";
    handleFunction(out,node,node->getName());
    out<<"END_FUNC"<<setEnd<<":\n";
    out<<"\tADD SP,"<<variable_count*2<<'\n';
    variable_count=0;
    out<<"\tPOP BP\n";
    if(argument_count>0)
        out<<"\tRET "<<argument_count*2<<'\n';
    else 
        out<<"\tRET\n";
    out<<node->getName()<<" ENDP\n";
}
void handleMainFunc(ofstream &out,SymbolInfo* node){
    isMain=true;
    //cout<<"aise\n";
    if(!codeStarted){
        codeStarted=true;
        out<<".CODE\n";
    }
    out<<"main PROC\n";
    out<<"\tMOV AX, @DATA\n";
    out<<"\tMOV DS,AX\n";
    handleFunction(out,node,"main");
    out<<"\tADD SP,"<<variable_count*2<<'\n';
    variable_count=0;
    out<<"\tPOP BP\n";
    out<<"\tMOV AX,4CH\n";
    out<<"\tINT 21H\n";
    out<<"main ENDP\n";
    isMain=false;
}
void find_golbalVar(ofstream &out,SymbolInfo *node)
{
    if(node == NULL) return;
    SymbolInfo *temp=node;
        //dbg(temp->getRule());
        if(temp->getRule()=="unit : var_declaration"){
            //cout<<"eikhane\n";
            out<<"\n\t;Line no: "<<node->getStartLine()<<'\n';
            handleVarDeclaration(out,temp->getChild()->
                                getChild()->getNext());
            return;
        }
    temp=temp->getChild();
    while(temp!=NULL)
    {
        find_golbalVar(out,temp);
        temp=temp->getNext();
    }
}
void runRecursion(ofstream &out,SymbolInfo *root){
    if(root == NULL) return;
    SymbolInfo *temp=root;
    //cout<<temp->getRule()<<endl;
    //cout<<temp->getType()<<endl;
    // if(temp->getType()=="declaration_list"){
    //     //cout<<"eikhane\n";
    //     handleVarDeclaration(out,temp);
    //     return;
    // }
    if(temp->getType()=="func_definition"){
        if(temp->getName()=="main"){
            handleMainFunc(out,temp);
        }
        else handleFuncDefinition(out,temp);
        localMap.clear();
        variable_count=0;
        argument_count=0;
        argumentMap.clear();
        return;
    }
    temp=temp->getChild();
    while(temp!=NULL)
    {
        runRecursion(out,temp);
        temp=temp->getNext();
    }
}

void writeFinalAssembly(ofstream &out) {
    out << "new_line proc" << endl;
    out << "\tpush ax" << endl;
    out << "\tpush dx" << endl;
    out << "\tmov ah,2" << endl;
    out << "\tmov dl,0Dh" << endl;
    out << "\tint 21h" << endl;
    out << "\tmov ah,2" << endl;
    out << "\tmov dl,0Ah" << endl;
    out << "\tint 21h" << endl;
    out << "\tpop dx" << endl;
    out << "\tpop ax" << endl;
    out << "\tret" << endl;
    out << "new_line endp" << endl;

    out << "print_output proc" << endl;
    out << "\tpush ax" << endl;
    out << "\tpush bx" << endl;
    out << "\tpush cx" << endl;
    out << "\tpush dx" << endl;
    out << "\tpush si" << endl;
    out << "\tlea si,number" << endl;
    out << "\tmov bx,10" << endl;
    out << "\tadd si,4" << endl;
    out << "\tcmp ax,0" << endl;
    out << "\tjnge negate" << endl;
    out << "print:" << endl;
    out << "\txor dx,dx" << endl;
    out << "\tdiv bx" << endl;
    out << "\tmov [si],dl" << endl;
    out << "\tadd [si],'0'" << endl;
    out << "\tdec si" << endl;
    out << "\tcmp ax,0" << endl;
    out << "\tjne print" << endl;
    out << "\tinc si" << endl;
    out << "\tlea dx,si" << endl;
    out << "\tmov ah,9" << endl;
    out << "\tint 21h" << endl;
    out << "\tpop si" << endl;
    out << "\tpop dx" << endl;
    out << "\tpop cx" << endl;
    out << "\tpop bx" << endl;
    out << "\tpop ax" << endl;
    out << "\tret" << endl;
    out << "negate:" << endl;
    out << "\tpush ax" << endl;
    out << "\tmov ah,2" << endl;
    out << "\tmov dl,'-'" << endl;
    out << "\tint 21h" << endl;
    out << "\tpop ax" << endl;
    out << "\tneg ax" << endl;
    out << "\tjmp print" << endl;
    out << "print_output endp" << endl;
}

void printInAssembly(ofstream & out,SymbolInfo *root){
    printInitial(out);
    find_golbalVar(out,root);
    runRecursion(out,root);
    writeFinalAssembly(out);
    out<<"END main\n";

}
void splitter(string& line, vector<string>& words) {
    string word;
    for (char c : line) {
        if (c == ' ' || c == ',' || c=='\t') {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        } else {
            word += c;
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }
}
void generateOpt1(ofstream &out,ifstream &in){
    string line;
    string next_line;
    while(getline(in,line))
    {   
        //cout<<line<<'\n';
        vector<string> v;
        splitter(line,v);
        //dbg(v);
        //dbg(v.front(),v.back());
        if(v.empty()) continue;
        if(v.front()=="MOV")
        {
            if(!getline(in,next_line)){
                break;
            }
            vector<string> v2;
            splitter(next_line,v2);
            //dbg(v2);
            if(v2.empty()){
                out<<line<<'\n';
                continue;
            }
            if(v2.front()=="MOV"){

                if(v2.back()==v[1] && v.back()==v2[1])
                    continue;
            }
            //out<<"here\n";
            //cout<<next_line<<endl;
            out<<line<<'\n';
            out<<next_line<<'\n';
            continue;
        }
        // else if(v.front()=="MOV")
        // {
        //     if(!getline(in,next_line)){
        //         break;
        //     }
        //     vector<string> v2;
        //     splitter(next_line,v2);
        //     //dbg(v2);
        //     if(v2.empty()){
        //         out<<line<<'\n';
        //         continue;
        //     }
        //     if(v2.front()=="MOV"){

        //         if(v2.back()==v[1])
        //             continue;
        //     }
        //     //out<<"here\n";
        //     //cout<<next_line<<endl;
        //     out<<line<<'\n';
        //     out<<next_line<<'\n';
        //     continue;
        // }
        else{
            if(v.front()=="ADD" && v.back()=="0") continue;
            if(v.front()=="SUB" && v.back()=="0") continue;
            if((v.front()=="MUL" || v.back()=="DIV") && v.back()=="1") continue;
            if((v.front()=="IMUL" || v.back()=="IDIV")&& v.back()=="1") continue;
            out<<line<<'\n';
        }
    }

}
void generateOptimizedCode(ofstream &out,ifstream &in2){
    ofstream  temp("temp.txt");
    generateOpt1(temp,in2);
    temp.close() ;
    ifstream in("temp.txt");
    string line;
    string next_line;
    while(getline(in,line))
    {   
        //cout<<line<<'\n';
        vector<string> v;
        splitter(line,v);
        //dbg(v);
        //dbg(v.front(),v.back());
        if(v.empty()) continue;
        if(v.front()=="PUSH")
        {
            if(!getline(in,next_line)){
                break;
            }
            vector<string> v2;
            splitter(next_line,v2);
            //dbg(v2);
            if(v2.empty()){
                out<<line<<'\n';
                continue;
            }
            if(v2.front()=="POP"){

                if(v2.back()==v.back())
                    continue;
            }
            //out<<"here\n";
            //cout<<next_line<<endl;
            out<<line<<'\n';
            out<<next_line<<'\n';
            continue;
        }
        // else if(v.front()=="MOV")
        // {
        //     if(!getline(in,next_line)){
        //         break;
        //     }
        //     vector<string> v2;
        //     splitter(next_line,v2);
        //     //dbg(v2);
        //     if(v2.empty()){
        //         out<<line<<'\n';
        //         continue;
        //     }
        //     if(v2.front()=="MOV"){

        //         if(v2.back()==v[1])
        //             continue;
        //     }
        //     //out<<"here\n";
        //     //cout<<next_line<<endl;
        //     out<<line<<'\n';
        //     out<<next_line<<'\n';
        //     continue;
        // }
        else{
            if(v.front()=="ADD" && v.back()=="0") continue;
            if(v.front()=="SUB" && v.back()=="0") continue;
            if((v.front()=="MUL" || v.back()=="DIV") && v.back()=="1") continue;
            if((v.front()=="IMUL" || v.back()=="IDIV")&& v.back()=="1") continue;
            out<<line<<'\n';
        }
    }
}

