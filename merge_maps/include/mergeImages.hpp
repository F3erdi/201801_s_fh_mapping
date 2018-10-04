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
    cv_bridge::CvImage cv_img_new;


    int stat_received;
    int dyn_received;




    //cv_bridge::CvImage map;


    cv_bridge::CvImage merge()
    {
        cv_img_stat.header.frame_id = "stat_temp";
        cv_img_stat.encoding = sensor_msgs::image_encodings::MONO8;
        cv_img_dyn.header.frame_id = "dyn_temp";
        cv_img_dyn.encoding = sensor_msgs::image_encodings::MONO8;

        ROS_INFO("stat: %d  %d",cv_img_stat.image.rows,cv_img_stat.image.cols);
        ROS_INFO("dyn: %d  %d",cv_img_dyn.image.rows,cv_img_dyn.image.cols);
        ROS_INFO("new: %d  %d",cv_img_new.image.rows,cv_img_new.image.cols);






        if(stat_received == 1 && dyn_received==1)
        {


            cv_img_new.image = cv::Mat(cv_img_stat.image.rows, cv_img_stat.image.cols, CV_8U);

            cv::add(cv_img_stat.image,cv_img_dyn.image,cv_img_new.image);


        dyn_received=0;

            return(cv_img_new);
        }

        else
        {
            ROS_INFO("fail");
        }



    }








};

#endif //CATKIN_MERGEIMAGES_HPP
