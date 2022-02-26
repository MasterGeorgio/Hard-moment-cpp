// TestProject2.cpp : Defines the entry point for the console application.
//


#include <iostream>
#include <fstream>
#include <iomanip>

#include <string>
#include <vector>
#include <algorithm>
#include <Windows.h>

#include "Timer.hpp"

using namespace std;


// Task 1
template <class T>
void Swap(T * t1, T * t2) {
	T t = *t1;
	*t1 = *t2;
	*t2 = t;
}
void Task_1() {
	cout << "Task 1" << endl;

	int *a = new int(10);
	int *b = new int(20);

	cout << a << endl << b << endl;
	cout << endl;
	cout << *a << endl << *b << endl;
	Swap(&a, &b);
	cout << endl;
	cout << a << endl << b << endl;
	cout << endl;
	cout << *a << endl << *b << endl;
}

// Task 2
template <class T1>
void SortPointers(vector<T1*> &vec) {

	sort(vec.begin(), vec.end(),
		[&](T1* &a, T1* &b) {

		return *a > *b;
	});
}

void Task_2() {
	cout << "Task 2" << endl;

	vector<int*> vec;

	size_t n = 10;
	while (n--)
	{
		int *a = new int(rand());
		vec.push_back(a);
		cout << *a << '\t';
	}
	cout << endl;

	SortPointers(vec);
	n = 10;
	while (n--)
	{
		cout << *vec.back() << '\t';
		vec.pop_back();
	}
}

// Task 3
void Task_3() {
	cout << endl << "Task 3" << endl;

	ifstream file("War of Piece.txt", ios::binary);
	file.seekg(0, std::ios::end);
	size_t size = file.tellg();
	file.seekg(0);
	string s(size, ' ');
	//file.read(&s[0], size);

	vector<string> result;

	string word;

	string strText = "";

	while (!file.eof()) {
		file >> word;
		strText += word;
		result.push_back(word);
	}
	file.close();

	vector<char> vowel_letter = {
		'A', 'E', 'I', 'O', 'U', 'Y',
		'a', 'e', 'i', 'o', 'u', 'y',
		'À', 'Å', '¨', 'È', 'Î', 'Ó', 'Û', 'Ý', 'Þ', 'ß',
		'à', 'å', '¸', 'è', 'î', 'ó', 'û', 'ý', 'þ', 'ÿ',
	};

	// count_if & find
	size_t dwCount = 0;
	Timer timer_1("count_if & find");
	dwCount = count_if(strText.begin(), strText.end(), [vowel_letter](char c) {

		return vowel_letter.end() != find(vowel_letter.begin(), vowel_letter.end(), c);
	});
	timer_1.print();
	cout << "vowel_letter var1: " << dwCount << endl;

	// count_if & cycle for
	Timer timer_2("count_if & cycle for");
	dwCount = count_if(strText.begin(), strText.end(), [vowel_letter](char c) {

		for (const auto& compare : vowel_letter)
			if (compare == c)
				return 1;
		return 0;
	});
	timer_2.print();
	cout << "vowel_letter var2: " << dwCount << endl;

	dwCount = 0;
	// cycle for & find
	Timer timer_3("cycle for & find");
	for (const auto& c : strText)
		if (vowel_letter.end() != find(vowel_letter.begin(), vowel_letter.end(), c))
			dwCount++;
	timer_3.print();
	cout << "vowel_letter var3: " << dwCount << endl;

	dwCount = 0;
	// 2 cycle for
	Timer timer_4("2 cycle for");
	for (const auto& c : strText)
		for (const auto& compare : vowel_letter)
			if (compare == c)
				dwCount++;
	timer_4.print();
	cout << "vowel_letter var4: " << dwCount << endl;
}


int main() {

	Task_1();

	Task_2();

	Task_3();

	system("pause");
	return 0;
}