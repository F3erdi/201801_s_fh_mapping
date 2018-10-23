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
    int off_x,off_y;
    double angle;

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
        int v1_x = amcl_offset_x /*+ abs(stat_origin_x)*/;
        int v1_y;
        int v2_x = abs(dyn_origin_x);

        if (dyn_origin_x==stat_origin_x) {
            off_x= 0;
        }
        else{
            off_x=abs(stat_origin_x)-v2_x;
        }

        if (dyn_origin_y==stat_origin_y)
        {
            v1_y=stat_sizey-abs(stat_origin_y);
        }
        else
        {
            int v1_ytemp = amcl_offset_y + abs(stat_origin_y);

            v1_y=stat_sizey-v1_ytemp;
        }



            int v2_ytemp = abs(dyn_origin_y);
            int v2_y=dyn_sizey-v2_ytemp;

        off_y=v1_y-v2_y;






            return(1);
    }
        else {
            return(0);
        }
    }


};







#endif //CATKIN_INIT_TF_H
