// programming assignment

/*
	In this assignment, we will implement four sorting algorithms.  I have stubbed
	the sorting routines.  Before each sort, my code calls loadArr.  The counts in
	the array should sum to 3946 after loading.  before sorting, the array index may
	be interpreted as an ASCII code; however, the character and its weight stay together.

	You may choose the direction of your sort.
*/

#include <iostream>
#include <fstream>
#include <cstddef>
#include <ctype.h>
#include <utility> // std::swap
using namespace std;

struct statType
{
	char ascii;
	int	weight;
    
    bool operator == (statType& rhs) { return (weight == rhs.weight); }
    bool operator != (statType& rhs) { return (weight != rhs.weight); }
    bool operator <  (statType& rhs) { return (weight <  rhs.weight); }
    bool operator <= (statType& rhs) { return (weight <= rhs.weight); }
    bool operator >  (statType& rhs) { return (weight >  rhs.weight); }
    bool operator >= (statType& rhs) { return (weight >= rhs.weight); }
    
    void operator=(statType& x) {
        this->ascii  = x.ascii;
        this->weight = x.weight;
    }
};

const int ARR_BOUND=256;

void loadArr(statType*);
void printArr(statType*, string="");

void selectionSort(statType*);
void bubbleSort(statType*);
void insertionSort(statType*);
void heapSort(statType*, int);
void heapify(statType*, int, int);


int main() {
	statType* dataArr;
	dataArr=new statType[ARR_BOUND];

	loadArr(dataArr);			// counts the occurrences of each  UTF-8 character in 
                                // a file by using the character's ASCII code as an
                                // array index and incrementing that array position.
                                
  	printArr(dataArr, "Unsorted Data");			// prints the non-zero array positions
    
    selectionSort(dataArr);
    printArr(dataArr, "Selection Sort");	    // prints the non-zero positions of the sorted array

    loadArr(dataArr);
    bubbleSort(dataArr);
	printArr(dataArr, "Bubble Sort");

	loadArr(dataArr);
	insertionSort(dataArr);
	printArr(dataArr, "Insertion Sort");

	loadArr(dataArr);
	heapSort(dataArr, ARR_BOUND);
	printArr(dataArr, "Heap Sort");

    delete [] dataArr;
    
	return 0;
}

// *************************************************

void loadArr(statType* arr) {
	ifstream inFile;
	inFile.open("data_in.txt");  // The input file must be in same directory as source file
	if( inFile.fail() ) {
		cout<<"file error\n";
		cin.get();
		exit(1);
	}

    for(int i=0; i<ARR_BOUND; i++) { // initialize the array
		arr[i].ascii=(char)i;
		arr[i].weight=0;
	}

	char ch;
	while(true) {
		ch=inFile.get();
		//cout<<ch;  // stream to console (optional).
                   // Comment this line to suppress the echo print.

		if( inFile.eof() )
			break;

		arr[(int)ch].weight++;
	}
	inFile.close();
	inFile.clear(); // resets the IO flags
	cin.get();
}

// **************************************************

void printArr(statType* arr, string caption) {
	int chCnt=0;
    cout<<"\n\n\t"<<caption<<endl;
    for(int i=0; i<ARR_BOUND; i++) {
        if(arr[i].weight) {
            cout<<"\t*\t"<<i<<'\t'<<arr[i].ascii<<'\t'<<arr[i].weight<<" ~\n";
            chCnt+=arr[i].weight;
        }
    }
    cout<<"\n\n\t"<<chCnt<<" characters processed.\n\tInput paused, press 'Enter'"; 
		cin.get();
}

//***************************************************

void selectionSort(statType* arr) {
    statType temp;
    
    for (int i = 0; i < ARR_BOUND-1; i++) {
        for (int j = i+1; j < ARR_BOUND; j++) {
            if (arr[j] < arr[i]) {
                // Swap elements
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

// *************************************************

void bubbleSort(statType* arr) {
    statType temp;
    
    for (int i = 0; i < ARR_BOUND-1; i++) {
        // Last i elements are already in place
        for (int j = 0; j < ARR_BOUND-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                // Swap elements
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// *************************************************

void insertionSort(statType* arr) {
    int j;
    statType temp;
    
       for( int i = 1; i < ARR_BOUND; i++) {
          temp = arr[i]; // Store value in temporary variable
          j = i;
          while (j > 0 && arr[j-1] > temp) {
             arr[j] = arr[j-1];
             j--;
          }
          arr[j] = temp;  // Insert into correct position
       }
}

// *************************************************

// Heapify a subtree rooted with node i which is an index in arr
void heapify(statType* arr, int n, int i)
{
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2 * i + 1
    int r = 2 * i + 2; // right = 2 * i + 2

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest]) {
        largest = l;
    }

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest]) {
        largest = r;
    }
    
    // If largest is not root
    if (largest != i) {
        // Swap struct elements
        swap(arr[i].ascii, arr[largest].ascii);
        swap(arr[i].weight, arr[largest].weight);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// *************************************************

void heapSort(statType* arr, int n) {
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    
    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(arr[0].ascii, arr[i].ascii);
        swap(arr[0].weight, arr[i].weight);

        // Call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}
