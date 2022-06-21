/*
 * DLL.cpp
 *
 *
 *      Author: andrew Gugger
 */
#include "DNode.hpp"
#include "DLL.hpp"
#include <iostream>
#include <stdlib.h>
#include <typeinfo>
using namespace std;


	DLL::DLL(){  // constructor - initializes an empty list
		last = NULL;
		first = NULL;
		numTasks = 0;
		tothrs = 0;
		totmin = 0;
	}
	DLL::DLL(string t, int p, int h, int m){  // constructor, initializes a list with one new node with data x
		DNode *n = new DNode (t,p,h,m);
		first = n;
		last = n;
		numTasks=1;
		tothrs = h;
		totmin = m;
	}
	/***************************************************************************************************/
	/*Part 1																																		*/
	/***************************************************************************************************/
	void DLL::push(string n, int p, int h, int m) {
    // does what you'd think, with a caveat that if the
	//priority isn't 3, it will move the task up to the end of the set of tasks with that priority.
	//In other words, if the priority is 1, it will traverse the list in reverse order until it finds a
	//task with a priority of 1, and insert the new task between the last task with a priority of
	//1 and the first task with a priority of 2
	//it also updates the total time of the list
		DNode *newNode = new DNode(n, p, h, m); //Name, priority, hours, minutes

		//check if list is empty:
		if(this->numTasks == 0){
			this->first = newNode;
			this->last = newNode;
			this->numTasks +=1;
		}

		//Add tasks to this list and sort them by iterating through in REVERSE:
		//Case of 1 node in list
		else if(this->numTasks==1){
			cout<<"second node adding"<<endl;
			DNode *currNode = this->last;
			if(newNode->task->priority<currNode->task->priority){
				newNode->next = this->first;
				this->first = newNode;
				currNode ->prev = this->first;
			}
			else if(newNode->task->priority>=currNode->task->priority){
				currNode->next = newNode;
				newNode->prev = currNode;
				this->last = newNode;
			}
			this->numTasks+=1;

		}

		//all other cases adding
		else{
			DNode *currNode = this->last;
			while(currNode){
				if(newNode->task->priority>=currNode->task->priority){
					if(currNode==this->last){
						currNode->next = newNode;
						newNode->prev = currNode;
						this->last = newNode;
						break;

					}
					else{
						newNode->next = currNode->next;
						newNode->prev = currNode->next->prev;
						currNode->next->prev = newNode;
						currNode->next = newNode;
						break;
					}
				}
				else{
					currNode = currNode->prev;
				}
			}
			this->numTasks+=1;

		}


	}

	Task *DLL::pop() {
	//does what you'd think - make sure to update the total time of the list.
	//Note -this isn’t all that necessary for this particular project, but I
	//kinda had to make you write pop because it’s //fundamental to so much of
	//linked list data type uses (e.g., stack, undo).
		Task *popTask = this->last->task;
		this->last = this->last->prev;
		this->last->next = NULL;
		return popTask;
	}

	void DLL::printList() {
		//prints out the entire list, along with the total time necessary to complete all tasks
		//on the list
		DNode *currNode = this->first;
		int total_hr = 0;
		int total_min = 0;
		if(this->numTasks == 1) {
			cout << "Total Time Required: "<< currNode->task->hr <<":"<<currNode->task->min<< endl;
			cout << currNode->task->task << endl;
		}
		else {
			cout<<this->first->task->tasknum<<endl;
			while(currNode) {
				total_hr+=currNode->task->hr;
				total_min+=currNode->task->min;
				currNode = currNode->next;
			}
			total_hr += total_min/60;
			total_min = total_min%60;
			cout << "Total Time Required: "<< total_hr <<":"<<total_min<< endl;
			currNode = this->first;
			while(currNode) {
				cout <<"("<<currNode->task->tasknum<<") "<< currNode->task->task << ", "<<currNode->task->priority <<"......... "<< currNode->task->hr<<":"<<currNode->task->min<<endl;
				currNode = currNode->next;
			}
		}


	}

	void DLL::printList(int p) {
		//print out only all the tasks with a priority of p, along with the total time necessary
		//to complete the tasks with a priority of p
		DNode *currNode = this->first;
		int total_hr = 0;
		int total_min = 0;
		if(this->numTasks == 1 && currNode->task->priority ==p) {
			cout << "Total Time Required: "<< currNode->task->hr <<":"<<currNode->task->min<< endl;
			cout << currNode->task->task << endl;
		}
		else {
			while(currNode) {
				if(currNode->task->priority ==p){
					total_hr+=currNode->task->hr;
					total_min+=currNode->task->min;
					currNode = currNode->next;
				}
				else{
					currNode = currNode->next;
				}
			}
			total_hr += total_min/60;
			total_min = total_min%60;
			cout << "Total Time Required: "<< total_hr <<":"<<total_min<< endl;
			currNode = this->first;
			while(currNode) {
				if(currNode->task->priority ==p){
					cout <<"("<<currNode->task->tasknum<<") "<< currNode->task->task << ", "<<currNode->task->priority <<"......... "<< currNode->task->hr<<":"<<currNode->task->min<<endl;
				}
				currNode = currNode->next;
			}
		}
	}

	void DLL::moveUp(int t) {
		// moves task with number tn up one in the list.
	    //If it is at the beginning of the list,
        //it will be moved to the end of the list.
		// NOTE: if this moves a task up before a task with a higher priority (1 is
		// higher priority than 2 - I know the wording is a bit weird), then this
		// changes the priority of the task being moved to that higher priority
		DNode *currNode = this->first;
		while(currNode->task->tasknum != t){
			currNode = currNode->next;
		}

		//moving up if the task being moved is first
		if(currNode ==this->first){
			this->first = currNode->next;
			this->first->prev = NULL;
			this->last->next = currNode;
			currNode->prev = this->last;
			this->last = currNode;
			currNode->next = NULL;
			//change priority to be whatever the priority is of the following task:
			this->last->task->priority = this->last->prev->task->priority;
		}

		else{
			if(currNode->prev ==this->first){
				currNode->prev->next = currNode->next;
				currNode->next->prev = currNode->prev;
				currNode->prev->prev = currNode;
				currNode->next =currNode->prev;
				currNode->prev = NULL;
				this->first = currNode;
			}
			else if(currNode ==this->last){
				this->last = currNode->prev;
				currNode->next = this->last;
				currNode->prev = this->last->prev;
				this->last->prev = currNode;
				this->last->next = NULL;
				currNode->prev->next = currNode;

			}
			else{
				currNode->prev->prev->next = currNode;
				currNode->next->prev = currNode->prev;
				currNode->prev->next=currNode->next;
				currNode->next = currNode->prev;
				currNode->prev = currNode->prev->prev;
				currNode->next->prev = currNode;

			}
			if(currNode->prev){
				if(currNode->next->task->priority!=currNode->task->priority){
					currNode->task->priority = currNode->next->task->priority;
				}
			}
			else if(currNode == this->first){
				currNode->task->priority = currNode->next->task->priority;
			}


		}


	}

	void DLL::listDuration(int *th, int *tm,int p) {
		// gets the list duration in hours and minutes (passed
		//in as pointers) of a particular priority (so the total time
		//needed to complete all tasks with priority of p)
		// I had you pass in the parameters as pointers for practice.
		DNode *currNode = this->first;



		while(currNode->next){
			if(currNode->task->priority==p){
				th+=currNode->task->hr;
				tm+=currNode->task->min;
			}
			currNode = currNode->next;
		}
		cout<<"Total time for task priority of "<<p<<" is "<< th<< ":"<<tm<<endl;

	}


	void DLL::moveDown(int tn) {
		//moves task with task number tn down one in the list.
		//If it is at the end of the list, it will move to
		//beginning of the list.
		//NOTE: if this moves a task after a task with a lower priority (again, 3 is
		//a lower priority than 2) then this changes the priority of the task being
		//moved.
		DNode *currNode = this->first;

		while(currNode->task->tasknum != tn){
			currNode = currNode->next;
		}

		//if the task is at the beginning of the list
		if(currNode==this->first){
			this->first = currNode->next;
			currNode->next = currNode->next->next;
			this->first->next->prev = currNode;
			currNode->prev = this->first;
			this->first->prev = NULL;
			this->first->next = currNode;
			currNode->task->priority = currNode->prev->task->priority;
		}

		else if(currNode==this->last){
			currNode->prev->next=NULL;
			this->last = currNode->prev;
			currNode->prev = NULL;
			currNode->next = this->first;
			this->first->prev = currNode;
			this->first = currNode;
			currNode->task->priority = currNode->next->task->priority;
		}

		else if(currNode->next==this->last){
			currNode->prev->next = this->last;
			this->last->prev = currNode->prev;
			currNode->prev = this->last;
			currNode->next = NULL;
			this->last->next=currNode;
			this->last = currNode;
			currNode->task->priority = currNode->prev->task->priority;

		}
		else{
			currNode->next->next->prev = currNode;
			currNode->prev->next = currNode->next;
			currNode->next->prev = currNode->prev;
			currNode->next = currNode->next->next;
			currNode->prev->next->next = currNode;
			currNode->prev = currNode->prev->next;
			currNode->task->priority = currNode->prev->task->priority;
		}
	}

	int DLL::remove(int tn) {
		//removes a task (based on its number) and updates the total time of the list
		//Make sure you link the next to the previous and the previous to the next.  The
		//biggest catch with this method is making sure you test to make sure the node
		//after and/or the node before the node you’re deleting aren’t NULL (i.e., you’re
		//not deleting the first or last node in the list)
		DNode *currNode = this->first;
		while(currNode->task->tasknum != tn){
			currNode = currNode->next;
		}

		if(currNode==this->first){
			currNode->next->prev = NULL;
			this->first = currNode->next;
			currNode->next = NULL;
			delete currNode;

		}
		else if(currNode==this->last){
			this->last = currNode->prev;
			this->last->next= NULL;
			currNode->prev = NULL;
			delete currNode;

		}
		else{
			currNode->next->prev = currNode->prev;
			currNode->prev->next = currNode->next;
			currNode->next = NULL;
			currNode->prev = NULL;
			delete currNode;
		}

		return 0;


	}

	void DLL::changePriority(int tn, int newp) {
		//changes the priority of the task.  This method also moves the task to the end
		//of the set of tasks with
		//that priority.  In other words, if you have the following:
		/*task1, 1, 2:20
		task2, 1, 3:20
		task3, 1, 1:15
		task4, 2, 3:10
		task5, 2, 1:10
		task6, 3, 3:15
		task7, 3, 2:54

		And you change task6’s priority to 1, the resulting list should be:
		task1, 1, 2:20
		task2, 1, 3:20
		task3, 1, 1:15
		task6, 1, 3:15
		task4, 2, 3:10
		task5, 2, 1:10
		task7, 3, 2:54
		*/
		DNode *currNode = this->first;

		while(currNode->task->tasknum != tn){
			currNode = currNode->next;
		}
		currNode->task->priority = newp;

		if(currNode==this->first){
			this->first = currNode->next;
			this->first->prev = NULL;
		}
		else if(currNode==this->last){
			this->last = currNode->prev;
			this->last->next = NULL;
		}
		else{
			currNode->prev->next = currNode->next;
			currNode->next->prev = currNode->prev;
		}


		DNode *findNode = this->first;
		if(findNode->task->priority<newp){
			while(findNode->task->priority!=newp){
				findNode = findNode->next;
			}
		}
		while(findNode->next->task->priority==newp){
			findNode = findNode->next;
		}
		findNode->next->prev = currNode;
		currNode->next = findNode->next;
		findNode->next = currNode;
		currNode->prev = findNode;

	}

	DLL::~DLL(){
		DNode *tmp = first;
		DNode *tmp2 = first->next;
		while (tmp != NULL) {
			delete tmp;
			tmp = tmp2;
			if (tmp != NULL) {
				tmp2 = tmp2->next;
			}
		}
		first = NULL;
		last = NULL;
		numTasks = 0;
		tothrs = 0;
		totmin = 0;
	}

	/******************Optional Helper Methods********************************/
	void DLL::addTime(int h, int m) {
	}

	void DLL::removeTime(int h, int m) {
	}
	/********************End of Optional Helper Methods ********************/




