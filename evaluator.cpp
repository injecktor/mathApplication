#include "evaluator.h"

Evaluator::Evaluator() {}

QString Evaluator::eval(QString str) {
    tokenizer = new Tokenizer(str.replace( " ", "" ));
    std::optional<QVector<Token>> tokens = tokenizer->tokenize();
    if (!tokens.has_value()) {
        qDebug() << "Tokenization gone wrong";
        return "";
    }
    parser = new Parser(tokens.value());
    QString answer = parser->solve();
    if (answer == "") {
        qDebug() << "Error in parser";
    }
    emit returnEvaluation(answer);
    return answer;
}
