#include "tokenizer.h"

Tokenizer::Tokenizer(QString input, int mode) : m_str(input), m_mode(mode) {
    isEquation = isBitSet(Modes::equation);
}

QVector<Token> Tokenizer::tokenize() {
    QVector<Token> tokens;
    while (m_index < m_str.length()) {
        if (isError()) return {};
        QChar cur = consume();
        if (cur.isDigit()) {
            tokens.push_back({.tokenType = TokenType::number, .value = takeWholeNumber()});
        }
        else if (cur == '-') {
            if (isMinusNumber(-1)) {
                if (isError()) return {};
                tokens.push_back({.tokenType = TokenType::number, .value = takeWholeNumber()});
            }
            else {
                if (isError()) return {};
                tokens.push_back({.tokenType = TokenType::minus});
            }
        }
        else if (cur == '+') {
            tokens.push_back({.tokenType = TokenType::plus});
        }
        else if (cur == '*') {
            tokens.push_back({.tokenType = TokenType::multiplication});
        }
        else if (cur == '/') {
            tokens.push_back({.tokenType = TokenType::division});
        }
        else if (cur == '^') {
            tokens.push_back({.tokenType = TokenType::power});
        }
        else if (cur == '(') {
            tokens.push_back({.tokenType = TokenType::openParen});
        }
        else if (cur == ')') {
            tokens.push_back({.tokenType = TokenType::closeParen});
        }
        else if (cur == '|') {
            if (isOpenModule(-1)) {
                if (isError()) return {};
                tokens.push_back({.tokenType = TokenType::openModule});
            }
            else {
                if (isError()) return {};
                tokens.push_back({.tokenType = TokenType::closeModule});
            }
        }
        else if (isX(cur)) {
            checkIfEquation();
            tokens.push_back({.tokenType = TokenType::x});
        }
        else if (cur == '=') {
            checkIfEquation();
            tokens.push_back({.tokenType = TokenType::equal});
        }
        else {
            errors.push_back("Incorrect input. Code: 5");
        }
    }
    return tokens;
}

bool Tokenizer::isOpenModule(int index) {
    if (!peek(index).has_value()) {
        errors.push_back("Incorrect index in isOpenModule");
    }
    if (peek(index).value() != '|') {
        errors.push_back("Working with not a module");
    }
    else if (!peek(index - 1).has_value()) {
        return true;
    }
    else if (peek(index - 1).value().isDigit() || peek(index - 1).value() == ')') {
        return false;
    }
    else if (peek(index - 1).value() == '|') {
        if (isOpenModule(index - 1)) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (isX(index - 1)) {
        checkIfEquation();
        return false;
    }
    return true;
}

bool Tokenizer::isMinusNumber(int index) {
    if (!peek(index).has_value()) {
        errors.push_back("Incorrect index in isMinusNumber");
    }
    if (peek(index).value() != '-') {
        errors.push_back("Working with not a minus");
    }
    else if (!peek(index - 1).has_value()) {
        if (peek(index + 1).has_value()) {
            if (peek(index + 1).value().isDigit()) {
                return true;
            }
            else if (isX(index + 1)) {
                checkIfEquation();
                return false;
            }
            else {
                return false;
            }
        }
        else {
            errors.push_back("Incorrect input. Code: 7");
            return false;
        }
    }
    else if (peek(index - 1).value().isDigit() || peek(index - 1).value() == ')' || (peek(index - 1).value() == '|' && !isOpenModule(index - 1))) {
        return false;
    }
    else if (isX(index - 1)) {
        checkIfEquation();
        return false;
    }
    else if (peek(index - 1).value() == '(' || (peek(index - 1).value() == '|' && isOpenModule(index - 1)) || peek(index - 1).value() == '=') {
        if (peek(index + 1).has_value()) {
            if (peek(index + 1).value().isDigit()) {
                return true;
            }
            else if (isX(index + 1)) {
                checkIfEquation();
                return false;
            }
            else {
                return false;
            }
        }
        else {
            errors.push_back("Incorrect input. Code: 6");
        }
    }
    return true;
}

double Tokenizer::takeWholeNumber() {
    QString number;
    number += peek(-1).value();
    while (peek().has_value() && (peek().value().isDigit() || peek().value() == '.')) {
        number += consume();
    }
    return number.toDouble();
}

QChar Tokenizer::consume() {
    return m_str.at(m_index++);
}

std::optional<QChar> Tokenizer::peek(int offset) {
    if (m_index + offset >= m_str.length() || m_index + offset < 0) {
        return {};
    }
    else {
        return m_str.at(m_index + offset);
    }
}

bool Tokenizer::isBitSet(int bit) {
    if (m_mode & (1 << bit)) return true;
    return false;
}

bool Tokenizer::isX(int index) {
    if (!peek(index).has_value()) {
        errors.push_back("Incorrect index in isX");
        return true;
    }
    if (peek(index).value() == 'x') {
        return true;
    }
    return false;
}

bool Tokenizer::isX(QChar character) {
    if (character == 'x') {
        return true;
    }
    return false;
}

void Tokenizer::checkIfEquation() {
    if (!isEquation) {
        errors.push_back("It's not an equation mode");
    }
}
