#include "mainwindow.h"

#include <QApplication>
#include <csignal>

void sigHandler(int s)
{
    std::signal(s, SIG_DFL);
    qApp->quit();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //to shut down the ROS node gracefully if CTRL-C is hit
    std::signal(SIGINT,  sigHandler);
    std::signal(SIGTERM, sigHandler);

	rclcpp::init(argc,argv);
    MainWindow w;
    w.show();
	auto res=a.exec();
    rclcpp::shutdown();
    return res;
}
