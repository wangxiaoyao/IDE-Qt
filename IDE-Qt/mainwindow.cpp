#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QFileDialog>
#include <QString>
#include <QTextCodec>
#include <QFileInfo>
#include <QDebug>
#define couts qDebug()


QString MainWindow::fileName = nullptr;

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

// 提取出来的保存文件函数：参数：内容和文件
void MainWindow::saveFile(const char *buf, const char *file){
    FILE *fp = fopen(file,"w");
    if(!fp){
        return;
    }
    fputs(buf,fp);
    fclose(fp);

}
void MainWindow::on_actionopen_triggered()
{
    fileName = QFileDialog::getOpenFileName();
    /*
    // Qstring 类型和 char* 类型。需要先转类型,或者使用QFile类. window下为GBK
    // 1 fromUnicode 为将QString转为char *  2 反之用toUnicode
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
void MainWindow::on_actionsave_triggered()
{
    if(fileName==nullptr){
        fileName = QFileDialog::getSaveFileName();
    }

    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    char * file = codec->fromUnicode(fileName).data();

    QString txt= ui->textEdit->toPlainText();

    // 两种方式： QString =》 char *
    char *buf = codec->fromUnicode(txt).data();
//    const char *buf = txt.toStdString().data();

    saveFile(buf,file);

    /*
    QFile file;
    file.setFileName(fileName);
    bool isok = file.open(QIODevice::WriteOnly);
    if(!isok){
        couts<<"文件打开失败";
        return;
    }
    QString str = ui->textEdit->toPlainText();
    file.write(str.toLocal8Bit());
    file.close();
    */
}

// 另存为
void MainWindow::on_actionsavesa_triggered()
{
    QString fileName = QFileDialog::getSaveFileName();
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    char * file = codec->fromUnicode(fileName).data();

    QString txt= ui->textEdit->toPlainText();
    char *buf = codec->fromUnicode(txt).data();
    saveFile(buf,file);
}

// 新建
void MainWindow::on_actionnew_triggered()
{
    QString txt = ui->textEdit->toPlainText();
    if(!txt.isEmpty()){
        ui->textEdit->clear();
    }
    fileName.clear();
}


void MainWindow::on_actionexit_triggered()__attribute__((noreturn))
{
    exit(0);
}
void MainWindow::on_actioncopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionpaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actioncut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionundo_triggered()
{
    ui->textEdit->undo();
}



void MainWindow::on_actioncompile_triggered()
{
    /*
     * 1 判断文件是否保存。
     * 2 保存：
     * 3 没有保存：
     * 4 编译： system("gcc fileName -o fileName不要.c")  以及考虑报错的情况
     */
    if(fileName==nullptr){
        fileName = QFileDialog::getSaveFileName();
        QTextCodec *codec = QTextCodec::codecForName("utf-8");
        char * file = codec->fromUnicode(fileName).data();

        QString txt= ui->textEdit->toPlainText();
        char *buf = codec->fromUnicode(txt).data();
        saveFile(buf,file);
    } else{
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        // codec->fromUnicode(fileName) 是QByteArray   => data()  成为char *
        char *file = codec->fromUnicode(fileName).data();
        QString des = fileName;
        des.replace(".c"," ");
        char *desPointer = codec->fromUnicode(des).data();
        char com[1024] = "gcc -o ";
        strcat(com,desPointer);
        strcat(com,file);
        system(com);
    }
}

void MainWindow::on_actionrun_triggered()
{
    if(fileName==nullptr){
        // 补充弹出框
        couts<< "请先保存";
        MainWindow::on_actionsave_triggered();
    }else{
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        // codec->fromUnicode(fileName) 是QByteArray   => data()  成为char *
        QString des = fileName;
        des.replace(".c","");
        char *desPointer = codec->fromUnicode(des).data();
        system(desPointer);
    }
}
