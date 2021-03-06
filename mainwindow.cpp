#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(600,600);
    setWindowTitle("Shy's Compressed software");
    com=new Compression();
    connect(com,&Compression::error,this,&MainWindow::clear);
    connect(com,SIGNAL(mysignal(double)),this,SLOT(myslot(double)));
    ui->progressBar->setMaximum(100);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setValue(0);
    QMenu* pFile=ui->menuBar->addMenu("帮助");
    QAction* pNew=pFile->addAction("关于此压缩软件");
    connect(pNew,&QAction::triggered,[=]()
    {
        QMessageBox::about(this,"关于此压缩软件",""
                                         "此乃数据结构课程设计。该压缩软件可能存在一些Bug(运行过程中可能会卡顿，不要点击，否则可能强退），时间原因无法全面排查，如您在使用过程有所发现，欢迎反馈。");
    });
}

MainWindow::~MainWindow()
{
    delete ui;
    delete com;
}

void MainWindow::clear()
{
    ui->lineEdit->clear();
    path.clear();
}

void MainWindow::myslot(double per)
{
    if(per>ui->progressBar->value())
        ui->progressBar->setValue(per);
}

void MainWindow::on_pushButton_open_clicked()
{
    path=QFileDialog::getOpenFileName(this,QString("选择文件"));
    ui->lineEdit->setText(path);
}



void MainWindow::on_pushButton_compression_clicked()
{
    com->zip(path);
    ui->lineEdit->clear();
    this->path.clear();
    ui->progressBar->setValue(0);
}

void MainWindow::on_pushButton_decompression_clicked()
{
    com->unzip(path);
    ui->lineEdit->clear();
    this->path.clear();
    ui->progressBar->setValue(0);
}

