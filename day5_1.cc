#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <set>

using namespace std;

struct input
{
    vector<int> left_col, right_col;
    vector< vector<int> > sequences;
};

input parse_input(string filename)
{
    input in;
    ifstream file(filename);
    string line;
    while (getline(file, line))
    {
        if(line.size() < 1) break;
        int left, right;
        left = stoi(line.substr(0, 2));
        right = stoi(line.substr(3, 2));
        in.left_col.push_back(left);
        in.right_col.push_back(right);
    }

    while (getline(file, line))
    {
        vector<int> seq;
        for (int i = 0; i < line.size(); i += 3)
        {
            int num = stoi(line.substr(i, 2));
            seq.push_back(num);
        }
        in.sequences.push_back(seq);
    }

    file.close();
    return in;
}

struct node
{
    set<int> children;
    set<int> parents;
};

node nodes[100];

bool is_sequence_valid(vector<int> seq)
{
    for (int i = 0; i < seq.size(); i++)
    {
        for(int j = i + 1; j < seq.size(); ++j)
        {
            if(nodes[seq[i]].parents.find(seq[j]) != nodes[seq[i]].parents.end() || nodes[seq[j]].children.find(seq[i]) != nodes[seq[j]].children.end())
            {
                return false;
            } 
        }
    }
    return true;
}

int main()
{
    const char* filename = "inputs/day5.txt";
    input in = parse_input(filename);
    int left = 0, right = 0;
    for (int i = 0; i < in.left_col.size(); i++)
    {
        nodes[in.left_col[i]].children.insert(in.right_col[i]);
        nodes[in.right_col[i]].parents.insert(in.left_col[i]);
    }

    long long sum = 0;

    for(int i = 0; i < in.sequences.size(); ++i)
    {
        if(is_sequence_valid(in.sequences[i]))
        {
            sum += in.sequences[i][in.sequences[i].size() / 2];
        }
    }
    cout << "Sum: " << sum << endl;
}