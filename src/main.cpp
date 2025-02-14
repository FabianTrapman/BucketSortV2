#include <iostream>
#include <vector>
#include <random>    // random_device, mt19937, mersenne_engine
#include <algorithm> // generate
#include <chrono>    // Timing functions
using namespace std;
using namespace std::chrono;

int find_maxDigits(vector<int> vec) {
    
    int maxDigits = 0;
    for (int num : vec) {
        int numDigits = std::to_string(num).length();
        maxDigits = std::max(maxDigits, numDigits);
    }

    return maxDigits;
}

vector<string> pad_integers(vector<int> vec, int maxDigits) {
    
    vector<string> padded_vec;

    // Pad each number with leading zeros
    for (int num : vec) {
        std::string numStr = std::to_string(num);
        int numDigits = numStr.length();
        int padding = maxDigits - numDigits;
        
        // Add leading zeros
        numStr.insert(0, padding, '0');
        padded_vec.push_back(numStr);
    }

    return padded_vec;
}

vector<vector<string>> distribution_pass(vector<string> oneD, int index) {

    vector<vector<string>> twoD(10);

    for (string oneD_value : oneD) {
        int row = oneD_value[index] - '0';
        twoD[row].push_back(oneD_value);
    }

    return twoD;
}

vector<string> gathering_pass(vector<vector<string>> twoD) {

    vector<string> oneD;
    
    for (vector<string> row : twoD) {
        for (string num : row) {
            oneD.push_back(num);
        }
    }

    return oneD;
}

vector<int> BucketSort(vector<int> oneD) {
    
    int maxDigits = find_maxDigits(oneD);
    int maxIndex = maxDigits - 1;
    vector<string> oneD_string = pad_integers(oneD, maxDigits);

    for (int i = 0; i < maxDigits; i++) {

        vector<vector<string>> twoD = distribution_pass(oneD_string, maxIndex);
        oneD_string = gathering_pass(twoD);
        maxIndex--;

    }

    vector<int> oneD_return;

    for (string num : oneD_string) {
        oneD_return.push_back(stoi(num));
    }
    
    return oneD_return;
}

vector<int> BucketSort_negative(vector<int> oneD) {
    
    vector<int> positive;
    vector<int> negative;

    for (int num : oneD) {
        if (num < 0) {
            negative.push_back(num * -1);
        } else {
            positive.push_back(num);
        }
    }

    positive = BucketSort(positive);
    negative = BucketSort(negative);

    reverse(negative.begin(), negative.end());

    for (int i = 0; i < negative.size(); i++) {
        negative[i] *= -1;
    }

    vector<int> sorted_list;

    for (int num : negative) {
        sorted_list.push_back(num);
    }
    for (int num : positive) {
        sorted_list.push_back(num);
    }

    return sorted_list;
}

vector<vector<int>> timing_data(vector<int> ns, int runs) {

    vector<vector<int>> times;

    for (int n : ns) {

        int total = 0;

        for (int i = 0; i < runs; i++) {

            // Generate a random vector to sort
            random_device rnd_device;
            mt19937 mersenne_engine {rnd_device()};
            uniform_int_distribution<int> dist {1, 1000};

            auto gen = [&dist, &mersenne_engine](){
                        return dist(mersenne_engine);
                    };

            vector<int> vec(n);

            generate(begin(vec), end(vec), gen);
            

            // Start timing
            steady_clock::time_point begin = steady_clock::now();

            // Do the thing!
            BucketSort(vec);

            // Stop timing
            steady_clock::time_point end = steady_clock::now();

            // Calculate and print time
            int time_ms = duration_cast<microseconds>(end - begin).count();

            total += time_ms;

                }

        times.push_back({n, total/runs});

    }

    return times;

}

int main() {

    vector<int> oneD(50);
    random_device rnd_device;
    mt19937 mersenne_engine {rnd_device()};
    uniform_int_distribution<int> dist {-100000, 100000};

    auto gen = [&dist, &mersenne_engine](){
        return dist(mersenne_engine);
    };

    generate(begin(oneD), end(oneD), gen);


    cout << "Voor BucketSort: " << endl;
    for (int num : oneD) {
        cout << num << " ";
    }
    cout << endl;
    cout << endl;

    oneD = BucketSort_negative(oneD);

    cout << "Na BucketSort: " << endl;
    for (int num : oneD) {
        cout << num << " ";
    }

    return 0;
}

// int main() {

//     // Create a vector to store the generated numbers
//     std::vector<int> ns;

//     // Use a for loop to generate the list
//     for (int i = 10; i <= 10000; i += 10) {
//         ns.push_back(i);
//     }

//     // vector<int> ns = {10, 100, 1000, 10000};

//     // Set the number of runs
//     int runs = 100;

//     // Get the timing data
//     vector<vector<int>> times = timing_data(ns, runs);

//     for (vector<int> time : times) {
//         cout << time[0] << ", " << time[1] << endl;
//     }

//     return 0;
// }