#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <QObject>
#include <QVector>
#include <optional>
#include <QtMath>
#include <QDebug>

typedef enum {
    evaluation = 0,
    equation,
    trig
} Modes;

typedef enum {
    number = 0,
    plus,
    minus,
    multiplication,
    division,
    power,
    openParen,
    closeParen,
    openModule,
    closeModule,
    equal,
    x
} TokenType;

struct Token {
    TokenType tokenType;
    std::optional<double> value;
};

extern QVector<QString> info;
extern QVector<QString> errors;
extern bool isError();


class Parser
{
public:
    Parser(QVector<Token> tokens, int mode);

    bool isCorrect();
    QString solve();

private:
    int m_index = 0;
    QVector<Token> m_tokens;
    QVector<Token> numbers;
    QVector<Token> symbols;
    int m_mode;

    bool isEquation;
    bool isTrig;

    Token consume();
    std::optional<Token> peek(int offset = 0);
    int getPriority(Token token);
    Token makeOperation();
    bool isBitSet(int bit);
};

#endif // PARSER_H
