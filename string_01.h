#ifndef CPP_STRING_H
#define CPP_STRING_H


namespace string_toys {

auto reverse(const std::string& str) -> std::string {
    std::string reversed(str.rbegin(), str.rend());
    return reversed;
}

auto first_to_upper(const std::string& str) -> std::string {
    std::string result = str;
    if (!result.empty()) {
        result[0] = toupper(result[0]);
    }
    return result;
}

auto count_vowels(const std::string& str) -> int {
    int count = 0;
    for (char c : str) {
        if (tolower(c) == 'a' || tolower(c) == 'e' || tolower(c) == 'i' || tolower(c) == 'o' || tolower(c) == 'u') {
            ++count;
        }
    }
    return count;
}

auto sum_digits(const std::string& str) -> int {
    int sum = 0;
    for (char c : str) {
        if (isdigit(c)) {
            sum += c - '0';
        }
    }
    return sum;
}

auto search_substr(const std::string& str, const std::string& substr) -> int {
    size_t pos = str.find(substr);
    if (pos != std::string::npos) {
        return pos;
    }
    return -1;
}

auto custom_serach(const char* str, const char* substr) -> int {
    const char* result = strstr(str, substr);
    if (result != nullptr) {
        return result - str;
    }
    return -1;
}

}  // namespace string_toys

#endif /* CPP_STRING_H */
