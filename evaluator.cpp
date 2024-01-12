#include "evaluator.h"

Evaluator::Evaluator(int mode): m_mode(mode) {
    isEquation = isBitSet(Modes::equation);
}

QString Evaluator::eval(QString str) {
    QString string = str.replace( " ", "" );
    string = string.replace("pi", QString::number(3.1415926535));
    string = string.replace("phi", QString::number(1.6180339887));
    string = string.replace("e", QString::number(2.7182818284));
    if (string == "") {
        return "";
    }
    info.push_back("Evaluating: " + string);
    tokenizer = new Tokenizer(string, m_mode);
    QVector<Token> tokens = tokenizer->tokenize();
    if (tokens.isEmpty()) {
        info.push_back("Tokenization gone wrong");
        return "";
    }
    parser = new Parser(tokens, m_mode);
    QString answer = parser->solve();
    if (answer == "") {
        info.push_back("Error in parser");
    }
    info.push_back("Answer: " + answer + '\n');
    emit returnEvaluation(answer);
    return answer;
}

bool Evaluator::isBitSet(int bit) {
    if (m_mode & (1 << bit)) return true;
    return false;
}
