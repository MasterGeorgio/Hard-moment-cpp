// TestProject2.cpp : Defines the entry point for the console application.
//


#include <iostream>
#include <fstream>
#include <iomanip>

#include <string>

#include <tuple>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;


// Task 1
struct Person {
	string m_strFamily;
	string m_strName;
	//optional<string> m_wAddNumber;
	string m_strSurname;

	friend ostream& operator<< (ostream &out, const Person &person) {
		out << setw(15)
			<< person.m_strFamily
			<< setw(15)
			<< person.m_strName
			<< setw(15)
			<< person.m_strSurname;

		return out;
	}
	/**/
	friend istream& operator>> (istream &in, Person &person) {
		in >> person.m_strFamily
			>> person.m_strName
			>> person.m_strSurname;

		return in;
	}
	friend ifstream& operator >> (ifstream &in, Person &person) {
		in >> person.m_strFamily
			>> person.m_strName
			>> person.m_strSurname;

		return in;
	}
	/**/

	friend bool operator<(const Person &p1, const Person &p2) {

		return tie(p1.m_strFamily, p1.m_strName) <
			tie(p2.m_strFamily, p2.m_strName);
	}
	friend bool operator>(const Person &p1, const Person &p2) {

		return tie(p1.m_strFamily, p1.m_strName) >
			tie(p2.m_strFamily, p2.m_strName);
	}
	friend bool operator==(const Person &p1, const Person &p2) {

		return !((p1 < p2) || (p1 > p2));
	}
};


// Task 2
struct PhoneNumber {
	uint16_t m_wCountry;
	uint16_t m_wCity;
	string m_strNumber;

	uint16_t m_wAddNumber;
	//optional<int> m_wAddNumber;

	friend ostream& operator<< (ostream &out, const PhoneNumber &phoneNum) {
		out << setw(15)
			<< '+'
			<< phoneNum.m_wCountry
			<< '('
			<< phoneNum.m_wCity
			<< ')'
			<< phoneNum.m_strNumber
			<< ' '
			<< phoneNum.m_wAddNumber;
		return out;
	}

	friend istream& operator >> (istream &in, PhoneNumber &phoneNum) {
		in >> phoneNum.m_wCountry
			>> phoneNum.m_wCity
			>> phoneNum.m_strNumber
			>> phoneNum.m_wAddNumber;

		return in;
	}
	friend ifstream& operator >> (ifstream &in, PhoneNumber &phoneNum) {
		in >> phoneNum.m_wCountry
			>> phoneNum.m_wCity
			>> phoneNum.m_strNumber
			>> phoneNum.m_wAddNumber;

		return in;
	}

	friend bool operator<(const PhoneNumber &pn1, const PhoneNumber &pn2) {

		return tie(pn1.m_wCountry, pn1.m_wCity, pn1.m_strNumber, pn1.m_wAddNumber) <
			tie(pn2.m_wCountry, pn2.m_wCity, pn2.m_strNumber, pn2.m_wAddNumber);
	}
	friend bool operator>(const PhoneNumber &pn1, const PhoneNumber &pn2) {

		return !(pn1 < pn2);
	}
	friend bool operator==(const PhoneNumber &pn1, const PhoneNumber &pn2) {

		return !((pn1 < pn2) || (pn1 > pn2));
	}
};

// Task 3
class PhoneBook
{
public:
	PhoneBook(ifstream &file) {

		if (!file.is_open())
		{
			cout << "file not open" << endl;
			return;
		}


		while (!file.eof()) {

			Person person;
			PhoneNumber phoneNumber;
			string surName;
			int addNum = 0;

			file >> person.m_strFamily
				>> person.m_strName
				>> surName
				>> phoneNumber.m_wCountry
				>> phoneNumber.m_wCity
				>> phoneNumber.m_strNumber
				>> addNum;

			if (surName != "-")
				person.m_strSurname = surName;
			if (addNum != '-')
				phoneNumber.m_wAddNumber = addNum;

			m_Book.push_back({ { person }, { phoneNumber } });
		}

		file.close();
		/*/
		// modeling test
		return;

		vector<pair<string, int>> poets{
			{ "Pushkin", 1799 },
			{ "Lermontov", 1814 },
			{ "Zhukovsky", 1783 }
		};


		vector<pair<Person, PhoneNumber> > book{
			{ Person{"Ilin", "Petr", "Artemovich"}, PhoneNumber{7, 17, "4559767"} },
			{ Person{"Zaitsev", "Zakhar", "Artemovich"}, PhoneNumber{ 125, 44, "4164751"} },
			{ Person{"Dubinin", "Aleksei", "Mikhailovich"}, PhoneNumber{ 7, 473, "7449054"} },
			{ Person{"Solovev", "Artur", "Mikhailovich"}, PhoneNumber{ 4, 940, "2556793"} },
			{ Person{"Gerasimov", "Miroslav", "Stanislavovich"}, PhoneNumber{ 7, 367, "7508887"} },
			{ Person{ "Kotov", "Vasilii", "Eliseevich"}, PhoneNumber{ 7, 367, "7508888" } },
			{ Person{ "Ivanov", "Daniil", "Maksimovich" }, PhoneNumber{ 7, 366, "7508887" } }
		};

		m_Book = book;
		/**/

	}

	~PhoneBook() {

	}

	friend ostream& operator<<(ostream &out, const PhoneBook &book) {

		for (auto b : book.m_Book)
			cout << b.first << b.second << endl;
		return out;
	}

	// Sort by name
	void SortByName() {
		sort(m_Book.begin(), m_Book.end());
	}

	friend istream& operator >> (istream &in, PhoneBook &book) {

		Person person;
		PhoneNumber phoneNumber;

		in >> person
			>> phoneNumber;

		book.m_Book.push_back(make_pair(person, phoneNumber));

		return in;
	}

	// Sort by phone
	void SortByPhone() {
		sort(m_Book.begin(), m_Book.end(),
			[](pair<Person, PhoneNumber> &left, pair<Person, PhoneNumber> &rigth) {
			
			return left.second < rigth.second;
		});
	}

	pair<string, PhoneNumber> GetPhoneNumber(string FamilyName) {

		int nCount  = 0;
		PhoneNumber phoneNumb;

		for (auto b : m_Book)
		{
			if (b.first.m_strFamily == FamilyName) {
				if (nCount)
					break;

				nCount++;
				phoneNumb = b.second;
			}
		}

		pair<string, PhoneNumber> result = { "", phoneNumb };

		(nCount == 0) ? result.first = "not found" : void();

		(nCount > 1) ? result.first = "found more than 1" : void();

		return result;
	}

	// Изменить номер человека на новый
	void ChangePhoneNumber(Person person, PhoneNumber topNumber) {
		for (auto b : m_Book)
			if (person == b.first) {
				b.second = topNumber;
				break;
			}
	}

private:
	vector<pair<Person, PhoneNumber> > m_Book;
};


int main() {

	ifstream file("F:\\PROJECTS\\GeekBrains\\Hard moments Cpp\\Home works\\Lesson1\\XXX.txt"); // путь к файлу PhoneBook.txt
	PhoneBook book(file);
	cout << book;

	cout << "------SortByPhone-------" << endl;
	book.SortByPhone();
	cout << book;

	cout << "------SortByName--------" << endl;
	book.SortByName();
	cout << book;
	/**/
	cout << "-----GetPhoneNumber-----" << endl;
	// лямбда функция, которая принимает фамилию и выводит номер телефона этого    	человека, либо строку с ошибкой
	auto print_phone_number = [&book](const string& surname) {
		cout << surname << "\t";
		auto answer = book.GetPhoneNumber(surname);
		if (get<0>(answer).empty())
			cout << get<1>(answer);
		else
			cout << get<0>(answer);
		cout << endl;
	};
	// вызовы лямбды
	print_phone_number("Ivanov");
	print_phone_number("Petrov");

	cout << "----ChangePhoneNumber----" << endl;
	book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" }, PhoneNumber{ 7, 123, "15344458", 10 });
	book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" }, PhoneNumber{ 16, 465, "9155448", 13 });
	cout << book;
	/**/

	return 0;
}