#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <set>
#include <regex>

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
    ifstream urls("links.txt");
    ofstream output_count("output_count.txt");
    ofstream output_cross("cross-reference.txt");
    ofstream output_url("output_urls.txt");

    if (!input || !urls) {
        cerr << "Error" << endl;
        return 1;
    }

    set<string> validTLDs;
    string tld;
    while (getline(urls, tld)) {
        validTLDs.insert(tld);
    }

    unordered_map<string, int> wordCount;
    unordered_map<string, set<int>> wordLines;

    regex urlRegex(R"((https?:\/\/)?(www\.)?[\w\-]+\.[a-z]{2,}(\.[a-z]{2,})?([\/\w\-\.\?\=\&\#]*)?)", regex::icase);
    set<string> foundUrls;

    string line;
    int line_number = 0;
    while (getline(input, line)) {

        stringstream ss(line);
        string word;
        line_number++;

        //Zodziu skaiciavimas/trackinimas
        while (ss >> word) {
            string cleaned = cleanWord(word);
            if (!cleaned.empty()) {
                wordCount[cleaned]++;
                wordLines[cleaned].insert(line_number);
            }
        }

         // URL 
        sregex_iterator it(line.begin(), line.end(), urlRegex);
        sregex_iterator end;
        while (it != end) {
            string url = it->str();

            
            // remove protocol if needed
            size_t protocolEnd = url.find("://");
            size_t start = (protocolEnd != string::npos) ? protocolEnd + 3 : 0;

            // only get domain
            size_t slashPos = url.find('/', start);
            string domain = (slashPos != string::npos) ? url.substr(start, slashPos - start) : url.substr(start);

            // extract tld
            size_t lastDot = domain.rfind('.');
            if (lastDot != string::npos) {
                string tldPart = domain.substr(lastDot + 1);
                transform(tldPart.begin(), tldPart.end(), tldPart.begin(), ::tolower);

                if (validTLDs.count(tldPart)) { //check validity
                    foundUrls.insert(url);  
                }
            }

            ++it;
        }
    }

    for (const auto& [word, count] : wordCount) {
        if (count > 1) {
            output_count << word << " : " << count << '\n';
        }
    }

    for (const auto& [word, lines] : wordLines) {

        if(wordCount[word] > 1) { 
                output_cross << word << " : ";
                for (const auto& number : lines) {
                    output_cross << number << " ";
                }

            output_cross << endl;
        }
    }

    output_url << "Rasti URL adresai\n";
    output_url << string(50, '-') << endl;
    for (const string url : foundUrls) {
        output_url << url << endl;
    }

    cout << "Baigta!" << endl;
    return 0;
}