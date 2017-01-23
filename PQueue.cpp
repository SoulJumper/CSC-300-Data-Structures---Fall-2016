#include <iostream>
#include <fstream>
#include <string>

#define FILE "input.txt"

using namespace std;

//Class used to store info about each person
class Person{
	friend class PQueue;
private:
	Person *_next;
public:
	int _ticket;			//Ticket #
	string _name;			//First name
	Person(int, string);	//Initialize person
	Person(void);
};

Person::Person(void)
{
	_ticket = 0;
	_name = "";
	_next = NULL;
}

Person::Person(int ticket, string name)
{
	_ticket = ticket;
	_name = name;
}

//Priority queue used to serve each person
class PQueue{
private:
	int _size;
	Person *_front;
	Person *_back;
	Person *_next;
public:
	PQueue(void);			//Initialize PQueue
	~PQueue(void);			//PQueue destructor	
	void enqueue(int ticket, string name);
	void dequeue(void);
	Person* front(void);
	Person* back(void);
	bool empty(void);
	int size(void);
};

PQueue::PQueue(void)
{
	_size = 0;
	_front = NULL;
	_back = NULL;
	_next = NULL;
}

//Destructor 
PQueue::~PQueue(void)
{
	while(!this->empty())
		this->dequeue();
}

//Creates new Person, sorts them, and adds them to queue
void PQueue::enqueue(int ticket, string name)
{
	Person *temp, *p;
	temp = new Person;
	temp->_ticket = ticket;
	temp->_name = name;

	if(temp)	//Memory validation 
	{
		//Checks list for NULL, then checks new ticket # with current front's #
		if(_front == NULL || ticket < _front->_ticket)
		{
			temp->_next = _front;
			_front = temp;
		}
		else
		{
			p = _front;		//Point to front node

			//Traverse queue comparing ticket numbers
			while(p->_next != NULL && p->_next->_ticket <= ticket)
				p = p->_next;

			//Sets temp node equal to the reference that *p finds when comparing
			temp->_next = p->_next;
			p->_next = temp;
		}
	}
	else
	{
		cout << "Couldn't allocate space for new Person!" << endl;
	}
	
}

void PQueue::dequeue(void)
{
	Person *temp = _front;

	if(temp)
	{
		_front = _front->_next;
		delete temp;
	}
	temp = NULL;
}

Person* PQueue::front(void)
{
	Person *temp;
	temp = _front;

	return temp;
}

Person* PQueue::back(void)
{
	Person *temp;
	temp = _front;

	//Traverse queue until the end is found and return it as temp
	while(temp->_next != NULL)
		temp = temp->_next;

	return temp;
}

bool PQueue::empty(void)
{
	return (_front == NULL);
}

//Keeps track of queue size
int PQueue::size(void)
{
	_size++;
	return _size;
}


int main (void)
{
	int ticket;
	string name;

	PQueue my_queue;
	
	ifstream myFile("input.txt");
	
	if(myFile.is_open())
	{	
		while(myFile)
		{
			myFile >> ticket;
			myFile.ignore();
			getline(myFile, name);
			my_queue.enqueue(ticket, name);		//Pass variables to enqueue to add person to list
			my_queue.size();					//Increment size by 1 each pass
		}

		myFile.close();
	} 
	else
	{
		cout << "That file could not be opened!" << endl;
	}
	
	cout << endl;  //To clean up output in terminal

	//Traverse through queue while it has nodes in it and list names from them
	while(!my_queue.empty())
	{
		cout << "Admitting " << my_queue.front()->_name << "..." << endl;
		my_queue.dequeue();
	}

	cout << endl << endl;	//To clean up output in terminal

	return 0;
}
