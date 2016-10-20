#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//File to be opened defined as a constant 
#define FILE "sample.txt"

//Date class to store date published ints
class Date{
public:
    int _month;
    int _day;
    int _year;

    Date(void);
    Date(int, int, int);
    ~Date(void);
};

Date::Date(void)
{
    _month = 0;
    _day = 0;
    _year = 0;
}

Date::Date(int month, int day, int year)
{
    _month = month;
    _day = day;
    _year = year;
}

class Book{
public:
    string _title;
    string _author;
    Date _published;	//Nested Date class
    string _publisher;
    float _price;
    string _isbn;
    int _pages;
    int _copies;

    Book();
    Book(string, string, class Date, string, float, string, int, int);
    ~Book(void);
};

Book::Book(void)
{
    _title = "";
    _author = "";
    Date();
    _publisher = "";
    _price = 0;
    _isbn = "";
    _pages = 0;
    _copies = 0;
}

Book::Book(string title, string author, class Date published, string publisher, float price, string isbn, int pages, int copies)
{
    _title = title;
    _author = author;
    _published = published;
    _publisher = publisher;
    _price = price;
    _isbn = isbn;
    _pages = pages;
    _copies = copies;
}

class Node{
    friend class LinkedList;
private:
    Book *_book;
    Node *_next;
public:
    Node(void);
    Node(Book*);
    Node(Book*, Node*);
    ~Node(void);
};

Node::Node(void)
{
    _book = NULL;
    _next = NULL;
}

Node::Node(Book *book)
{
    _book = book;
    _next = NULL;
}

Node::Node(Book *book, Node *next)
{
    _book = book;
    _next = next;
}

class LinkedList{
private:
    Node *_head;
    Node *_tail;
public:
    LinkedList(void);
    LinkedList(Book*);
    ~LinkedList(void);
    void insert_front(Book*);
    void insert_rear(Book*);
    void print_list(void);
};

LinkedList::LinkedList(void)
{
    _head = NULL;
    _tail = NULL;
}

LinkedList::LinkedList(Book *book)
{
    _head = new Node(book);
    _tail = _head;
}

void LinkedList::insert_front(Book *book)
{
    if(_head == NULL)
    {
        _head = new Node(book);
        _tail = _head;
    }
    else
        _head = new Node(book, _head);
}

void LinkedList::insert_rear(Book *book)
{
    if(_head == NULL)
    {
        _head = new Node(book);
        _tail = _head;
    }
    else
    {
        _tail->_next = new Node(book);
        _tail = _tail->_next;
    }
}

//Print linked list built from myFile
void LinkedList::print_list(void)
{
    Node *temp = _head;

    while(temp != NULL)
    {
    	cout << endl;	//Extra space to clean up output in terminal
        cout << "Title:\t\t" << "\"" << temp->_book->_title << "\"" << endl;
        cout << "Author:\t\t" << temp->_book->_author << endl;
        cout << "Published:\t";
        cout << temp->_book->_published._month << "/";
        cout << temp->_book->_published._day << "/";
        cout << temp->_book->_published._year << endl;
        cout << "Publisher:\t" << temp->_book->_publisher << endl;
        cout << "Price:\t\t$" << temp->_book->_price << endl;
        cout << "ISBN:\t\t" << temp->_book->_isbn << endl;
        cout << "Pages:\t\t" << temp->_book->_pages << endl;
        cout << "Copies:\t\t" << temp->_book->_copies << endl;

        temp = temp->_next;
    }
    cout << endl;	//Extra space to clean up output in terminal
}

//Class deconstructors 
LinkedList::~LinkedList(void)
{

}

Book::~Book(void)
{

}

Date::~Date(void)
{

}

int main(void)
{
    string title;
    string author;
    int month, day, year;
    string publisher;
    float price;
    string isbn;
    int pages;
    int copies;

	LinkedList myList;
    ifstream myFile("sample.txt");

    Book *temp = NULL;

    temp = new Book;

    //Check to make sure memory exists for new Book
    if (temp)
        {
        if (myFile.is_open())
            {
            //Loop through entire file
            while (myFile)
                {
                    if (!getline(myFile, title))
                        break;
                    getline(myFile, author);
                    myFile >> month >> day >> year;
                    myFile.ignore();
                    getline(myFile, publisher);
                    myFile >> price;
                    myFile.ignore();
                    getline(myFile, isbn);
                    myFile >> pages;
                    myFile >> copies;
                    myFile.ignore();

                    //Check to see if list is empy, if so add to top (maybe unnecessary?)
                    if (temp == NULL)
                    	myList.insert_front(new Book(title, author, Date(month, day, year), publisher, price, isbn, pages, copies));
                    else

                    //If list isn't empty, add new Book node to the back of the list
                    myList.insert_rear(new Book(title, author, Date(month, day, year), publisher, price, isbn, pages, copies));
                }

                //Call to print contents of list
                myList.print_list();

                //Close out the file when done reading from it
                myFile.close();
            }
            else
                {
                    cout << "Could not open file!" << endl;
                }
        }
        else
            {
                cout << "Issues allocating space for books!" << endl;
            }

    //Delete temp if it was allocated in memory
    if (temp)
        {
            delete temp;
        }

	return 0;
}