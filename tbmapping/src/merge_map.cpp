//
// Created by fhaefner on 30.01.18.
//

//#include "merge_map.hpp"
#include "ros/ros.h"
#include "nav_msgs/OccupancyGrid.h"
#include "nav_msgs/MapMetaData.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>


std::vector<int> compression_params;
cv::Mat stat_mat;
cv::Mat dyn_mat;
cv::Mat temp;
int i = 0;


void DYNCallback(const nav_msgs::OccupancyGrid& dyn)
{
    ROS_INFO("DYNerhalten!");

    if(i%2==0) {
        temp.create(cv::Size(dyn.info.width, dyn.info.height), CV_8SC1);
        dyn_mat.create(cv::Size(dyn.info.width, dyn.info.height), CV_8UC1);

        std::cout<<"temp: "<<temp.isContinuous()<<std::endl;
        std::cout<<"dyn: "<<dyn_mat.isContinuous()<<std::endl;



        memcpy(&temp.data, &dyn.data, sizeof(dyn.data));
        memcpy(&dyn_mat.data, &dyn.data, sizeof(dyn.data));



        dyn_mat.setTo(255, temp < 0);


        cv::imwrite("dyn.png", dyn_mat,compression_params);
        cv::imwrite("temp.png", temp,compression_params);


        std::cout<<i<<std::endl;
    }
    i++;

}

void STATCallback(const nav_msgs::OccupancyGrid& stat)
{
    ROS_INFO("STATerhalten!");


    stat_mat = cv::Mat::zeros(cv::Size(stat.info.width,stat.info.height),CV_8SC1);

    memcpy(&stat_mat.data,&stat.data,sizeof(stat.data));

    stat_mat.setTo(255,stat_mat<0);

    cv::imwrite("stat.png",stat_mat,compression_params);



}


int main(int argc, char **argv)
{
    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(0);

    ros::init(argc,argv,"merge_map");



    ros::NodeHandle n;






    ros::Subscriber stat_map = n.subscribe("map", 100, STATCallback);
    //   ros::Subscriber stat_data = n.subscribe("map_metadata", 100, stat_dataCallback);

    ros::Subscriber dyn_map = n.subscribe("newmap", 100, DYNCallback);
    //ros::Subscriber stat_data = n.subscribe("dyn_metadata", 100, dyn_dataCallback);





    ros::spin();


    return 0;
};