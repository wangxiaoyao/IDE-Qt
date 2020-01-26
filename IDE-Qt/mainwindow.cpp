#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QFileDialog>
#include <QString>
#include <QTextCodec>
#include <QDebug>
#define couts qDebug()


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionopen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName();
    couts <<"==="<< fileName <<"====";

    /*
    // Qstring 类型和 char* 类型。需要先转类型,或者使用QFile类
    // fromUnicode 为将QString转为char *
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    char * file = codec->fromUnicode(fileName).data();
    FILE *fp = fopen(file,"r");
    if(!fp){
        return;
    }
    couts << "文件打开成功";

    char buf[1024];
    QString txt;
    while (!feof(fp)) {
        memset(buf,0,1024);
        fgets(buf,1024,fp);
        txt += codec->toUnicode(buf);
    }
    // 我们需要将char *类型转为QString类型
    ui->textEdit->setText(txt);
    fclose(fp);
    */
    QFile file(fileName);
    bool isok = file.open(QIODevice::ReadOnly);
    if(!isok){
        couts<<"文件打开失败";
        return;
    }
    QByteArray arr;
    while (!file.atEnd()) {
        arr+= file.readLine();
    }
    ui->textEdit->setText(arr);
    file.close();
}