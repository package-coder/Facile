//
// Created by CHRIS on 5/9/2022.
//

#ifndef FACILE_PARSER_H
#define FACILE_PARSER_H

#include "Scanner.h"
#include "CharList.h"
#include "SyntaxList.h"
#include <vector>
#include <any>
#include <iostream>
#include <sstream>

using namespace std;
using namespace scan;



enum class TYPE{

};

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


class ExpressionSyntax : public SyntaxNode{};

class IdentifierExpressionSyntax : public ExpressionSyntax{
    SyntaxToken* identifierToken;

public:
    IdentifierExpressionSyntax(SyntaxToken *identifierToken) : identifierToken(identifierToken) {}

    SYNTAX::TYPE getTokenType() override {
        return SYNTAX::IDENTIFIER_EXPRESSION;
    }

    vector<SyntaxNode *> getChildren() override {
        return { identifierToken };
    }

    vector<SyntaxNode *> getDataChildren() override {
        return { identifierToken };
    }

    SyntaxToken *getIdentifierToken() const {
        return identifierToken;
    }
};

class NumberExpressionSyntax : public ExpressionSyntax{
    SyntaxToken* numberToken;

public:
    NumberExpressionSyntax(SyntaxToken *numberToken) : numberToken(numberToken) {}

public:
    SYNTAX::TYPE getTokenType() override {
        return SYNTAX::NUMBER_EXPRESSION;
    }

    vector<SyntaxNode *> getChildren() override {
        return { numberToken };
    }

    vector<SyntaxNode *> getDataChildren() override {
        return { numberToken };
    }

    SyntaxToken *getNumberToken() const {
        return numberToken;
    }
};

class LiteralExpressionSyntax : public ExpressionSyntax{
    SyntaxToken* literalToken;

public:
    LiteralExpressionSyntax(SyntaxToken *literalToken) : literalToken(literalToken) {}

    SYNTAX::TYPE getTokenType() override {
        return SYNTAX::LITERAL_EXPRESSION;
    }

    vector<SyntaxNode *> getChildren() override {
        return { literalToken };
    }

    vector<SyntaxNode *> getDataChildren() override {
        return { literalToken };
    }

    SyntaxToken *getLiteralToken() const {
        return literalToken;
    }
};

class BinaryExpressionSyntax : public ExpressionSyntax{
    SyntaxToken* operatorToken;
    ExpressionSyntax* leftOperand;
    ExpressionSyntax* rightOperand;

public:
    BinaryExpressionSyntax(SyntaxToken *operatorToken, ExpressionSyntax *leftOperand, ExpressionSyntax *rightOperand)
            : operatorToken(operatorToken), leftOperand(leftOperand), rightOperand(rightOperand) {}

    SYNTAX::TYPE getTokenType() override {
        return SYNTAX::BINARY_EXPRESSION;
    }

    vector<SyntaxNode *> getChildren() override {
        return { operatorToken, leftOperand, rightOperand };
    }

    vector<SyntaxNode *> getDataChildren() override {
        return { leftOperand, rightOperand };
    }

    SyntaxToken *getOperatorToken() const {
        return operatorToken;
    }

    ExpressionSyntax *getLeftOperand() const {
        return leftOperand;
    }

    ExpressionSyntax *getRightOperand() const {
        return rightOperand;
    }
};

class ParenthesizedExpressionSyntax : public ExpressionSyntax{
    SyntaxToken* openParenthesisToken;
    ExpressionSyntax* expression;
    SyntaxToken* closeParenthesisToken;

public:
    ParenthesizedExpressionSyntax(SyntaxToken *openParenthesisToken, ExpressionSyntax *expression, SyntaxToken *closeParenthesisToken) : openParenthesisToken(
            openParenthesisToken), expression(expression), closeParenthesisToken(closeParenthesisToken) {}

    SYNTAX::TYPE getTokenType() override {
        return SYNTAX::PARENTHESIZED_EXPRESSION;
    }

    vector<SyntaxNode *> getChildren() override {
        return {openParenthesisToken, expression, closeParenthesisToken};
    }

    vector<SyntaxNode *> getDataChildren() override {
        return { expression };
    }

    SyntaxToken *getOpenToken() const {
        return openParenthesisToken;
    }

    ExpressionSyntax *getExpression() const {
        return expression;
    }

    SyntaxToken *getCloseToken() const {
        return closeParenthesisToken;
    }
};

class VariableStatementSyntax : public SyntaxNode{
    SyntaxToken* variableBlockKeyword;
    SyntaxNode* multipleVariableSyntax;

public:
    VariableStatementSyntax(SyntaxToken *variableBlockKeyword, SyntaxNode *multipleVariableSyntax)
            : variableBlockKeyword(variableBlockKeyword), multipleVariableSyntax(multipleVariableSyntax) {}

    SYNTAX::TYPE getTokenType() override {
        return SYNTAX::VARIABLE_STATEMENT;
    }

    vector<SyntaxNode *> getChildren() override {
        return {variableBlockKeyword, multipleVariableSyntax };
    }

    vector<SyntaxNode *> getDataChildren() override {
        return { multipleVariableSyntax };
    }

    SyntaxToken *getVariableBlockKeyword() const {
        return variableBlockKeyword;
    }

    SyntaxNode *getMultipleVariableSyntax() const {
        return multipleVariableSyntax;
    }
};

class CodeStatementSyntax : public SyntaxNode{
    SyntaxToken* codeKeyword;
    SyntaxToken* openBraceToken;
    vector<SyntaxNode*> statements;
    SyntaxToken* closeBraceToken;

public:
    CodeStatementSyntax(SyntaxToken *codeKeyword, SyntaxToken *openBraceToken, const vector<SyntaxNode *> &statements,
                        SyntaxToken *closeBraceToken) : codeKeyword(codeKeyword), openBraceToken(openBraceToken),
                                                        statements(statements), closeBraceToken(closeBraceToken) {}

    SYNTAX::TYPE getTokenType() override {
        return SYNTAX::CODE_STATEMENT;
    }

    vector<SyntaxNode *> getChildren() override {
        vector<SyntaxNode *> children { codeKeyword, openBraceToken };
        children.insert(children.end(), statements.begin(), statements.end());
        children.push_back(closeBraceToken);

        return children;
    }

    vector<SyntaxNode *> getDataChildren() override {
        return statements;
    }

    SyntaxToken *getCodeKeyword() const {
        return codeKeyword;
    }

    SyntaxToken *getOpenBraceToken() const {
        return openBraceToken;
    }

    const vector<SyntaxNode *> &getStatements() const {
        return statements;
    }

    SyntaxToken *getCloseBraceToken() const {
        return closeBraceToken;
    }
};

class MultipleDeclarationStatementSyntax : public SyntaxNode{
    SyntaxToken* openBraceToken;
    vector<SyntaxNode*> declarationStatements;
    SyntaxToken* closeBraceToken;

public:
    MultipleDeclarationStatementSyntax(SyntaxToken *openBraceToken, const vector<SyntaxNode *> &declarationStatements,
                                       SyntaxToken *closeBraceToken) : openBraceToken(openBraceToken),
                                                                       declarationStatements(declarationStatements),
                                                                       closeBraceToken(closeBraceToken) {}

    SYNTAX::TYPE getTokenType() override {
        return SYNTAX::MULTIPLE_DECLARATION_STATEMENT;
    }

    vector<SyntaxNode *> getChildren() override {
        vector<SyntaxNode*> children;
        children.push_back(openBraceToken);
        children.insert(children.end(), declarationStatements.begin(), declarationStatements.end());
        children.push_back(closeBraceToken);
        return children;
    }

    vector<SyntaxNode *> getDataChildren() override {
        vector<SyntaxNode*> children(declarationStatements.begin(), declarationStatements.end());
        return children;
    }

    SyntaxToken *getOpenBraceToken() const {
        return openBraceToken;
    }

    const vector<SyntaxNode *> &getDeclarationStatements() const {
        return declarationStatements;
    }

    SyntaxToken *getCloseBraceToken() const {
        return closeBraceToken;
    }
};

class DeclarationStatementSyntax : public SyntaxNode{
    SyntaxToken* dataTypeToken;
    SyntaxToken* identifierToken;
    SyntaxToken* semicolonToken;

public:

    DeclarationStatementSyntax(SyntaxToken *dataTypeToken, SyntaxToken *identifierToken, SyntaxToken *semicolonToken)
            : dataTypeToken(dataTypeToken), identifierToken(identifierToken), semicolonToken(semicolonToken) {}

    SYNTAX::TYPE getTokenType() override {
        return SYNTAX::DECLARATION_STATEMENT;
    }

    vector<SyntaxNode *> getChildren() override {
        return { dataTypeToken, identifierToken, semicolonToken };
    }

    vector<SyntaxNode *> getDataChildren() override {
        return { identifierToken };
    }

    SyntaxToken *getDataTypeToken() const {
        return dataTypeToken;
    }

    SyntaxToken *getIdentifierToken() const {
        return identifierToken;
    }

    SyntaxToken *getSemicolonToken() const {
        return semicolonToken;
    }
};

class PrintStatementSyntax : public SyntaxNode{
    SyntaxToken* printToken;
    ExpressionSyntax* expression;
    SyntaxToken* semicolonToken;

public:
    PrintStatementSyntax(SyntaxToken *printToken, ExpressionSyntax *expression, SyntaxToken *semicolonToken) : printToken(
            printToken), expression(expression), semicolonToken(semicolonToken) {}

    SYNTAX::TYPE getTokenType() override {
        return SYNTAX::PRINT_STATEMENT;
    }

    vector<SyntaxNode *> getChildren() override {
        return {printToken, expression, semicolonToken };
    }

    vector<SyntaxNode *> getDataChildren() override {
        return {expression };
    }

    SyntaxToken *getPrintToken() const {
        return printToken;
    }

    SyntaxNode *getExpression() const {
        return expression;
    }

    SyntaxToken *getSemicolonToken() const {
        return semicolonToken;
    }
};

class PutStatementSyntax : public SyntaxNode{
    SyntaxToken* putKeyword;
    ExpressionSyntax* expression;
    SyntaxToken* identifierToken;
    SyntaxToken* assignKeyword;
    SyntaxToken* semicolonToken;

public:
    PutStatementSyntax(SyntaxToken *putKeyword, ExpressionSyntax *statement, SyntaxToken *identifierToken,
                       SyntaxToken *assignKeyword, SyntaxToken *semicolonToken) : putKeyword(putKeyword),
                                                                                  expression(statement),
                                                                                  identifierToken(identifierToken),
                                                                                  assignKeyword(assignKeyword),
                                                                                  semicolonToken(semicolonToken) {}

    SYNTAX::TYPE getTokenType() override {
        return SYNTAX::PUT_STATEMENT;
    }

    vector<SyntaxNode *> getChildren() override {
        return {putKeyword, expression, assignKeyword, identifierToken, semicolonToken };
    }

    vector<SyntaxNode *> getDataChildren() override {
        return {expression, identifierToken };
    }

    SyntaxToken *getPutKeyword() const {
        return putKeyword;
    }

    SyntaxNode *getStatement() const {
        return expression;
    }

    SyntaxToken *getIdentifierToken() const {
        return identifierToken;
    }

    SyntaxToken *getAssignKeyword() const {
        return assignKeyword;
    }

    SyntaxToken *getSemicolonToken() const {
        return semicolonToken;
    }
};

class AskStatementSyntax : public SyntaxNode{
    SyntaxToken* askKeyword;
    ExpressionSyntax* identifierExpression;
    SyntaxToken* semicolonToken;

public:
    AskStatementSyntax(SyntaxToken *askKeyword, ExpressionSyntax *identifierExpression, SyntaxToken *semicolonToken) : askKeyword(
            askKeyword), identifierExpression(identifierExpression), semicolonToken(semicolonToken) {}

    SYNTAX::TYPE getTokenType() override {
        return SYNTAX::ASK_STATEMENT;
    }

    vector<SyntaxNode *> getChildren() override {
        return {askKeyword, identifierExpression, semicolonToken };
    }

    vector<SyntaxNode *> getDataChildren() override {
        return { identifierExpression };
    }

    SyntaxToken *getAskKeyword() const {
        return askKeyword;
    }

    SyntaxNode *getIdentifierToken() const {
        return identifierExpression;
    }

    SyntaxToken *getSemicolonToken() const {
        return semicolonToken;
    }
};

class SyntaxTree{
    SyntaxNode* variableStatement;
    SyntaxNode* codeStatement;
    SyntaxToken* eofToken;
public:
    SyntaxTree(SyntaxNode *variableStatement, SyntaxNode *codeStatement, SyntaxToken *eofToken) : variableStatement(
            variableStatement), codeStatement(codeStatement), eofToken(eofToken) {}

    SyntaxNode *getVariableStatement() const {
        return variableStatement;
    }

    SyntaxNode *getCodeStatement() const {
        return codeStatement;
    }

    SyntaxToken *getEofToken() const {
        return eofToken;
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
        SyntaxNode* variableStatement = parseVariableStatement();
        SyntaxNode* codeStatement = parseCodeBlockStatement();
        SyntaxToken* eofToken = moveNextTokenIfMatch(SYNTAX::EOF_TOKEN);
        return new SyntaxTree(variableStatement, codeStatement, eofToken);
    }

    SyntaxNode* parseStatement(){
        SyntaxToken *currentToken = getCurrentToken();
        switch(currentToken->getTokenType()){
            case SYNTAX::PRT_KEYWORD:
                return parsePrintStatement();
            case SYNTAX::PUT_KEYWORD:
                return parsePutStatement();
            case SYNTAX::ASK_KEYWORD:
                return parseAskStatement();
            case SYNTAX::ADD_KEYWORD:
            case SYNTAX::SUB_KEYWORD:
            case SYNTAX::MUL_KEYWORD:
            case SYNTAX::DIV_KEYWORD:
            case SYNTAX::MOD_KEYWORD:
                return parseExpression();
        }

        std::stringstream ss;
        ss << "Unexpected expression: " << SYNTAX::toString(currentToken->getTokenType());
        diagnostic.report(ss.str());
        return currentToken;
    }


    SyntaxNode* parsePrintStatement() {
        SyntaxToken* printKeyword = moveNextTokenIfMatch(SYNTAX::PRT_KEYWORD);
        ExpressionSyntax* statement = parseExpression();
        SyntaxToken* semicolon = moveNextTokenIfMatch(SYNTAX::SEMICOLON_TOKEN);
        return new PrintStatementSyntax(printKeyword, statement, semicolon);
    }

    SyntaxNode* parsePutStatement(){
        SyntaxToken* putKeyword = moveNextTokenIfMatch(SYNTAX::PUT_KEYWORD);
        ExpressionSyntax* statement = parseExpression();
        SyntaxToken* assignKeyword = moveNextTokenIfMatch(SYNTAX::IN_KEYWORD);
        SyntaxToken* identifierToken = moveNextTokenIfMatch(SYNTAX::IDENTIFIER_TOKEN);
        SyntaxToken* semicolonToken = moveNextTokenIfMatch(SYNTAX::SEMICOLON_TOKEN);

        return new PutStatementSyntax(putKeyword, statement, identifierToken, assignKeyword, semicolonToken);
    }

    SyntaxNode* parseAskStatement(){
        SyntaxToken* askKeyword = moveNextTokenIfMatch(SYNTAX::ASK_KEYWORD);
        ExpressionSyntax* identifierExpression = parseIdentifierExpression();
        SyntaxToken* semicolonToken = moveNextTokenIfMatch(SYNTAX::SEMICOLON_TOKEN);

        return new AskStatementSyntax(askKeyword, identifierExpression, semicolonToken);
    }

    ExpressionSyntax* parseExpression(){
        SyntaxToken *currentToken = getCurrentToken();

        switch (currentToken->getTokenType()) {
            case SYNTAX::ADD_KEYWORD:
            case SYNTAX::SUB_KEYWORD:
            case SYNTAX::MUL_KEYWORD:
            case SYNTAX::DIV_KEYWORD:
            case SYNTAX::MOD_KEYWORD:
                SyntaxToken* operatorToken = nextToken();
                ExpressionSyntax* leftOperand = parseExpression();
                ExpressionSyntax* rightOperand = parseExpression();
                return new BinaryExpressionSyntax(operatorToken, leftOperand, rightOperand);
        }

        return parsePrimaryExpression();
    }

    ExpressionSyntax* parsePrimaryExpression() {
        SyntaxToken *currentToken = getCurrentToken();

        switch (currentToken->getTokenType()) {
            case SYNTAX::OPEN_PARENTHESIS_TOKEN:
                return parseParenthesizedExpression();
            case SYNTAX::NUMBER_TOKEN:
                return parseNumberLiteral();
            case SYNTAX::STRING_TOKEN:
                return parseStringLiteral();
            default:
                return parseIdentifierExpression();
        }
    }

    ExpressionSyntax* parseIdentifierExpression(){
        SyntaxToken* identifierToken = moveNextTokenIfMatch(SYNTAX::IDENTIFIER_TOKEN);
        return new IdentifierExpressionSyntax(identifierToken);
    }

    ExpressionSyntax* parseParenthesizedExpression(){
        SyntaxToken* openToken = moveNextTokenIfMatch(SYNTAX::OPEN_PARENTHESIS_TOKEN);
        ExpressionSyntax* expression = parseExpression();
        SyntaxToken* closeToken = moveNextTokenIfMatch(SYNTAX::CLOSE_PARENTHESIS_TOKEN);
        return new ParenthesizedExpressionSyntax(openToken, expression, closeToken);
    }

    ExpressionSyntax* parseNumberLiteral(){
        SyntaxToken* numberToken = moveNextTokenIfMatch(SYNTAX::NUMBER_TOKEN);
        return new NumberExpressionSyntax(numberToken);
    }

    ExpressionSyntax* parseStringLiteral(){
        SyntaxToken* stringToken = moveNextTokenIfMatch(SYNTAX::STRING_TOKEN);
        return new LiteralExpressionSyntax(stringToken);
    }

    SyntaxNode* parseVariableStatement(){
        SyntaxToken* variableStatement = moveNextTokenIfMatch(SYNTAX::VARIABLE_KEYWORD);
        SyntaxNode* members = parseMultipleDeclarationStatement();
        return new VariableStatementSyntax(variableStatement, members);
    }

    SyntaxNode* parseCodeBlockStatement(){
        SyntaxToken* codeStatement = moveNextTokenIfMatch(SYNTAX::CODE_KEYWORD);
        SyntaxToken* openBraceToken = moveNextTokenIfMatch(SYNTAX::OPEN_BRACE_TOKEN);
        vector<SyntaxNode*> statements;

        while(!(checkCurrentToken(SYNTAX::CLOSE_BRACE_TOKEN) || checkCurrentToken(SYNTAX::EOF_TOKEN))){
            auto* startToken = getCurrentToken();

            SyntaxNode* members = parseStatement();
            statements.push_back(members);

            if(startToken == getCurrentToken())
                nextToken();
        }


        SyntaxToken* closeBraceToken = moveNextTokenIfMatch(SYNTAX::CLOSE_BRACE_TOKEN);

        return new CodeStatementSyntax(codeStatement, openBraceToken, statements, closeBraceToken);
    }

    SyntaxNode* parseMultipleDeclarationStatement(){

        vector<SyntaxNode*> declarations;
        SyntaxToken* openBraceToken = moveNextTokenIfMatch(SYNTAX::OPEN_BRACE_TOKEN);

        while(checkCurrentToken(SYNTAX::INT_KEYWORD)||
              checkCurrentToken(SYNTAX::STG_KEYWORD) ||
              checkCurrentToken(SYNTAX::BLN_KEYWORD)){

            auto* startToken = getCurrentToken();

            auto* variableDeclaration = parseDeclarationStatement();
            declarations.push_back(variableDeclaration);

            if(startToken == getCurrentToken())
                nextToken();

        }

        SyntaxToken* closeBraceToken = moveNextTokenIfMatch(SYNTAX::CLOSE_BRACE_TOKEN);

        return new MultipleDeclarationStatementSyntax(openBraceToken, declarations, closeBraceToken);
    }

    SyntaxNode* parseDeclarationStatement(){
        SyntaxToken* dataTypeKeyword = nextToken();
        SyntaxToken* identifierToken = moveNextTokenIfMatch(SYNTAX::IDENTIFIER_TOKEN);
        SyntaxToken* semicolonToken = moveNextTokenIfMatch(SYNTAX::SEMICOLON_TOKEN);

        return new DeclarationStatementSyntax(dataTypeKeyword, identifierToken, semicolonToken);
    }


    Diagnostic& getDiagnostic(){
        return diagnostic;
    }

};



#endif //FACILE_PARSER_H
