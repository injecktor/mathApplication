#include "evaluator.h"

Evaluator::Evaluator() {}

void Evaluator::eval(QString str) {
    tokenizer = new Tokenizer(str);
    std::optional<QVector<Token>> tokens = tokenizer->tokenize();
    if (!tokens.has_value()) {
        qDebug() << "Tokenization gone wrong";
        return;
    }
    parser = new Parser(tokens.value());
    QString answer = parser->solve();
    if (answer == "") {
        qDebug() << "Error in parser";
    }
    emit returnEvaluation(answer);
}
