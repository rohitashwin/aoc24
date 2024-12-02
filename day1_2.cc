#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

int main()
{
    constexpr char* input_path = "inputs/day1.txt";
    ifstream input_file(input_path);
    int counting_map[99999] = {0};
    vector<int> col1;
    string line;
    while(!input_file.eof())
    {
        int num1, num2;
        input_file >> num1 >> num2;
        col1.push_back(num1);
        counting_map[num2]++;
    }
    unsigned long long cumsum = 0;
    for (int i = 0; i < col1.size(); i++)
    {
        cumsum += counting_map[col1[i]] * col1[i];
    }
    cout << "Similarity: " << cumsum << endl;
}