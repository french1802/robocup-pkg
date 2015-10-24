#ifndef EXPLOINFOSUBSCRIBER_H
#define EXPLOINFOSUBSCRIBER_H

#include <ros/ros.h>
#include <string>

#include "comm_msg/ExplorationInfo.h" 
#include "comm_msg/ExplorationSignal.h" 
#include "comm_msg/ExplorationZone.h"
#include "comm_msg/LightSpec.h"

#include "FeuClientAction.h" 

class ExploInfoSubscriber {
public :
  ExploInfoSubscriber();
  virtual  ~ExploInfoSubscriber();
  void tesCallback(const comm_msg::ExplorationInfo &msg);
  void interpretationFeu();
  std::string type;
  uint8_t zone;
  std::vector<comm_msg::LightSpec> lSpec;
  std::vector<comm_msg::ExplorationSignal>  m_signals;
  std::vector<comm_msg::ExplorationZone>  m_zones;
  ros::Subscriber m_sub;
};
#endif 
