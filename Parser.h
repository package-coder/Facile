//
// Created by CHRIS on 5/9/2022.
//

#ifndef FACILE_PARSER_H
#define FACILE_PARSER_H

#include "Scanner.h"
#include "CharList.h"
#include <vector>
#include <any>
#include <iostream>
#include <sstream>

using namespace std;
using namespace scan;

class Diagnostic{
    std::vector<string> errors;
public:
    void report(string msg){
        errors.push_back(msg);
    }

    bool any(){
        return !errors.empty();
    }

    std::vector<string> getErrors(){
        return errors;
    }
};

class SyntaxNode {
public:
    virtual SYNTAX::TYPE getTokenType() = 0;
    virtual std::vector<SyntaxNode*> getChildren() = 0;
    virtual std::vector<SyntaxNode*> getDataChildren() = 0;

    friend ostream &operator<<(ostream &os, const SyntaxNode &node) {
        return os;
    }
};

class SyntaxToken : public SyntaxNode {
    SYNTAX::TYPE tokenType;
    std::string lexeme;
    std::any value;
    int position;
    bool isPresent;

public:
    SyntaxToken(SYNTAX::TYPE tokenType, int position)
        : tokenType(tokenType), position(position) {
        this->value = NULL;
        this->isPresent = false;
    }

    SyntaxToken(SYNTAX::TYPE tokenType, std::string lexeme, std::any value, int position)
            : tokenType(tokenType), lexeme(lexeme), value(value), position(position) {
        this->isPresent = true;
    }

    SYNTAX::TYPE getTokenType() override {
        return tokenType;
    }

    vector<SyntaxNode*> getChildren() override {
        return {};
    }

    vector<SyntaxNode *> getDataChildren() override {
        return {};
    }

    const string &getLexeme() const {
        return lexeme;
    }

    const any &getValue() const {
        return value;
    }

    int getPosition() const {
        return position;
    }

    bool isEmpty() const {
        return !isPresent;
    }

    friend ostream &operator<<(ostream &os, const SyntaxToken &token) {
        os << static_cast<const SyntaxNode &>(token) << " tokenType: " << token.tokenType << " lexeme: " << token.lexeme
           << " value: " << token.value.has_value() << " position: " << token.position << " isPresent: " << token.isPresent;
        return os;
    }
};

class Syntax : public SyntaxNode {};

class NumberExpressionSyntax : public Syntax {
    SyntaxToken *numberToken;
public:

    NumberExpressionSyntax(SyntaxToken *numberToken) : numberToken(numberToken) {}

    SYNTAX::TYPE getTokenType() override {
        return SYNTAX::NUMBER_TOKEN;
    };

    vector<SyntaxNode*> getChildren() override {
        return {};
    };

    vector<SyntaxNode *> getDataChildren() override {
        return { numberToken };
    }
};

class VariableBlockSyntax : public Syntax{
    SyntaxToken* variableBlockKeyword;
    Syntax* multipleVariableSyntax;

public:

    VariableBlockSyntax(SyntaxToken *variableBlockKeyword, Syntax *multipleVariableSyntax) : variableBlockKeyword(
            variableBlockKeyword), multipleVariableSyntax(multipleVariableSyntax) {}

    SYNTAX::TYPE getTokenType() override {
        return SYNTAX::VARIABLE_BLOCK;
    }

    vector<SyntaxNode *> getChildren() override {
        return {variableBlockKeyword, multipleVariableSyntax };
    }

    vector<SyntaxNode *> getDataChildren() override {
        return { multipleVariableSyntax };
    }
};

class CodeBlockSyntax : public Syntax{
    SyntaxToken* openBraceToken;
    vector<Syntax*> variableExpression;
    SyntaxToken* closeBraceToken;

public:
    CodeBlockSyntax(SyntaxToken *openBraceToken, const vector<Syntax *> &variableExpression,
                    SyntaxToken *closeBraceToken) : openBraceToken(openBraceToken),
                                                    variableExpression(variableExpression),
                                                    closeBraceToken(closeBraceToken) {}

    SYNTAX::TYPE getTokenType() override {
        return SYNTAX::CODE_BLOCK;
    }

    vector<SyntaxNode *> getChildren() override {
        vector<SyntaxNode*> children;
        children.push_back(openBraceToken);
        children.insert(children.end(), variableExpression.begin(), variableExpression.end());
        children.push_back(closeBraceToken);
        return children;
    }

    vector<SyntaxNode *> getDataChildren() override {
        vector<SyntaxNode*> children(variableExpression.begin(), variableExpression.end());
        return children;
    }
};

class MultipleVariableDeclarationSyntax : public Syntax{
    SyntaxToken* openBraceToken;
    vector<Syntax*> variableExpression;
    SyntaxToken* closeBraceToken;

public:
    MultipleVariableDeclarationSyntax(SyntaxToken *openBraceToken, const vector<Syntax *> &variableExpression,
                                      SyntaxToken *closeBraceToken) : openBraceToken(openBraceToken),
                                                                      variableExpression(variableExpression),
                                                                      closeBraceToken(closeBraceToken) {}

    SYNTAX::TYPE getTokenType() override {
        return SYNTAX::MULTIPLE_VARIABLE_DECLARATION;
    }

    vector<SyntaxNode *> getChildren() override {
        vector<SyntaxNode*> children;
        children.push_back(openBraceToken);
        children.insert(children.end(), variableExpression.begin(), variableExpression.end());
        children.push_back(closeBraceToken);
        return children;
    }

    vector<SyntaxNode *> getDataChildren() override {
        vector<SyntaxNode*> children(variableExpression.begin(), variableExpression.end());
        return children;
    }
};

class VariableDeclarationSyntax : public Syntax{
    SyntaxToken* dataTypeToken;
    SyntaxToken* identifierToken;
    SyntaxToken* semicolonToken;

public:

    VariableDeclarationSyntax(SyntaxToken *dataTypeToken, SyntaxToken *identifierToken, SyntaxToken *semicolonToken)
            : dataTypeToken(dataTypeToken), identifierToken(identifierToken), semicolonToken(semicolonToken) {}

    SYNTAX::TYPE getTokenType() override {
        return SYNTAX::VARIABLE_DECLARATION;
    }

    vector<SyntaxNode *> getChildren() override {
        return { dataTypeToken, identifierToken, semicolonToken };
    }

    vector<SyntaxNode *> getDataChildren() override {
        return { identifierToken };
    }
};

class StringLiteralExpressionSyntax : public Syntax{
    SyntaxToken* openDollar;
    SyntaxToken* stringToken;
    SyntaxToken* closeDollar;

public:
    StringLiteralExpressionSyntax(SyntaxToken *openDollar, SyntaxToken *stringToken, SyntaxToken *closeDollar)
            : openDollar(openDollar), stringToken(stringToken), closeDollar(closeDollar) {}

    SYNTAX::TYPE getTokenType() override {
        return SYNTAX::STRING_LITERAL_EXPRESSION;
    }

    vector<SyntaxNode *> getChildren() override {
        return {openDollar, stringToken, closeDollar};
    }

    vector<SyntaxNode *> getDataChildren() override {
        return { stringToken };
    }
};

class PrintStatementSyntax : public Syntax{
    SyntaxToken* printToken;
    Syntax* statement;

public:
    PrintStatementSyntax(SyntaxToken *printToken, Syntax *statement) : printToken(printToken), statement(statement) {}

    SYNTAX::TYPE getTokenType() override {
        return SYNTAX::PRINT_STATEMENT;
    }

    vector<SyntaxNode *> getChildren() override {
        return { printToken, statement };
    }

    vector<SyntaxNode *> getDataChildren() override {
        return { statement };
    }
};

class SyntaxTree{
    Syntax* root;
    SyntaxToken* eofToken;
public:

    SyntaxTree(Syntax *root, SyntaxToken *eofToken) : root(root), eofToken(eofToken) {}

    Syntax *getRoot() const {
        return root;
    }

    void setRoot(Syntax *root) {
        this->root = root;
    }

    SyntaxToken *getEofToken() const {
        return eofToken;
    }

    void setEofToken(SyntaxToken *eofToken) {
        this->eofToken = eofToken;
    }

};

class Parser
{
    vector<SyntaxToken*> tokens;
    unsigned long position = 0;
    unsigned long offset = 0;
    SyntaxList syntaxList;
    Diagnostic diagnostic;

private:
    SyntaxToken* getCurrentToken(){
        return peek(offset);
    }

    SyntaxToken* nextToken(){
        SyntaxToken* current = getCurrentToken();
        position++;
        return current;
    }

    SyntaxToken* moveNextTokenIfMatch(SYNTAX::TYPE expectedType){
        auto* currentToken = getCurrentToken();

        if(currentToken->getTokenType() == expectedType)
            return nextToken();

        //Report error
        std::stringstream ss;
        ss << "Unexpected <" << SYNTAX::toString(currentToken->getTokenType()) << "> in length "
             << currentToken->getPosition() << "; Expected <" << SYNTAX::toString(expectedType) << ">";
        diagnostic.report(ss.str());

        auto* expectedToken =new SyntaxToken(expectedType, currentToken->getPosition());
        nextToken();
        return expectedToken;
    }

    bool checkCurrentToken(SYNTAX::TYPE expectedType){
        auto* currentToken = getCurrentToken();
        return currentToken->getTokenType() == expectedType;
    }

    std::any parseValue(string value, SYNTAX::TYPE tokenCode){
        switch (tokenCode) {
            case SYNTAX::NUMBER_TOKEN:      return stoi(value);
            case SYNTAX::STRING_TOKEN:      return value;
            default:                        return NULL;
        }
    }

    SyntaxToken* peek(unsigned long offset){
        unsigned long index = this->position + offset;
        if(index >= tokens.size())
            return tokens.back();

        return tokens.at(index);
    }

public:
    Parser(string source) {
        Scanner scanner(source, CharList());
        SYNTAX::TYPE tokenType;


        do {
            tokenType = scanner.next_token();
            std::string lexeme = scanner.lexeme_string();

            if(syntaxList.contains(lexeme))
                tokenType = syntaxList.get(lexeme);
            else if(tokenType == SYNTAX::WORD_TOKEN)
                tokenType = SYNTAX::IDENTIFIER_TOKEN;

            std::any value = parseValue(lexeme, tokenType);

            auto* syntaxToken = new SyntaxToken(tokenType, lexeme, value, scanner.get_position());
            tokens.push_back(syntaxToken);


        } while (tokenType != SYNTAX::EOF_TOKEN);
    }

    SyntaxTree* parse(){
        Syntax* variableBlockImplementation = parseVariableBlockImplementation();
        SyntaxToken* eofToken = moveNextTokenIfMatch(SYNTAX::EOF_TOKEN);
        return new SyntaxTree(variableBlockImplementation, eofToken);
    }



    Syntax* parseStatement(){
        SyntaxToken *currentToken = getCurrentToken();
        switch(currentToken->getTokenType()){
            case SYNTAX::PRT_KEYWORD:
                return parsePrintStatement();

        }
    }

    Syntax* parsePrintStatement() {
        SyntaxToken* printKeyword = moveNextTokenIfMatch(SYNTAX::PRT_KEYWORD);
        auto* statement = dynamic_cast<Syntax *>(parseStatementValue());
        return new PrintStatementSyntax(printKeyword, statement);
    }


    SyntaxNode* parseStatementValue() {
        SyntaxToken *currentToken = getCurrentToken();
        switch(currentToken->getTokenType()){
            case SYNTAX::IDENTIFIER_TOKEN:
            case SYNTAX::NUMBER_TOKEN:
            case SYNTAX::STRING_TOKEN:
                return nextToken();
        }
    }

    Syntax* parseVariableBlockImplementation(){
        SyntaxToken* variableBlockKeyword = moveNextTokenIfMatch(SYNTAX::VARIABLE_KEYWORD);
        Syntax* members = parseMultipleVariableDeclaration();
        return new VariableBlockSyntax(variableBlockKeyword, members);
    }

    Syntax* parseNumberExpression(){
        SyntaxToken* numberToken = moveNextTokenIfMatch(SYNTAX::NUMBER_TOKEN);
        return new NumberExpressionSyntax(numberToken);
    }

    Syntax* parseMultipleVariableDeclaration(){

        vector<Syntax*> declarations;
        SyntaxToken* openBraceToken = moveNextTokenIfMatch(SYNTAX::OPEN_BRACE_TOKEN);

        while(checkCurrentToken(SYNTAX::INT_KEYWORD)||
              checkCurrentToken(SYNTAX::STG_KEYWORD) ||
              checkCurrentToken(SYNTAX::BLN_KEYWORD)){

            auto* startToken = getCurrentToken();

            auto* variableDeclaration = parseVariableDeclaration();
            declarations.push_back(variableDeclaration);

            if(startToken == getCurrentToken())
                nextToken();

        }

        SyntaxToken* closeBraceToken = moveNextTokenIfMatch(SYNTAX::CLOSE_BRACE_TOKEN);

        return new MultipleVariableDeclarationSyntax(openBraceToken, declarations, closeBraceToken);
    }

    Syntax* parseVariableDeclaration(){

        SYNTAX::TYPE expectedDataType;
        auto* currentToken = getCurrentToken();

        switch (currentToken->getTokenType()) {
            case SYNTAX::INT_KEYWORD:
                expectedDataType = SYNTAX::INT_KEYWORD;
                break;
            case SYNTAX::STG_KEYWORD:
                expectedDataType = SYNTAX::STG_KEYWORD;
                break;
            case SYNTAX::BLN_KEYWORD:
                expectedDataType = SYNTAX::BLN_KEYWORD;
                break;
        }

        SyntaxToken* dataTypeKeyword = moveNextTokenIfMatch(expectedDataType);
        SyntaxToken* identifierToken = moveNextTokenIfMatch(SYNTAX::IDENTIFIER_TOKEN);
        SyntaxToken* semicolonToken = moveNextTokenIfMatch(SYNTAX::SEMICOLON_TOKEN);

        return new VariableDeclarationSyntax(dataTypeKeyword, identifierToken, semicolonToken);
    }

    Diagnostic& getDiagnostic(){
        return diagnostic;
    }

};



#endif //FACILE_PARSER_H
