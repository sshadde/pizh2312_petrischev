#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    
    setlocale(LC_ALL, "Rus");
    
    if (argc < 2) {
        std::cout << "Использование: WordCount.exe [опции] файл1 [файл2 ...]\n";
        return 1;
    }

    bool showLines = false;
    bool showWords = false;
    bool showBytes = false;
    bool showChars = false;

    int fileStartIndex = 1;
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg[0] == '-') {
            for (int j = 1; j < arg.size(); j++) {
                if (arg[j] == 'l') showLines = true;
                else if (arg[j] == 'w') showWords = true;
                else if (arg[j] == 'b') showBytes = true;
                else if (arg[j] == 'c') showChars = true;
            }
        } else {
            fileStartIndex = i;
            break;
        }
    }

    if (!showLines && !showWords && !showBytes && !showChars) {
        showLines = true;
        showWords = true;
        showBytes = true;
    }

    for (int i = fileStartIndex; i < argc; i++) {
        std::string filename = argv[i];
        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cout << "Не удалось открыть файл: " << filename << std::endl;
            continue;
        }

        int lineCount = 0;
        int wordCount = 0;
        int charCount = 0;

        std::string line;
        while (getline(file, line)) {
            lineCount++;
            charCount += line.length() + 1;
            bool inWord = false;

            for (int j = 0; j < line.length(); j++) {
                if (isspace(line[j])) {
                    inWord = false;
                } else {
                    if (!inWord) {
                        wordCount++;
                        inWord = true;
                    }
                }
            }
        }

        file.clear();
        file.seekg(0, std::ios::end);
        int byteCount = file.tellg();
        file.close();

        if (showLines) std::cout << lineCount << " ";
        if (showWords) std::cout << wordCount << " ";
        if (showBytes) std::cout << byteCount << " ";
        if (showChars) std::cout << charCount - 1 << " ";

        std::cout << filename << std::endl;
    }

    return 0;
}
