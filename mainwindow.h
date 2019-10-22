#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include "protocol_in.h"
#include "protocol_out.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTcpSocket * socket;
    QString datafromServer;
    void clientReadData();
    void buttonClick1();
    void buttonClick2();
    void removeSession();
signals:
    void connectClosed();
};

#endif // MAINWINDOW_H
