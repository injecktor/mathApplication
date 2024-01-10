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
    openModule,
    closeModule
} TokenType;

struct Token {
    TokenType tokenType;
    std::optional<double> value;
};

extern QVector<QString> info;
extern bool isError;

class Parser
{
public:
    Parser(QVector<Token> tokens);

    bool isCorrect();
    QString solve();

private:
    int m_index = 0;
    QVector<Token> m_tokens;
    QVector<Token> numbers;
    QVector<Token> symbols;

    Token consume();
    std::optional<Token> peek(int offset = 0);

    int getPriority(Token token);
    Token makeOperation();
};

#endif // PARSER_H
