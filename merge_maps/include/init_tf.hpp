//
// Created by ferdi on 06.10.18.
//

#ifndef CATKIN_INIT_TF_H
#define CATKIN_INIT_TF_H
#include "ros/ros.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <geometry_msgs/Point.h>


class init_tf{

public:
    int dyn_origin_x;
    int dyn_origin_y;
    int amcl_offset_x;
    int amcl_offset_y;
    int stat_origin_x;
    int stat_origin_y;
    int dyn_sizex,stat_sizex,dyn_sizey,stat_sizey;
    int tf_x,tf_y;
    int dyn,stat,orig;
    geometry_msgs::Point src_tri,dst_tri;

    ros::Publisher offset_pub;

    ros::NodeHandle Handler()
    {
        ros::NodeHandle m;
        return(m);
    }
    int coordinates()
    {

  if(dyn==1 && stat==1 && orig==1)
    {
            int v1_x = amcl_offset_x + abs(stat_origin_x);
            int v1_ytemp = amcl_offset_y + abs(stat_origin_y);

            int v1_y=stat_sizey-v1_ytemp;

            src_tri.x= v1_x;
            src_tri.y= v1_y;
            src_tri.z=0;

            int v2_x = abs(dyn_origin_x);
            int v2_ytemp = abs(dyn_origin_y);

            int v2_y=dyn_sizey-v2_ytemp;
            dst_tri.x= v2_x;
            dst_tri.y= v2_y;
            dst_tri.z=0;

            return(1);
    }
        else {
            return(0);
        }
    }


};







#endif //CATKIN_INIT_TF_H
