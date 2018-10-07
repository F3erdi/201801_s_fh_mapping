//
// Created by ferdi on 06.10.18.
//
#include "ros/ros.h"
#include "nav_msgs/OccupancyGrid.h"
#include "nav_msgs/MapMetaData.h"
#include <cv_bridge/cv_bridge.h>
#include <nav_msgs/GetMap.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include "../include/init_tf.hpp"
#include <merge_maps/triangle.h>


int offset_x,offset_y;
init_tf Cords;
merge_maps::triangle tri_msg;
int i=0;

void dynPose_Callback(const nav_msgs::MapMetaDataConstPtr& dynData)
{
    float d_x=dynData->origin.position.x;
    float d_y=dynData->origin.position.y;
    float res=dynData->resolution;
    Cords.dyn_sizey=dynData->height;
    Cords.dyn_origin_x=d_x/res;
    Cords.dyn_origin_y=d_y/res;


    ROS_INFO("dynx: %i  dyny: %i",Cords.dyn_origin_x,Cords.dyn_origin_y);
    Cords.dyn=1;

    i=Cords.coordinates();

    if(i==1) {
        tri_msg.src = Cords.src_tri;

        tri_msg.dst = Cords.dst_tri;

        Cords.offset_pub.publish(tri_msg);
    }
}

void statPose_Callback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& pose_amcl)
{
    float x_temp = pose_amcl->pose.pose.position.x;
    float y_temp = pose_amcl->pose.pose.position.y;

    offset_x=x_temp/0.05;
    offset_y=y_temp/0.05;

    Cords.amcl_offset_x=offset_x;
    Cords.amcl_offset_y=offset_y;

    ROS_INFO("statx: %i  staty: %i",offset_x,offset_y);
    Cords.stat=1;

}
void origin_Callback(const nav_msgs::MapMetaDataConstPtr& origin)
{
    float o_x=origin->origin.position.x;
    float o_y=origin->origin.position.y;
    float res=origin->resolution;
    Cords.stat_sizey=origin->height;
    Cords.stat_origin_x=o_x/res;
    Cords.stat_origin_y=o_y/res;

    ROS_INFO("orx: %i  ory: %i",Cords.stat_origin_x,Cords.stat_origin_y);
    Cords.orig=1;

}




int main(int argc, char **argv)
{


    ros::init(argc,argv,"init_tf");

    ros::NodeHandle m = Cords.Handler();


    ros::Subscriber originPose = m.subscribe("map_metadata",1,origin_Callback);
    ros::Subscriber dynPose = m.subscribe("dyn_metadata",1,dynPose_Callback);
    ros::Subscriber statPose = m.subscribe("amcl_pose", 1, statPose_Callback);
    Cords.offset_pub= m.advertise<merge_maps::triangle>("offset",2);




    ros::spin();


    return 0;
};