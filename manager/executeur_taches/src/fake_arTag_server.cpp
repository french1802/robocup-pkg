#include "ros/ros.h"
#include <trait_im_msg/artag.h>


bool test_arTag(trait_im_msg::artag::Request &req, trait_im_msg::artag::Response &res)
{
	res.id = 34;
	return true;
}

int main(int argc, char** argv)
{
	ros::init(argc,argv,"artag_server");
	ros::NodeHandle n;
    ros::ServiceServer service = n.advertiseService("computerVision/artag", test_arTag);

	ros::spin();
	return 0;
}
