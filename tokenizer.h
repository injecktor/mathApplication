#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <QString>
#include <QObject>
#include <QVector>
#include <optional>
#include <QtMath>
#include <QDebug>
#include <ctype.h>
#include <stdio.h>

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

class Tokenizer : public QObject
{
    Q_OBJECT
public:
    Tokenizer();
    QVector<Token> tokenize(QString input);
private:
    QChar consume();
    std::optional<QChar> peek(int offset = 0);
    unsigned int m_index = 0;
    QString m_str;
};

#endif // TOKENIZER_H
