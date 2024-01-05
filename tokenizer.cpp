#include "tokenizer.h"

Tokenizer::Tokenizer() {

}

QVector<Token> Tokenizer::tokenize(QString input) {
    QVector<Token> tokens;
    m_str = input.trimmed();
    while (m_index < m_str.length()) {
        QChar cur = consume();
        if (!cur.isDigit()) {
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
            else if (cur == 'p') {
                if (peek() == 'i') {
                    tokens.push_back({.tokenType = TokenType::number, .value = M_PI});
                    consume();
                    continue;
                }
                else if (peek() == 'h' && peek(1) == 'i') {
                    tokens.push_back({.tokenType = TokenType::number, .value = 1.6180339887});
                    consume();
                    consume();
                    continue;
                }
                else {
                    qDebug() << "Incorrect input";
                    return {};
                }
            }
            else if (cur == '|') {
                tokens.push_back({.tokenType = TokenType::module});
                continue;
            }
            else if (cur == 'e') {
                tokens.push_back({.tokenType = TokenType::number, .value = 2.7182818284});
                continue;
            }
            else {
                qDebug() << "Incorrect input";
                return {};
            }
        }
        else {
            QString tmp = peek(-1).value();
            while (peek().has_value() && (peek().value().isDigit() || peek().value() == '.')) {
                tmp += consume();
            }
            tokens.push_back({.tokenType = TokenType::number, .value = tmp.toDouble()});
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

