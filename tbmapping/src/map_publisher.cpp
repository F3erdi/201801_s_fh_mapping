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
/*
    if(publisher.meta_erhalten==1) {

        nav_msgs::OccupancyGrid gridmap ;


        gridmap.info.width = publisher.meta.width;

        gridmap.info.height = publisher.meta.height;

        gridmap.info.resolution = publisher.meta.resolution;

        gridmap.info.origin = publisher.meta.origin;

        gridmap.info.map_load_time = ros::Time::now();

        gridmap.header.frame_id = "map";

        int size_x = map_image->step;
        int size_y = map_image->height;



        ROS_INFO("size x: %i, y: %i",size_x,size_y);


        const std::vector<unsigned char> &mat_data_stat(map_image->data);

        //std::vector <int8_t> &map_data_p_(gridmap.data);

        ROS_INFO("map erhalten");

        //We have to flip around the y axis, y for image starts at the top and y for map at the bottom
        int size_y_rev = size_y - 1;
        int size_x_rev= size_x-1;

        for (int y = size_y_rev; y > 0; --y) {

            int idx_img_y = size_x * (size_y-y);
            int idx_map_y = size_x_rev * y;

            for (int x = 0; x < size_x; ++x) {


                int idx = idx_map_y + x;


                switch (mat_data_stat[idx_img_y + x]) {
                    case 63:
                        //map_data_p_[idx] =(int8_t) -1;
                        //gridmap.data[idx] = (int8_t) -1;
                        daten[idx]= (int8_t)-1;
                        break;

                    case 127:
                        //map_data_p_[idx] =(int8_t) 0;
                        //gridmap.data[idx] = (int8_t) 0;
                        daten[idx]=(int8_t) 0;
                        break;

                    case 0:
                        //map_data_p_[idx] =(int8_t) 100;
                        //gridmap.data[idx] = (int8_t) 100;
                        daten[idx]= (int8_t)100;
                        break;

                    case 126:
                        //map_data_p_[idx] =(int8_t) -1;
                        //gridmap.data[idx] = (int8_t) -1;
                        daten[idx]=(int8_t) -1;
                        break;

                    case 254:
                        //map_data_p_[idx] =(int8_t) 0;
                        //gridmap.data[idx] = (int8_t) 0;
                        daten[idx]=(int8_t) 0;
                        break;
                }
            }
        }


        ROS_INFO("memcpy?? %lu, %lu", sizeof(daten), sizeof(gridmap.data));
        //memcpy(&gridmap.data,&daten, sizeof(gridmap.data));
        gridmap.data =  daten;
        //nav_msgs::OccupancyGrid msg = gridmap;
        ROS_INFO("map gesendet");
        publisher.map_pub.publish(gridmap);
    }*/
}

void metaData(const nav_msgs::MapMetaDataConstPtr& meta_data)
{
    if(publisher.meta_erhalten==0)
    {
        publisher.meta.origin = meta_data->origin;

        publisher.meta.width = meta_data->width;

        publisher.meta.height = meta_data->height;

        publisher.meta.resolution = meta_data->resolution;


        publisher.meta_erhalten = 1;
    }
}

int main(int argc, char **argv)
{
    /*
    ros::init(argc,argv,"map_publisher");




    ros::NodeHandle n=publisher.Handler();


    ros::Subscriber data = n.subscribe("map_metadata",1,metaData);
    ros::Subscriber image = n.subscribe("mapimage",1,mapimage);
    publisher.map_pub= n.advertise<nav_msgs::OccupancyGrid>("tempmap",1);

    ros::spin();
    */
  return 0;
};