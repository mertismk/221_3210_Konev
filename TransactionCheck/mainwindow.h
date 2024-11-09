#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Transaction {
    QString amount;
    QString walletNumber;
    QString date;
    QString hash;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onButtonClicked();

private:
    Ui::MainWindow *ui;

    QList<Transaction> loadTransactions(const QString &filePath);
    void displayTransactions(const QList<Transaction> &transactions);
};

#endif // MAINWINDOW_H
