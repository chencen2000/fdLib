#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QImageReader>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_ImageBuffer = new BYTE[m_BufferSize];


    //创建共享内存文件
    m_FileSharedHandler = CreateFile(L"shared_memory",
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (m_FileSharedHandler == INVALID_HANDLE_VALUE)
    {
        //创建共享内存失败
    }
    //创建共享内存Mapping,这里会开辟空间
    m_FileMappingHandler = CreateFileMapping(
        m_FileSharedHandler,        // Use paging file - shared memory
        NULL,                       // Default security attributes
        PAGE_READWRITE,             // Allow read and write access
        0,                          // High-order DWORD of file mapping max size
        m_BufferSize,               // Low-order DWORD of file mapping max size
        L"shared_memory");          // Name of the file mapping object

    //开放共享内存文件
    m_ShareLp = MapViewOfFile(
        m_FileMappingHandler,       // Handle of the map object
        FILE_MAP_ALL_ACCESS,        // Read and write access
        0,                          // High-order DWORD of the file offset
        0,                          // Low-order DWORD of the file offset
        m_BufferSize);              // The number of bytes to map to view

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    try
    {
        //把数据拷贝到共享内存中
        clock_t starttime = clock();
        memcpy(m_ShareLp, m_ImageBuffer, m_BufferSize * sizeof(BYTE));
//        FlushViewOfFile(m_ShareLp, m_BufferSize);
        clock_t endtime = clock();
        int nCostTime = endtime - starttime;
        ui->label_3->setText(QString("Share Image Buffer CostTime:%1ms").arg(nCostTime));
    }
    catch(...)
    {
        return;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    FlushViewOfFile(m_ShareLp, m_BufferSize);
    UnmapViewOfFile(m_ShareLp);
    CloseHandle(m_FileMappingHandler);
    CloseHandle(m_FileSharedHandler);
}

void MainWindow::on_pushButton_3_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("选择图片文件"), ".", tr("Image Files(*.bmp *.jpg *.png)"));
    ui->label->setText(filePath);
    QFile file(filePath);
    if(!file.exists())
    {
        ui->label_3->setText("Image File is not exists");
        return;
    }
    QImageReader Reader;
    Reader.setFileName(filePath);
    if (Reader.canRead())
    {
        QImage Image = Reader.read();
//        Image = Image.mirrored(false, true);
        int nHeight = Image.height();
        int nWidth = Image.width();
        int nChannel = Image.depth() / 8;
        if(nHeight != 16000 || nWidth != 7296)
        {
            ui->label_3->setText("Image Size is not (16000x7296)!");
            return;
        }
        if(nChannel != 1)
        {
            ui->label_3->setText("Image is not gray!");
        }
        memcpy(m_ImageBuffer, Image.bits(), nChannel * nWidth * nHeight * sizeof(BYTE));
        ui->label_3->setText("Read Image Success");
    }
    else
    {
        ui->label_3->setText("Read Image Fail");
        return;
    }
}
