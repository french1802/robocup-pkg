#include "LocaSubscriber.h"
#include "MPS.h"

//std::vector<MPS> machine(24);

LocaSubscriber::LocaSubscriber():m_machine(24)
{
	ros::NodeHandle n;
	m_sub = n.subscribe("objectDetection/landmarks",1000,&LocaSubscriber::tesCallback, this);
}

LocaSubscriber::~LocaSubscriber(){}

void LocaSubscriber::tesCallback(const deplacement_msg::LandmarksConstPtr &msg)
{
	ROS_INFO_ONCE("I heard the localisation publisher ");

	tab_machine = msg->landmarks;

	for (int i=0; i< msg->landmarks.size(); i++)
    {
    	int zone = getZone(msg->landmarks[i].x, msg->landmarks[i].y);
    	m_machine[zone-1].x = msg->landmarks[i].x;
    	m_machine[zone-1].y = msg->landmarks[i].y;
    	m_machine[zone-1].theta = msg->landmarks[i].theta;
    	m_machine[zone-1].isHere = true;
    	m_machine[zone-1].zone = zone;
	}
	/*for(int i=0; i<tab_machine.size(); i++){
		ROS_INFO("x :landmarks[%d] = %f", i,tab_machine[i].x);
	}*/
}
int LocaSubscriber::getZone(float x, float y)
{
	int zone = 0;

	// Right side
	if(x >= 0 && y >= 0) 
	{
		// Anti-division par 0
		if(x==0) x=1;
		int w = (int)(x/2);

		// Anti-division par 0
		if(y==0) y=1;
		int h = (int)(y/1.5)+1;

		zone = w*4 + h;
	}
	// Left side
	else if (x < 0 && y >= 0) 
	{
		int w = (int)(-x/2);

		// Anti-division par 0
		if(y==0) y=1;
		int h = (int)(y/1.5)+1;

		zone = w*4 + h + 12;
	}

	else 
	{
		int zone = 0;
	}

	return zone;
}