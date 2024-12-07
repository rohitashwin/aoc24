#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <set>

using namespace std;

constexpr const int map_width = 130;
constexpr const int map_height = 130;

enum class direction
{
    up = 1,
    down = 2,
    left = 4,
    right = 8,
    none = 0
};

struct map_node
{
    bool visited = false;
    bool obstacle = false;
    int direction = 0;
};

map_node pat_map[map_width][map_height];
int start_row = 0;
int start_col = 0;
direction start_direction = direction::none;
direction current_direction = direction::none;

void parse_map(const string& filename)
{
    ifstream file(filename);
    string line;
    int row = 0;  // Changed from y to row for clarity
    while (getline(file, line))
    {
        for (int col = 0; col < line.size(); ++col)  // Changed from x to col
        {
            if (line[col] == '#')
            {
                // orig_map[row][col].obstacle = true;  // Swapped order to [row][col]
                pat_map[row][col].obstacle = true;  // Swapped order to [row][col]
            }
            else
            {
                switch(line[col])
                {
                    case '^':
                        start_direction = direction::up;
                        current_direction = direction::up;
                        start_row = row;    // Fixed from x
                        start_col = col;    // Fixed from y
                        break;
                    case 'v':
                        start_direction = direction::down;
                        current_direction = direction::down;
                        start_row = row;
                        start_col = col;
                        break;
                    case '<':
                        start_direction = direction::left;
                        current_direction = direction::left;
                        start_row = row;
                        start_col = col;
                        break;
                    case '>':
                        start_direction = direction::right;
                        current_direction = direction::right;
                        start_row = row;
                        start_col = col;
                        break;
                    default:
                        break;
                }
            }
        }
        ++row;
    }
    file.close();
}

bool is_next_obstacle(int row, int col, direction dir)
{
    switch(dir)
    {
        case direction::up:
            // if(row - 1 < 0) return true;
            return pat_map[row - 1][col].obstacle;
        case direction::down:
            // if(row + 1 >= map_height) return true;
            return pat_map[row + 1][col].obstacle;  // Fixed from col + 1
        case direction::left:
            // if(col - 1 < 0) return true;
            return pat_map[row][col - 1].obstacle;  // Fixed from row - 1
        case direction::right:
            // if(col + 1 >= map_width) return true;
            return pat_map[row][col + 1].obstacle;
        default:
            return false;
    }
}

bool is_cycle(int row, int col, direction dir)
{
    if(pat_map[row][col].visited && ((pat_map[row][col].direction & static_cast<int>(dir)) != 0))
    {
        return true;
    }
    return false;
}

bool is_done(int row, int col, direction dir)
{
    switch(dir)
    {
        case direction::up:
            return row - 1 < 0;
        case direction::down:
            return row + 1 >= map_height;
        case direction::left:   
            return col - 1 < 0;
        case direction::right:
            return col + 1 >= map_width;
        default:
            return false;
    }
}

void print_map()
{
    for (int row = 0; row < map_height; ++row)
    {
        for (int col = 0; col < map_width; ++col)
        {
            if(pat_map[row][col].obstacle)
            {
                cout << "#";
            } 
            else if (pat_map[row][col].visited)
            {
                cout << "X";
            } 
            else 
            {
                cout << ".";
            }
        }
        cout << endl;
    }
}

long long solve()
{
    int row = start_row;
    int col = start_col;
    long long sum = 0;
    while (true)
    {
        if(row < 0 || row >= map_height || col < 0 || col >= map_width)
        {
            break;
        }
        pat_map[row][col].direction |= static_cast<int>(current_direction);
        if(!pat_map[row][col].visited)
        {
            sum++;
            pat_map[row][col].visited = true;
        }
        if(is_done(row, col, current_direction))
        {
            return sum;
        }
        if(is_next_obstacle(row, col, current_direction))
        {
            switch(current_direction)
            {
                case direction::up:
                    current_direction = direction::right;
                    break;
                case direction::down:
                    current_direction = direction::left;
                    break;
                case direction::left:
                    current_direction = direction::up;
                    break;
                case direction::right:
                    current_direction = direction::down;
                    break;
                default:
                    break;
            }
        } else {
            switch(current_direction)
            {
                case direction::up:
                    --row;
                    break;
                case direction::down:
                    ++row;
                    break;
                case direction::left:
                    --col;
                    break;
                case direction::right:
                    ++col;
                    break;
                default:
                    break;
            }
        }
    }
    return false;
}

int main()
{
    const char* filename = "inputs/day6.txt";
    parse_map(filename);
    long long sum = 0;
    sum = solve();
    cout << "Sum: " << sum << endl;
    return 0;
}