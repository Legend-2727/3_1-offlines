#include<string>
#include<fstream>
#include<iostream>
using namespace std;
class Parameter{
    string name;
    string type;
    bool is_array=0;
    int array_size=0;
    Parameter *next;
    public:
        Parameter(string name,string type){
            this->name=name;
            this->type=type;
            next=NULL;
        }
        void setIsArray(){is_array=1;}
        void setArraySize(int size){array_size=size;}
        int getArraySize(){return array_size;}
        bool isArray(){return is_array;}
        string getName(){
            return name;
        }
        string getType(){
            return type;
        }
        void setNext(Parameter* p) {
            next = p;
        }
        Parameter* getNext(){
            return next;
        }
};
class SymbolInfo{
    string name="";
    string type="";
    SymbolInfo* child_head,*child_tail;
    SymbolInfo* next;
    string rule="";
    string data_type;
    int startLine=-1,endLine=-1;
    Parameter *param_tail=NULL,*param_head=NULL;
    int parameterCount=0;
    string returnType="";
public:
    SymbolInfo(string n,string t,int startLine,string data_type=""){
        this->name=n;
        this->type=t;
        child_head=NULL;
        child_tail=NULL;
        next=NULL;
        if(data_type.size()==0){
            this->data_type=t;
        }
        else{
            this->data_type=data_type;
        }
        this->rule=this->data_type+" : "+n;
        this->startLine=startLine;
        this->endLine=-1;
    }
    SymbolInfo(string n,string t,string d=""){
        this->name=n;
        this->type=t;
        if(d.size()==0){
            this->data_type=t;
        }
        else{
            this->data_type=d;
        }
        child_head=child_tail=NULL;
        next=NULL;
    }
    void setReturnType(string r){
        returnType=r;
    }
    string getReturnType(){
        return returnType;
    }
    void addParameterList(Parameter *p){
        if(this->param_head==NULL){
            param_head=param_tail=p;
            parameterCount++;
        }
        else{
            param_tail->setNext(p);
            param_tail=p;
            parameterCount++;
        }
        while(param_tail->getNext()!=NULL){
            param_tail=param_tail->getNext();
            parameterCount++;
        }
    }
    Parameter* getParameterList(){
        return param_head;
    }
    int getParamCount(){
        return parameterCount;
    }
    void addChild(SymbolInfo* n){
        if(child_head==NULL){
            child_head=child_tail = n;
        } 
        else{
            child_tail->next=n;
            child_tail=n;
        }
        // cout<<rule<<'\n';
        // cout<<startLine<<" "<<endLine<<"\n";
        // cout<<"\t"<<n->getRule()<<'\n';
        // cout<<"n "<<n->getStartLine()<<" "<<n->getEndLine()<<'\n';
        if(startLine<0){
            startLine=n->getStartLine();
        }
        else if(n->getStartLine()>=0){
            startLine=min(startLine,n->getStartLine());
        }
        if(endLine<0){
            if(n->getEndLine()==-1){
                endLine=startLine;
            }
            else{
                endLine=n->getEndLine();
            }
        }
        else{
            endLine=max(endLine,n->getEndLine());
        }
    }
    SymbolInfo* getNext(){
        return next;
    }
    int getStartLine(){
        return startLine;
    }
    int getEndLine(){
        return endLine;
    }
    void setStartLine(int l){
        startLine=l;
    }
    void setEndLine(int l){
        endLine=l;
    }
    SymbolInfo* getChild(){
        return child_head;
    }
    void setName(string n){
        name=n;
    }
    string getName(){
        return name;
    }
    void setType(string t){
        type=t;
    }
    string getType(){
        return type;
    }
    string getDataType(){
        return data_type;
    }
    void setDataType(string data){
        data_type=data;
    }
    string getRule(){
        return rule;
    }
    void setRule(string rule){
        this->rule=rule;
    }
    void printParameter(ofstream &out){
        Parameter *temp=param_head;
        while (temp!=NULL)
        {
            out<<temp->getName()<<" "<<temp->getType()<<endl;
            temp=temp->getNext();
        }
    }
    ~SymbolInfo(){
        SymbolInfo* temp=child_head;
        while(temp!=NULL){
            child_head=child_head->next;
            delete temp;
            temp=child_head;
        }
        delete child_head;
        delete child_tail;
        Parameter *temp2=param_head;
        while(temp2!=NULL){
            param_head=param_head->getNext();
            delete temp2;
            temp2=param_head;
        }
        delete next;
        delete param_head,param_tail;
    }
};

class ScopeTable{
    
    SymbolInfo** arrSymbolInfo;
    ScopeTable* parentScope;
    int total_buckets;
    int childCount;
    string id;


    unsigned long long SDBMHash(const string &str) {
        unsigned long long hash = 0;
        unsigned int i = 0;
        unsigned int len = str.length();

        for (i = 0; i < len; i++) {
            hash = ((str[i]) + (hash << 6) + (hash << 16) - hash);
        }
        return hash%total_buckets;
    }
    unsigned int hashFunct(const string &str){
        return (int)SDBMHash(str)%total_buckets;
    }
public:
    ScopeTable(int bucket_count,ScopeTable* parent){
        parentScope = parent;
        total_buckets = bucket_count;
        childCount=0;
        arrSymbolInfo=new SymbolInfo*[total_buckets];
        for(int i=0;i<total_buckets;i++){
            arrSymbolInfo[i]=NULL;
        }
        setId(parent);
        //out<<"\tScopeTable# "<<id<<" created\n";
    }
    
    bool insert(string name,string type,string data_type,int line,ofstream &out){
        
        int index=hashFunct(name);
        if(arrSymbolInfo[index]!=NULL){
            SymbolInfo* temp,*prevTemp;
            temp=arrSymbolInfo[index];
            prevTemp=arrSymbolInfo[index];
            int secondIndex=1;
            while(temp != NULL){
                if(temp->getName()==name){
                    if(type!="FUNCTION"){
                            if(temp->getDataType()==data_type || temp->getType()==type){
                            out<<"Line# "<<line
                            <<": Redefinition of parameter '"<<name<<"'"<<'\n';
                            return false;
                        }
                        else if(temp->getType()!=type){
                            out<<"Line# "<<line
                            <<": '"<<name<<"' redeclared as different kind of symbol"<<'\n';
                            return false;
                        }
                    }
                    else{
                        if(temp->getDataType()!=data_type){
                        out<<"Line# "<<line
                        <<": Conflicting types for '"<<name<<"'"<<'\n';
                        }
                        else{
                            out<<"Line# "<<line
                            <<": Redefinition of function '"<<name<<"'"<<'\n';
                            return false;
                        }
                    return false;
                    }
                }
                prevTemp=temp;
                temp=temp->getChild();
                secondIndex++;
            }
            prevTemp->addChild(new SymbolInfo(name,type,data_type));
            //out<<"\tInserted  at position <"<<index+1<<", "<<secondIndex
            //<<"> of ScopeTable# "<<id<<'\n';
            return true;
        }
        else{
            arrSymbolInfo[index]= new SymbolInfo(name,type);
            //out<<"\tInserted  at position <"<<index+1<<", 1> of ScopeTable# "<<id<<'\n';
            return true;
        }
    }

    void setId(ScopeTable* parent){
        if(parent==NULL){
            id="1";
            return;
        }
        string temp=parent->getID();
        temp.push_back('.');
        string temp2=to_string(parentScope->getChildCount()+1);
        id=temp+temp2;
    }
    string getID(){
        return id;
    }
    int getChildCount(){
        return childCount;
    }
    void increaseChildCount(){
        childCount+=1;
    }
    SymbolInfo* lookUp(string name){
        
        int index=hashFunct(name);
        SymbolInfo *temp=arrSymbolInfo[index];
        int secondIndex=1;
        while (temp != NULL) {
            if (temp->getName()==name) {
                // out<<"\t'"<<name<<"'"
                // <<" found at position <"<<index+1<<", "<<secondIndex
                // <<"> of ScopeTable# "<<id<<'\n';
                return temp;
            }
            temp = temp->getChild();
            secondIndex++;
        }
        return NULL;
    }

    bool Delete(string name,ofstream &out){
        int index=hashFunct(name);
        SymbolInfo *temp=arrSymbolInfo[index];
        SymbolInfo *prevTemp=NULL;
        int secondIndex=1;

        if(temp==NULL){
            out<<"\t"<<"Not found in the current ScopeTable# "<<id<<endl;
            return false;
        }
        else if(temp->getName()==name){
            arrSymbolInfo[index]=temp->getChild();
            out<<"\tDeleted '"<<name<<"' from position <"
            <<index+1<<", "<<secondIndex<<"> of ScopeTable# "<<id<<'\n';
            delete temp;
            return true;
        }
        else{
            prevTemp=temp;
            temp=temp->getChild();
            while(temp!=NULL && temp->getName()!=name){
                prevTemp=temp;
                temp=temp->getChild();
                secondIndex++;
            }
            if(temp == NULL){
                out<<"\t"<<" Not found in the current ScopeTable# "<<id<<endl;
                return false;
            }
            else{
                prevTemp->addChild(temp->getChild());
                out<<"\tDeleted '"<<name<<"' from position <"
                <<index+1<<", "<<secondIndex<<"> of ScopeTable# "<<id<<'\n';
                delete temp;
                return true;
            }
        }
        // while (temp!=NULL) {
        //     if (temp->getName() == name) {
        //         if(prevTemp!=NULL)
        //             prevTemp->addChild(temp->getChild());
        //         delete temp;
        //         temp=NULL;
        //         out<<"\tDeleted '"<<name<<"' from position <"
        //         <<index+1<<", "<<secondIndex<<"> of ScopeTable# "<<id<<'\n';
        //         return true;
        //     }
        //     prevTemp=temp;
        //     temp=temp->getChild();
        //     secondIndex++;
        // }
        // out<<"\t'"<<name<<"' is not present in this ScopeTable# "<<id<<endl;
        // return false;
    }

    void print(ofstream &out){
        out<<"\tScopeTable# "<<id<<'\n';
        for(int i=0;i<total_buckets;i++){
            out<<'\t'<<i+1;
            SymbolInfo *temp=arrSymbolInfo[i];
            while (temp!=NULL) {
                if(temp->getType()=="FUNCTION")
                {
                    out<<" -->"<<" ("<<temp->getName()<<",FUNCTION,"<<temp->getDataType()<<")";
                }
                else out<<" -->"<<" ("<<temp->getName()<<","<<temp->getDataType()<<")";
                temp=temp->getChild();
            }
            out<<"\n";
        }
    }
    void setParentScope(ScopeTable * parent){
        parentScope=parent;
    }
    ScopeTable* getParentScope(){
        return parentScope;
    }
    SymbolInfo* getArraySymbol(int i){
        return arrSymbolInfo[i];
    }
    void addSymbol(SymbolInfo *info){
        
    }
    ~ScopeTable(){
        for(int i=0;i<total_buckets;i++){
            if(arrSymbolInfo[i]!=NULL){
                while(arrSymbolInfo[i]->getChild() != NULL){
                    SymbolInfo *temp = arrSymbolInfo[i]->getChild()->getChild();
                    delete arrSymbolInfo[i]->getChild();
                    arrSymbolInfo[i]->addChild(temp);
                }
                delete arrSymbolInfo[i];
            }
        }
        delete [] arrSymbolInfo;
        //out<<"\tScopeTable# "<<id<<" deleted"<<'\n';
    }
};

class SymbolTable{
    ScopeTable* currScopeTable=NULL;
    int bucketCount;
public:
    SymbolTable(int b){
        bucketCount=b;
        enterScope();
    }
    void enterScope(){
        if(currScopeTable==NULL){
            string initID=to_string(0);
            currScopeTable=new ScopeTable(bucketCount,NULL);
            return;
        }
        ScopeTable *temp=new ScopeTable(bucketCount,currScopeTable);
        currScopeTable->increaseChildCount();
        temp->setParentScope(currScopeTable);
        currScopeTable=temp;
    }
    // void copyScope(ScopeTable *sc,ofstream &out){
    //     enterScope();
    //     for(int i=0;i<bucketCount;i++){
    //         SymbolInfo *temp=sc->getArraySymbol(i);
    //         while (temp!=NULL) {
    //             insert(temp->getName(),temp->getType(),out);
    //             temp=temp->getChild();
    //         }
    //     }
    // }
    void exitScope(){   
        ScopeTable *temp=currScopeTable;
        if(temp->getParentScope()==NULL){
            //out<<"\tScopeTable# "<<temp->getID()<<" cannot be deleted\n";
            return;
        }
        currScopeTable=currScopeTable->getParentScope();
        delete temp;
    }
    bool insert(string name,string type,string data_type,int line,ofstream &out){
        if(currScopeTable==NULL){
            enterScope();
        }
        return currScopeTable->insert(name,type,data_type,line,out);
    }
    
    bool Delete(string name,ofstream &out){
        return currScopeTable->Delete(name,out);
    }
    SymbolInfo* lookup(string name,int line,ofstream &out){
        ScopeTable* temp=currScopeTable;
        SymbolInfo* tempSymbol;
        while(true){
            tempSymbol=temp->lookUp(name);
            if(tempSymbol!=NULL){
                return tempSymbol;
            }
            if(temp->getParentScope() == NULL){
                out<<"Line# "<<line<<"Undeclared variable "<<name<<endl;
                return NULL;
            }
            temp=temp->getParentScope();
        }
    }
    void printCurrScope(ofstream &out){
        currScopeTable->print(out);
    }
    void printAllScope(ofstream &out){
        ScopeTable* temp=currScopeTable;
        while (temp != NULL){
            //out<<"\tScopeTable# "<<temp->getID()<<'\n';
            temp->print(out);
            temp = temp -> getParentScope();
        }
    }
    void addSymbol(SymbolInfo *s){
        currScopeTable->addSymbol(s);
    }
    ~SymbolTable(){
        ScopeTable* temp=currScopeTable;
        while(temp!=NULL){
            currScopeTable=currScopeTable->getParentScope();
            delete temp;
            temp=currScopeTable;
        }
    }
};