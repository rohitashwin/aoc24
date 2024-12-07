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

bool is_pair_valid(int left, int right)
{
    return nodes[left].parents.find(right) == nodes[left].parents.end() && nodes[right].children.find(left) == nodes[right].children.end();
}

bool is_sequence_valid(const vector<int>& seq)
{
    for (int i = 0; i < seq.size(); i++)
    {
        for(int j = i + 1; j < seq.size(); ++j)
        {
            if(!is_pair_valid(seq[i], seq[j]))
            {
                return false;
            } 
        }
    }
    return true;
}

vector<int> sort_seq(const vector<int>& seq)
{
    // sorting rule: for every two numbers a and b, they should satisfy is_pair_valid(a, b)
    auto sorter_func = [](int a, int b) -> bool
    {
        return is_pair_valid(a, b);
    };
    vector<int> sorted_seq = seq;
    sort(sorted_seq.begin(), sorted_seq.end(), sorter_func);
    return sorted_seq;
}

void print_seq(const vector<int>& seq)
{
    cout << "[";
    for(int i = 0; i < seq.size() - 1; ++i)
    {
        cout << seq[i] << " ";
    }
    cout << seq[seq.size() - 1] << "]" << endl;
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
        if(!is_sequence_valid(in.sequences[i]))
        {
            auto sorted = sort_seq(in.sequences[i]);
            sum += sorted[sorted.size() / 2];
        }
    }
    cout << "Sum: " << sum << endl;
}