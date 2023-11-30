#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(on_Timer()));
    // msec
    timer->start(1000);
    publisher_=std::make_shared<TwistPublisher>();
}

MainWindow::~MainWindow()
{
    timer->stop();

    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
publisher_->publish_message();
}
void MainWindow::on_Timer()
{
    qDebug("Hi!");
    rclcpp::spin_some	(publisher_);
}
