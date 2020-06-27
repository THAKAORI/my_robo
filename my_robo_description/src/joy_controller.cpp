#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>

sensor_msgs::Joy current_command;

void key_cb(const sensor_msgs::Joy::ConstPtr& msg){
    current_command = *msg;
}
int main(int argc, char **argv)
{
    ros::init(argc, argv, "offb_node");
    ros::NodeHandle nh;
    ROS_INFO("Get start");
    ros::Subscriber key_sub = nh.subscribe<sensor_msgs::Joy>
            ("/joy", 10, key_cb);
    ros::Publisher local_vel_pub = nh.advertise<geometry_msgs::Twist>
            ("/my_robo/diff_drive_controller/cmd_vel", 10);
    float linear_scale = 0.3, angular_scale = 0.3;

    geometry_msgs::Twist velocity;
    //the setpoint publishing rate MUST be faster than 2Hz
    ros::Rate rate(20.0);
    // wait for command
    while(ros::ok() && current_command.header.seq==0){
        ROS_INFO("wait command");
        ros::spinOnce();
        rate.sleep();
    }

    ROS_INFO("activated!!");
    while(ros::ok()){
        if (current_command.buttons[4] != 0)
	{
	    linear_scale *= 1.1;
	    ROS_INFO("%f", linear_scale);	
	}
	if (current_command.buttons[5] != 0)
	{
	    angular_scale *= 1.1;	
            ROS_INFO("%f", angular_scale);	
	}
	if (current_command.buttons[6] != 0)
	{
	    linear_scale /= 1.1;
	    ROS_INFO("%f", linear_scale);		
	}
	if (current_command.buttons[7] != 0)
	{
	    angular_scale /= 1.1;	
            ROS_INFO("%f", angular_scale);
	}
	velocity.linear.x = linear_scale * current_command.axes[1];
	velocity.angular.z = angular_scale * current_command.axes[3];

        local_vel_pub.publish(velocity);
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}
