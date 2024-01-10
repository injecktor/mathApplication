#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "parser.h"

class Tokenizer : public QObject
{
    Q_OBJECT
public:
    Tokenizer(QString input);
    QVector<Token> tokenize();

private:
    QChar consume();
    std::optional<QChar> peek(int offset = 0);
    int m_index = 0;
    QString m_str;

    bool isMinusNumber(int index);
    bool isOpenModule(int index);
    double takeWholeNumber();
};

#endif // TOKENIZER_H
