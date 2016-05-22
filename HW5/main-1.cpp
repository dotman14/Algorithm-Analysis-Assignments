//
//  main.cpp
//  HW5
//
/*
 *  Codes works well in Xcode and Microsoft Visual Studio 2013
 *
 *  Created by Hang Dinh on 4/13/2016.
 *	The purpose of this assignment is to perform empirical analysis of sorting algorithms
 */

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;
const int N = 100000; //maximal data size
double qSTime, bSTime;
long long int badSortComparison, quickSortComparison;

/**************************** function prototypes ******************************/

int Hoare_partition(int a[], int first, int last);

void quicksort(int a[], int first, int last);

//Interchanges the values of v1 and v2.
void swapValues(int& v1, int& v2);

//sorts the numbers in a[0...(n-1)].
void badsort(int a[], int n);

/**
 *  Display content of a given array
 *
 *  @param size Size of Array you want to generate values for
 *  @param arr  Array to fill
 */
void arrayDisplay(int size, int * arr);

/**
 *  Generate content for a given array. Implemented using rand() % 99999) + 9999.
 *
 *  @param size Size of Array you want to generate values for
 *  @param arr  Array to fill
 */
void generateArray(int size, int arr[]);

/**
 *  Function to copy dynamic array using reference to pointer
 *
 *  @param origin Original Array
 *  @param dest   Array Copy
 *  @param size   Size of Array
 */
void copyArray(int *& origin, int * dest, int size);

/**
 *  Wrapper function for quick sort and also time it takes to sort a given array
 *
 *  @param arr        Array to quicksort
 *  @param first      First array index
 *  @param last       Last array index
 *  @param arraySize  Size of array
 */
void QSMain(int arr[], int first, int last, int arraySize);

/**
 *  Wrapper function for badsort and also time it takes to sort a given array.
 *  @param arr       Array to badsort
 *  @param arraySize Size of array
 */
void BSMain(int arr[], int arraySize);


/****************************** main function  ********************************/

int main()
{
    int  arraySize;
    char generateArr;
    
    //Random number generator with time as seed
    srand((unsigned) time(0));
    
    cout << "Enter the length of the array to be sorted: ";
    cin >> arraySize;
    
    int * arr = new int[arraySize];
    int * quickSortCpy = new int[arraySize];
    int * badSortCopy = new int[arraySize];
    
    cout << "Do you want to enter values for the input array? (y/n): ";
    cin >> generateArr;
    
    if (generateArr == 'Y' || generateArr == 'y')
    {
        for (int i = 0; i < arraySize; ++i)
        {
            cin >> arr[i];
        }
    }
    else if (generateArr == 'N' || generateArr == 'n')
    {
        generateArray(arraySize, arr);
        
        char seeUnsorted;
        
        cout << "Would you like to see the generated array? (y/n): ";
        cin >> seeUnsorted;
        
        if (seeUnsorted == 'Y' || seeUnsorted == 'y')
        {
            cout << "We have generated " << arraySize << " random numbers for the input array.\n";
            cout << "The array generated is: ";
            arrayDisplay(arraySize, arr);
        }
    }
    
    copyArray(arr, quickSortCpy, arraySize);
    copyArray(arr, badSortCopy, arraySize);
    
    QSMain(quickSortCpy, 0, arraySize - 1, arraySize);
    BSMain(badSortCopy, arraySize);
    
    cout << "\n\n";
    
    //Delete all dynamic arrays
    delete[] arr;
    delete[] quickSortCpy;
    delete[] badSortCopy;
    
    return 0;
}


/****************************** function definitions  ********************************/

int Hoare_partition(int a[], int first, int last)
{
    int pivot = a[first];
    int i = first - 1, j = last + 1;
    while (true)
    {
        do
        {
            quickSortComparison++;
            ++i;
        }
        while (a[i] < pivot);
        do
        {
            quickSortComparison++;
            --j;
        }
        
        while (a[j] > pivot);
        if (i<j)
        {
            swap(a[i], a[j]);
        }
        else
            return j;
    }
}

void quicksort(int a[], int first, int last)
{
    if (last <= first) 	//bast case;
        return; 	//arrays of length <= 1 are sorted
    int p = Hoare_partition(a, first, last);
    quicksort(a, first, p);
    quicksort(a, p + 1, last);
}

void QSMain(int arr[], int first, int last, int arraySize)
{
    time_t quickStart = time(0);
    quicksort(arr, first, last);
    time_t quickEnd = time(0);
    double quickSortTime = difftime(quickEnd, quickStart);
    
    cout << "\n\nSorting the array using quicksort...\n";
    cout << "Time taken by quicksort to sort " << arraySize << " numbers is " <<  quickSortTime << " seconds.\n";
    cout << "Total number of input object comparisons made by quicksort is " << quickSortComparison << "\n";
    
    char displayQArray;
    
    cout << "Would you like to see sorted array (y/n): ";
    cin >> displayQArray;
    
    if (displayQArray == 'Y' || displayQArray == 'y')
    {
        cout << "The array after being sorted is:";
        arrayDisplay(arraySize, arr);
    }
}


void swapValues(int& v1, int& v2)
{
    int temp;
    temp = v1;
    v1 = v2;
    v2 = temp;
}

void badsort(int a[], int n)
{
    int i = 0;
    badSortComparison = 0;
    while (i < n - 1)
    {
        badSortComparison++;
        if (a[i] > a[i + 1])
        {
            swap(a[i], a[i + 1]);
            i = 0;	//Note that i is being reset!
            continue;
        };
        i++;
    }
}

void BSMain(int arr[], int arraySize)
{
    time_t badStart = time(0);
    badsort(arr, arraySize);
    time_t badEnd = time(0);
    double badSortTime = difftime(badEnd, badStart);
    
    cout << "\n\nSorting the array using badsort...\n";
    cout << "Time taken by quicksort to sort " << arraySize << " numbers is " <<  badSortTime << " seconds.\n";
    cout << "Total number of input object comparisons made by badsort is " << badSortComparison << "\n";
    
    char displayQArray;
    
    cout << "Would you like to see sorted array (y/n): ";
    cin >> displayQArray;
    
    if (displayQArray == 'Y' || displayQArray == 'y')
    {
        cout << "The array after being sorted is:";
        arrayDisplay(arraySize, arr);
    }
}


void generateArray(int size, int *arr)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = (rand() % 99999) + 9999; //Minimum number is 9999
    }
}

void arrayDisplay(int size, int arr[])
{
    for (int i = 0; i < size; i++)
    {
        if (i % 10 == 0) //Display 10 values per line
            cout << "\n";
        
        cout << arr[i] << "\t";
    }
}

void copyArray(int *& origin, int * dest, int size)
{
    for (int i = 0; i < size; i++)
        dest[i] = origin[i];
}