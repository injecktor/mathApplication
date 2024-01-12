#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tests.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    hideAll();
    showFrame({Frames::regularCalculatorFrame});

    m_mode = setMode({Modes::evaluation});

    evaluator = new Evaluator(m_mode);
    tokenizerThread = new QThread;
    evaluator->moveToThread(tokenizerThread);
    tokenizerThread->start();
    infoTimer = new QTimer;

    connect(evaluator, SIGNAL(returnEvaluation(QString)), this, SLOT(getEvaluation(QString)));

    isTest = true;
    testNumber = 0;

    if (isTest) {
        connect(this, SIGNAL(eval(QString)), evaluator, SLOT(eval(QString)), Qt::BlockingQueuedConnection);
        test();
    }
    else {
        connect(this, SIGNAL(eval(QString)), evaluator, SLOT(eval(QString)));
    }

    connect(infoTimer, &QTimer::timeout, this, [this]() {
        while (!info.isEmpty()) {
            ui->textInfo->append(info.first());
            info.pop_front();
        }
    });
    infoTimer->start(100);
}

void MainWindow::test() {
    if (testNumber != 0) {
        QString tmp = evaluator->eval(tests.at(testNumber));
        if (tmp == answers.at(testNumber)) {
            info.push_back("Completed test: " + QString::number(testNumber) + '\n');
        }
        else {
            info.push_back("Incorrect test: " + QString::number(testNumber) + ". Correct answer: " + answers.at(testNumber) + ". Evaluated value: " + tmp + '\n');
        }
    }
    else {
        if (tests.size() != answers.size()) {
            info.push_back("Not all tests have answer or too much answers");
            return;
        }
        for (int var = 0; var < tests.size(); ++var) {
            QString tmp = evaluator->eval(tests.at(var));
            if (tmp == answers.at(var)) {
                info.push_back("Completed test: " + QString::number(var));
            }
            else {
                info.push_back("Incorrect test: " + QString::number(var) + ". Correct answer: " + answers.at(var) + ". Evaluated value: " + tmp);
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getEvaluation(QString answer) {
    ui->display->setText(answer);
}

int MainWindow::setMode(QVector<int> modes) {
    int mode = 0;
    for (int var = 0; var < modes.size(); ++var) {
        mode |= (1 << modes.at(var));
    }
    return mode;
}

void MainWindow::on_radioRegularCalculator_released()
{
    showFrame({Frames::regularCalculatorFrame});
}

void MainWindow::on_radioEquation_released()
{
    showFrame({Frames::equationFrame});
}

void MainWindow::showFrame(QVector<int> frames) {
    hideAll();
    int frame = 0;
    for (int var = 0; var < frames.size(); ++var) {
        frame |= (1 << frames.at(var));
    }
    for (int var = 0; var < m_frameCount; ++var) {
        if (frame & (1 << var)) {
            switch(var) {
            case Frames::regularCalculatorFrame:
                ui->regularCalculatorFrame->show();
                break;
            case Frames::equationFrame:
                ui->regularCalculatorFrame->show();
                ui->equationFrame->show();
                break;
            default:
                info.push_back("Unknown frame");
                isError = true;
            }
        }
    }
}

void MainWindow::hideAll() {
    ui->regularCalculatorFrame->hide();
    ui->equationFrame->hide();
}

void MainWindow::on_evalButton_released()
{
    emit eval(ui->display->toPlainText());
}

void MainWindow::on_zeroButton_released()
{
    ui->display->setText(ui->display->toPlainText() + "0");
}

void MainWindow::on_oneButton_released()
{
    ui->display->setText(ui->display->toPlainText() + "1");
}

void MainWindow::on_twoButton_released()
{
    ui->display->setText(ui->display->toPlainText() + "2");
}

void MainWindow::on_threeButton_released()
{
    ui->display->setText(ui->display->toPlainText() + "3");
}

void MainWindow::on_fourButton_released()
{
    ui->display->setText(ui->display->toPlainText() + "4");
}

void MainWindow::on_fiveButton_released()
{
    ui->display->setText(ui->display->toPlainText() + "5");
}

void MainWindow::on_sixButton_released()
{
    ui->display->setText(ui->display->toPlainText() + "6");
}

void MainWindow::on_sevenButton_released()
{
    ui->display->setText(ui->display->toPlainText() + "7");
}

void MainWindow::on_eightButton_released()
{
    ui->display->setText(ui->display->toPlainText() + "8");
}

void MainWindow::on_nineButton_released()
{
    ui->display->setText(ui->display->toPlainText() + "9");
}

void MainWindow::on_plusButton_released()
{
    ui->display->setText(ui->display->toPlainText() + "+");
}

void MainWindow::on_minusButton_released()
{
    ui->display->setText(ui->display->toPlainText() + "-");
}

void MainWindow::on_multiplicationButton_released()
{
    ui->display->setText(ui->display->toPlainText() + "*");
}

void MainWindow::on_divisionButton_released()
{
    ui->display->setText(ui->display->toPlainText() + "/");
}

void MainWindow::on_powerButton_released()
{
    ui->display->setText(ui->display->toPlainText() + "^");
}

void MainWindow::on_dotButton_released()
{
    ui->display->setText(ui->display->toPlainText() + ".");
}

void MainWindow::on_openParenButton_released()
{
    ui->display->setText(ui->display->toPlainText() + "(");
}

void MainWindow::on_closeParenButton_released()
{
    ui->display->setText(ui->display->toPlainText() + ")");
}

void MainWindow::on_moduleButton_released()
{
    ui->display->setText(ui->display->toPlainText() + "|");
}

void MainWindow::on_piButton_released()
{
    ui->display->setText(ui->display->toPlainText() + "pi");
}

void MainWindow::on_eButton_released()
{
    ui->display->setText(ui->display->toPlainText() + "e");
}

void MainWindow::on_phiButton_released()
{
    ui->display->setText(ui->display->toPlainText() + "phi");
}

void MainWindow::on_CButton_released()
{
    ui->display->setText(ui->display->toPlainText().removeAt(ui->display->toPlainText().size() - 1));
}

void MainWindow::on_CEButton_released()
{
    ui->display->setText("");
}


void MainWindow::on_xButton_released()
{
    ui->display->setText(ui->display->toPlainText() + "x");
}


void MainWindow::on_equalButton_released()
{
    ui->display->setText(ui->display->toPlainText() + "=");
}

