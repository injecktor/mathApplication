#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <QObject>
#include <QVector>
#include <optional>
#include <QtMath>
#include <QDebug>

typedef enum {
    number,
    plus,
    minus,
    multiplication,
    division,
    power,
    openParen,
    closeParen,
    module
} TokenType;

struct Token {
    TokenType tokenType;
    std::optional<double> value;
};

class Parser
{
public:
    Parser(QVector<Token> tokens);

    bool isCorrect();
    QString solve();

private:
    unsigned int m_index = 0;
    QVector<Token> m_tokens;

    Token consume();
    std::optional<Token> peek(int offset = 0);
};

#endif // PARSER_H