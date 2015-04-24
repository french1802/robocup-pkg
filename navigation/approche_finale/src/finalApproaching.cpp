#include "finalApproaching.h"
#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <manager_msg/finalApproachingAction.h>
#include <cmath>
#include <vector>
#include <list>
#include "bumperlistener.h"
#include "geometry_msgs/Twist.h"
#include "fa_utils.h"
#include "laserScan.h"
#include "Point.h"
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/Point.h>

int a=0,b=0,c=0,d=0;

	finalApproaching::~finalApproaching(void){}

	void finalApproaching::executeCB(const manager_msg::finalApproachingGoalConstPtr &goal)
  {
    // helper variables
    ROS_INFO("test2");
    ros::Rate loop_rate(100);
    m_pub_mvt = nh_.advertise<geometry_msgs::Twist>("/cmd_vel",1000);
    //m_marker_pub = nh_.advertise<visualization_msgs::Marker>("/visualization_marker",1000);
	bool success = true;
    
    BumperListener bp;

    feedback_.percent_complete = 0;
		// check that preempt has not been requested by the client
    if (as_.isPreemptRequested() || !ros::ok()){
      ROS_INFO("%s: Preempted", action_name_.c_str());
      // set the action state to preempted
      as_.setPreempted();
      success = false;
      //break;
    }
    // publish info to the console for the user
    ROS_INFO("%s: Executing, creating finalApproaching sequence of type %i with side %i and parameter %i", action_name_.c_str(), goal->type, goal->side,goal->parameter);
    int type, side, parameter; 
    /*nh_.param<int>("fa_type",type,goal->type);
    nh_.param<int>("fa_side",side,goal->side);
    nh_.param<int>("fa_parameter",parameter,goal->parameter);*/
    m_type = goal->type;
    m_side = goal->side;
    m_parameter = goal->parameter;
   		  
    laserScan ls;
		//loop_rate.sleep();
		float position_y;
		float angle;
		float ortho;
		float moy_y;
		float moy_o;
		int max_points=0;
		int nearby=0;
		int j = 0;
		std::list<float> liste_position_y;
		std::list<float> liste_ortho;
		/*visualization::Marker msg_marker;
		msg_marker.header.frame.id = "/laser_link";
		msg_marker.header.stamp = ros::Time::now();
		msg_marker.ns = "visualization_segments";
		msg_marker.action = visualization_msgs::Marjer::ADD;
		msg_marker.pose.orientation.w = 1.0;
		msg_marker.id = 2;
		msg_marker.type = visualization_msgs::Marker::LINE_LIST;

		msg_marker.scale.x = 0.1;
		msg_marker.color.r = 1.0;
		msg_marker.color.a = 1.0;
		geometry_msgs::Point p;
		msg_marker.points.push_back(p);
		msg_marker.points.push_back(p);*/
		std::cout << "En attente d'un scan laser complet" << std::endl;
		while(ros::ok() && !bp.get_state() && c!=2){
		  if(ls.getRanges().size() == 513 && ls.getTabSegments().size()>0){
				nearby = ls.nearest_segment();
				std::cout << " numero du segment le plus proche = " << nearby << std::endl;


				/*msg_marker.points[0].x;
				msg_marker.points[0].y;
				msg_marker.points[1].x;
				msg_marker.points[1].y;
				m_marker_pub.publish(msg_marker);*/

				std::vector<Segment> tabseg = ls.getTabSegments();
				angle = tabseg[nearby].get_angle();
				std::cout << "angle du segment le plus proche : " << angle << std::endl;
				position_y = ls.position_y(tabseg[nearby]);
				std::cout << "l objet se trouve a environ "<< position_y << " m du bord" << std::endl;
				if(j<10){
					liste_position_y.push_back(position_y);
					liste_ortho.push_back(ortho);
					j++;}
				else{
					/*liste_position_y.pop_front();
					liste_ortho.pop_front();
					liste_position_y.push_back(position_y);
					liste_ortho.push_back(ortho);*/
					moy_y = moy(liste_position_y);
					moy_o = moy(liste_ortho);
					liste_position_y.clear();
					liste_ortho.clear();
					j=0;
					a = asservissement_angle(m_pub_mvt,angle);
					ortho = ls.distance_ortho(tabseg[nearby]);
					/*while(a!=1){
					a = asservissement_angle(m_pub_mvt,angle);
					}
					ortho = ls.distance_ortho(tabseg[nearby]);
					while(b!=1){
						if(a==1){
							b = asservissement_position_y(m_pub_mvt,position_y,objectif_y(),ortho);}}
					while(c!=2){
						if(a==1 && b==1){
							c=asservissement_position_x(m_pub_mvt,ortho,objectif_x());}}*/
					if(a == 1){
						b = asservissement_position_y(m_pub_mvt,moy_y,objectif_y(),moy_o);
						if(b == 1){
							c = asservissement_position_x(m_pub_mvt,moy_o,0.35);	
						}
					}
				/*if(c==2){
					d = asservissement_position_x(m_pub_mvt,moy_o,objectif_x());
				*/}
			
		feedback_.percent_complete = avancement(a,b,c);
		as_.publishFeedback(feedback_);
		ros::spinOnce();
    std::cout<<"etat du bumper "<<bp.get_state()<<std::endl;
		loop_rate.sleep();
		}
	}    
   /*
    // start executing the action
    for(int i=1; i<=100; i++)
    {
      // check that preempt has not been requested by the client
      if (as_.isPreemptRequested() || !ros::ok())
      {
        ROS_INFO("%s: Preempted", action_name_.c_str());
        // set the action state to preempted
        as_.setPreempted();
        success = false;
        break;
      }
      feedback_.percent_complete++;
      //tasks to do 
      // publish the feedback
      as_.publishFeedback(feedback_);
      
      
      loop_rate.sleep();
    }*/
    
	if(bp.get_state())
{success=false;
geometry_msgs::Twist arret;
arret.linear.x = 0;
arret.linear.y = 0;
arret.angular.z = 0;
m_pub_mvt.publish(arret);
}
    if(success)
    {
      result_.success = true;
      ROS_INFO("%s: Succeeded", action_name_.c_str());
      // set the action state to succeeded
      a=0;
      b=0;
      c=0;
      as_.setSucceeded(result_);
    }
}
  
  
int finalApproaching::avancement(int a, int b, int c){
	int tmp=-20;
	if(c==2){
		tmp = 100;
	}
	else{
		if(b == 1 && (c == 0 || c==1)){
			tmp = 67;
		}	
		else{
			if(a==1 && b==0 && (c == 0 || c==1)){
				tmp = 33;
			}
			else{
				tmp = 0;
			}
		}
	}
	return tmp;	
}


float finalApproaching::objectif_y(){
	float tmp=0;
	switch(m_parameter){
		case manager_msg::finalApproachingGoal::S1 :
			tmp = 0.28; break;
		case manager_msg::finalApproachingGoal::S2 :
			tmp = 0.175; break;
		case manager_msg::finalApproachingGoal::S3 :
			tmp = 0.08; break;
		case manager_msg::finalApproachingGoal::LANE_RS :
			tmp = 0.09; break;
		case manager_msg::finalApproachingGoal::LIGHT :
			tmp = 0.4; break;
		case manager_msg::finalApproachingGoal::CONVEYOR :
			switch(m_side){
				case manager_msg::finalApproachingGoal::IN :
					tmp = 0.37; break;
				case manager_msg::finalApproachingGoal::OUT :
					tmp = 0.32; break;
			}
		default: break;
	}
	return tmp;
}

float finalApproaching::objectif_x(){
	float tmp = 0;
	if(m_parameter == manager_msg::finalApproachingGoal::LIGHT){
		tmp = 0.35;
	}
	else{
		tmp = 0.14;
	}
	return tmp;
}

