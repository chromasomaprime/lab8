// Дана строка, содержащая английский текст.
// Вывести в порядке, обратном к алфавитному, слова текста,
// не содержащие повторяющихся букв, в остальных словах удалить гласные буквы.

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <set>
#include <vector>

bool isVowel(char c)
{
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

bool hasUniqueLetters(const std::string& word)
{
    std::set<char> letters;
    for (char c : word)
    {
        if (isalpha(c))
        {
            char lowerChar = tolower(c);
            if (letters.count(lowerChar) > 0)
            {
                return false;
            }
            letters.insert(lowerChar);
        }
    }
    return true;
}

std::string removeVowels(const std::string& word)
{
    std::string result;
    for (char c : word)
    {
        if (isalpha(c) && !isVowel(c))
        {
            result += c;
        }
    }
    return result;
}

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

// Функция для сортировки слов в порядке, обратном к алфавитному
void sortWordsReverse(std::vector<std::string>& words)
{
    std::sort(words.begin(), words.end(), std::greater<std::string>());
}

int main()
{
    std::string text;
    std::cout << "enter text: ";
    std::getline(std::cin, text);

    std::vector<std::string> words;
    splitString(text, words);

    std::vector<std::string> uniqueWords;
    std::vector<std::string> processedWords;

    // Обработка каждого слова
    for (const auto& word : words)
    {
        if (hasUniqueLetters(word))
        {
            uniqueWords.push_back(word);
        }
        else
        {
            processedWords.push_back(removeVowels(word));
        }
    }

    sortWordsReverse(uniqueWords);

    std::cout << "words in reverse order:" << std::endl;
    for (const auto& word : uniqueWords)
    {
        std::cout << word << " ";
    }

    std::cout << "\n processed words with vowels removed:" << std::endl;
    for (const auto& word : processedWords)
    {
        std::cout << word << " ";
    }

    std::cout << std::endl;
    return 0;
}