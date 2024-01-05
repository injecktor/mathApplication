#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "parser.h"

class Tokenizer : public QObject
{
    Q_OBJECT
public:
    Tokenizer(QString input);

public slots:
    QVector<Token> tokenize();

private:
    QChar consume();
    std::optional<QChar> peek(int offset = 0);
    unsigned int m_index = 0;
    QString m_str;
};

#endif // TOKENIZER_H
