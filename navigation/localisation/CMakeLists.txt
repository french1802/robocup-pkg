cmake_minimum_required(VERSION 2.8.3)
project(localisation)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  nav_msgs
  roscpp
  rospy
  sensor_msgs
  visualization_msgs
  cmake_modules
  deplacement_msg
  tf
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)
find_package(Eigen REQUIRED)

## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend and a run_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependencies might have been
##     pulled in transitively but can be declared for certainty nonetheless:
##     * add a build_depend tag for "message_generation"
##     * add a run_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

## Generate messages in the 'msg' folder
#add_message_files(
#   messages/deplacement_msg/msg
#   Landmarks.msg
#)

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
# generate_messages(
#   DEPENDENCIES
#   geometry_msgs#   nav_msgs#   sensor_msgs
# )

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
   INCLUDE_DIRS include/localisation /usr/include/eigen3
   LIBRARIES localisation
   CATKIN_DEPENDS geometry_msgs nav_msgs roscpp rospy sensor_msgs message_runtime
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${Eigen_INCLUDE_DIRS}
  include/localisation
)

## Declare a cpp library
# add_library(localisation
#   src/${PROJECT_NAME}/localisation.cpp
# )

## Declare a cpp executable
add_executable(
  landmarks_extraction
  src/landmarks_extraction_node.cpp
  src/landmarks_detection_utils.cpp
  src/math_functions.cpp
  src/conversion_functions.cpp
  src/cartographie_utils.cpp
  src/LaserScan.cpp
  src/Line.cpp
  src/Segment.cpp
  src/Model.cpp
  src/Machine.cpp)
set_target_properties(landmarks_extraction PROPERTIES COMPILE_FLAGS -std=c++0x)
add_dependencies(landmarks_extraction deplacement_msg_gencpp ${catkin_EXPORTED_TARGETS})
target_link_libraries(
  landmarks_extraction
  ${catkin_LIBRARIES}
)

add_executable(
  odometry_correction
  src/odometry_correction_node.cpp)
set_target_properties(odometry_correction PROPERTIES COMPILE_FLAGS -std=c++0x)
add_dependencies(odometry_correction deplacement_msg_gencpp ${catkin_EXPORTED_TARGETS})
target_link_libraries(
  odometry_correction
  ${catkin_LIBRARIES}
)

add_executable(
  visualisation
  src/visualisationOK.cpp)
set_target_properties(visualisation PROPERTIES COMPILE_FLAGS -std=c++0x)
add_dependencies(visualisation deplacement_msg_gencpp ${catkin_EXPORTED_TARGETS})
target_link_libraries(
  visualisation
  ${catkin_LIBRARIES}
)

add_executable(
  try
  src/try.cpp
  src/cartographie_utils.cpp
  src/landmarks_detection_utils.cpp
  src/math_functions.cpp
  src/conversion_functions.cpp
  src/LaserScan.cpp
  src/Line.cpp
  src/Segment.cpp
  src/Model.cpp
  src/Machine.cpp)
set_target_properties(try PROPERTIES COMPILE_FLAGS -std=c++0x)
add_dependencies(try deplacement_msg_gencpp ${catkin_EXPORTED_TARGETS})
target_link_libraries(
  try
  ${catkin_LIBRARIES}
)

add_executable(
  ekf
  src/ekf_node.cpp
  src/Ekf.cpp)
set_target_properties(ekf PROPERTIES COMPILE_FLAGS -std=c++0x)
add_dependencies(ekf deplacement_msg_gencpp ${catkin_EXPORTED_TARGETS})
target_link_libraries(
  ekf
  ${catkin_LIBRARIES}
)

add_executable(
  cartographie
  src/cartographie_node.cpp
  src/landmarks_detection_utils.cpp
  src/math_functions.cpp
  src/conversion_functions.cpp
  src/cartographie_utils.cpp
  src/Segment.cpp
  src/Machine.cpp
  src/Line.cpp
  src/Model.cpp)
set_target_properties(cartographie PROPERTIES COMPILE_FLAGS -std=c++0x)
add_dependencies(cartographie deplacement_msg_gencpp ${catkin_EXPORTED_TARGETS})
target_link_libraries(
  cartographie
  ${catkin_LIBRARIES}
)

add_executable(
  fake_scan
  src/fake_scan_node.cpp)
set_target_properties(fake_scan PROPERTIES COMPILE_FLAGS -std=c++0x)
add_dependencies(fake_scan deplacement_msg_gencpp ${catkin_EXPORTED_TARGETS})
target_link_libraries(
  fake_scan
  ${catkin_LIBRARIES}
)


#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS localisation localisation_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
  PATTERN ".svn" EXCLUDE)

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_localisation.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
