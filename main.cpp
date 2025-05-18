#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
using namespace std;

const string allowedLetters = 
    "abcdefghijklmnopqrstuvwxyz"
    "ąčęėįšųūž";

string cleanWord(const string& word) {
    string result;
    bool hasLetter = false;

    for (size_t i = 0; i < word.size(); ++i) {
        unsigned char c = word[i];

        if ((c & 0x80) == 0) { // ASCII
            char lower = tolower(c);
            if (allowedLetters.find(lower) != string::npos) {
                result += lower;
                hasLetter = true;
            }
        } else {
            // UTF-8 nustatyt kiek uzima 
            size_t len = 1;
            if ((c & 0xE0) == 0xC0) len = 2;
            else if ((c & 0xF0) == 0xE0) len = 3;
            else if ((c & 0xF8) == 0xF0) len = 4;

            if (i + len <= word.size()) {
                string utfChar = word.substr(i, len);

                // patikrint ar LT raide
                if (allowedLetters.find(utfChar) != string::npos) {
                    result += utfChar;
                    hasLetter = true;
                }

                i += len - 1;
            }
        }
    }

    return hasLetter ? result : "";
}




int main() {
    ifstream input("tekstas.txt");
    ofstream outFile("output_words.txt");

    if (!input) {
        cerr << "Error" << endl;
        return 1;
    }

    unordered_map<string, int> wordCount;
    string line;

    while (getline(input, line)) {
        stringstream ss(line);
        string word;

        while (ss >> word) {
            string cleaned = cleanWord(word);
            if (!cleaned.empty()) {
                wordCount[cleaned]++;
            }
        }
    }

    for (const auto& [word, count] : wordCount) {
        if (count > 1) {
            outFile << word << " : " << count << '\n';
        }
    }

    return 0;
}