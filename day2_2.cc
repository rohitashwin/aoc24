#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

inline bool is_invalid(const vector<int>& row, int exclude_index)
{
    vector<int> copy;
    for(size_t i = 0; i < row.size(); ++i)
    {
        if(i != exclude_index)
        {
            copy.push_back(row[i]);
        }
    }
    for(size_t i = 0; i < copy.size()-1; ++i)
    {
        if((copy[0] < copy[1] && copy[i] >= copy[i+1]) || (copy[0] >= copy[1] && copy[i] <= copy[i+1]) || abs(copy[i] - copy[i+1]) > 3)
        {
            return true;
        }
    }
    return false;
}

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
        bool isvalid = false;
        for(size_t j = 0; j < inputs[i].size(); ++j)
        {
            if(!is_invalid(row, j))
            {
                isvalid = true;
                break;
            }
        }
        if(!isvalid)
        {
            valid--;
        }
    }
    cout << "Valid: " << valid << endl;
}