// mainwindow.cpp
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QWidget>

void Worker::doWork() {
    // Simule un travail long
    for(int i = 0; i <= 100; i++) {
        QThread::msleep(100); // Pause de 100ms
        emit progressChanged(i);
    }
    emit finished();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Création de l'interface
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    progressBar = new QProgressBar(this);
    startButton = new QPushButton("Démarrer", this);

    layout->addWidget(progressBar);
    layout->addWidget(startButton);

    setCentralWidget(centralWidget);

    // Configuration de base
    progressBar->setRange(0, 100);

    // Connexion du bouton
    connect(startButton, &QPushButton::clicked, this, &MainWindow::startThread);
}

MainWindow::~MainWindow()
{
    if(thread && thread->isRunning()) {
        thread->quit();
        thread->wait();
    }
}

void MainWindow::startThread()
{
    // Désactive le bouton pendant le traitement
    startButton->setEnabled(false);

    // Création du thread et du worker
    thread = new QThread(this);
    worker = new Worker();
    worker->moveToThread(thread);

    // Connexions
    connect(thread, &QThread::started, worker, &Worker::doWork);
    connect(worker, &Worker::finished, thread, &QThread::quit);
    connect(worker, &Worker::finished, worker, &Worker::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    connect(worker, &Worker::progressChanged, this, &MainWindow::updateProgress);

    // Réactive le bouton quand le thread est terminé
    connect(thread, &QThread::finished, [this]() {
        startButton->setEnabled(true);
    });

    // Démarrage du thread
    thread->start();
}

void MainWindow::updateProgress(int value)
{
    progressBar->setValue(value);
}
