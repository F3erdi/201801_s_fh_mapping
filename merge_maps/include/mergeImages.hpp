//
// Created by fhaefner on 27.09.18.
//

#ifndef CATKIN_MERGEIMAGES_HPP
#define CATKIN_MERGEIMAGES_HPP

#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "ros/ros.h"
#include <sensor_msgs/image_encodings.h>

class mergeImages{

public:

    //mergeImages();

    //~mergeImages();

    cv_bridge::CvImage cv_img_dyn;

    cv_bridge::CvImage cv_img_stat;



    int stat_received;
    int dyn_received;




    //cv_bridge::CvImage map;


    cv_bridge::CvImage merge()
    {
        cv_img_stat.header.frame_id = "stat_temp";
        cv_img_stat.encoding = sensor_msgs::image_encodings::MONO8;
        cv_img_dyn.header.frame_id = "dyn_temp";
        cv_img_dyn.encoding = sensor_msgs::image_encodings::MONO8;


        if(stat_received == 1 && dyn_received==1)
        {

            cv_img_stat.image.setTo((unsigned char)(255),cv_img_dyn.image==255);
            ROS_INFO("hier?");
            cv_img_stat.image.setTo((unsigned char)(0),cv_img_dyn.image==0);


        dyn_received=0;
            return(cv_img_stat);
        }

        else
        {
            ROS_INFO("fail");
        }



    }








};

#endif //CATKIN_MERGEIMAGES_HPP
