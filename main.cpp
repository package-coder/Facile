#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

#include "Scanner.h"
#include "CharList.h"
#include "SyntaxType.h"
#include "Compilation.h"
#include "Parser.h"

using namespace std;

/*
*
*	Developer: Christian Paul Pujado
* 	C++ Version: ISO C++ 17
*
*/

void print(SyntaxNode* node, string space = ""){
    auto* token = (SyntaxToken*) &node;

    cout << space << "<" << SYNTAX::toString(node->getTokenType()) << ">";


    cout << endl;
    space += "\t";

    for(auto& item : node->getChildren())
        print(item, space);
}

void print(MapList<string, SyntaxToken*> symbolTable){
    for(auto& item : symbolTable.list()){
        cout << "identifier: " << item.first << "\t token_type: " << SYNTAX::toString(item.second->getTokenType()) << endl;
    }
}

MapList<string, SyntaxToken*> generateList(const vector<SyntaxNode *>& data){
    MapList<string, SyntaxToken*> symbolTable;

    for(auto& entry : data){
        SyntaxToken* syntaxToken = (SyntaxToken*)entry->getDataChildren().front();
        string key = syntaxToken->getLexeme();
        symbolTable.put(key, syntaxToken);
    }

    return symbolTable;
}

void printErrors(vector<string> errors){
    for(auto& error : errors){
        cout << error << endl;
    }
}



int main()
{

    ifstream file(R"(C:\Users\CHRIS\CLionProjects\Facile\pujado.go)");

    CharList charList;
    SyntaxList keywordList;



    //(int)std::any_cast<KW_CODES>(var->value)

    if (!file) {

        cerr << "== File not found! ==" << endl;
        return 1;
    }

    stringstream str;
    str << file.rdbuf();

    while(true){

        string input;
        cout << ">> ";
        getline(cin, input);

        if(input.empty()) break;

        Parser parser(input);
        SyntaxTree* syntaxTree = parser.parse();
        Diagnostic diagnostic = parser.getDiagnostic();

        if(diagnostic.any()){
            printErrors(diagnostic.getErrors());
        }
        else {
            print((SyntaxNode *) syntaxTree->getVariableStatement()); //variable block
            cout << endl;
            print((SyntaxNode *) syntaxTree->getCodeStatement()); //code block

            Compilation::execute(syntaxTree);
        }
        cout << endl << endl;
    }


    return 0;
}
