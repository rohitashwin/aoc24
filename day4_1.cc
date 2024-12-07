#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;
constexpr int wordSize = 4;

inline std::string extract_left(const std::vector<std::string>& lines, int row, int col)
{
    if(col < 3) return "";
    std::string result {};
    for(int i = col - 3; i <= col; ++i) result += lines[row][i];
    return reverse(result.begin(), result.end()), result;
}

inline std::string extract_right(const std::vector<std::string>& lines, int row, int col)
{
    if(col > lines[row].size() - 4) return "";
    std::string result {};
    for(int i = col; i <= col + 3; ++i) result += lines[row][i];
    return result;
}

inline std::string extract_up(const std::vector<std::string>& lines, int row, int col)
{
    if(row < 3) return "";
    std::string result {};
    for(int i = row - 3; i <= row; ++i) result += lines[i][col];
    return reverse(result.begin(), result.end()), result;
}

inline std::string extract_down(const std::vector<std::string>& lines, int row, int col)
{
    if(row > lines.size() - 4) return "";
    std::string result {};
    for(int i = row; i <= row + 3; ++i) result += lines[i][col];
    return result;
}

inline std::string extract_up_left(const std::vector<std::string>& lines, int row, int col)
{
    if(row < 3 || col < 3) return "";
    std::string result {};
    for(int i = 0; i < 4; ++i) result += lines[row - i][col - i];
    return result;
}

inline std::string extract_up_right(const std::vector<std::string>& lines, int row, int col)
{
    if(row < 3 || col > lines[row].size() - 4) return "";
    std::string result {};
    for(int i = 0; i < 4; ++i) result += lines[row - i][col + i];
    return result;
}

inline std::string extract_down_left(const std::vector<std::string>& lines, int row, int col)
{
    if(row > lines.size() - 4 || col < 3) return "";
    std::string result {};
    for(int i = 0; i < 4; ++i) result += lines[row + i][col - i];
    return result;
}

inline std::string extract_down_right(const std::vector<std::string>& lines, int row, int col)
{
    if(row > lines.size() - 4 || col > lines[row].size() - 4) return "";
    std::string result {};
    for(int i = 0; i < 4; ++i) result += lines[row + i][col + i];
    return result;
}

inline std::vector<std::string> extract_from_position(const std::vector<std::string>& lines, int row, int col)
{
    std::vector<std::string> result {};
    string res = extract_left(lines, row, col);
    if(res != "") { result.push_back(res); }
    res = extract_right(lines, row, col);
    if(res != "") { result.push_back(res); }
    res = extract_up(lines, row, col);
    if(res != "") { result.push_back(res); }
    res = extract_down(lines, row, col);
    if(res != "") { result.push_back(res); }
    res = extract_up_left(lines, row, col);
    if(res != "") { result.push_back(res); }
    res = extract_up_right(lines, row, col);
    if(res != "") { result.push_back(res); }
    res = extract_down_left(lines, row, col);
    if(res != "") { result.push_back(res); }
    res = extract_down_right(lines, row, col);
    if(res != "") { result.push_back(res); }
    return result;
}

int count_valid(std::vector<std::string>& extracted)
{
    int count = 0;
    for(const std::string& s: extracted)
    {
        count += s == "XMAS" ? 1 : 0;
    }
    return count;
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
            std::vector<std::string> extracted = extract_from_position(lines, i, j);
            sum += count_valid(extracted);
        }
    }
    std::cout << "Sum: " << sum << std::endl;

    // print every extraction for the position 3, 3 and print it for testing
    std::cout << "LEFT EXTRACTION: \n";
    std::cout << extract_left(lines, 3, 3) << std::endl;
    std::cout << "RIGHT EXTRACTION: \n";
    std::cout << extract_right(lines, 3, 3) << std::endl;
    std::cout << "UP EXTRACTION: \n";
    std::cout << extract_up(lines, 3, 3) << std::endl;
    std::cout << "DOWN EXTRACTION: \n";
    std::cout << extract_down(lines, 3, 3) << std::endl;
    std::cout << "UP LEFT EXTRACTION: \n";
    std::cout << extract_up_left(lines, 3, 3) << std::endl;
    std::cout << "UP RIGHT EXTRACTION: \n";
    std::cout << extract_up_right(lines, 3, 3) << std::endl;
    std::cout << "DOWN LEFT EXTRACTION: \n";
    std::cout << extract_down_left(lines, 3, 3) << std::endl;
    std::cout << "DOWN RIGHT EXTRACTION: \n";
    std::cout << extract_down_right(lines, 3, 3) << std::endl;
    return 0;
}