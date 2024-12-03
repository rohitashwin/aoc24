#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

int main()
{
    constexpr char* input_path = "inputs/day2.txt";
    ifstream input_file(input_path);
    std::string line;
    vector< vector<int> > inputs;
    while(getline(input_file, line))
    {
        std::stringstream ss(line);
        vector<int> row;
        int num;
        while(ss >> num)
        {
            row.push_back(num);
        }
        inputs.push_back(row);
    }
    int valid = inputs.size();
    for(size_t i = 0; i < inputs.size(); ++i)
    {
        const vector<int>& row = inputs[i];
        bool increasing = row[0] < row[1];
        for(size_t j = 0; j < inputs[i].size()-1; ++j)
        {
            if((increasing && row[j] >= row[j+1]) || (!increasing && row[j] <= row[j+1]) || abs(row[j] - row[j+1]) > 3)
            {
                valid--;
                break;
            }
        }
    }
    cout << "Valid: " << valid << endl;
}