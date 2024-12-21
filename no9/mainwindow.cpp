#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Connect digit buttons
    for (int i = 0; i <= 9; ++i) {
        QString buttonName = "button" + QString::number(i);
        QPushButton *digitButton = findChild<QPushButton *>(buttonName);
        connect(digitButton, &QPushButton::clicked, this, &MainWindow::onDigitPressed);
    }

    // Connect clear button
    connect(ui->buttonClear, &QPushButton::clicked, this, &MainWindow::onClearPressed);

    // Connect equals button
    connect(ui->buttonEquals, &QPushButton::clicked, this, &MainWindow::onEqualsPressed);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onDigitPressed() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        ui->display->setText(ui->display->text() + button->text());
    }
}

void MainWindow::onClearPressed() {
    ui->display->clear();
}

void MainWindow::onEqualsPressed() {
    // Perform simple evaluation logic
    ui->display->setText(QString::number(currentNumber));
}
