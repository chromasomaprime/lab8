// Вариант 10

// Дан файл, содержащий английский текст. Найти в тексте N<=2000 самых длинных слов,
// не содержащих ни одной из трех заданных букв. 
// Записать найденные слова в текстовый файл в порядке невозрастания длины.
// Все найденные слова должны быть разными!

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
#include <set>
#include <vector>

// Функция для проверки, содержит ли слово запрещенные буквы
bool containsForbiddenLetters(const std::string& word, const std::set<char>& forbidden)
{
    for (char c : word)
    {
        if (forbidden.count(tolower(c)) > 0)
        {
            return true;
        }
    }
    return false;
}

// Функция для разделения строки на слова
void splitString(const std::string& str, std::vector<std::string>& words)
{
    std::string word;
    for (char c : str)
    {
        if (isalpha(c))
        {
            word += c;
        }
        else
        {
            if (!word.empty())
            {
                words.push_back(word);
                word.clear();
            }
        }
    }

    if (!word.empty())
    {
        words.push_back(word);
    }
}

// Функция для сортировки слов по длине в порядке невозрастания
void sortWordsByLength(std::vector<std::string>& words)
{
    std::sort(words.begin(), words.end(), [](const std::string& a, const std::string& b)
    {
        return a.length() > b.length();
    });
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

    const int maxWords = 2000;
    std::vector<std::string> words;

    splitString(text, words);

    std::set<std::string> uniqueWords;
    std::set<char> forbiddenLetters = {'a', 'b', 'c'}; // Запрещенные буквы

    for (const auto& word : words)
    {
        if (!containsForbiddenLetters(word, forbiddenLetters))
        {
            uniqueWords.insert(word);
        }
    }

    std::vector<std::string> filteredWords(uniqueWords.begin(), uniqueWords.end());

    sortWordsByLength(filteredWords);

    if (filteredWords.size() > maxWords)
    {
        filteredWords.resize(maxWords);
    }

    std::ofstream outputFile("output.txt");
    if (!outputFile.is_open())
    {
        std::cerr << "error" << std::endl;
        return 1;
    }

    for (const auto& word : filteredWords)
    {
        outputFile << word << std::endl;
    }

    outputFile.close();
    std::cout << "new text in output.txt" << std::endl;

    return 0;
}