#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QPushButton>
#include <QThread>

#include "tokenizer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_zeroButton_released();
    void on_oneButton_released();
    void on_twoButton_released();
    void on_threeButton_released();
    void on_fourButton_released();
    void on_fiveButton_released();
    void on_sixButton_released();
    void on_sevenButton_released();
    void on_eightButton_released();
    void on_nineButton_released();
    void on_plusButton_released();
    void on_minusButton_released();
    void on_multiplicationButton_released();
    void on_divisionButton_released();
    void on_powerButton_released();
    void on_dotButton_released();
    void on_openParenButton_released();
    void on_closeParenButton_released();
    void on_moduleButton_released();
    void on_piButton_released();
    void on_eButton_released();
    void on_phiButton_released();
    void on_CButton_released();
    void on_CEButton_released();

    void on_evalButton_released();

private:
    Ui::MainWindow *ui;

    Tokenizer* tokenizer;

    QThread* tokenizerThread;
};
#endif // MAINWINDOW_H
