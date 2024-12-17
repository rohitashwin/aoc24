#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <set>

using namespace std;
using u8 = uint_fast8_t;

vector<u8> parse_input(const string& filename)
{
    ifstream file(filename);
    vector<u8> in;
    string line;
    getline(file, line);
    istringstream iss(line);
    char token;
    while(iss >> token)
    {
        in.push_back(token - '0');
    }
    file.close();
    return in;
}
void print_sequence(const vector<u8>& in)
{
    cout << "Size: " << in.size() << endl;
    for(const auto& i: in)
    {
        cout << (int)i;
    }
    cout << endl;
}

unsigned long long compute_checksum(const vector<u8>& in)
{
    unsigned long long checksum = 0;
    int front_index = 0;
    int back_index = in.size() - 1;
    int fi = in[front_index];
    int bi = in[back_index];
    int front_id = 0;
    int back_id = in.size()/2;
    int curr_pos = 0;
    bool front = true;

    while(true)
    {
        // if(front_index >= back_index) break;

        if(fi <= 0)
        {
            front_index++;
            fi = in[front_index];
            if (front_index % 2 == 0)
                front_id++;
        }
        if(bi <= 0)
        {
            back_index -= 2;
            back_id--;
            bi = in[back_index];
        }

        if(front_index >= back_index) break;

        if(front_index % 2 == 0)
        {
            cout << "[F] Checksum += " << curr_pos << " * " << front_id << endl;
            checksum += curr_pos * front_id;
            fi--;
        }
        else
        {
            cout << "[B] Checksum += " << curr_pos << " * " << back_id << endl;
            checksum += curr_pos * back_id;
            fi--;
            bi--;
        }

        curr_pos++;
    }

    return checksum;
}

int main()
{
    const string filename = "inputs/test.txt";
    vector<u8> in = parse_input(filename);
    unsigned long long checksum = compute_checksum(in);
    cout << "Checksum: " << checksum << endl;
    return 0;
}