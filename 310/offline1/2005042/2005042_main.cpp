#include "2005042_SymbolTable.h"


int split(string line,string word[]){
    int i = 0,j=0;
    while(line[i]==' ') i++;
    while (i<line.length()) {
        if(line[i]==' ')
        {
            j++;
            while(line[i]==' ') i++;
            continue;
        }
        word[j].push_back(line[i]);
        i++;
    }
    return j+1;  
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    string command;
    int bucketCount;
    cin>>bucketCount;
    SymbolTable symbolTable(bucketCount);
    int cmdCount=0;
    while (getline(cin,command)){
        int countOFwords=0;
        string word[10];
        countOFwords=split(command,word);

        if(word[0].size()==0) continue;
        cmdCount++;

        cout<<"Cmd "<<cmdCount<<": "<<command<<endl;
        if (word[0] == "I"){
            if(countOFwords!=3){
                cout<<"\tWrong number of arugments for the command "<<word[0]<<'\n';
                continue;
            }
            string key, value;
            key=word[1];
            value=word[2];
            symbolTable.insert(key, value);
            } 
        else if (word[0] == "L") {
            if(countOFwords!=2){ 
                cout<<"\tWrong number of arugments for the command "<<word[0]<<'\n';
                continue;
            }
            string key;
            key=word[1];
            symbolTable.lookup(key);
        }  
        else if (word[0] == "D") {
            if(countOFwords!=2){
                cout<<"\tWrong number of arugments for the command "<<word[0]<<'\n';
                continue;
            }
            string key;
            key=word[1];
            symbolTable.Delete(key);
        } 
        else if (word[0] == "P") {
            if(countOFwords!=2){ 
                cout<<"\tWrong number of arugments for the command "<<word[0]<<'\n';
                continue;
            }
            string temp;
            temp=word[1];
            if(temp=="A") symbolTable.printAllScope();
            else if(temp=="C") symbolTable.printCurrScope();
            else{
                cout<<"\tInvalid argument for the command P\n";
            }
        } 
        else if (word[0] == "S") {
            if(countOFwords!=1){ 
                cout<<"\tWrong number of arugments for the command "<<word[0]<<'\n';
                continue;
            }
            symbolTable.enterScope();
        }
        else if (word[0] == "E") {
            if(countOFwords!=1){ 
                cout<<"\tWrong number of arugments for the command "<<word[0]<<'\n';
                continue;
            }
            symbolTable.exitScope();
        }
        else if(word[0]=="Q"){
            break;
        }
        else{
            cout<<"Command not recognized: "<<word[0]<<endl;
        }
    }
}