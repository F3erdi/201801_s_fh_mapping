//
// Created by ferdi on 07.10.18.
//

#ifndef TBMAPPING_MAP_PUBLISHER_HPP
#define TBMAPPING_MAP_PUBLISHER_HPP

#include "ros/ros.h"

class map_publisher
{
public:
    ros::Publisher map_pub;
    
    ros::NodeHandle Handler()
    {
        ros::NodeHandle n;
        return(n);
    }
    
    
    
    
    
};





#endif //TBMAPPING_MAP_PUBLISHER_HPP
