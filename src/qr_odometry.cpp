#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>

void odomCb(const geometry_msgs::PoseStamped::ConstPtr& msg){
 double x = msg->pose.position.x;
 double y = msg->pose.position.y;
 ROS_INFO("x: %f, y: %f", x, y);

}
 
int main(int argc, char** argv){
 ros::init(argc, argv, "qr_odometry");
 ros::NodeHandle nh;
 ros::Subscriber Sub = nh.subscribe("object_position", 1, odomCb);
 ros::spin();
 return 0;
}
