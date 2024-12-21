#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onDigitPressed();
    void onClearPressed();
    void onEqualsPressed();

private:
    Ui::MainWindow *ui;
    double currentNumber = 0.0;
    QString pendingOperator;
};

#endif // MAINWINDOW_H
