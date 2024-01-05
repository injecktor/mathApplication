#include "evaluator.h"

Evaluator::Evaluator() {}

QString Evaluator::eval(QString str) {
    tokenizer = new Tokenizer(str);
    std::optional<QVector<Token>> tokens = tokenizer->tokenize();
    if (tokens.has_value()) {
        parser = new Parser(tokens.value());
    }
}
