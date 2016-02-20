#include <ros/ros.h>
#include "sensor_msgs/LaserScan.h"
#include <vector>
#include <cmath>

int main(int argc, char** argv)
{
	ROS_INFO("Starting node FakeScan_node");
	//Initialisation du noeud ROS
	ros::init(argc, argv, "FakeScan_node");
	ros::NodeHandle n;
	//on publie un scan laser sur le topic /fake_scan
	ros::Publisher pub_scan = n.advertise<sensor_msgs::LaserScan>("hardware/fake_scan", 1000);
	//construction du faux scan
	sensor_msgs::LaserScanPtr scan(new sensor_msgs::LaserScan());


    scan->angle_min = -M_PI_2;
    scan->angle_max =  M_PI_2;
    scan->angle_increment = 0.00613592332229;
    scan->range_min = 0;
    scan->range_max = 5;

    std::vector<float> ranges = {0.5870000123977661, 0.5920000076293945, 0.5870000123977661, 0.593999981880188, 0.593999981880188, 0.593999981880188, 0.5879999995231628, 0.5960000157356262, 0.5920000076293945, 0.5879999995231628, 0.5920000076293945, 0.5920000076293945, 0.5879999995231628, 0.5879999995231628, 0.5879999995231628, 0.5879999995231628, 0.5879999995231628, 0.5899999737739563, 0.5879999995231628, 0.5889999866485596, 0.5849999785423279, 0.5870000123977661, 0.5870000123977661, 0.5889999866485596, 0.5899999737739563, 0.5899999737739563, 0.5910000205039978, 0.5910000205039978, 0.5910000205039978, 0.5820000171661377, 0.5849999785423279, 0.5839999914169312, 0.5839999914169312, 0.5820000171661377, 0.5820000171661377, 0.5820000171661377, 0.5770000219345093, 0.5820000171661377, 0.5759999752044678, 0.5839999914169312, 0.5849999785423279, 0.5849999785423279, 0.5849999785423279, 0.5870000123977661, 0.5879999995231628, 0.5889999866485596, 0.5960000157356262, 0.5960000157356262, 0.5960000157356262, 0.5960000157356262, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 1.1779999732971191, 1.1720000505447388, 1.1649999618530273, 1.1640000343322754, 1.1640000343322754, 1.1649999618530273, 1.1640000343322754, 1.1640000343322754, 1.1629999876022339, 1.1610000133514404, 1.1610000133514404, 1.1610000133514404, 1.1579999923706055, 1.156000018119812, 1.1419999599456787, 1.1180000305175781, 1.1139999628067017, 1.090999960899353, 1.0820000171661377, 1.055999994277954, 0.8410000205039978, 0.8410000205039978, 0.8370000123977661, 0.8410000205039978, 0.8460000157356262, 0.847000002861023, 0.8460000157356262, 0.847000002861023, 0.8560000061988831, 0.8560000061988831, 0.8569999933242798, 0.8579999804496765, 0.8619999885559082, 0.8619999885559082, 0.8629999756813049, 0.8669999837875366, 0.8700000047683716, 0.8759999871253967, 0.878000020980835, 0.8820000290870667, 0.8820000290870667, 0.8820000290870667, 0.8939999938011169, 0.9020000100135803, 0.9039999842643738, 0.9039999842643738, 0.9049999713897705, 0.9100000262260437, 0.9129999876022339, 0.9169999957084656, 0.9179999828338623, 0.9210000038146973, 0.9380000233650208, 0.9380000233650208, 0.9390000104904175, 0.9390000104904175, 0.9399999976158142, 0.9399999976158142, 0.9490000009536743, 0.9520000219345093, 0.953000009059906, 0.9639999866485596, 0.9750000238418579, 0.9819999933242798, 0.984000027179718, 0.9850000143051147, 0.9900000095367432, 0.9909999966621399, 0.996999979019165, 1.0019999742507935, 1.0160000324249268, 1.0180000066757202, 1.0199999809265137, 1.0240000486373901, 1.0240000486373901, 1.031999945640564, 1.0410000085830688, 1.0420000553131104, 1.0520000457763672, 1.062000036239624, 1.0640000104904175, 1.0759999752044678, 1.0809999704360962, 1.0870000123977661, 1.090999960899353, 1.0989999771118164, 1.1039999723434448, 1.1089999675750732, 1.1130000352859497, 1.128000020980835, 1.1319999694824219, 1.1399999856948853, 1.156000018119812, 1.1610000133514404, 1.1670000553131104, 1.1799999475479126, 1.1890000104904175, 1.1929999589920044, 1.1979999542236328, 1.2120000123977661, 1.2130000591278076, 1.2339999675750732, 1.2430000305175781, 1.2510000467300415, 1.2640000581741333, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 2.503000020980835, 2.4670000076293945, 2.447999954223633, 2.437000036239624, 2.4170000553131104, 2.4049999713897705, 2.38100004196167, 2.3589999675750732, 2.3399999141693115, 2.3239998817443848, 2.2980000972747803, 2.2899999618530273, 2.2720000743865967, 2.25600004196167, 2.236999988555908, 2.2269999980926514, 2.2149999141693115, 2.193000078201294, 2.188999891281128, 2.1630001068115234, 2.1519999504089355, 2.140000104904175, 2.121000051498413, 2.109999895095825, 2.0910000801086426, 2.0810000896453857, 2.062999963760376, 2.058000087738037, 2.0369999408721924, 2.0329999923706055, 2.01200008392334, 2.01200008392334, 2.01200008392334, 2.433000087738037, 2.434999942779541, 5.599999904632568, 2.434999942779541, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 2.3410000801086426, 2.328000068664551, 2.322999954223633, 2.296999931335449, 2.296999931335449, 2.296999931335449, 2.296999931335449, 4.993000030517578, 5.015999794006348, 5.076000213623047, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 4.086999893188477, 4.074999809265137, 3.9779999256134033, 4.074999809265137, 4.086999893188477, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 1.6740000247955322, 1.659999966621399, 1.659000039100647, 1.659000039100647, 1.659999966621399, 1.659000039100647, 1.659000039100647, 1.659999966621399, 1.659999966621399, 1.659000039100647, 1.659000039100647, 1.659000039100647, 1.6549999713897705, 1.6519999504089355, 1.6519999504089355, 1.6519999504089355, 1.652999997138977, 1.652999997138977, 1.6540000438690186, 1.656000018119812, 1.656000018119812, 1.656000018119812, 1.656000018119812, 1.6549999713897705, 1.6549999713897705, 1.6549999713897705, 1.6549999713897705, 1.6579999923706055, 1.6699999570846558, 1.6640000343322754, 1.6640000343322754, 1.6640000343322754, 1.6649999618530273, 1.6640000343322754, 1.656000018119812, 1.656000018119812, 1.652999997138977, 1.6519999504089355, 1.6519999504089355, 1.649999976158142, 1.649999976158142, 1.6519999504089355, 1.649999976158142, 1.6519999504089355, 1.6519999504089355, 1.6549999713897705, 1.6519999504089355, 1.656000018119812, 1.656000018119812, 1.656000018119812, 1.656000018119812, 1.659999966621399, 1.6640000343322754, 1.6679999828338623, 1.6679999828338623, 1.6670000553131104, 1.6679999828338623, 1.6690000295639038, 1.6699999570846558, 1.6699999570846558, 1.6699999570846558, 1.6729999780654907, 1.6770000457763672, 1.680999994277954, 1.680999994277954, 1.684000015258789, 1.684999942779541, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 5.599999904632568, 3.140000104904175, 3.13100004196167, 3.128999948501587, 3.121999979019165, 3.11899995803833, 3.0999999046325684, 3.0999999046325684, 3.0940001010894775, 3.0789999961853027, 3.0789999961853027, 3.069999933242798, 3.069000005722046, 3.058000087738037, 3.052000045776367, 3.0510001182556152, 3.0480000972747803, 3.0409998893737793, 3.0390000343322754, 3.0360000133514404, 3.0269999504089355, 3.0269999504089355, 3.0260000228881836, 3.0160000324249268, 3.009999990463257, 3.009999990463257, 3.003000020980835, 2.996000051498413, 2.992000102996826, 2.990000009536743, 2.9860000610351562, 2.984999895095825, 2.9809999465942383, 2.9800000190734863, 2.9790000915527344, 0.7020000219345093, 0.7020000219345093, 0.7020000219345093, 0.7080000042915344, 0.7080000042915344, 0.7170000076293945, 0.7170000076293945, 0.7170000076293945, 0.7099999785423279, 0.7099999785423279, 0.7099999785423279, 0.9120000004768372, 1.1200000047683716, 1.2910000085830688, 1.2910000085830688, 1.5, 1.621000051498413, 1.7230000495910645, 1.7690000534057617, 1.7710000276565552, 1.7730000019073486, 1.7979999780654907, 1.8020000457763672, 1.805999994277954, 1.805999994277954, 2.8919999599456787, 5.599999904632568};
    scan->ranges = ranges;
    scan->header.frame_id = "laser_link";

	ros::Rate loop_rate (10);
	while(n.ok())
	{
		// Publish
		pub_scan.publish(scan);
		// Spin
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}