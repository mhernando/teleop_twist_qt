#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QtGamepad/QGamepad>
#include <QtGamepad/QGamepadManager>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
enum GamepadMode {DIFF_DRIVE, OMNI1, OMNI2};
class MainWindow : public QMainWindow, public rclcpp::Node
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_Timer();
 private:
    Ui::MainWindow *ui;
    QTimer *timer=nullptr;
    QGamepad *gamepad=nullptr;
    GamepadMode gamepadmode=DIFF_DRIVE;
    void virtualGamePadControl();
    void handleGamePadStatus();
    void gamePadControl();
    //ROS2 components
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
};
#endif // MAINWINDOW_H
