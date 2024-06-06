#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// function for gettig max array
int getMax(vector<int>& arr) {
    int max = arr[0];//first we say max in aar 0 to store
    for (size_t i = 1; i < arr.size(); i++) {//using for loops to get each array
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// holding sortung  output after countingSort based on exp
void countingSort(vector<int>& arr, int exp, int base) {
    int n = arr.size();
    vector<int> output(n);
    vector<int> count(base, 0);

    // Store the base and digit
//this is how we do it
//IMPORTANT
//this was the code and I modified with searches: since we have diffrent base
//count[(arr[i] / exp) % 10]++;

    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % base]++;
    }//this is how to get rid of base and counted  in base 10 and sort

    // Change the base and how output in base 8

    for (int i = 1; i < base; i++) {
        count[i] += count[i - 1];
    }

    //OUT PUT THE ARRAY when change the base here
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % base] - 1] = arr[i];
        count[(arr[i] / exp) % base]--;
    }

    //have output array and print it
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

// Radix Sort function
//radix sort time complexity: O(nk)
void radixSort(vector<int>& arr, int base) {
    int max = getMax(arr);

   //every digit needs to have counting sort
//based on time complexity O(n+K)
    for (int exp = 1; max / exp > 0; exp *= base) {
        countingSort(arr, exp, base);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        //check if the base has gotton in command
        cerr << "Usage: " << argv[0] << " <base>" << endl;
        return 1;
    }

//get the base from command line like ./radixsort 8

    int base = atoi(argv[1]);
    if (base != 2 && base != 8 && base != 10 && base != 16) {

//we use cerr for error message and it is important 
//actualy cerr is character error 

cerr << "Invalid base. Supported bases are 2, 8, 10, 16." << endl;

        return 1;
    }

    // random number syntax
    srand(time(nullptr));

    // Sizes of the arrays to sort
    vector<int> sizes = {10, 100, 1000, 10000};

    for (int size : sizes) {
        cout << "Radix Sort: base = " << base << " size = " << size << endl;

        // array with random number
        vector<int> arr(size);
        for (int i = 0; i < size; i++) {
            arr[i] = rand() % 10000; // Random number between 0 and 9999
        }

        // Display unsorted
        if (size == 10) {
            cout << "Unsorted: ";
            for (int number : arr) {
                cout << number << " ";
            }
            cout << endl;
        }

        // Run the radix sort and cal ave
//I searched regardinf this part.
// how to use clock time and check the time taken
        double total_time = 0.0;
        for (int i = 0; i < 10; i++) {
            vector<int> arr_copy = arr;
            clock_t start_time = clock();
            radixSort(arr_copy, base);
            clock_t end_time = clock();
            double time_taken = double(end_time - start_time) / CLOCKS_PER_SEC * 1e9;
            total_time += time_taken;

            cout << "Pass " << i + 1 << ": " << time_taken << " nanoseconds." << endl;

            // Display sorted array for the smallest size
            if (size == 10 && i == 0) {
                cout << "Sorted: ";
                for (int num : arr_copy) {
                    cout << num << " ";
                }
                cout << endl;
            }
        }

        double average_time = total_time / 10.0;
        cout << "Average: " << average_time << " nanoseconds." << endl;
    }

    return 0;
}

