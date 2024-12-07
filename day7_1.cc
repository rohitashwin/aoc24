#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

struct input_item
{
    long long res;
    vector<long long> vals;
};

vector<input_item> parse_input(string filename)
{
    vector<input_item> in;
    ifstream file(filename);
    string line;
    while (getline(file, line))
    {
        long long val;
        char _;
        stringstream ss(line);
        ss >> val >> _;
        in.push_back({val, {}});
        while(ss >> val) in.back().vals.push_back(val);
    }
    file.close();
    return in;
}

bool is_possible(long long res, const vector<long long>& vals)
{
    if (vals.size() == 0) return false;
    if (vals.size() == 1) return vals[0] == res;
    long long num1 = vals[0];
    long long num2 = vals[1];
    auto slice = vector<long long>(vals.begin() + 2, vals.end());
    vector<long long> add = {num1 + num2};
    vector<long long> mul = {num1 * num2};
    add.insert(add.end(), slice.begin(), slice.end());
    mul.insert(mul.end(), slice.begin(), slice.end());
    return is_possible(res, add) || is_possible(res, mul);
}

int main()
{
    const char* filename = "inputs/test.txt";
    vector<input_item> in = parse_input(filename);
    long long ressum = 0;
    for(auto& item : in)
    {
        if(is_possible(item.res, item.vals)) ressum += item.res;
    }
    cout << "Sum: " << ressum << endl;
    return 0;
}