#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), Node("teleop_twist_qt")
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(on_Timer()));
    // msec
    timer->start(100);
    //publisher reg
    publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
}

MainWindow::~MainWindow()
{
    timer->stop();

    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    auto message = geometry_msgs::msg::Twist();
    ui->joyPadL->setX(0);
    ui->joyPadL->setY(0);
    ui->joyPadR->setX(0);
    ui->joyPadR->setY(0);
    RCLCPP_INFO(this->get_logger(), "STOPPING cmd_vel = 000000");
    publisher_->publish(message);
}
void MainWindow::on_Timer()
{

    rclcpp::spin_some	(this->get_node_base_interface());
    handleGamePadStatus();
    gamePadControl();

}
void MainWindow::handleGamePadStatus()
{
    //check if there is a real gamepad connected
    //gamepad connect
    if(!gamepad){
      auto gamepads = QGamepadManager::instance()->connectedGamepads();
      if (!gamepads.isEmpty()){
          qDebug() << "gamepad present";
          gamepad=new QGamepad(gamepads[0], this);
      }
    }
    //check the gamepad_mode
    if(ui->rb_diff_drive->isChecked()){
        gamepadmode=DIFF_DRIVE;
        ui->joyPadR->setEnabled(false);
    }else
    if(ui->rb_omni1->isChecked()){
        gamepadmode=OMNI1;
        ui->joyPadR->setEnabled(true);

    }else {
        gamepadmode=OMNI2;
        ui->joyPadR->setEnabled(true);
    }

}
void  MainWindow::gamePadControl()
{
    if((!gamepad)||(!gamepad->isConnected()))goto CONTROL;
    //if(ui->enableGamePad->isChecked()==false)goto CONTROL;
    //AQUI VA EL CONTROL por polling... habría que gestionar que en caso de desconexion lo detecte y pare el comando robot ultimo.
    ui->joyPadL->setX(MainWindow::gamepad->axisLeftX());
    ui->joyPadL->setY(-MainWindow::gamepad->axisLeftY());
    ui->joyPadR->setX(MainWindow::gamepad->axisRightX());
    ui->joyPadR->setY(-MainWindow::gamepad->axisRightY());
  CONTROL:
    virtualGamePadControl();


}
void MainWindow::virtualGamePadControl()
{
    static bool moved=false;

    float xL=ui->joyPadL->x(), yL = ui->joyPadL->y();
    float xR=ui->joyPadR->x(), yR = ui->joyPadR->y();


    auto message = geometry_msgs::msg::Twist();



    if(xL*xL+yL*yL+xR*xR+yR*yR<0.1){
        //no publica si el valor es cero y ya se envio la parada
        if(!moved)return;
        moved=false;
        qDebug() << "Reset cmd_vel"<<0.0<<endl;
        RCLCPP_INFO(this->get_logger(), "Publicando: '%f'", message.linear.x);
        publisher_->publish(message);
        return;
    }
    double vl_max=ui->d_linearvel->value();
    double va_max=ui->d_angularvel->value();

    //auto speeds = RM2_Kinematics::compute_screw_speeds(yL,xL,xR);
    switch(gamepadmode){
        case OMNI2:
            message.linear.y = vl_max*static_cast<double>(-xR);
        case DIFF_DRIVE:
            message.linear.x = vl_max*static_cast<double>(yL);
            message.angular.z = va_max*static_cast<double>(-xL);
        break;
        default:
            message.linear.x = vl_max*static_cast<double>(yL);
            message.linear.y = vl_max*static_cast<double>(-xL);
            message.angular.z = va_max*static_cast<double>(-xR);

    }





    //ENVIAR EL TWIST en funcion de las selecciones
    RCLCPP_INFO(this->get_logger(), "Published: 'vx:%f vy:%f vyaw:%f'", message.linear.x, message.linear.y, message.angular.z);
    publisher_->publish(message);
    moved=true;
}
