#include <iostream>
#include <vector>
using namespace std;

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

int main() {

    vector<int> oneD = {170, 45, 75, 90, 802, 24, 2, 66};

    oneD = BucketSort(oneD);

    for (int num : oneD) {
        cout << num << " ";
    }

    return 0;
}