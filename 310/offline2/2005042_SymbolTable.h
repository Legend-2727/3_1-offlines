#include<string>
#include<fstream>
#include<iostream>
using namespace std;

class SymbolInfo{
    string name;
    string type;
    SymbolInfo* next;

public:
    SymbolInfo(string n,string t){
        this->name=n;
        this->type=t;
        next=NULL;
    }
    void setNextPointer(SymbolInfo* n){
        next = n;
    }
    SymbolInfo* getNextPointer(){
        return next;
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
    ~SymbolInfo(){
        next=NULL;
        //delete next;
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
    
    bool insert(string name,string type,ofstream &out){
        
        int index=hashFunct(name);
        if(arrSymbolInfo[index]!=NULL){
            SymbolInfo* temp,*prevTemp;
            temp=arrSymbolInfo[index];
            prevTemp=arrSymbolInfo[index];
            int secondIndex=1;
            while(temp != NULL){
                if(temp->getName()==name){
                    out<<"\t"<<name
                    <<" already exists in the current ScopeTable"<<'\n';
                    return false;
                }
                prevTemp=temp;
                temp=temp->getNextPointer();
                secondIndex++;
            }
            prevTemp->setNextPointer(new SymbolInfo(name,type));
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
    SymbolInfo* lookUp(string name,ofstream &out){
        
        int index=hashFunct(name);
        SymbolInfo *temp=arrSymbolInfo[index];
        int secondIndex=1;
        while (temp != NULL) {
            if (temp->getName()==name) {
                out<<"\t'"<<name<<"'"
                <<" found at position <"<<index+1<<", "<<secondIndex
                <<"> of ScopeTable# "<<id<<'\n';
                return temp;
            }
            temp = temp->getNextPointer();
            secondIndex++;
        }
        //out<<"\t'"<<name<<"' is not found in any of the ScopeTables."<<endl;
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
            arrSymbolInfo[index]=temp->getNextPointer();
            out<<"\tDeleted '"<<name<<"' from position <"
            <<index+1<<", "<<secondIndex<<"> of ScopeTable# "<<id<<'\n';
            delete temp;
            return true;
        }
        else{
            prevTemp=temp;
            temp=temp->getNextPointer();
            while(temp!=NULL && temp->getName()!=name){
                prevTemp=temp;
                temp=temp->getNextPointer();
                secondIndex++;
            }
            if(temp == NULL){
                out<<"\t"<<" Not found in the current ScopeTable# "<<id<<endl;
                return false;
            }
            else{
                prevTemp->setNextPointer(temp->getNextPointer());
                out<<"\tDeleted '"<<name<<"' from position <"
                <<index+1<<", "<<secondIndex<<"> of ScopeTable# "<<id<<'\n';
                delete temp;
                return true;
            }
        }
        // while (temp!=NULL) {
        //     if (temp->getName() == name) {
        //         if(prevTemp!=NULL)
        //             prevTemp->setNextPointer(temp->getNextPointer());
        //         delete temp;
        //         temp=NULL;
        //         out<<"\tDeleted '"<<name<<"' from position <"
        //         <<index+1<<", "<<secondIndex<<"> of ScopeTable# "<<id<<'\n';
        //         return true;
        //     }
        //     prevTemp=temp;
        //     temp=temp->getNextPointer();
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
                out<<" -->"<<" ("<<temp->getName()<<","<<temp->getType()<<")";
                temp=temp->getNextPointer();
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
    ~ScopeTable(){
        for(int i=0;i<total_buckets;i++){
            if(arrSymbolInfo[i]!=NULL){
                while(arrSymbolInfo[i]->getNextPointer() != NULL){
                    SymbolInfo *temp = arrSymbolInfo[i]->getNextPointer()->getNextPointer();
                    delete arrSymbolInfo[i]->getNextPointer();
                    arrSymbolInfo[i]->setNextPointer(temp);
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
    void exitScope(){
        ScopeTable *temp=currScopeTable;
        if(temp->getParentScope()==NULL){
            //out<<"\tScopeTable# "<<temp->getID()<<" cannot be deleted\n";
            return;
        }
        currScopeTable=currScopeTable->getParentScope();
        delete temp;
    }
    bool insert(string name,string type,ofstream &out){
        if(currScopeTable==NULL){
            enterScope();
        }
        return currScopeTable->insert(name,type,out);
    }
    bool Delete(string name,ofstream &out){
        return currScopeTable->Delete(name,out);
    }
    SymbolInfo* lookup(string name,ofstream &out){
        ScopeTable* temp=currScopeTable;
        SymbolInfo* tempSymbol;
        while(true){
            tempSymbol=temp->lookUp(name,out);
            if(tempSymbol!=NULL){
                return tempSymbol;
            }
            if(temp->getParentScope() == NULL){
                out<<"\t'"<<name<<"' not found in any of the ScopeTables"<<endl;
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
    ~SymbolTable(){
        ScopeTable* temp=currScopeTable;
        while(temp!=NULL){
            currScopeTable=currScopeTable->getParentScope();
            delete temp;
            temp=currScopeTable;
        }
    }
};