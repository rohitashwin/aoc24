#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

int main()
{
    constexpr char* input_path = "inputs/day1.txt";
    ifstream input_file(input_path);
    long long total_dist = 0;
    vector<long> col1, col2;
    while(!input_file.eof())
    {
        long dist1, dist2;
        input_file >> dist1 >> dist2;
        col1.push_back(dist1);
        col2.push_back(dist2);
    }
    std::sort(col1.begin(), col1.end());
    std::sort(col2.begin(), col2.end());
    for (int i = 0; i < col1.size(); i++)
    {
        total_dist += abs(col1[i] - col2[i]);
    }
    cout << "Total distance: " << total_dist << endl;
}