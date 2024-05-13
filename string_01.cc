#include "string_01.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <filesystem>

auto main() -> int { return 0; }
namespace fs = std::filesystem;

// Funkcja do sprawdzenia czy plik istnieje i czy jest plikiem tekstowym
bool isTextFile(const std::string& filename) {
    fs::path filePath(filename);
    return fs::exists(filePath) && fs::is_regular_file(filePath) && filePath.extension() == ".txt";
}

// Funkcja do podstawowej analizy tekstu
void analyzeText(const std::string& filename, std::map<std::string, int>& wordCount, int& lineCount, int& wordTotal, int& charTotal) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        ++lineCount;
        std::istringstream iss(line);
        std::string word;
        while (iss >> word) {
            word = string_toys::custom_tolower(word); // Zamiana na małe litery
            ++wordCount[word];
            ++wordTotal;
            charTotal += word.size();
        }
        ++charTotal; // Dodajemy znak nowej linii
    }
}

// Funkcja do zapisu wyników analizy tekstu do pliku
void saveAnalysis(const std::string& filename, const std::map<std::string, int>& wordCount, const std::vector<std::string>& wordsByLength) {
    std::ofstream output(filename);
    output << "Liczba linii: " << wordCount.size() << std::endl;
    output << "Liczba wyrazów: " << wordCount.size() << std::endl;
    output << "Liczba znaków: " << wordCount.size() << std::endl;
    output << std::endl;

    output << "Wystąpienia poszczególnych słów:" << std::endl;
    for (const auto& pair : wordCount) {
        output << pair.first << ": " << pair.second << std::endl;
    }
    output << std::endl;

    output << "Słowa posortowane alfabetycznie:" << std::endl;
    for (const auto& word : wordsByLength) {
        output << word << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Podaj nazwę pliku tekstowego jako argument." << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    if (!isTextFile(filename)) {
        std::cerr << "Plik nie istnieje lub nie jest plikiem tekstowym." << std::endl;
        return 1;
    }

    std::map<std::string, int> wordCount;
    int lineCount = 0;
    int wordTotal = 0;
    int charTotal = 0;

    analyzeText(filename, wordCount, lineCount, wordTotal, charTotal);

    // Sortowanie słów alfabetycznie
    std::vector<std::string> wordsAlphabetically;
    for (const auto& pair : wordCount) {
        wordsAlphabetically.push_back(pair.first);
    }
    std::sort(wordsAlphabetically.begin(), wordsAlphabetically.end());

    // Sortowanie słów według długości
    std::vector<std::string> wordsByLength(wordsAlphabetically);
    std::sort(wordsByLength.begin(), wordsByLength.end(), [](const std::string& a, const std::string& b) {
        if (a.size() == b.size()) {
            return a < b;
        }
        return a.size() < b.size();
    });

    std::string outputFilename = "analysis.txt";
    saveAnalysis(outputFilename, wordCount, wordsByLength);

    std::cout << "Analiza zapisana w pliku: " << outputFilename << std::endl;

    return 0;
}
