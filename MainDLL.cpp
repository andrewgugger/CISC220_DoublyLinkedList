/*
 * MainDLL.cpp
 *
 *
 *      Author: andrew Gugger
 */
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "TaskManager.hpp"
using namespace std;

int main() {
	srand(time(NULL));
	TaskManager *list = new TaskManager("ListofTasks.txt");
}





