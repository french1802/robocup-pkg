cmake_minimum_required(VERSION 2.8.3)
project(feu_tricolore)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  trait_im_msg
  image_transport
  cv_bridge
  actionlib
)

find_package(OpenCV)


###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES feu_tricolore
#  CATKIN_DEPENDS roscpp
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
	include
	${catkin_INCLUDE_DIRS}
	${OpenCV_INCLUDE_DIRS}
)

# Declare all cpp executables
add_executable(
	lecture_feu_node 
	src/lecture_feu_node.cpp
	src/cv_algo.cpp
	src/cv_utils.cpp
  src/display-histogram.cpp
)
add_dependencies(
  lecture_feu_node 
  trait_im_msg_generate_messages_cpp
)
target_link_libraries(
  lecture_feu_node
	${catkin_LIBRARIES}
	${OpenCV_LIBRARIES}
)


add_executable(sim_light_detection 
	src/simLightDetection_node.cpp
	src/SimLightDetection.cpp
)
add_dependencies(sim_light_detection 
	trait_im_msg_gencpp
)
target_link_libraries(sim_light_detection
	${catkin_LIBRARIES}
)


add_executable(
	fake_img_publisher_node 
	src/fake_img_publisher_node.cpp
)
target_link_libraries(
	fake_img_publisher_node
	${catkin_LIBRARIES}
	${OpenCV_LIBRARIES}
)


add_executable(
	test_node 
	src/test_node.cpp
)
target_link_libraries(
  test_node
	${catkin_LIBRARIES}
)