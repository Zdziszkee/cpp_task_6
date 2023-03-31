#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Returns the number of spaces needed to make a line reach maxWidth
int getSpacesNeeded(string line, int maxWidth) {
    int spacesNeeded = maxWidth - line.length();
    return spacesNeeded;
}

// Adds spaces to a line to make it reach maxWidth
string justifyLine(string line, int maxWidth) {
    int spacesNeeded = getSpacesNeeded(line, maxWidth);
    int numWords = count(line.begin(), line.end(), ' ') + 1; // Count number of words in the line
    if (numWords == 1) {
        // If there is only one word in the line, pad with spaces on the right
        line += string(spacesNeeded, ' ');
    } else {
        // Otherwise, distribute the spaces evenly between the words
        int spacesPerWord = spacesNeeded / (numWords - 1);
        int extraSpaces = spacesNeeded % (numWords - 1);
        string spaceStr(spacesPerWord, ' '); // Create a string of spaces
        vector<string> words;
        size_t pos = 0;
        string delimiter = " ";
        while ((pos = line.find(delimiter)) != string::npos) {
            words.push_back(line.substr(0, pos));
            line.erase(0, pos + delimiter.length());
        }
        words.push_back(line); // Add the last word to the vector
        string justifiedLine;
        for (int i = 0; i < words.size() - 1; i++) {
            justifiedLine += words[i] + spaceStr;
            if (extraSpaces > 0) {
                justifiedLine += " ";
                extraSpaces--;
            }
        }
        justifiedLine += words.back(); // Add the last word without spaces
        if (justifiedLine.length() < maxWidth) {
            justifiedLine += string(maxWidth - justifiedLine.length(), ' '); // Pad with spaces on the right
        }
        line = justifiedLine;
    }
    return line;
}

// Justifies a block of text to a given maxWidth
string justifyText(string text, int maxWidth) {
    string result;
    size_t pos = 0;
    string delimiter = "\n";
    while ((pos = text.find(delimiter)) != string::npos) {
        string line = text.substr(0, pos);
        result += justifyLine(line, maxWidth) + "\n";
        text.erase(0, pos + delimiter.length());
    }
    result += justifyLine(text, maxWidth); // Justify the last line
    return result;
}

// Example usage
int main() {
    string text = "This is a sample text. It contains some lines that need to be justified.\n";
    text += "This is another line that needs to be justified. It is a bit longer than the previous line.\n";
    int maxWidth = 50;
    cout << justifyText(text, maxWidth) << endl;
    return 0;
}