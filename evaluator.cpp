#include "evaluator.h"

Evaluator::Evaluator() {}

QString Evaluator::eval(QString str) {
    tokenizer = new Tokenizer(str);
    std::optional<QVector<Token>> tokens = tokenizer->tokenize();
    if (!tokens.has_value()) {
        qDebug() << "Tokenization gone wrong";
        return "";
    }
    parser = new Parser(tokens.value());
}
