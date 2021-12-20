#include <iostream>
#pragma warning (disable:4996)
using namespace std;
enum class gender { male, female };
class Person
{
private:
	const int ID;
	char* aName;
	gender aGender;
	Person* aMother;
	Person* aFather;
	static int aID;
public:
	int getID() const;
	char* getName() const;
	Person(const char*, gender, Person* = nullptr, Person* = nullptr);
	Person* giveBirth(const char*, gender, Person* = nullptr);
	void print();
	char* getMother() const;
	char* getFather() const;
	const char* getGender() const;
};
int Person::aID = 0;
Person::Person(const char* name, gender gender, Person* mother, Person* father) :ID(++aID) {
	aName = new char[strlen(name) + 1];
	strcpy(aName, name);
	if (name == nullptr) {
		throw logic_error("person should have a name");
	}
	aGender = gender;
	aMother = mother;
	aFather = father;
	if (ID > 2 && mother == nullptr) {
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
	return aName;
}
int Person::getID() const {
	return ID;
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
	const char* enterName = "";
	if (name != nullptr) {
		enterName = name;
	}
	else {
		throw logic_error("baby should have a name");
	}
	auto baby = new Person(enterName, gend, this, father);
	return baby;
}

int main() {
	Person Adam("Adam", gender::male);
	Person Eva("Eva", gender::female);
	Person Masha = *Eva.giveBirth("Masha", gender::female, &Adam);
	Person Artem = *Eva.giveBirth("Artem", gender::male, &Adam);
	Person Oxana = *Masha.giveBirth("Oxana", gender::female, &Artem);
	Person Bogdan = *Oxana.giveBirth("Bogdan", gender::male);
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
	cout << endl;
	return 0;
}
