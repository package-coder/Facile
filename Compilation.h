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
    MapList<string, Object*> symbolTable;
    
    

    void executeDeclaration(SyntaxNode* root){
         if(root == nullptr) return;

        if(root->getTokenType() == SYNTAX::DECLARATION_STATEMENT){
            auto *declarationStatementSyntax = dynamic_cast<DeclarationStatementSyntax *>(root);
            SyntaxToken *identifierToken = declarationStatementSyntax->getIdentifierToken();
            string lexeme = identifierToken->getLexeme();

            SyntaxToken *dataTypeToken = declarationStatementSyntax->getDataTypeToken();
            
            if(!symbolTable.contains(lexeme)){
                Object* object = nullptr;
                switch (dataTypeToken->getTokenType()) {
                    case SYNTAX::INT_KEYWORD:
                        object = new Integer(0);
                        break;
                    case SYNTAX::STG_KEYWORD:
                        object = new String("");
                        break;
                    case SYNTAX::BLN_KEYWORD:
                        object = new Boolean(false);
                        break;
                }
                symbolTable.put(lexeme, object);
            }
            else
                //TODO redeclaration of variable
                ;
        }

        for(auto& item : root->getChildren())
            executeDeclaration(item);
    }

    void executeMain(CodeStatementSyntax * root){
        for(auto& entry : root->getStatements())
            executeStatement(entry);
    }

    void executeStatement(SyntaxNode* root){
        switch(root->getTokenType()){
            case SYNTAX::PRINT_STATEMENT:
                executePrintStatement(dynamic_cast<PrintStatementSyntax *>(root));
                break;
            case SYNTAX::PUT_STATEMENT:
                executePutStatement(dynamic_cast<PutStatementSyntax *>(root));
                break;
            case SYNTAX::ASK_STATEMENT:
                executeAskStatement(dynamic_cast<AskStatementSyntax *>(root));
                break;
        }
    }

    void executePrintStatement(PrintStatementSyntax* root){
        Object *expression = executeExpression(dynamic_cast<ExpressionSyntax *>(root->getExpression()));
        cout << expression->toString();
    }

    void executePutStatement(PutStatementSyntax* root){
        ExpressionSyntax *expression = root->getExpression();
        SyntaxToken *identifierToken = root->getIdentifierToken();

        const string &key = identifierToken->getLexeme();
        Object *tableValue = getSymbolTableValue(key);
        Object *expressionResult = executeExpression(expression);
    
        if(tableValue->matchType(reinterpret_cast<Object &>(expression))){
            setSymbolTableValue(key, expressionResult);
        }

    }

    void executeAskStatement(AskStatementSyntax* root){

    }
    

    Object* executeExpression(ExpressionSyntax* expression){
        if(expression->getTokenType() == SYNTAX::BINARY_EXPRESSION){
            auto* binarySyntax = dynamic_cast<BinaryExpressionSyntax *>(expression);
            SyntaxToken *operatorToken = binarySyntax->getOperatorToken();

            Object* leftExpression = executeExpression(binarySyntax->getLeftOperand());
            Object* rightExpression = executeExpression(binarySyntax->getRightOperand());

            if(leftExpression->type() == SYNTAX::LITERAL_EXPRESSION){
                stringstream ss;
                ss << "Unexpected left expression <" << leftExpression->type() <<  "> in an arithmetic expression";
                throw ss.str();
            }

            if(rightExpression->type() == SYNTAX::LITERAL_EXPRESSION){
                stringstream ss;
                ss << "Unexpected right expression <" << leftExpression->type() <<  "> in an arithmetic expression";
                throw ss.str();
            }

            int leftOperand =  dynamic_cast<Integer *>(leftExpression)->getValue();
            int rightOperand = dynamic_cast<Integer *>(rightExpression)->getValue();

            switch(operatorToken->getTokenType()){
                case SYNTAX::ADD_KEYWORD:   return new Integer(leftOperand + rightOperand);
                case SYNTAX::SUB_KEYWORD:   return new Integer(leftOperand - rightOperand);
                case SYNTAX::MUL_KEYWORD:   return new Integer(leftOperand * rightOperand);
                case SYNTAX::DIV_KEYWORD:   return new Integer(leftOperand / rightOperand);
                case SYNTAX::MOD_KEYWORD:   return new Integer(leftOperand % rightOperand);
            }
        }

        return executePrimaryExpression(expression);
    }

    Object* executePrimaryExpression(ExpressionSyntax* expression){
        switch (expression->getTokenType()) {
            case SYNTAX::PARENTHESIZED_EXPRESSION:
                return executeParenthesizedExpression(dynamic_cast<ParenthesizedExpressionSyntax*>(expression));
            case SYNTAX::NUMBER_EXPRESSION:
                return executeNumberExpression(dynamic_cast<NumberExpressionSyntax*>(expression));
            case SYNTAX::LITERAL_EXPRESSION:
                return executeLiteralExpression(dynamic_cast<LiteralExpressionSyntax*>(expression));
            default:
                return executeIdentifierExpression(dynamic_cast<IdentifierExpressionSyntax*>(expression));
        }
    }
    
    Object* executeNumberExpression(NumberExpressionSyntax* numberExpression){
        SyntaxToken *numberToken = numberExpression->getNumberToken();
        int value = any_cast<int>(numberToken->getValue());
        return new Integer(value);
    }
    
    Object* executeLiteralExpression(LiteralExpressionSyntax* literalExpression){
        SyntaxToken *literalToken = literalExpression->getLiteralToken();
        const string &value = any_cast<string>(literalToken->getValue());
        return new String(value);
    }
    
    Object* executeParenthesizedExpression(ParenthesizedExpressionSyntax* parenthesizedExpression){
        ExpressionSyntax *expression = parenthesizedExpression->getExpression();
        return executeExpression(expression);
    }


    Object* executeIdentifierExpression(IdentifierExpressionSyntax* identifierExpression){
        SyntaxToken *identifierToken = identifierExpression->getIdentifierToken();
        const string &key = identifierToken->getLexeme();
        return getSymbolTableValue(key);
    }


    Object* getSymbolTableValue(string key){
        const optional<Object *> &optionalStatement = symbolTable.findByKey(key);
        if(!optionalStatement.has_value())
            throw "CompilationError: Unexpected Identifier Token";

        return optionalStatement.value();
    }

    void setSymbolTableValue(string key, Object* newValue){
        symbolTable.put(key, newValue);
    }

    void run(SyntaxTree* tree){
        executeDeclaration(tree->getVariableStatement());
        executeMain(dynamic_cast<CodeStatementSyntax *>(tree->getCodeStatement()));
    }
public:

    static void execute(SyntaxTree* tree){
        Compilation().run(tree);
    }
};




#endif //FACILE_COMPILATION_H
