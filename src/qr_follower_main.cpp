#include <ros/ros.h>
#include <ros/console.h>
#include <pluginlib/class_list_macros.h>
#include <nodelet/nodelet.h>
#include <sensor_msgs/LaserScan.h>
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
		QRFollower() : stopDistance_(0.1), speed_(0.75), iGain_(5), pGain_(5), maxLinearVel_(2), maxAngularVel(2)
		{
		}
		~QRFollower()
		{
		}

	//Definitions
	private:
		double stopDistance_; //margin of space between powerbot and QRcode being followed, for safety
		double speed_; //constant to scale speed by (proportional control)
		double iGain_; //constant to scale turning by (integral control)
		double pGain_; //constant to scale turning by (proportional control)
		double maxLinearVel_; //max linear velocity
		double maxAngularVel; //max angular velocity

		float prevX_ = 0; //store past linear velocity x
		float prevZ_ = 0; //store past Angular velocity z
		float noQRDetection_ = -1; //-1 when nothing detected, the point which is detected by laser scan
		float CameraDistance = 0.1; //distance between camera and front of Powerbot, along x-axis of Powerbot

		ros::Subscriber QRSub_;
//		ros::Subscriber scanSub_;
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
			QRSub_ = nh.subscribe<geometry_msgs::PoseStamped>("object_position", 1, &QRFollower::QRcodeCb, this);

			//Subscribe to laserscan as an avoidance point
			//scanSub_ = nh.subscribe<sensor_msgs::LaserScan>("scan", 1, &QRFollower::scanCb, this);
                        //scanSub_ = nh.subscribe<sensor_msgs::LaserScan>("scan", 1);

			//Publish movement commands to base
			cmdPub_ = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1);
		}


		/*
		Callback for laserscan subscriber. Calls stop function if anything is detected closer than the set stop_distance_
		Input: laserscan array, containing distance to each scanned point
		Returns: N/A
		*/
/*
		void scanCb(const sensor_msgs::LaserScan::ConstPtr& scan) {
			noQRDetection_ = -1;
			for (auto val : scan->ranges) {
				if (!std::isnan(val)) {
					if (val < noQRDetection_ || noQRDetection_ < 0) {
						noQRDetection_ = val;
					}
				}
			}
			//call stop if there is obstacle which is closer than our set stopDistance_
			if (noQRDetection_ < stopDistance_) {
				stop(noQRDetection_ - stopDistance_);
				// ROS_ERROR("Laser detects something too close, error: %.3f", noDetection_ - stopDistance_);
			}
		}

*/

		/*
		 Callback for QRcode detector
		 Input: tracked_QRcode
		 Returns: N/A
		*/
		void QRcodeCb(const geometry_msgs::PoseStamped::ConstPtr& QRcodePos)
		{
			//QRcodePose
			float currentDistance = Distance(QRcodePos->pose.position.x, QRcodePos->pose.position.y);
			while (currentDistance > stopDistance_)
			{
                        	follow(QRcodePos);
                                ros::spin();
                        }
			if (currentDistance < stopDistance_ + CameraDistance)	//detected QRcode is too close, don't follow it
                        {
				stop(currentDistance - stopDistance_ - CameraDistance);
                        }
			else if (noQRDetection_ > stopDistance_)
                        {
				slowdown();
                        }
                 ROS_DEBUG("Hello %s", "World");
                 ROS_INFO("Hello %s", "World");
                 ROS_WARN("Hello %s", "World") ;
                 ROS_ERROR("Hello %s", "World");
                 ROS_FATAL("Hello %s", "World");

		}


		/*
		Helper method to get distance of vector (x, y)
		Input: x, y coordinates
		Returns: Distance
		*/
		float Distance(float x, float y)
		{
			return sqrt(x*x + y*y);
		}




		/*
		 Publishs to cmd_vel to move powerbot to QRcode
		*/
		void follow(const geometry_msgs::PoseStamped::ConstPtr& QRcodePos)
		{
			geometry_msgs::TwistPtr cmd(new geometry_msgs::Twist());
			float currentDistance = Distance(QRcodePos->pose.position.x, QRcodePos->pose.position.y);
			cmd->linear.x = (currentDistance - stopDistance_ - CameraDistance) * speed_; //catch up to person
			cmd->angular.z = iGain_ * atan(QRcodePos->pose.position.y / QRcodePos->pose.position.x) + pGain_ * (currentDistance - stopDistance_ - CameraDistance);

			//limit velocity commands to max
			if (cmd->linear.x > maxLinearVel_)
				cmd->linear.x = maxLinearVel_;
			else if (cmd->linear.x < -1 * maxLinearVel_)
				cmd->linear.x = -1 * maxLinearVel_;

			if (cmd->angular.z > maxAngularVel)
				cmd->angular.z = maxAngularVel;
			else if (cmd->angular.z < -1 * maxAngularVel)
				cmd->angular.z = -1 * maxAngularVel;

			cmdPub_.publish(cmd);
			prevX_ = cmd->linear.x;
			prevZ_ = cmd->angular.z;
		}


		/*
		Stop powerbot or retreat based on error value.
		Input: Error - distance a detected object (for safty)
		Return: N/A
		*/
		void stop(float error)
		{
			geometry_msgs::TwistPtr cmd(new geometry_msgs::Twist());
			if (fabs(error) < stopDistance_ / 10)
                        {
				//error is a small fraction of the safety distance, stop moving
				cmd->linear.x = 0;
				cmd->angular.z = 0;
			}
			else
                        {
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
		void slowdown()
                {
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
