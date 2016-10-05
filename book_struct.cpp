#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

#define FILE "input.txt"
#define MAX_INDEX 100
#define MAX_STR 100
#define MAX_LINE (MAX_STR-1)

typedef struct book{
    char title[100];
    char author[100];
    char publisher[100];
    float price;
    char isbn[100];
    int pages;
    int copies;
} Book;

struct book collection[100];
int currentIndex = 0;


void indexBook(Book *my_book)
{
    if (currentIndex < MAX_INDEX)
    {
        memcpy(&collection[currentIndex], my_book, sizeof(Book));
        currentIndex++;
    }
    else
    {
        cout << "Collection is full!" << endl;
    }

}

void printCollection(void)
{
    int i;

    for (i = 0; i < currentIndex; i++)
    {
        cout << "Title:\t" << collection[i].title << endl;
        cout << "Author:\t" << collection[i].author << endl;
        cout << "Publisher:\t" << collection[i].publisher << endl;
        cout << "Price:\t" << collection[i].price << endl;
        cout << "ISBN:\t" << collection[i].isbn << endl;
        cout << "Pages:\t" << collection[i].pages << endl;
        cout << "Copies:\t" << collection[i].copies << endl;
        cout << endl;
    }
}

int main()
{
    ifstream fin(FILE);
    Book *temp = NULL;

    temp = new Book;

    if(temp)
    {
        if (fin.is_open())
        {
            while (1)
            {
                if (!fin.getline(temp->title, MAX_LINE))
                    break;
                fin.getline(temp->author, MAX_LINE);
                fin.getline(temp->publisher, MAX_LINE);
                fin >> temp->price;
                fin.ignore();
                fin.getline(temp->isbn, MAX_LINE);
                fin >> temp->pages;
                fin >> temp->copies;
                fin.ignore();
                indexBook(temp);
            }
            printCollection();

            fin.close();
        }
        else
        {
            cout << "Could not open file!" << endl;
        }
    }
    else
    {
        cout << "Could not allocate space for Book Structure!" << endl;
    }

    if (temp)
    {
        delete temp;
    }

    return 0;
}
