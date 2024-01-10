#include "tokenizer.h"

Tokenizer::Tokenizer(QString input) : m_str(input) {

}

QVector<Token> Tokenizer::tokenize() {
    QVector<Token> tokens;
    while (m_index < m_str.length()) {
        QChar cur = consume();
        if (cur.isDigit() || (m_index == 1 && cur == '-') || (cur == '(' && peek().has_value() && peek().value() == '-') ||
            (cur == '|' && peek().has_value() && peek().value() == '-')) {
            QString number;
            if (!cur.isDigit()) {
                if (cur == '(' && peek().has_value() && peek().value() == '-') {
                    if (peek(1).has_value()) {
                        if (peek(1).value().isDigit()) {
                            tokens.push_back({.tokenType = TokenType::openParen});
                            cur = consume();
                        }
                        else if (peek(1).value() == '(') {
                            tokens.push_back({.tokenType = TokenType::openParen});
                            continue;
                        }
                        else {
                            info.push_back("Incorrect input. Code: 1");
                            return {};
                        }
                    }
                    else {
                        info.push_back("Incorrect input. Code: 2");
                        return {};
                    }
                }
                else if (cur == '(' && peek().has_value() && peek().value().isDigit()) {
                    tokens.push_back({.tokenType = TokenType::openParen});
                    continue;
                }
                else if (cur == '-' && peek().has_value() && peek().value() == '(') {
                    tokens.push_back({.tokenType = TokenType::minus});
                    continue;
                }
                else if (cur == '|' && peek().has_value() && peek().value() == '-') {
                    tokens.push_back({.tokenType = TokenType::module});
                    cur = consume();
                }
                else if (cur != '-' || !peek().has_value() || !peek().value().isDigit()) {
                    info.push_back("Incorrect input. Code: 3");
                    return {};
                }
            }
            number += cur;
            while (peek().has_value() && (peek().value().isDigit() || peek().value() == '.')) {
                number += consume();
            }
            tokens.push_back({.tokenType = TokenType::number, .value = number.toDouble()});
        }
        else {
            if (cur == '+') {
                tokens.push_back({.tokenType = TokenType::plus});
                continue;
            }
            else if (cur == '-') {
                tokens.push_back({.tokenType = TokenType::minus});
                continue;
            }
            else if (cur == '*') {
                tokens.push_back({.tokenType = TokenType::multiplication});
                continue;
            }
            else if (cur == '/') {
                tokens.push_back({.tokenType = TokenType::division});
                continue;
            }
            else if (cur == '^') {
                tokens.push_back({.tokenType = TokenType::power});
                continue;
            }
            else if (cur == '(') {
                tokens.push_back({.tokenType = TokenType::openParen});
                continue;
            }
            else if (cur == ')') {
                tokens.push_back({.tokenType = TokenType::closeParen});
                continue;
            }
            else if (cur == '|') {
                tokens.push_back({.tokenType = TokenType::module});
                continue;
            }
            else {
                info.push_back("Incorrect input. Code: 5");
                return {};
            }
        }
    }
    return tokens;
}

QChar Tokenizer::consume() {
    return m_str.at(m_index++);
}

std::optional<QChar> Tokenizer::peek(int offset) {
    if (m_index + offset >= m_str.length()) {
        return {};
    }
    else {
        return m_str.at(m_index + offset);
    }
}

