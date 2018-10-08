//
// Created by ferdi on 07.10.18.
//

#ifndef TBMAPPING_MAP_PUBLISHER_HPP
#define TBMAPPING_MAP_PUBLISHER_HPP

#include "ros/ros.h"
#include <nav_msgs/MapMetaData.h>
#include <geometry_msgs/Point.h>

class map_publisher
{
public:


    nav_msgs::MapMetaData meta;
    int meta_erhalten;


    ros::Publisher map_pub;
    
    ros::NodeHandle Handler()
    {
        ros::NodeHandle n;
        return(n);
    }
    
    
    
    
    
};





#endif //TBMAPPING_MAP_PUBLISHER_HPP
