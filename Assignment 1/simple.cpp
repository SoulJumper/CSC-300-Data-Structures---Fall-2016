#include <iostream>	/* cout, cin */
#include <iomanip>	/* setw */

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

void fill(int*,int);
void printa(int*,int);

int main(void)
{
    int length = 100;
    int* a = new int [length]();    //Dynamic allocation of memory for array

    fill(a, length);
    printa(a, length);

    delete[] a;     //Frees up memory used by the dynamically allocated array
}

void fill(int* a, int length)
{
    srand (time(NULL));

    //Iterates through array and assigns a random number to each element
    for (int i = 0; i < length; i++)
    {
        a[i] = 0 + (rand() % 101);
    }
}

void printa(int *a, int length)
{
    int i;

    //iterates through the array and prints each element with a width of 3 and space afterward
    for(i = 0; i < length; i++)
    {
        cout << setw(3) << a[i] << " ";

        //Returns to a new line when the remainder of (i + 1) / 10 == 0
        //(i + 1) because the initial value of i (0) divided by 10 would already be 0
        if((i + 1) % 10 == 0)
        {
            cout << endl;
        }
    }
}

