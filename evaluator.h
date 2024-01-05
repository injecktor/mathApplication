#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "tokenizer.h"

class Evaluator : public QObject
{
    Q_OBJECT
public:
    Evaluator();

    QString eval(QString str);

private:
    Tokenizer* tokenizer;
    Parser* parser;
};

#endif // EVALUATOR_H
