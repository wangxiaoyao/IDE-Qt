#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionopen_triggered();

    void on_actionsave_triggered();

    void on_actionnew_triggered();

    void on_actionexit_triggered();

    void on_actioncopy_triggered();

    void on_actionpaste_triggered();

    void on_actioncut_triggered();

    void on_actionundo_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
