#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <windows.h>
#include "HalconCpp.h"

using namespace HalconCpp;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    std::string m_StrText;
    unsigned char * m_ImageBuffer;
    unsigned long m_BufferSize = 16000 * 7296 * 1;

    HANDLE m_FileSharedHandler;
    HANDLE m_FileMappingHandler;
    LPVOID m_ShareLp;

};

#endif // MAINWINDOW_H
