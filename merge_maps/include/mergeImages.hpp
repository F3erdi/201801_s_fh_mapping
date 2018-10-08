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
#include <geometry_msgs/Point.h>
#include <image_transport/image_transport.h>


class mergeImages{

public:

    //mergeImages();

    //~mergeImages();

    cv_bridge::CvImage cv_img_dyn;
    cv_bridge::CvImage cv_img_stat;
    cv_bridge::CvImage cv_img_new;
    cv_bridge::CvImage stat,dyn;
    cv::Mat warp_mat;
   // geometry_msgs::Point src_tri,dst_tri;
    int offset_x,offset_y;
    int offset_received;

    image_transport::ImageTransport itx();
    image_transport::Publisher pub;

    int stat_received;
    int dyn_received;


    ros::NodeHandle Handler()
    {
        ros::NodeHandle n;
        return(n);
    }

    //cv_bridge::CvImage map;


    cv_bridge::CvImage merge()
    {
        cv_img_stat.header.frame_id = "stat_temp";
        cv_img_stat.encoding = sensor_msgs::image_encodings::MONO8;
        cv_img_dyn.header.frame_id = "dyn_temp";
        cv_img_dyn.encoding = sensor_msgs::image_encodings::MONO8;
        cv_bridge::CvImage cv_img_dyn_w;



        if(stat_received == 1 && dyn_received==1)
        {

            cv_img_new.image=cv::Mat::zeros(cv_img_stat.image.size(),CV_8U);
            cv_img_dyn_w.image=cv::Mat (cv_img_stat.image.size(),CV_8U);

           // offset_x=src_tri.x-dst_tri.x;
            //offset_y=src_tri.y-dst_tri.y;


            ROS_INFO("ofx: %i, ofy: %i",offset_x,offset_y);


            float of[]={1,0,-offset_x,0,1,offset_y};


            warp_mat = cv::Mat (2,3,CV_32FC1,of);



            cv::warpAffine(cv_img_dyn.image,cv_img_dyn_w.image,warp_mat,cv_img_dyn_w.image.size());

          //  ROS_INFO("stat: %d  %d",cv_img_stat.image.rows,cv_img_stat.image.cols);
          //  ROS_INFO("dyn: %d  %d",cv_img_dyn.image.rows,cv_img_dyn.image.cols);
          //  ROS_INFO("new: %d  %d",cv_img_new.image.rows,cv_img_new.image.cols);

            cv::imwrite("warp.png", cv_img_dyn_w.image);

            cv::add(cv_img_stat.image,cv_img_dyn_w.image,cv_img_new.image);


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
