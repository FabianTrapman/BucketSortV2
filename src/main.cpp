#include <iostream>
#include <vector>
#include <random>    
#include <algorithm> 
#include <chrono>    

using namespace std;
using namespace std::chrono;

// Function to find the maximum number of digits in the input vector
int find_maxDigits(vector<int> vec) {
    int maxDigits = 0;
    for (int num : vec) {
        // Convert each number to a string to determine its number of digits
        int numDigits = to_string(num).length();
        maxDigits = max(maxDigits, numDigits); // Update maxDigits if a larger value is found
    }
    return maxDigits;
}

// Function to pad integers with leading zeros to match the maximum digit length
vector<string> pad_integers(vector<int> vec, int maxDigits) {
    vector<string> padded_vec;

    for (int num : vec) {
        string numStr = to_string(num);         // Convert the integer to a string
        int numDigits = numStr.length();       
        int padding = maxDigits - numDigits;   // Calculate the required padding
        
        // Add leading zeros to make all numbers have the same length
        numStr.insert(0, padding, '0');
        padded_vec.push_back(numStr);
    }

    return padded_vec;
}

// Function to perform a distribution pass (assigning values to buckets based on the digit at the current index)
vector<vector<string>> distribution_pass(vector<string> oneD, int index) {
    vector<vector<string>> twoD(10); // 10 buckets (for digits 0-9)

    for (string oneD_value : oneD) {
        // Determine the digit at the specified index and use it as the bucket index
        int row = oneD_value[index] - '0';
        twoD[row].push_back(oneD_value); // Place the value in the corresponding bucket
    }

    return twoD;
}

// Function to perform a gathering pass (combining all buckets back into a single array)
vector<string> gathering_pass(vector<vector<string>> twoD) {
    vector<string> oneD;
    
    for (vector<string> row : twoD) {
        for (string num : row) {
            oneD.push_back(num); // Add all values from each bucket back to the main array
        }
    }

    return oneD;
}

// Core BucketSort function for positive integers
vector<int> BucketSort(vector<int> oneD) {
    int maxDigits = find_maxDigits(oneD); // Find the maximum number of digits in the input
    int maxIndex = maxDigits - 1;         // Start sorting from the least significant digit
    vector<string> oneD_string = pad_integers(oneD, maxDigits); // Pad numbers with leading zeros

    // Perform distribution and gathering passes for each digit position
    for (int i = 0; i < maxDigits; i++) {
        vector<vector<string>> twoD = distribution_pass(oneD_string, maxIndex); // Distribution pass
        oneD_string = gathering_pass(twoD);                                    // Gathering pass
        maxIndex--; // Move to the next more significant digit
    }

    // Convert the sorted strings back to integers
    vector<int> oneD_return;
    for (string num : oneD_string) {
        oneD_return.push_back(stoi(num));
    }
    
    return oneD_return;
}

// Modified BucketSort to handle both positive and negative integers
vector<int> BucketSort_negative(vector<int> oneD) {
    vector<int> positive; // Vector to hold positive numbers
    vector<int> negative; // Vector to hold negative numbers

    // Separate the input into positive and negative numbers
    for (int num : oneD) {
        if (num < 0) {
            negative.push_back(num * -1); // Convert negatives to positives temporarily
        } else {
            positive.push_back(num);
        }
    }

    // Sort positive and negative numbers separately
    positive = BucketSort(positive);
    negative = BucketSort(negative);

    // Reverse the order of negative numbers (descending order for negatives)
    reverse(negative.begin(), negative.end());

    // Convert negatives back to their original form
    for (int i = 0; i < negative.size(); i++) {
        negative[i] *= -1;
    }

    // Combine the sorted negative and positive numbers
    vector<int> sorted_list;
    for (int num : negative) {
        sorted_list.push_back(num);
    }
    for (int num : positive) {
        sorted_list.push_back(num);
    }

    return sorted_list;
}

// Function to collect timing data for various input sizes
vector<vector<int>> timing_data(vector<int> ns, int runs) {
    vector<vector<int>> times; // Vector to store timing results

    for (int n : ns) {
        int total = 0;

        for (int i = 0; i < runs; i++) {
            // Generate a random vector of size `n`
            random_device rnd_device;
            mt19937 mersenne_engine {rnd_device()};
            uniform_int_distribution<int> dist {1, 1000}; // Random numbers in the range 1-1000

            auto gen = [&dist, &mersenne_engine]() {
                return dist(mersenne_engine);
            };

            vector<int> vec(n);
            generate(begin(vec), end(vec), gen); // Fill the vector with random numbers
            
            // Start timing
            steady_clock::time_point begin = steady_clock::now();

            // Sort the vector using BucketSort
            BucketSort(vec);

            // Stop timing
            steady_clock::time_point end = steady_clock::now();

            // Calculate time in microseconds
            int time_ms = duration_cast<microseconds>(end - begin).count();
            total += time_ms;
        }

        // Store the average time for this input size
        times.push_back({n, total / runs});
    }

    return times;
}

// int main() {

//     vector<int> oneD(50);
//     random_device rnd_device;
//     mt19937 mersenne_engine {rnd_device()};
//     uniform_int_distribution<int> dist {-100000, 100000};

//     auto gen = [&dist, &mersenne_engine](){
//         return dist(mersenne_engine);
//     };

//     generate(begin(oneD), end(oneD), gen);


//     cout << "Voor BucketSort: " << endl;
//     for (int num : oneD) {
//         cout << num << " ";
//     }
//     cout << endl;
//     cout << endl;

//     oneD = BucketSort_negative(oneD);

//     cout << "Na BucketSort: " << endl;
//     for (int num : oneD) {
//         cout << num << " ";
//     }

//     return 0;
// }

// Main function to test timing data
int main() {
    vector<int> ns;

    // Generate a list of input sizes (from 10 to 10,000 in steps of 10)
    for (int i = 10; i <= 10000; i += 10) {
        ns.push_back(i);
    }

    int runs = 100; // Number of runs for each input size

    // Collect timing data for the input sizes
    vector<vector<int>> times = timing_data(ns, runs);

    // Output the timing data
    for (vector<int> time : times) {
        cout << time[0] << ", " << time[1] << endl; // Print input size and average time
    }

    return 0;
}
