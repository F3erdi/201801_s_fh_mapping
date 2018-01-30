//
// Created by fhaefner on 30.01.18.
//

//#include "merge_map.hpp"
#include "ros/ros.h"
#include "nav_msgs/OccupancyGrid.h"


void DYNCallback(const nav_msgs::OccupancyGrid& msg)
{
    ROS_INFO("DYNerhalten!");
}
void STATCallback(const nav_msgs::OccupancyGrid& msgs)
{
    ROS_INFO("STATerhalten!");
}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"merge_map");

    ros::NodeHandle n;

    ros::Subscriber stat = n.subscribe("map",100,STATCallback);

    ros::Subscriber dyn = n.subscribe("newmap",100,DYNCallback);

    ros::spin();

    return 0;
};