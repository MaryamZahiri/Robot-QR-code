#include <ros/ros.h>
#include <pluginlib/class_list_macros.h>
#include <nodelet/nodelet.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseStamped.h>
#include <cmath> 
#include <limits>

/* 
QR_follower.cpp
Qoal: Subscribe to object_position 
      Publishes a cmd_vel to move Powerbot to follow detcted QR code
*/

namespace QR_follower {

	//Class for QRcode following
	class QRFollower : public nodelet::Nodelet
	{
	public:
		QRFollower() : stopDistance_(1)
		{
		}
		~QRFollower()
		{
		}

	private:
		double stopDistance_; //margin of space between powerbot and QRcode being followed, for safety
		
		float prevX_ = 0; //store past linear velocity x
		float prevZ_ = 0; //store past Angular velocity z

		ros::Subscriber QRSub_;
		ros::Publisher cmdPub_;

		/*
		Class initialization method. Sets up private variables, publishers, and subscribers.
		Inputs: N/A
		Returns: N/A
		*/
			virtual void onInit()
		{
			ros::NodeHandle& nh = getNodeHandle();

			//Subscribe to QRcode detectoing data
			QRSub_ = nh.subscribe<geometry_msgs::PoseStamped>("object_position", 1);

			//Publish movement commands to base
			cmdPub_ = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1);
		}




		/*
		safty functions
		*/




        /*
		Publishs to cmd_vel to move powerbot to QRcode (Define controller)
		*/



	   
		/*
		Stop powerbot or retreat based on error value.
		Input: Error - distance a detected object (for safty)
		Return: N/A
		*/
		void stop(float error)
		{
			geometry_msgs::TwistPtr cmd(new geometry_msgs::Twist());
			if (fabs(error) < stopDistance_ / 10) { 
				//if error is a small fraction of the safety distance, stop moving 
				cmd->linear.x = 0;
				cmd->angular.z = 0;
			}
			else { 
				//otherwise, move backwards to make space
				cmd->linear.x = error;
				cmd->angular.z = 0;
			}
			cmdPub_.publish(cmd);
			prevX_ = cmd->linear.x;
			prevZ_ = cmd->angular.z;
		}

		/*
		Slow down powerbot's linear velocity and stop turning.
		Input: N/A
		Return: N/A
		*/
		void slowdown() {
			geometry_msgs::TwistPtr cmd(new geometry_msgs::Twist());
			cmd->linear.x = prevX_ / 100;
			cmd->angular.z = 0;
			cmdPub_.publish(cmd);

			prevX_ = cmd->linear.x;
			prevZ_ = cmd->angular.z;
		}
	};


	PLUGINLIB_EXPORT_CLASS(QR_follower::QRFollower, nodelet::Nodelet)
}

