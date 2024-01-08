#ifndef TESTS_H
#define TESTS_H

#include <QString>
#include <QVector>

QVector<QString> tests = {
    "1 + 2 * ( 3 - 4 )",
    "8/2*(2+2)",
    "8 / 4*(3 - 1)",
    "(43 -8)/7+2*(34-22)-3*8/6"
};

QVector<QString> answers = {
    "-1",
    "16",
    "4",
    "25"
};

#endif // TESTS_H
