//
// Created by CHRIS on 5/27/2022.
//

#ifndef FACILE_COMPILATION_H
#define FACILE_COMPILATION_H

#include <iostream>
#include "Parser.h"
#include "MapList.h"
using namespace std;

class Compilation{
private:
    SyntaxTree* tree;
    MapList<string, SyntaxNode*> symbolTable;

    void executeDeclaration(SyntaxNode* root){
         if(root == nullptr) return;

        auto *declarationStatementSyntax = dynamic_cast<DeclarationStatementSyntax *>(root);
        if(declarationStatementSyntax != nullptr){
            SyntaxToken *identifierToken = declarationStatementSyntax->getIdentifierToken();
            string lexeme = identifierToken->getLexeme();
            symbolTable.put(lexeme, root);
        }

        for(auto& item : root->getChildren())
            executeDeclaration(item);
    }

    void executeMain(SyntaxNode* root){
        for(auto& entry : root->getChildren()){
            auto* expression = dynamic_cast<ExpressionSyntax *>(entry);
            if(expression != nullptr)
                cout << "Result: " << executeExpression(expression) << endl;
        }
    }

    int executeExpression(ExpressionSyntax* root){
        auto *expressionSyntax = dynamic_cast<NumberExpressionSyntax *>(root);
        if(expressionSyntax != nullptr)
            return executeNumberExpression(expressionSyntax);

        auto* identifierSyntax = dynamic_cast<IdentifierExpressionSyntax *>(root);
        if(identifierSyntax != nullptr)
            return executeIdentifierExpression(identifierSyntax);

        auto* parenthesizedSyntax = dynamic_cast<ParenthesizedExpressionSyntax *>(root);
        if(parenthesizedSyntax != nullptr)
            return executeExpression(parenthesizedSyntax->getExpression());
        
        auto* binarySyntax = dynamic_cast<BinaryExpressionSyntax *>(root);
        if(binarySyntax != nullptr){
            SyntaxToken *operatorToken = binarySyntax->getOperatorToken();

            int leftOperand = executeExpression(binarySyntax->getLeftOperand());
            int rightOperand = executeExpression(binarySyntax->getRightOperand());

            switch(operatorToken->getTokenType()){
                case SYNTAX::ADD_KEYWORD:   return leftOperand + rightOperand;
                case SYNTAX::SUB_KEYWORD:   return leftOperand - rightOperand;
                case SYNTAX::MUL_KEYWORD:   return leftOperand * rightOperand;
                case SYNTAX::DIV_KEYWORD:   return leftOperand / rightOperand;
                case SYNTAX::MOD_KEYWORD:   return leftOperand % rightOperand;
            }
        }


        throw "Out of bounds exception";
    }

    int executeNumberExpression(NumberExpressionSyntax* root){
        return any_cast<int>(root->getNumberToken()->getValue());
    }

    int executeIdentifierExpression(IdentifierExpressionSyntax* root){

    }

    void run(SyntaxTree* tree){
        //executeDeclaration(tree->getVariableStatement());
        executeMain(tree->getCodeStatement());
    }


public:
//    static Compilation execute(SyntaxTree* tree){
//        Compilation().run(tree);
//    }

    static void execute(SyntaxTree* tree){
        Compilation().run(tree);
    }
};


#endif //FACILE_COMPILATION_H
