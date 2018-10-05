//
// Created by fhaefner on 27.09.18.
//


#include "ros/ros.h"
#include "nav_msgs/OccupancyGrid.h"
#include "nav_msgs/MapMetaData.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <nav_msgs/GetMap.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <sensor_msgs/image_encodings.h>
#include "../include/mergeImages.hpp"



cv_bridge::CvImage cv_img_full_;
cv_bridge::CvImage cv_img_full_stat;
mergeImages mergeImages1;
std::vector<int> compression_params;
bool stat_received=false;
int i = 0;
int offset_x = 0;
int offset_y = 0;
void origin(const nav_msgs::MapMetaDataConstPtr& origin)
{
    float o_x=origin->origin.position.x;
    float o_y=origin->origin.position.y;
    mergeImages1.origin_x=o_x;
    mergeImages1.origin_y=o_y;
}



void init(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& pose_init)
{
       float x_temp = pose_init->pose.pose.position.x;
       float y_temp = pose_init->pose.pose.position.y;

    offset_x=x_temp/0.05;
    offset_y=y_temp/0.05;
    mergeImages1.offset_x=offset_x;
    mergeImages1.offset_y=offset_y;

}

void DYNCallback(const nav_msgs::OccupancyGridConstPtr& dyn_grid) {

    int size_x = dyn_grid->info.width;
    int size_y = dyn_grid->info.height;


    if ((size_x < 3) || (size_y < 3)) {
        ROS_INFO("Map size is only x: %d,  y: %d . Not running map to image conversion", size_x, size_y);
        return;
    }



    cv_img_full_.header.frame_id = "dyn_image";
    cv_img_full_.encoding = sensor_msgs::image_encodings::MONO8;
    // Only if someone is subscribed to it, do work and publish full map image

    cv::Mat *map_mat = &cv_img_full_.image;

    // resize cv image if it doesn't have the same dimensions as the map
    if ((map_mat->rows != size_y) && (map_mat->cols != size_x)) {
        *map_mat = cv::Mat(size_y, size_x, CV_8U);
    }

    const std::vector <int8_t> &map_data(dyn_grid->data);

    unsigned char *map_mat_data_p = (unsigned char *) map_mat->data;

    //We have to flip around the y axis, y for image starts at the top and y for map at the bottom
    int size_y_rev = size_y-1;

    for (int y = size_y_rev; y >= 0; --y) {

        int idx_map_y = size_x * (size_y - y);
        int idx_img_y = size_x * y;

        for (int x = 0; x < size_x; ++x) {

            int idx = idx_img_y + x;

            switch (map_data[idx_map_y + x]) {
                case -1:
                    map_mat_data_p[idx] = 63;
                    break;

                case 0:
                    map_mat_data_p[idx] = 127;
                    break;

                case 100:
                    map_mat_data_p[idx] = 0;
                    break;
            }
        }
    }


    cv::imwrite("dyn.png", cv_img_full_.image,compression_params);
    mergeImages1.cv_img_dyn=cv_img_full_;
    mergeImages1.Provide_Dyn();
    mergeImages1.dyn_received=1;

    cv_bridge::CvImage map = mergeImages1.merge();
    cv::imwrite("map.png", map.image,compression_params);

    }


void STATCallback(const nav_msgs::OccupancyGridConstPtr& stat_grid)
{


    int size_x = stat_grid->info.width;
    int size_y = stat_grid->info.height;


    if ((size_x < 3) || (size_y < 3) ){
        ROS_INFO("Map size is only x: %d,  y: %d . Not running map to image conversion", size_x, size_y);
        return;
    }

    cv_img_full_stat.header.frame_id = "stat_image";
    cv_img_full_stat.encoding = sensor_msgs::image_encodings::MONO8;

    cv::Mat* map_mat_stat = &cv_img_full_stat.image;

    // resize cv image if it doesn't have the same dimensions as the map
    if ( (map_mat_stat->rows != size_y) && (map_mat_stat->cols != size_x)){
        *map_mat_stat = cv::Mat(size_y, size_x, CV_8U);
    }


    const std::vector<int8_t>& map_data_stat (stat_grid->data);

    unsigned char *map_mat_data_p_stat=(unsigned char*) map_mat_stat->data;

    //We have to flip around the y axis, y for image starts at the top and y for map at the bottom
    int size_y_rev = size_y-1;

    for (int y = size_y_rev; y >= 0; --y) {

        int idx_map_y = size_x * (size_y - y);
        int idx_img_y = size_x * y;

        for (int x = 0; x < size_x; ++x) {

            int idx = idx_img_y + x;

            switch (map_data_stat[idx_map_y + x]) {
                case -1:
                    map_mat_data_p_stat[idx] = 63;
                    break;

                case 0:
                    map_mat_data_p_stat[idx] = 127;
                    break;

                case 100:
                    map_mat_data_p_stat[idx] = 0;
                    break;
            }
        }
    }

    cv::imwrite("stat.png", cv_img_full_stat.image,compression_params);

    mergeImages1.cv_img_stat=cv_img_full_stat;
    mergeImages1.Provide_Stat();
    mergeImages1.stat_received=1;
}


int main(int argc, char **argv)
{
    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(0);

    ros::init(argc,argv,"merge_map");




    ros::NodeHandle n;




    ros::Subscriber originPose = n.subscribe("MapMetaData",1,origin);
    ros::Subscriber initPose = n.subscribe("initialpose",1,init);
    ros::Subscriber stat_map = n.subscribe("map", 100, STATCallback);


    ros::Subscriber dyn_map = n.subscribe("newmap", 100, DYNCallback);






    ros::spin();


    return 0;
};