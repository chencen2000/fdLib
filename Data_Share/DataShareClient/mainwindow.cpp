#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->label->setText(" ");
    try
    {
        HANDLE FileMappingHandler = OpenFileMapping(
            FILE_MAP_ALL_ACCESS,
            NULL,
            L"shared_memory");

        LPVOID LpBase = MapViewOfFile(
            FileMappingHandler,
            FILE_MAP_ALL_ACCESS,
            0,
            0,
            0);
        BYTE *ShareBuffer = (BYTE *)LpBase;

        HObject ho_ShareImage;
        GenImage1Extern(&ho_ShareImage, "byte", 7296, 16000, (Hlong)ShareBuffer, NULL);
        WriteImage(ho_ShareImage, "bmp",0, "ShareImage.bmp");
        ui->label->setText("Read Success!");
        UnmapViewOfFile(LpBase);
        CloseHandle(FileMappingHandler);
    }
    catch(...)
    {
        return;
    }
}
