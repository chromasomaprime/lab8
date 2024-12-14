// В текстовом файле input.txt записан английский текст.
// Найти в тексте слова, содержащие две одинаковые гласные буквы подряд,
// записать их заглавными буквами и указать после каждого такого слова в скобках найденные буквы.
// Полученный текст записать в файл output.txt. Весь текст, кроме найденных слов,
// должен остаться неизменным, включая и знаки препинания

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

bool hasDoubleVowels(const std::string& word, char& doubleVowel)
{
    const std::string vowels = "aeiouAEIOU";
    for (size_t i = 0; i < word.length() - 1; ++i)
    {
        if (vowels.find(word[i]) != std::string::npos && word[i] == word[i + 1])
        {
            doubleVowel = word[i];
            return true;
        }
    }
    return false;
}

std::string processWord(const std::string& word)
{
    char doubleVowel;
    if (hasDoubleVowels(word, doubleVowel))
    {
        std::string upperWord = word;
        for (char& c : upperWord)
        {
            c = toupper(c);
        }
        return upperWord + doubleVowel + doubleVowel;
    }
    return word;
}

void processText(const std::string& text, std::ofstream& outputFile)
{
    std::string currentWord;
    for (char c : text)
    {
        if (isalpha(c))
        {
            currentWord += c;
        }
        else
        {
            if (!currentWord.empty())
            {
                outputFile << processWord(currentWord);
                currentWord.clear();
            }
            outputFile << c;
        }
    }
    if (!currentWord.empty())
    {
        outputFile << processWord(currentWord);
    }
}

int main()
{
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open())
    {
        std::cerr << "error" << std::endl;
        return 1;
    }

    std::string text((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    std::ofstream outputFile("output.txt");
    if (!outputFile.is_open())
    {
        std::cerr << "error" << std::endl;
        return 1;
    }

    processText(text, outputFile);

    outputFile.close();
    std::cout << "new text in output.txt" << std::endl;

    return 0;
}