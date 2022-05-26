#include <iostream>
#include <string>
#include <regex>
#include <windows.h>

using namespace std;

// Дано предложение. Определить содержит ли оно одно из имен : Анна, Антонина, Алевтина, Алла.

bool search(string text)
{
	regex re(".*А(нн|лл|нтонин|левтин)а.*");
	return regex_match(text, re);
}
int main()
{
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string text;
	cout << "Введите текст:" << endl;
	getline(cin, text);
	if (search(text)) cout << "В тексте содержится одно из имен: Анна, Антонина, Алевтина, Алла";
	else cout << "В тексте не содержится ни одно из имен: Анна, Антонина, Алевтина, Алла";
	return 0;
}
