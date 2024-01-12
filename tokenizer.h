#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "parser.h"

class Tokenizer : public QObject
{
    Q_OBJECT
public:
    Tokenizer(QString input, int mode);
    QVector<Token> tokenize();

private:
    QChar consume();
    std::optional<QChar> peek(int offset = 0);
    int m_index = 0;
    QString m_str;
    int m_mode;

    bool isEquation;
    bool isTrig;

    bool isMinusNumber(int index);
    bool isOpenModule(int index);
    bool isX(int index);
    double takeWholeNumber();
    bool isBitSet(int bit);
};

#endif // TOKENIZER_H
