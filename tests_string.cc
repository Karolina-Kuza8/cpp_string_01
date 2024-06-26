#include <iostream>
#include <utility>
#include <vector>

#include "string_01.h"

using namespace string_toys;

#include <ostream>
namespace Color
{
enum Code
{
    FG_RED = 31,
    FG_GREEN = 32,
    FG_BLUE = 34,
    FG_DEFAULT = 39,
    BG_RED = 41,
    BG_GREEN = 42,
    BG_BLUE = 44,
    BG_DEFAULT = 49
};

class Modifier
{
    Code code;

  public:
    Modifier(Code pCode)
        : code(pCode)
    {
    }
    friend std::ostream& operator<<(std::ostream& os, const Modifier& mod) { return os << "\033[" << mod.code << "m"; }
};
}  // namespace Color

template<class F, class R, class... I>
auto verify(const char* fname, F func, R ref_value, I... inputs) -> bool
{
    auto out_value = func(inputs...);

    static Color::Modifier green(Color::FG_GREEN);
    static Color::Modifier red(Color::FG_RED);
    static Color::Modifier def(Color::FG_DEFAULT);

    std::cout << fname << " : ";
    if (out_value != ref_value) {
        std::cout << red << "Test failed" << def;
    } else {
        std::cout << green << "Test passed" << def;
    }
    std::cout << " for INPUT: ";
    ((std::cout << ' ' << inputs), ...) << "  OUTPUT: " << out_value << '\n';

    return true;
}

auto main() -> int
{
    std::vector<std::pair<std::string, std::string>> data_reverse = {
        {"abc", "cba"}, {"xZz\nqwe", "ewq\nzZx"}, {"Litwo, ojczyzno moja", "ajom onzyzcjo ,owtiL"}};

    for (const auto& data : data_reverse) {
        verify("reverse", reverse, data.second, data.first);
    }

    // ---
    std::vector<std::pair<std::string, std::string>> data_first_to_upper = {
        {"abc", "Abc"}, {"xZz\nqwe", "XZz\nQwe"}, {"Litwo, ojczyzno moja", "Litwo, Ojczyzno Moja"}};

    for (const auto& data : data_first_to_upper) {
        verify("first_to_upper", first_to_upper, data.second, data.first);
    }

    // ---
    std::vector<std::pair<std::string, int>> data_count_vowels = {{"abc", 1}, {"xZz", 0}, {"Litwo, ojczyzno moja", 7}};

    for (const auto& data : data_count_vowels) {
        verify("count_vovels", count_vowels, data.second, data.first);
    }

    // ---
    std::vector<std::pair<std::string, int>> data_sum_digits = {
        {"abc", 0}, {"xZz", 0}, {"Countdown: 3... 2... 1... Start!", 6}, {"First prime numbers are: 3, 5, 7, 11, 13", 21}};

    for (const auto& data : data_sum_digits) {
        verify("sum_digits", sum_digits, data.second, data.first);
    }

    // ---
    std::vector<std::tuple<std::string, std::string, int>> data_search_substr = {
        {"abc", "d", -1}, {"xZz", "z", 2}, {"Litwo, ojczyzno moja", "ojcz", 7}};

    for (const auto& data : data_search_substr) {
        verify("search_substr", search_substr, std::get<2>(data), std::get<0>(data), std::get<1>(data));
    }

    return 0;
}
