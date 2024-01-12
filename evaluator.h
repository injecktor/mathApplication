#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "tokenizer.h"

class Evaluator : public QObject
{
    Q_OBJECT
public:
    Evaluator(int mode);

public slots:
    QString eval(QString str);

signals:
    void returnEvaluation(QString);

private:
    Tokenizer* tokenizer;
    Parser* parser;
    int m_mode;

    bool isEquation;

    bool isBitSet(int bit);
};

#endif // EVALUATOR_H
