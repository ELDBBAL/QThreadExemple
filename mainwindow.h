// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QProgressBar>
#include <QPushButton>

class Worker : public QObject
{
    Q_OBJECT
public:
    Worker() = default;

public slots:
    void doWork();

signals:
    void progressChanged(int value);
    void finished();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startThread();
    void updateProgress(int value);

private:
    QThread* thread;
    Worker* worker;
    QProgressBar* progressBar;
    QPushButton* startButton;
};

#endif // MAINWINDOW_H
