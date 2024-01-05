#include "parser.h"

Parser::Parser(QVector<Token> tokens) :m_tokens(tokens) {

}

bool Parser::isCorrect() {
    bool isOpenParenFound = false;
    unsigned int openParenCount = 0;
    unsigned int closeParenCount = 0;

    while (m_index < m_tokens.size()) {
        Token cur = consume();
        if (cur.tokenType == TokenType::openParen) {
            isOpenParenFound = true;
            openParenCount++;
        }
        else if (cur.tokenType == TokenType::closeParen) {
            if (isOpenParenFound) {
                closeParenCount++;
            }
            else {
                qDebug() << "Close parenthese can't be before open parenthese";
                return false;
            }
        }
    }
    if (openParenCount != closeParenCount) {
        qDebug() << "Open parenthese's count must be equal close parenthese's count";
        return false;
    }
    return true;
}

QString Parser::solve() {

}

Token Parser::consume() {
    return m_tokens.at(m_index++);
}

std::optional<Token> Parser::peek(int offset) {
    if (m_index + offset >= m_tokens.size()) {
        return {};
    }
    else {
        return m_tokens.at(m_index + offset);
    }
}
