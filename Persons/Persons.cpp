#include <iostream>
#pragma once
#pragma warning (disable:4996)
using namespace std;

enum class gender { male, female };
class Person
{
private:
	const int _ID;
	char* aname;
	gender aGender;
	Person* aMother;
	Person* aFather;
	//void erase();
	static int _nextID;
public:
	int getID() const;
	char* getName() const;
	Person(const char*, gender, Person* = nullptr, Person* = nullptr);
	Person* giveBirth(const char*, gender, Person* = nullptr);
	//Person();
	void print();
	char* getMother() const;
	char* getFather() const;
	const char* getGender() const;
	//Person operator = (const Person);
};
int Person::_nextID = 0;
Person::Person(const char* name, gender gend, Person* mother, Person* father) :_ID(++_nextID) {
	aname = new char[strlen(name) + 1];
	strcpy(aname, name);
	if (name == nullptr) {
		throw logic_error("person should have a name");
	}
	aGender = gend;
	aMother = mother;
	aFather = father;
	if (_ID > 2 && mother == nullptr) {
		throw logic_error("one of the parents must be mother");
	}
	if (mother != nullptr && mother->aGender == gender::male) {
		throw logic_error("mother must be female");
	}
	if (father != nullptr && father->aGender == gender::female) {
		throw logic_error("father must be male");
	}
}
const char* Person::getGender() const {
	return this->aGender == gender::male ? "male" : "female";
}
char* Person::getName() const {
	return aname;
}
int Person::getID() const {
	return _ID;
}
char* Person::getMother() const {
	return aMother->getName();
}
char* Person::getFather() const {
	return aFather->getName();
}

void Person::print() {
	cout << "person's name: " << getName() << endl;
	cout << "person's ID: " << getID() << endl;
	cout << "person's gender: " << getGender() << endl;
	if (aMother != nullptr) {
		cout << "person's mother name: " << getMother() << endl;
	}
	else {
		cout << "no mother for this person" << endl;
	}
	if (aFather != nullptr) {
		cout << "person's father name: " << getFather() << endl;
	}
	else {
		cout << "no father for this person" << endl;
	}

}

Person* Person::giveBirth(const char* name, gender gend, Person* father) {
	const char* addname = "";
	if (name != nullptr) {
		addname = name;
	}
	else {
		throw logic_error("baby should have a name");
	}
	auto child = new Person(addname, gend, this, father);
	return child;
}

int main() {
	Person Adam("Adam", gender::male);
	Person Eva("Eva", gender::female);
	Person Masha = *Eva.giveBirth("Masha", gender::female, &Adam);
	Person Artem = *Eva.giveBirth("Ivan", gender::male, &Adam);
	Person Oxana = *Masha.giveBirth("Anya", gender::female, &Artem);
	Person Bogdan = *Oxana.giveBirth("Jenya", gender::male);
	Adam.print();
	cout << endl;
	Eva.print();
	cout << endl;
	Masha.print();
	cout << endl;
	Artem.print();
	cout << endl;
	Oxana.print();
	cout << endl;
	Bogdan.print();
	system("PAUSE");
	return 0;
}