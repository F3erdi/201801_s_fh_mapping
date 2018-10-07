//
// Created by ferdi on 07.10.18.
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
#include <geometry_msgs/Point.h>
#include <image_transport/image_transport.h>
#include "../include/map_publisher.hpp"

map_publisher publisher;



void mapimage(const sensor_msgs::ImagePtr& map_image)
{
    nav_msgs::OccupancyGrid gridmap;

    gridmap.info.width=map_image->width;
    gridmap.info.height=map_image->height;
    gridmap.info.resolution= 0.05;
    gridmap.info.map_load_time=ros::Time::now();
    gridmap.header.frame_id = "map";

    int size_x =map_image->width;
    int size_y =map_image->height;





    const std::vector<unsigned char>& map_data_stat (map_image->data);
    std::vector<int8_t>& map_mat_data_p_=(std::vector<int8_t>&) gridmap.data;



    //We have to flip around the y axis, y for image starts at the top and y for map at the bottom
    int size_y_rev = size_y-1;

    for (int y = size_y_rev; y >= 0; --y) {

        int idx_img_y = size_x * (size_y - y);
        int idx_map_y = size_x * y;

        for (int x = 0; x < size_x; ++x) {

            int idx = idx_map_y + x;

            switch (map_data_stat[idx_img_y + x]) {
                case 63:
                    map_mat_data_p_[idx]  = -1;
                    break;

                case 127:
                    map_mat_data_p_[idx]  = 0;
                    break;

                case 0:
                    map_mat_data_p_[idx]  = 100;
                    break;

                case 126:
                    map_mat_data_p_[idx]  = -1;
                    break;

                case 254:
                    map_mat_data_p_[idx]  = 0;
                    break;
            }
        }
    }

    nav_msgs::OccupancyGrid msg = gridmap;

    publisher.map_pub.publish(msg);
}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"map_publisher");




    ros::NodeHandle n=publisher.Handler();

    ros::Subscriber image = n.subscribe("mapimage",1,mapimage);
    publisher.map_pub= n.advertise<nav_msgs::OccupancyGrid>("tempmap",1);

    ros::spin();
  return 0;
};