#ifndef TESTS_H
#define TESTS_H

#include <QString>
#include <QVector>

QVector<QString> tests = {
    "1 + 2 * ( 3 - 4 )", //0
    "8/2*(2+2)",
    "8 / 4*(3 - 1)",
    "(43 -8)/7+2*(34-22)-3*8/6",
    "2^3",
    "(-1)", //5
    "5",
    "(-1)^2",
    "-1^2",
    "-1^3",
    "-(-1)", //10
    "(2/5)^2",
    "2-(-1)",
    "1^(-2)",
    "3 ^ (-3)",
    "4^(1/2)", //15
    "4^(-1/2)",
    "2^(-2)",
    "-(-(-(-(-1))))",
};

QVector<QString> answers = {
    "-1", //0
    "16",
    "4",
    "25",
    "8",
    "-1", //5
    "5",
    "1",
    "1",
    "-1",
    "1", //10
    "0.16",
    "3",
    "1",
    "0.037037",
    "2", //15
    "0.5",
    "0.25",
    "-1",
};

#endif // TESTS_H
