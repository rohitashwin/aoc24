#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <set>

using namespace std;

struct map_node
{
    bool contains_antinode = false;
};

struct input
{
    array< vector< array<int, 2> >, 256  > antenna_positions;
    set<char> unique_antennas;
    vector< vector<map_node> > map;
    int map_width;
    int map_height;
};

input parse_input(const string& filename)
{
    input in;
    ifstream file(filename);
    string line;
    int row = 0;
    while (getline(file, line))
    {
        for (int col = 0; col < line.size(); ++col)
        {
            if(line[col] == '.') continue;
            in.antenna_positions[line[col]].push_back({row, col});
            in.unique_antennas.insert(line[col]);
        }
        in.map_width = line.size();
        in.map.push_back(vector<map_node>(line.size()));
        ++row;
    }
    file.close();
    return in;
}

bool oob(int row, int col, const input& in)
{
    return row < 0 || row >= in.map_height || col < 0 || col >= in.map_width;
}

long long count_antinodes(input& in)
{
    long long sum = 0;
    for(const auto &uniq_antenna : in.unique_antennas)
    {
        for(int i = 0; i < in.antenna_positions[uniq_antenna].size(); ++i)
        {
            // cout << "Antenna: " << uniq_antenna << " Position: " << in.antenna_positions[uniq_antenna][i][0] << ", " << in.antenna_positions[uniq_antenna][i][1] << endl;
            for(int j = i; j < in.antenna_positions[uniq_antenna].size(); ++j)
            {
                if(i == j) continue;
                int row1 = in.antenna_positions[uniq_antenna][i][0];
                int col1 = in.antenna_positions[uniq_antenna][i][1];
                int row2 = in.antenna_positions[uniq_antenna][j][0];
                int col2 = in.antenna_positions[uniq_antenna][j][1];
                if(!in.map[row1][col1].contains_antinode)
                {
                    sum++;
                }
                in.map[row1][col1].contains_antinode = true;
                if(!in.map[row2][col2].contains_antinode)
                {
                    sum++;
                }
                in.map[row2][col2].contains_antinode = true;
                int row_diff = row2 - row1;
                int col_diff = col2 - col1;
                int possible_antinode_row1 = row1; // - row_diff;
                int possible_antinode_col1 = col1; // - col_diff;
                int possible_antinode_row2 = row2; // + row_diff;
                int possible_antinode_col2 = col2; // + col_diff;
                while(true)
                {
                    possible_antinode_row1 -= row_diff;
                    possible_antinode_col1 -= col_diff;
                    possible_antinode_row2 += row_diff;
                    possible_antinode_col2 += col_diff;
                    if(oob(possible_antinode_row1, possible_antinode_col1, in) && oob(possible_antinode_row2, possible_antinode_col2, in))
                    {
                        break;
                    }
                    if(!oob(possible_antinode_row1, possible_antinode_col1, in))
                    {
                        if(!in.map[possible_antinode_row1][possible_antinode_col1].contains_antinode)
                        {
                            sum++;
                        }
                        in.map[possible_antinode_row1][possible_antinode_col1].contains_antinode = true;
                    }
                    if(!oob(possible_antinode_row2, possible_antinode_col2, in))
                    {
                        if(!in.map[possible_antinode_row2][possible_antinode_col2].contains_antinode)
                        {
                            sum++;
                        }
                        in.map[possible_antinode_row2][possible_antinode_col2].contains_antinode = true;
                    }
                }
                // if(!oob(possible_antinode_row1, possible_antinode_col1, in))
                // {
                //     if(!in.map[possible_antinode_row1][possible_antinode_col1].contains_antinode)
                //     {
                //         sum++;
                //     }
                //     in.map[possible_antinode_row1][possible_antinode_col1].contains_antinode = true;
                // }
                // if(!oob(possible_antinode_row2, possible_antinode_col2, in))
                // {
                //     if(!in.map[possible_antinode_row2][possible_antinode_col2].contains_antinode)
                //     {
                //         sum++;
                //     }
                //     in.map[possible_antinode_row2][possible_antinode_col2].contains_antinode = true;
                // }
            }
        }              
    }
    return sum;
}

void print_map(const input& in)
{
    for(int row = 0; row < in.map_height; ++row)
    {
        for(int col = 0; col < in.map_width; ++col)
        {
            if(in.map[row][col].contains_antinode)
            {
                cout << "X";
            } else {
                cout << ".";
            }
        }
        cout << endl;
    }
}

int main()
{
    const char* filename = "inputs/day8.txt";
    input in = parse_input(filename);
    in.map_height = in.map.size();
    cout << "Antinodes: " << count_antinodes(in) << endl;
    print_map(in);
    return 0;
}