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
            if (isOpenParenFound && (openParenCount > closeParenCount)) {
                closeParenCount++;
            }
            else {
                qDebug() << "Incorrect parentheses";
                return false;
            }
        }
    }
    m_index = 0;
    if (openParenCount != closeParenCount) {
        qDebug() << "Open parenthese's count must be equal close parenthese's count";
        return false;
    }
    return true;
}

QString Parser::solve() {
    if (!isCorrect()) return "";
    QVector<Token> numbers;
    QVector<Token> symbols;
    while (m_index < m_tokens.size()) {
        Token cur = consume();
        if (cur.value.has_value()) {
            numbers.push_back(cur);
        }
        else {
            if (symbols.isEmpty()) {
                symbols.push_back(cur);
            }
            else {
                if (cur.tokenType == TokenType::openParen) {
                    symbols.push_back(cur);
                }
                else if (cur.tokenType == TokenType::closeParen) {
                    while (symbols.last().tokenType != TokenType::openParen) {
                        Token second = numbers.last();
                        numbers.pop_back();
                        Token first = numbers.last();
                        numbers.pop_back();
                        numbers.push_back(makeOperation(first, second, symbols.last()));
                        symbols.pop_back();
                    }
                    symbols.pop_back();
                }
                else if (getPriority(cur) > getPriority(symbols.last())) {
                    symbols.push_back(cur);
                }
                else if (symbols.last().tokenType == TokenType::openParen) {
                    symbols.push_back(cur);
                }
                else {
                    Token second = numbers.last();
                    numbers.pop_back();
                    Token first = numbers.last();
                    numbers.pop_back();
                    numbers.push_back(makeOperation(first, second, symbols.last()));
                    symbols.pop_back();
                    symbols.push_back(cur);
                }
            }
        }
    }
    while (!symbols.isEmpty()) {
        Token second = numbers.last();
        numbers.pop_back();
        Token first = numbers.last();
        numbers.pop_back();
        numbers.push_back(makeOperation(first, second, symbols.last()));
        symbols.pop_back();
    }
    return QString::number(numbers.at(0).value.value());
}

Token Parser::makeOperation(Token first, Token second, Token operation) {
    double result;
    switch (operation.tokenType) {
        case TokenType::plus:
            result = first.value.value() + second.value.value();
            break;
        case TokenType::minus:
            result = first.value.value() - second.value.value();
            break;
        case TokenType::multiplication:
            result = first.value.value() * second.value.value();
            break;
        case TokenType::division:
            if (second.value.value() == 0.) {
                qDebug() << "Division by 0";
                return {.tokenType = TokenType::number, .value = 0};
            }
            result = first.value.value() / second.value.value();
            break;
        case TokenType::power:
            if (first.value.value() == 0. && second.value.value() == 0.) {
                qDebug() << "0 can't be in 0 power";
                return {.tokenType = TokenType::number, .value = 0};
            }
            result = pow(first.value.value(), second.value.value());
            break;
        default:
            qDebug() << "Unknown operation";
            result = 0;
            break;
    }
    return {.tokenType = TokenType::number, .value = result};
}

int Parser::getPriority(Token token) {
    switch (token.tokenType) {
    case TokenType::plus:
        return 5;
        break;
    case TokenType::minus:
        return 5;
        break;
    case TokenType::multiplication:
        return 10;
        break;
    case TokenType::division:
        return 10;
        break;
    case TokenType::power:
        return 15;
        break;
    case TokenType::openParen:
        return 20;
        break;
    case TokenType::closeParen:
        return 20;
        break;
    case TokenType::module:
        return 20;
        break;
    default:
        qDebug() << "Incorrect token priority";
        return 0;
        break;
    }
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
