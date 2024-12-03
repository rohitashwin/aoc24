#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

enum class parsing_state
{
    idle,
    parsing_name,
    parsing_arg1,
    parsing_arg2
};

struct parser
{
    parsing_state state = parsing_state::idle;
    int internal_counter = 0;
};

void filter_enabled(string& file_source)
{
    string filtered;
    bool enabled = true;
    for(int i = 0; i < file_source.size() - 7; ++i)
    {
        if(file_source[i] == 'd' && file_source[i+1] == 'o' && file_source[i+2] == '(' && file_source[i+3] == ')')
        {
            i += 4;
            enabled = true;
        }
        else if(file_source[i] == 'd' && file_source[i+1] == 'o' && file_source[i+2] == 'n' && file_source[i+3] == '\'' && file_source[i+4] == 't' && file_source[i+5] == '(' && file_source[i+6] == ')')
        {
            i += 7;
            enabled = false;
        }
        if(enabled)
            filtered += file_source[i];
    }
    for(int i = file_source.size() - 7; i < file_source.size(); ++i)
    {
        if(enabled)
            filtered += file_source[i];
    }
    file_source = filtered;
}

int main()
{
    long long accum = 0;
    constexpr char *input_path = "inputs/day3.txt";
    ifstream input_file(input_path);
    char c;
    long long arg1, arg2;
    string arg1_str, arg2_str;
    parser p;
    string file_contents((istreambuf_iterator<char>(input_file)), istreambuf_iterator<char>());
    filter_enabled(file_contents);
    for(const char c: file_contents)
    {
        switch (c)
        {
        case 'm':
        {
            if (p.state == parsing_state::idle)
            {
                p.state = parsing_state::parsing_name;
                p.internal_counter = 1;
            }
            else
            {
                p.state = parsing_state::idle;
                p.internal_counter = 0;
            }
        }
        break;
        case 'u':
        {
            if (p.state == parsing_state::parsing_name && p.internal_counter == 1)
            {
                p.internal_counter = 2;
            }
            else
            {
                p.state = parsing_state::idle;
                p.internal_counter = 0;
            }
        }
        break;
        case 'l':
        {
            if (p.state == parsing_state::parsing_name && p.internal_counter == 2)
            {
                p.internal_counter = 3;
            }
            else
            {
                p.state = parsing_state::idle;
                p.internal_counter = 0;
            }
        }
        break;
        case '(':
        {
            if (p.state == parsing_state::parsing_name && p.internal_counter == 3)
            {
                p.state = parsing_state::parsing_arg1;
                arg1_str = "";
                p.internal_counter = 0;
            }
            else
            {
                p.state = parsing_state::idle;
                p.internal_counter = 0;
            }
        }
        break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        {
            if (p.state == parsing_state::parsing_arg1)
            {
                if (p.internal_counter < 3)
                {
                    arg1_str += c;
                    p.internal_counter++;
                }
                else
                {
                    arg1_str = "";
                    p.state = parsing_state::idle;
                    p.internal_counter = 0;
                }
            }
            else if (p.state == parsing_state::parsing_arg2)
            {
                if (p.internal_counter < 3)
                {
                    arg2_str += c;
                    p.internal_counter++;
                }
                else
                {
                    arg2_str = "";
                    p.state = parsing_state::idle;
                    p.internal_counter = 0;
                }
            }
            else
            {
                p.state = parsing_state::idle;
                p.internal_counter = 0;
            }
        }
        break;
        case ',':
        {
            if (p.state == parsing_state::parsing_arg1)
            {
                arg1 = stoll(arg1_str);
                arg1_str = "";
                p.state = parsing_state::parsing_arg2;
                arg2_str = "";
                p.internal_counter = 0;
            }
            else
            {
                p.state = parsing_state::idle;
                p.internal_counter = 0;
            }
        }
        break;
        case ')':
        {
            if (p.state == parsing_state::parsing_arg2)
            {
                arg2 = stoll(arg2_str);
                arg2_str = "";
                accum += arg1 * arg2;
                p.state = parsing_state::idle;
                p.internal_counter = 0;
            }
            else
            {
                p.state = parsing_state::idle;
                p.internal_counter = 0;
            }
        }
        break;
        default:
        {
            p.state = parsing_state::idle;
            p.internal_counter = 0;
            arg1_str = "";
            arg2_str = "";
        }
        break;
        }
    }
    std::cout << "Accum: " << accum << std::endl;
}