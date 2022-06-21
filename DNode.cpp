/*
 * DNode.cpp
 *
 *
 *      Author: andrew Gugger
 */



#include <stdlib.h>
#include <iostream>
#include "DNode.hpp"
#include "Task.hpp"
using namespace std;



DNode::DNode(string t, int p, int h, int m){ //t = type, p = prioty, h = hours, m = minutes
/*You need to write this!!!! */
	task = new Task(t, p, h, m);
	next = NULL;
	prev = NULL;
}


DNode::DNode(){
	task = NULL;
	next = NULL;
	prev = NULL;
}

