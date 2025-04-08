#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(&socket_, &QAbstractSocket::connected, this, &MainWindow::doCoonnected);
    QObject::connect(&socket_, &QAbstractSocket::disconnected, this, &MainWindow::doDisConnected);
    QObject::connect(&socket_, &QIODevice::readyRead, this, &MainWindow::doReadyRead);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::doCoonnected(){
    QString msg = "connected\r\n";
    ui->pteMessage->insertPlainText(msg);
}

void MainWindow::doDisConnected(){
    QString msg = "disconnected\r\n";
    ui->pteMessage->insertPlainText(msg);
}

void MainWindow::doReadyRead(){
    QString msg = socket_.readAll();
    ui->pteMessage->insertPlainText(msg);
}

void MainWindow::on_pbConnect_clicked()
{
    QString host = ui->leHost->text();
    quint16 port = ui->lePort->text().toUShort();

    if (ui->rbTcp->isChecked()) {
        socket_.connectToHost(host, port);  // TCP 연결
    } else if (ui->rbSsl->isChecked()) {
        socket_.connectToHostEncrypted(host, port);  // SSL 연결
    }
}

void MainWindow::on_pbDIsconnect_clicked()
{
    socket_.disconnectFromHost();
}

void MainWindow::on_pbSend_clicked()
{
    socket_.write(ui->pteSend->toPlainText().toUtf8());
}

void MainWindow::on_pbClear_clicked()
{
    ui->pteMessage->clear();  // 화면 지우기
}
