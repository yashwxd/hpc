#include <iostream>
#include <omp.h>
#include <ctime>
#include <cstdlib>

using namespace std;

void find_min(const int *arr, int n)
{
    double min_val = arr[0]; // Initialize min_val with the first element
#pragma omp parallel for reduction(min:min_val)
    for (int i = 0; i < n; i++)
    {
        // Thread-safe access to min_val
        if (arr[i] < min_val)
        {
            min_val = arr[i];
        }
    }
    cout << "\nMinimum Value = " << min_val << endl;
}

void find_max(const int *arr, int n)
{
    double max_val = arr[0]; // Initialize max_val with the first element
#pragma omp parallel for reduction(max:max_val)
    for (int i = 0; i < n; i++)
    {
        // Thread-safe access to max_val
        if (arr[i] > max_val)
        {
            max_val = arr[i];
        }
    }
    cout << "\nMaximum Value = " << max_val << endl;
}

void calculate_avg(const int *arr, int n)
{
    float sum = 0.0;
#pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    float avg = sum / n;
    cout << "\nSum = " << sum << endl;
    cout << "\nAverage = " << avg << endl;
}

int main()
{
    int n;

    cout << "Enter the number of elements in the array: ";
    cin >> n;

    int *arr = new int[n];

    srand(time(0));
    cout << "\nArray elements are: ";
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100;
        cout << arr[i] << ",";
    }

    find_min(arr, n);
    find_max(arr, n);
    calculate_avg(arr, n);

    delete[] arr; // Free dynamically allocated memory

    return 0;
}
