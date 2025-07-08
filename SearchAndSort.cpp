#include<iostream>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include<chrono>

using namespace std;
using namespace std::chrono;

//function to generate n random numbers and store in array
void generateNumbers(int arr[], int n, int maxValue){
    srand(time(0)); //seed for random number generation
    cout<<"Generated Numbers: ";
    for(int i = 0;i < n; i++){
        arr[i] = rand() % (maxValue + 1); //generate random number
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

//partition function for Quick sort
int partition(int arr[], int low, int high){
    int pivot = arr[high]; //choosing last element as pivot
    int i = low - 1;

    for(int j = low; j < high; j++){
        if(arr[j] < pivot){
            i++;
            swap(arr[i], arr[j]); //swap if element is smaller than pivot
        }
    }

    swap(arr[i+1], arr[high]); //swap pivot to correct position
    return i+1;
}

//Quick sort algorithm (recursive)
void quickSort(int arr[], int low, int high){
    if(low < high){
        int p = partition(arr, low, high);
        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}

//merge two sorted halves (used in merge sort)
void merge(int arr[], int left, int mid, int right){
    int n1 = mid - left + 1;
    int n2 = right - mid;

    //temporary arrays
    int* L = new int[n1];
    int* R = new int[n2];

    //copy data to temp arrays
    for(int i = 0;i<n1; i++){
        L[i] = arr[left + i];
    }
    for(int j = 0; j<n2; j++){
        R[j] = arr[mid + 1 + j];
    }

    //merge the arrays
    int i = 0, j = 0, k = left;
    while(i<n1 && j < n2){
        if(L[i] <= R[j]){
            arr[k++] = L[i++];
        }
        else{
            arr[k++] = R[j++];
        }
    }

    //copy remaining elements
    while (i < n1){
        arr[k++] = L[i++];
    }
    while(j < n2){
        arr[k++] = R[j++];
    }

    //free memory
    delete[] L;
    delete[] R;
}

//merge sort algorithm (recursive)
void mergeSort(int arr[], int left, int right){
    if(left < right){
        int mid = left + (right - left) /2;
        mergeSort(arr, left, mid); //sort first half
        mergeSort(arr, mid+1, right); //sort second half
        merge(arr, left, mid, right); //merge both halves
    }
}

int bstep = 0;
//binary search algorithm: returns index if found, else -1
int BinarySearch(int arr[], int first,int last, int target){
    int index;

    if(first > last){
        index = -1;
    }
    else{
        int mid = (first + last) / 2;
        bstep++;

        if(target == arr[mid]){
            index = mid;
        }
        else if(target < arr[mid]){
            index = BinarySearch(arr, first, mid - 1, target);
        }
        else {
            index = BinarySearch(arr, mid + 1, last, target);
        }
    }
    return index;
}

//exponential search: uses binary seacrh within found range
int exponentialSearch(int arr[], int n, int target){
    if(arr[0] == target){
        return 0;
    }

    int bound = 1;
    while(bound < n && arr[bound] <= target){
        bound *= 2; //doubling bound to find range
    }

    int left = bound / 2;
    int right = min(bound, n - 1);

    //perform binary search on sub-array
     
    return BinarySearch(arr, left, right, target);
}

//utility function to display array
void displayArray(int arr[], int n){
    for(int i = 0; i < n; i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}



int main() {
    
    int n;
    int maxValue;
    cout<<"Enter maximum value for random numbers: ";
    cin>>maxValue;
    cout<<"Enter how many random numbers you want to generate: ";
    cin>>n;

    //Dynamically allocate arrays
    int* original = new int[n];
    generateNumbers(original, n, maxValue);

    // Copy original array for separate sorting
    int* arrQuick = new int[n];
    int* arrMerge = new int[n];
    copy(original, original + n, arrQuick);
    copy(original, original + n, arrMerge);
    
    //quick sort and runtime measurement
    auto start = high_resolution_clock::now();
    quickSort(arrQuick, 0, n-1);
    auto end = high_resolution_clock::now();
    auto quickTime = duration_cast<nanoseconds>(end - start);
    cout<<"\nSorted Numbers (using Quick Sort): ";
    displayArray(arrQuick, n);

    //Merge sort and runtime measurement
    start = high_resolution_clock::now();
    mergeSort(arrMerge, 0, n-1);
    end = high_resolution_clock::now();
    auto mergeTime = duration_cast<nanoseconds>(end - start);
    cout<<"\nSorted Numbers (using Merge Sort): ";
    displayArray(arrMerge, n);


    //Search operations
   int target;
   cout<<"\nEnter the number to search: ";
   cin>>target;

   //Binary Search on quick sorted array
   cout<<"\nUsing Binary Search (on Quick Sorted array):"<<endl;

   bstep = 0;
   start = high_resolution_clock::now();
   int result = BinarySearch(arrQuick,0, n-1, target);
   end = high_resolution_clock::now();
   auto binaryTime = duration_cast<nanoseconds>(end - start);
  
   if(result != -1){
        cout<<"\nElement found at index (0-based): "<<result<<endl;
   }
    else{
        cout<<"\nElement not found"<<endl;
    }

    cout<<"Binary Search Steps: "<<bstep<<endl;
    cout<<endl;
    
    //Exponential Search on merge sorted array
    cout<<"\nUsing Exponential Search (on Merge Sorted array):\n";
    start = high_resolution_clock::now();
    int idx2 = exponentialSearch(arrMerge, n, target);
    end = high_resolution_clock::now();
    auto exponentialTime = duration_cast<nanoseconds>(end - start);
    
    if (idx2 != -1){
        cout << "\nElement found at index (0-based): " << idx2 << "\n";
    }
    else{
        cout << "\nElement not found\n";
    }
    
    //display runtime for all algorithms
    cout<<"\n\nQuick Sort Runtime: "<<quickTime.count()<<"ns\n";
    cout<<"Merge Sort Runtime: "<<mergeTime.count()<<"ns\n";
    cout<<"Binary Search Runtime: "<<binaryTime.count()<<"ns\n";
    cout<<"Exponential Search Runtime: "<<exponentialTime.count()<<"ns\n";

    //free dynamically allocated memory
    delete[] original;
    delete[] arrQuick;
    delete[] arrMerge;
    
    return 0;
    
}
