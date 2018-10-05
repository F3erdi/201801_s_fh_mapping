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
    cv_bridge::CvImage stat,dyn;
    cv_bridge::CvImage bigStat,bigDyn;
    int offset_x,origin_x;
    int offset_y,origin_y;

    int stat_received;
    int dyn_received;




    //cv_bridge::CvImage map;
    void Provide_Stat()
    {
        stat.header.frame_id = "stat";
        stat.encoding = sensor_msgs::image_encodings::MONO8;
        stat.image = cv::Mat(800, 800, CV_8U);

        int cols_stat=cv_img_stat.image.cols;
        int rows_stat=cv_img_stat.image.rows;

        cv_img_stat.image.copyTo(stat.image(cv::Rect((400-(cols_stat/2))-(cols_stat%2),(400-(rows_stat/2))-(rows_stat%2),cols_stat,rows_stat)));

        return;
    }

    void Provide_Dyn()
    {


        dyn.header.frame_id = "dyn";
        dyn.encoding = sensor_msgs::image_encodings::MONO8;
        dyn.image = cv::Mat(800, 800, CV_8U);
        ROS_INFO("x: %i ",offset_x);
        ROS_INFO("y: %i",offset_y);

        int cols_dyn=cv_img_dyn.image.cols;
        int rows_dyn=cv_img_dyn.image.rows;
        int pos_x=((400-(cols_dyn/2))-(cols_dyn%2))-offset_x-origin_x;
        int pos_y=((400-(rows_dyn/2))-(rows_dyn%2))-offset_y+origin_y;

        cv_img_dyn.image.copyTo(dyn.image(cv::Rect(pos_x,pos_y,cols_dyn,rows_dyn)));

        return;
    }

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


            cv_img_new.image = cv::Mat(800, 800, CV_8U);

            cv::add(stat.image,dyn.image,cv_img_new.image);


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
