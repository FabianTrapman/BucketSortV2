#include <iostream>
#include <vector>
using namespace std;

// twee arrays:
// - een array met integers van een lengte N
// - een twee-dimensionale array van integers
//      * rijen genummerd van 0 tot 9 (dit zijn als het ware de buckets)
//      * kolommen geïndexeerd van 0 tot N-1

vector<vector<int>> distribution_pass(vector<int> oneD) {

    vector<vector<int>> twoD(10);
    
    for (int oneD_value : oneD) {
        int row = oneD_value % 10;
        twoD[row].push_back(oneD_value);
    }

    return twoD;
}

int main() {

    vector<int> oneD = {170, 45, 75, 90, 802, 24, 2, 66};

    vector<vector<int>> twoD = distribution_pass(oneD);

    for (int i = 0; i < 10; i++) {
        std::cout << "Rij " << i << ": ";
        for (int num : twoD[i]) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}