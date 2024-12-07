#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;
constexpr int wordSize = 4;

inline std::string extract_x(const std::vector<std::string>& lines, int row, int col)
{
    if(col < 1 || row < 1) return "";
    std::string res{};
    res += lines[row - 1][col - 1];
    res += lines[row - 1][col + 1];
    res += lines[row][col];
    res += lines[row + 1][col - 1];
    res += lines[row + 1][col + 1];
    return res;
}

inline bool is_valid(const std::string& s)
{
    const std::string valid_patterns[] = {
        "MSAMS",
        "MMASS",
        "SMASM",
        "SSAMM",
    };
    for(const std::string& pattern: valid_patterns)
    {
        if(s == pattern) return true;
    }
    return false;
}

int main()
{
    const char *input_path = "inputs/day4.txt";
    ifstream input_file(input_path);
    std::vector<std::string> lines {};
    std::string line;
    while(std::getline(input_file, line))
    {
        lines.push_back(line);
    }
    std::cerr << lines.size() << std::endl;
    int cols = lines[0].length();
    int rows = lines.size();
    long sum = 0;

    for(int i = 0; i < rows; ++i)
    {
        for(int j = 0; j < cols; ++j)
        {
            std::string extracted = extract_x(lines, i, j);
            if(is_valid(extracted))
            {
                sum += 1;
            }
        }
    }
    std::cout << "Sum: " << sum << std::endl;
    return 0;
}