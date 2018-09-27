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
cv::Mat dyn_temp;
cv::Mat stat_temp;
cv::Mat new_map;
cv::Mat mask;
bool stat_received=false;
int i = 0;


void DYNCallback(const nav_msgs::OccupancyGrid& dyn)
{


    if(i%2==0 && stat_received) {

        dyn_temp.create(cv::Size(dyn.info.width, dyn.info.height), CV_8SC1);
        dyn_mat.create(cv::Size(dyn.info.width, dyn.info.height), CV_8UC1);


        ROS_INFO("DYNerhalten!");

        memcpy(&dyn_temp.data, &dyn.data, sizeof(dyn.data));
       // memcpy(&dyn_mat.data, &dyn.data, sizeof(dyn.data));
        dyn_temp.copyTo(dyn_mat);

        /*dyn_mat.setTo(250, dyn_temp > 0);
        dyn_mat.setTo(0, dyn_temp < 0);
        dyn_mat.setTo(125, dyn_temp == 0);*/


        cv::imwrite("temp.png", dyn_temp, compression_params);
        cv::imwrite("dyn.png", dyn_mat,compression_params);

        new_map=dyn_mat.clone();


        mask.setTo(250, dyn_mat==100);

        /*new_map.setTo(100, mask==250);

        cv::imwrite("new_map.png",new_map,compression_params);
*/
        std::cout<<i<<std::endl;
    }
    i++;

}

void STATCallback(const nav_msgs::OccupancyGrid& stat)
{
    ROS_INFO("STATerhalten!");


    stat_temp.create(cv::Size(stat.info.width, stat.info.height), CV_8SC1);
    stat_mat.create(cv::Size(stat.info.width,stat.info.height),CV_8UC1);
    mask.zeros(stat_mat.size(),CV_8UC1);

    memcpy(&stat_temp.data, &stat.data, sizeof(stat.data));
    memcpy(&stat_mat.data,&stat.data,sizeof(stat.data));

    stat_mat.setTo(255,stat_temp<0);

    std::cout<<"stat Größe "<<stat_mat.size()<<std::endl;


    cv::imwrite("stat.png",stat_mat,compression_params);


    mask.setTo(250,stat_mat == 100);



    stat_received = true;

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