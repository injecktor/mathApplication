#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "tokenizer.h"

class Evaluator : public QObject
{
    Q_OBJECT
public:
    Evaluator();

public slots:
    QString eval(QString str);

signals:
    void returnEvaluation(QString);

private:
    Tokenizer* tokenizer;
    Parser* parser;
};

#endif // EVALUATOR_H
