#include <algorithm>
#include <cctype>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class SortApp
{

public:
    const static std::size_t MX_SZ = 2048;

    static std::string numeric_value(const std::string & str)
    {
        std::string numeric_str = "";
        for (std::size_t i = 0; i < str.size(); ++i) {
            if (std::iswspace(str[i])) {
                continue;
            }
            if (str[i] == '-') {
                numeric_str = "-";
                continue;
            }
            if (str[i] == '.') {
                numeric_str += '.';
                continue;
            }
            if (std::isdigit(str[i]) != 0) {
                numeric_str += str[i];
                continue;
            }
            break;
        }

        return numeric_str;
    }

    static bool compn(const std::string & a, const std::string & b)
    {
        std::string numeric_a = numeric_value(a);
        std::string numeric_b = numeric_value(b);

        bool flag_to_comp = true;
        if (numeric_a[0] == '-' && numeric_b[0] == '-') {
            flag_to_comp = false;
        }
        else if (numeric_a[0] == '-' || numeric_b[0] == '-') {
            return !numeric_a.empty() && numeric_a[0] == '-';
        }

        for (size_t i = 0; i < std::min(numeric_a.size(), numeric_b.size()); ++i) {
            if (numeric_a[i] == '.' && numeric_b[i] != '.') {
                return flag_to_comp;
            }
            if (numeric_a[i] != '.' && numeric_b[i] == '.') {
                return !flag_to_comp;
            }
            if (numeric_a[i] != numeric_b[i]) {
                return flag_to_comp ? std::atoi(&numeric_a[i]) < std::atoi(&numeric_b[i]) : std::atoi(&numeric_a[i]) > std::atoi(&numeric_b[i]);
            }
        }

        if (numeric_b[0] == '-') {
            return numeric_a.size() < numeric_b.size();
        }
        if (numeric_a.size() == numeric_b.size()) {
            return a < b;
        }
        return numeric_a.size() < numeric_b.size();
    }

    static bool compf(const std::string & a, const std::string & b)
    {
        for (std::size_t i = 0; i < std::min(a.size(), b.size()); ++i) {
            if (std::tolower(a[i]) == std::tolower(b[i])) {
                continue;
            }
            return std::tolower(a[i]) < std::tolower(b[i]);
        }
        return a.size() < b.size();
    }

    static bool comp(const std::string & a, const std::string & b)
    {
        return a < b;
    }

    static void sort_(std::vector<std::string> & sequence, bool (*comp)(const std::string & a, const std::string & b))
    {
        std::sort(sequence.begin(), sequence.end(), comp);
    }

    static void read_and_sort(const std::string & first_arg, const std::string & input_file, std::vector<std::string> & sequence)
    {
        const std::string f = "-f";
        const std::string n = "-n";
        const std::string nf = "-nf";

        std::ifstream in(input_file);

        std::istream & stream = in.is_open() ? in : std::cin;
        std::string str;

        while (std::getline(stream, str)) {
            sequence.emplace_back(str);
        }

        auto cmp = comp;
        if (first_arg == f) {
            cmp = compf;
        }
        else if (first_arg == n || first_arg == nf) {
            cmp = compn;
        }
        sort_(sequence, cmp);
    }
};

int main(int argc, char ** argv)
{
    std::string file_name = "";
    std::string first_arg = "";
    std::vector<std::string> sequence;
    sequence.reserve(SortApp::MX_SZ);
    if (argc == 2) {
        first_arg = argv[1];
        file_name = argv[1];
    }
    else if (argc == 3) {
        first_arg = argv[1];
        file_name = argv[2];
    }

    SortApp::read_and_sort(first_arg, file_name, sequence);

    for (std::size_t i = 0; i < sequence.size(); ++i) {
        std::cout << sequence[i] << '\n';
    }

    return 0;
}
