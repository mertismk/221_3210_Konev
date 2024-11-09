#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QCryptographicHash>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <QDebug>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    QList<Transaction> transactions = loadTransactions("../../../../../transactions.txt");
    displayTransactions(transactions);
}

MainWindow::~MainWindow()
{
    delete ui;
}


QList<Transaction> MainWindow::loadTransactions(const QString &filePath) {
    QList<Transaction> transactions;
    QFile file(filePath);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString amount = in.readLine().trimmed();
            QString walletNumber = in.readLine().trimmed();
            QString date = in.readLine().trimmed();
            QString hash = in.readLine().trimmed();

            if (!amount.isEmpty() && !walletNumber.isEmpty() && !date.isEmpty() && !hash.isEmpty()) {
                transactions.append({amount, walletNumber, date, hash});
            }
            in.readLine();
        }
        file.close();
    }
    return transactions;
}


void MainWindow::displayTransactions(const QList<Transaction> &transactions) {
    ui->tableWidget->setRowCount(transactions.size());
    qDebug() << transactions.size();

    for (int i = 0; i < transactions.size(); ++i) {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(transactions[i].amount));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(transactions[i].walletNumber));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(transactions[i].date));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(transactions[i].hash));
    }
}

void MainWindow::onButtonClicked()
{
    qDebug() << "я кнопка";
}

