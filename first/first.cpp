#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <windows.h>

using namespace std;

// Дан текст и множество подстрок - образцов.
// Сформировать таблицу, содержащую информацию о том, сколько раз каждый из образцов входит в исходный текст.

int check(char sym, vector <char> arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] == sym) return i;
    }
    return -1;
}
int searchBoyerMoore(string pattern, string text)
{
    char sym;
    int s = 0;
    int shift;
    map <char, int> table;
    vector <char> uniqe; 
    for (int i = pattern.length() - 2; i > -2; i--)
    {
        s++;
        if (i == -1) sym = pattern[pattern.length() - 1];
        else sym = pattern[i];
        if (check(sym, uniqe) == -1)
        {
            uniqe.push_back(sym);
            table[sym] = s;
        }
    }
    table['/'] = pattern.length();
    if (pattern.size() <= text.size())
    {
        int i = pattern.size() - 1;
        while (i < text.size())
        {
            int k = 0;
            int j = pattern.length() - 1;
            while (j >= 0)
            {
                if (text[i - k] != pattern[j])
                {
                    if (j == pattern.size() - 1)
                    {
                        if (check(text[i], uniqe) != -1) shift = table[text[i]];
                        else shift = table['/'];
                    }
                    else shift = table[pattern[j]];
                    i += shift;
                    break;
                }
                k++;
                j--;
            }
            if (j == -1)
            {
                return i - k + 1;
            }
        }
    }
    return -1;
}


int main()
{
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string text, pattern;
    map <string, int> shedule;
    cout << "Введите текст:" << endl;
    getline(cin, text);
    cout << "Введите количество слов-шаблонов: ";
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cout << i + 1 << ". ";
        cin >> pattern;
        shedule[pattern] = 0;
    }
    map <string, int> ::iterator it = shedule.begin();
    cout << right << setw(15) << "Слово-шаблон" << setw(25) << "Количество повторений" << endl;
    for (int i = 0; it != shedule.end(); i++, it++)
    {
        string temp_txt = text;
        int idx = searchBoyerMoore(it->first, text);
        if (idx != -1)
        {
            while (idx!=-1)
            {
                (it->second)++;
                temp_txt = temp_txt.substr(idx+1);
                idx = searchBoyerMoore(it->first, temp_txt);
            }
        }
        cout << right << setw(15) << it->first << setw(25) << it->second << endl;
    }
    return 0;
}
