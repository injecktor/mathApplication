#include "parser.h"

QVector<QString> info;
QVector<QString> errors;

Parser::Parser(QVector<Token> tokens, int mode) :m_tokens(tokens), m_mode(mode) {

}

bool Parser::isCorrect() {
    bool isOpenParenFound = false;
    bool isOpenModuleFound = false;

    unsigned int openParenCount = 0;
    unsigned int closeParenCount = 0;
    unsigned int openModuleCount = 0;
    unsigned int closeModuleCount = 0;

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
                errors.push_back("Incorrect parentheses");
                return false;
            }
        }
        else if (cur.tokenType == TokenType::openModule) {
            isOpenModuleFound = true;
            openModuleCount++;
        }
        else if (cur.tokenType == TokenType::closeModule) {
            if (isOpenModuleFound && (openModuleCount > closeModuleCount)) {
                closeModuleCount++;
            }
            else {
                errors.push_back("Incorrect modules");
                return false;
            }
        }
        else if (cur.tokenType == TokenType::equal) {
            if (openParenCount != closeParenCount) {
                errors.push_back("Incorrect parentheses");
                return false;
            }
            else if (openModuleCount != closeModuleCount) {
                errors.push_back("Incorrect modules");
                return false;
            }
        }
    }
    m_index = 0;
    if (openParenCount != closeParenCount) {
        errors.push_back("Open parenthese's count must be equal close parenthese's count");
        return false;
    }
    return true;
}

QString Parser::solve() {
    if (!isCorrect()) return "";
    while (m_index < m_tokens.size()) {
        if (isError()) return "";
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
                        if (numbers.size() > 1) {
                            numbers.push_back(makeOperation());
                            if (isError()) return "";
                        }
                        else {
                            numbers.last().value.value() *= -1;
                            symbols.pop_back();
                        }
                    }
                    symbols.pop_back();
                }
                else if (cur.tokenType == TokenType::openModule){
                    symbols.push_back(cur);
                }
                else if (cur.tokenType == TokenType::closeModule) {
                    while (symbols.last().tokenType != TokenType::openModule) {
                        if (numbers.size() > 1) {
                            numbers.push_back(makeOperation());
                            if (isError()) return "";
                        }
                        else {
                            numbers.last().value.value() *= -1;
                            symbols.pop_back();
                        }
                    }
                    numbers.last().value.value() = abs(numbers.last().value.value());
                    symbols.pop_back();
                }
                else if (getPriority(cur) > getPriority(symbols.last())) {
                    if (isError()) return "";
                    symbols.push_back(cur);
                }
                else if (symbols.last().tokenType == TokenType::openParen) {
                    symbols.push_back(cur);
                }
                else if (symbols.last().tokenType == TokenType::openModule) {
                    symbols.push_back(cur);
                }
                else {
                    numbers.push_back(makeOperation());
                    if (isError()) return "";
                    symbols.push_back(cur);
                }
            }
        }
    }
    while (!symbols.isEmpty()) {
        if (symbols.size() == 1 && symbols.at(0).tokenType == TokenType::minus && numbers.size() == 1) {
            numbers[0].value.value() *= -1;
            symbols.pop_back();
        }
        else {
            numbers.push_back(makeOperation());
            if (isError()) return "";
        }
    }
    return QString::number(numbers.at(0).value.value());
}

Token Parser::makeOperation() {
    Token second = numbers.last();
    numbers.pop_back();
    Token first = numbers.last();
    numbers.pop_back();
    Token operation = symbols.last();
    symbols.pop_back();
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
                errors.push_back("Division by 0");
                return {};
            }
            result = first.value.value() / second.value.value();
            break;
        case TokenType::power:
            if (first.value.value() == 0. && second.value.value() == 0.) {
                errors.push_back("0 can't be in 0 power");
                return {};
            }
            result = pow(first.value.value(), second.value.value());
            break;
        default:
            errors.push_back("Unknown operation");
            return {};
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
    case TokenType::openModule:
        return 20;
        break;
    case TokenType::closeModule:
        return 20;
        break;
    default:
        errors.push_back("Incorrect token priority");
        return 0;
        break;
    }
}

Token Parser::consume() {
    return m_tokens.at(m_index++);
}

std::optional<Token> Parser::peek(int offset) {
    if (m_index + offset >= m_tokens.size() || m_index + offset < 0) {
        return {};
    }
    else {
        return m_tokens.at(m_index + offset);
    }
}

bool Parser::isBitSet(int bit) {
    if (m_mode & (1 << bit)) return true;
    return false;
}

bool isError() {
    if (errors.size() == 0) {
        return false;
    }
    return true;
}
