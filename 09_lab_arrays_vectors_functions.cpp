// ============================================================
//  FILE     : 09_lab_arrays_vectors_functions.cpp
//  TOPIC    : Arrays, Vectors, Functions — Lab Questions
//  TITLE    : Lab Tasks — Q2 to Q10
//  TYPE     : Lab Task
//  CONCEPTS : Arrays, Vectors, Sorting logic, Primes, Pointers,
//             Overloading, Pass-by-reference, Sum/Average
// ============================================================

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// ============================================================
//  Q2 — 3rd Largest and 3rd Smallest
// ============================================================
void q2_third_largest_smallest() {
    cout << "\n--- Q2: 3rd Largest and 3rd Smallest ---\n";
    int n;
    cout << "How many numbers (min 3): "; cin >> n;
    if (n < 3) { cout << "Need at least 3 numbers.\n"; return; }

    int arr[100];
    cout << "Enter numbers: ";
    for (int i = 0; i < n; i++) cin >> arr[i];

    int max1 = arr[0], max2 = arr[1], max3 = arr[2];
    int min1 = arr[0], min2 = arr[1], min3 = arr[2];

    if (max1 < max2) swap(max1, max2);
    if (max1 < max3) swap(max1, max3);
    if (max2 < max3) swap(max2, max3);

    if (min1 > min2) swap(min1, min2);
    if (min1 > min3) swap(min1, min3);
    if (min2 > min3) swap(min2, min3);

    for (int i = 3; i < n; i++) {
        int x = arr[i];
        if      (x > max1) { max3 = max2; max2 = max1; max1 = x; }
        else if (x > max2) { max3 = max2; max2 = x; }
        else if (x > max3)   max3 = x;

        if      (x < min1) { min3 = min2; min2 = min1; min1 = x; }
        else if (x < min2) { min3 = min2; min2 = x; }
        else if (x < min3)   min3 = x;
    }
    cout << "3rd Largest: " << max3 << endl;
    cout << "3rd Smallest: " << min3 << endl;
}

// ============================================================
//  Q3 — Reverse a Vector
// ============================================================
void q3_reverse_vector() {
    cout << "\n--- Q3: Reverse a Vector ---\n";
    vector<int> nums = {1, 2, 3, 4, 5, 6};
    int n = nums.size();
    for (int i = 0; i < n / 2; i++)
        swap(nums[i], nums[n - i - 1]);
    cout << "Reversed: ";
    for (int x : nums) cout << x << " ";
    cout << endl;
}

// ============================================================
//  Q4 — Subarray with Sum = 0
// ============================================================
void q4_subarray_zero_sum() {
    cout << "\n--- Q4: Subarray with Sum = 0 ---\n";
    int n;
    cout << "Number of elements: "; cin >> n;
    vector<int> nums(n);
    cout << "Enter elements: ";
    for (int& x : nums) cin >> x;

    bool found = false;
    for (int i = 0; i < n && !found; i++) {
        int sum = 0;
        for (int j = i; j < n; j++) {
            sum += nums[j];
            if (sum == 0) { found = true; break; }
        }
    }
    cout << (found ? "Yes, a subarray with sum 0 exists.\n" : "No such subarray.\n");
}

// ============================================================
//  Q5 — Remove Duplicates from Array
// ============================================================
void q5_remove_duplicates() {
    cout << "\n--- Q5: Remove Duplicates ---\n";
    int n;
    cout << "Number of elements: "; cin >> n;
    int arr[100];
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) cin >> arr[i];

    cout << "Without duplicates: ";
    for (int i = 0; i < n; i++) {
        bool dup = false;
        for (int j = 0; j < i; j++)
            if (arr[i] == arr[j]) { dup = true; break; }
        if (!dup) cout << arr[i] << " ";
    }
    cout << endl;
}

// ============================================================
//  Q6 — Prime Numbers in a Range
// ============================================================
bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i < n; i++)
        if (n % i == 0) return false;
    return true;
}

void q6_primes_in_range() {
    cout << "\n--- Q6: Primes in Range ---\n";
    int start, end;
    cout << "Start: "; cin >> start;
    cout << "End:   "; cin >> end;
    int count = 0;
    cout << "Primes: ";
    for (int i = start; i <= end; i++)
        if (isPrime(i)) { cout << i << " "; count++; }
    cout << "\nTotal: " << count << endl;
}

// ============================================================
//  Q7 — Swap and Compare (pass-by-reference)
// ============================================================
void swapValues(int& a, int& b) {
    int temp = a; a = b; b = temp;
}

string compareValues(int a, int b) {
    if (a == b) return "Equal";
    return (a > b) ? "Greater (x > y)" : "Smaller (x < y)";
}

void q7_swap_compare() {
    cout << "\n--- Q7: Swap and Compare ---\n";
    int x, y;
    cout << "Enter two numbers: "; cin >> x >> y;
    cout << "Before: x=" << x << " y=" << y << endl;
    swapValues(x, y);
    cout << "After swap: x=" << x << " y=" << y << endl;
    cout << "Comparison: " << compareValues(x, y) << endl;
}

// ============================================================
//  Q8 — Area Calculator (Function Overloading)
// ============================================================
float area(float r)         { return 3.14f * r * r; }     // circle
float area(float l, float w){ return l * w; }              // rectangle
float area(float b, int h)  { return 0.5f * b * h; }      // triangle

void q8_area_calculator() {
    cout << "\n--- Q8: Area Calculator ---\n";
    cout << "1. Circle\n2. Rectangle\n3. Triangle\n";
    int choice; cin >> choice;
    cout << fixed << setprecision(2);
    if (choice == 1) {
        float r; cout << "Radius: "; cin >> r;
        cout << "Area = " << area(r) << endl;
    } else if (choice == 2) {
        float l, w; cout << "Length Width: "; cin >> l >> w;
        cout << "Area = " << area(l, w) << endl;
    } else if (choice == 3) {
        float b; int h;
        cout << "Base Height: "; cin >> b >> h;
        cout << "Area = " << area(b, h) << endl;
    } else {
        cout << "Invalid choice.\n";
    }
}

// ============================================================
//  Q9 — Find Max using Pointer
// ============================================================
int* findMax(int arr[], int size) {
    int* maxPtr = &arr[0];
    for (int i = 1; i < size; i++)
        if (arr[i] > *maxPtr) maxPtr = &arr[i];
    return maxPtr;
}

void q9_pointer_max() {
    cout << "\n--- Q9: Pointer to Max Element ---\n";
    int n;
    cout << "Number of elements: "; cin >> n;
    int arr[100];
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) cin >> arr[i];
    int* maxPtr = findMax(arr, n);
    cout << "Max value:   " << *maxPtr << endl;
    cout << "At address:  " << maxPtr  << endl;
}

// ============================================================
//  Q10 — Sum and Average
// ============================================================
int  sumArr(int arr[], int size) {
    int total = 0;
    for (int i = 0; i < size; i++) total += arr[i];
    return total;
}
float avgArr(int arr[], int size) { return (float)sumArr(arr, size) / size; }

void q10_sum_average() {
    cout << "\n--- Q10: Sum and Average ---\n";
    int n;
    cout << "Number of elements: "; cin >> n;
    int arr[100];
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) cin >> arr[i];
    int   s = sumArr(arr, n);
    float a = avgArr(arr, n);
    cout << fixed << setprecision(2);
    cout << "Sum: " << s << "\nAverage: " << a << endl;
    cout << (a > 50 ? "Average is above 50.\n" : "Average is below 50.\n");
}

// ----- Main — Run all questions -----
int main() {
    int choice;
    while (true) {
        cout << "\n=== Lab Questions Menu ===\n";
        cout << "2. 3rd Largest/Smallest\n";
        cout << "3. Reverse Vector\n";
        cout << "4. Subarray Sum = 0\n";
        cout << "5. Remove Duplicates\n";
        cout << "6. Primes in Range\n";
        cout << "7. Swap and Compare\n";
        cout << "8. Area Calculator\n";
        cout << "9. Pointer Max\n";
        cout << "10. Sum and Average\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 2:  q2_third_largest_smallest(); break;
            case 3:  q3_reverse_vector();         break;
            case 4:  q4_subarray_zero_sum();      break;
            case 5:  q5_remove_duplicates();      break;
            case 6:  q6_primes_in_range();        break;
            case 7:  q7_swap_compare();            break;
            case 8:  q8_area_calculator();         break;
            case 9:  q9_pointer_max();             break;
            case 10: q10_sum_average();            break;
            case 0:  return 0;
            default: cout << "Invalid.\n";
        }
    }
}
