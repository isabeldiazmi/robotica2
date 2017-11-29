#include <ros/ros.h>
#include <stdlib.h>
#include <iomanip>
#include <geometry_msgs/Pose2D.h>
#include <std_msgs/Float32.h>
#include <math.h>

double x;
double y;
double theta;


using namespace std;
//Metodo que manda llamar la pose
void poseMessageReceived(const geometry_msgs::Pose2D& msg){
    x=msg.x;
    y=msg.y;
    theta=msg.theta;
}

int main(int argc, char **argv){
    ros::init(argc, argv, "robot_controller");
    ros::NodeHandle nh;
    
    ros::Publisher pub1 = nh.advertise<std_msgs::Float32>("AutoNOMOS_mini/manual_control/velocity", 1000);
    ros::Publisher pub2 = nh.advertise<std_msgs::Float32>("AutoNOMOS_mini/manual_control/steering", 1000);

    double xesperada;
    double yesperada;
    double thetaesperada;

   ros::Subscriber sub = nh.subscribe("robot/pose", 1000, &poseMessageReceived);
    
    //Pose esperada
    cout<<"X esperada:";
    cin>>xesperada;
    cout<<"Y esperada:";
    cin>>yesperada;
    cout<<"Theta esperada:";
    cin>>thetaesperada;


    double difx = x-xesperada;
    double dify = y-yesperada;
    double ro = sqrt(difx*difx+dify*dify);
    double alpha = atan2(dify,difx)+theta;
    double beta = -theta-alpha;

    double kro = 1;
    double kalpha = 5;
    double kbeta = -2;
    double v= kro*ro;
    double gamma=kalpha*alpha+kbeta*beta;
    

    ros::Rate rate(10);


    while(ro>0.08){
        sub = nh.subscribe("robot/pose", 1000, &poseMessageReceived);
        difx=x-xesperada;
        dify=y-yesperada;
        ro=sqrt(difx*difx+dify*dify);
        alpha=atan2(dify,difx)+theta;
        beta=-theta-alpha;
        v=kro*ro;
        gamma=kalpha*alpha+kbeta*beta;

        //Crea mensaje
        std_msgs::Float32 msg1;
        std_msgs::Float32 msg2;
        msg1.data=float(v);
        msg2.data=float(gamma);


        //Publica mensaje.
        pub1.publish(msg1);
        pub2.publish(msg2);

        //Sale del loop
        rate.sleep();
    }
}

