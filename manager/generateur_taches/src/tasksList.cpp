#include <cstdlib>
#include <list>
#include "task.h"
#include "tasksList.h"
#include "product.h"

#include "manager_msg/order.h"  

using namespace std;
using namespace manager_msg;

list<Task> creationListTasksProduct(Product prod,int debut_livr,int fin_livr) {
	list<Task> liste;
	switch(prod.getComplexity())
	{
		case 0:
			liste.push_back(Task(int(orderRequest::TAKE_BASE),prod.getBaseColor(), prod.getComplexity(), 			
							debut_livr,fin_livr,120));
			liste.push_back(Task(int(orderRequest::PUT_CAP),  prod.getCapColor(),  prod.getComplexity(),
							debut_livr,fin_livr,90,25));
			liste.push_back(Task(int(orderRequest::TAKE_CAP), prod.getCapColor(),  prod.getComplexity(),
							debut_livr,fin_livr,60));
			liste.push_back(Task(int(orderRequest::DELIVER),  orderRequest::NONE,prod.getComplexity(),
							debut_livr,fin_livr,30,40));
			break;
		case 1:
			liste.push_back(Task(int(orderRequest::TAKE_BASE), prod.getBaseColor(),  prod.getComplexity(),
							debut_livr,fin_livr,210));
			liste.push_back(Task(int(orderRequest::PUT_RING),  prod.getRingColors(0),  prod.getComplexity(),
							debut_livr,fin_livr,180,60));
			liste.push_back(Task(int(orderRequest::TAKE_RING), prod.getRingColors(0),  prod.getComplexity(),
							debut_livr,fin_livr,120));
			liste.push_back(Task(int(orderRequest::PUT_CAP),   prod.getCapColor(),  prod.getComplexity(),
							debut_livr,fin_livr,90,25));
			liste.push_back(Task(int(orderRequest::TAKE_CAP),  prod.getCapColor(),  prod.getComplexity(),
							debut_livr,fin_livr,60));
			liste.push_back(Task(int(orderRequest::DELIVER),   orderRequest::NONE,prod.getComplexity(),	
							debut_livr,fin_livr,30,40));
			break;
		case 2:
			liste.push_back(Task(int(orderRequest::TAKE_BASE),    prod.getBaseColor(),  prod.getComplexity(),
							debut_livr,fin_livr,270));
    		liste.push_back(Task(int(orderRequest::PUT_RING),     prod.getRingColors(0),  prod.getComplexity(),
    						debut_livr,fin_livr,240,60));
			liste.push_back(Task(int(orderRequest::TAKE_RING),    prod.getRingColors(0),  prod.getComplexity(),
							debut_livr,fin_livr,210));
    		liste.push_back(Task(int(orderRequest::BRING_BASE_RS),prod.getRingColors(1),  prod.getComplexity(),
    						debut_livr,fin_livr,180,60));
			liste.push_back(Task(int(orderRequest::PUT_RING),     prod.getRingColors(1),  prod.getComplexity(),
							debut_livr,fin_livr,150,60));
    		liste.push_back(Task(int(orderRequest::TAKE_RING),    prod.getRingColors(1),  prod.getComplexity(),
    						debut_livr,fin_livr,120));
			liste.push_back(Task(int(orderRequest::PUT_CAP),      prod.getCapColor(),  prod.getComplexity(),
							debut_livr,fin_livr,90,25));
			liste.push_back(Task(int(orderRequest::TAKE_CAP),     prod.getCapColor(),  prod.getComplexity(),
							debut_livr,fin_livr,60));
			liste.push_back(Task(int(orderRequest::DELIVER),      orderRequest::NONE,prod.getComplexity(),
							debut_livr,fin_livr,30,40));
			break;
		case 3:
			liste.push_back(Task(int(orderRequest::TAKE_BASE),    prod.getBaseColor(), prod.getComplexity(),
							debut_livr,fin_livr,390));
			liste.push_back(Task(int(orderRequest::PUT_RING),     prod.getRingColors(0), prod.getComplexity(),
							debut_livr,fin_livr,360,60));
			liste.push_back(Task(int(orderRequest::TAKE_RING),    prod.getRingColors(0), prod.getComplexity(),
							debut_livr,fin_livr,330));
			liste.push_back(Task(int(orderRequest::BRING_BASE_RS),prod.getRingColors(1), prod.getComplexity(),
							debut_livr,fin_livr,300,60));
			liste.push_back(Task(int(orderRequest::BRING_BASE_RS),prod.getRingColors(1), prod.getComplexity(),
							debut_livr,fin_livr,270,60));
			liste.push_back(Task(int(orderRequest::PUT_RING),     prod.getRingColors(1), prod.getComplexity(),			
							debut_livr,fin_livr,240,60));
			liste.push_back(Task(int(orderRequest::TAKE_RING),    prod.getRingColors(1), prod.getComplexity(),
							debut_livr,fin_livr,210));
			liste.push_back(Task(int(orderRequest::BRING_BASE_RS),prod.getRingColors(2), prod.getComplexity(),
							debut_livr,fin_livr,180,60));
			liste.push_back(Task(int(orderRequest::PUT_RING),     prod.getRingColors(2), prod.getComplexity(),
							debut_livr,fin_livr,150,60));
			liste.push_back(Task(int(orderRequest::TAKE_RING),    prod.getRingColors(2), prod.getComplexity(),
							debut_livr,fin_livr,120));
			liste.push_back(Task(int(orderRequest::PUT_CAP),      prod.getCapColor(), prod.getComplexity(),
							debut_livr,fin_livr,90,25));
			liste.push_back(Task(int(orderRequest::TAKE_CAP),     prod.getCapColor(), prod.getComplexity(),
							debut_livr,fin_livr,60));
			liste.push_back(Task(int(orderRequest::DELIVER),      orderRequest::NONE,prod.getComplexity(),
							debut_livr,fin_livr,30,40));
			break;
		default:
			exit(-1);
	}
	return liste;
}

list<Task> creationListTasksAction(int action,Product prod,int debut_livr,int fin_livr) {
	list<Task> liste;
	switch(action)
	{
		case int(orderRequest::UNCAP): 
			liste.push_back(Task(int(orderRequest::UNCAP), prod.getCapColor(),prod.getComplexity(),
							debut_livr,fin_livr,30));
			break;
		case int(orderRequest::DESTOCK):
			liste.push_back(Task(int(orderRequest::DESTOCK),int(orderRequest::NONE),prod.getComplexity(),
							debut_livr,fin_livr,30));
			break;
		case int(orderRequest::STOCK):
			liste.push_back(Task(int(orderRequest::STOCK),  int(orderRequest::NONE),prod.getComplexity(),
							debut_livr,fin_livr,30));
			break;
		default:	
			exit(-2);
	}
	return liste;
}

bool uncapInWork(list<Task> liste){
	bool tmp = false;
	if(liste.begin()->getTitle() == int(orderRequest::UNCAP))
	{
		tmp =true;
	}
	return tmp;
}
