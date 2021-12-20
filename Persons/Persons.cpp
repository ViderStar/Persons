#include <iostream>
#pragma warning (disable:4996)
using namespace std;
enum class gender { 
	M, 
	FM 
};
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
	if (mother != nullptr && mother->aGender == gender::M) {
		throw logic_error("mother must be female");
	}
	if (father != nullptr && father->aGender == gender::FM) {
		throw logic_error("father must be male");
	}
}
const char* Person::getGender() const {
	return this->aGender == gender::M ? "male" : "female";
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
	cout << "name: " << getName() << endl;
	cout << "ID: " << getID() << endl;
	cout << "gender: " << getGender() << endl;
	if (aMother != nullptr) {
		cout << "mother name: " << getMother() << endl;
	}
	else {
		cout << "no mother for this person" << endl;
	}
	if (aFather != nullptr) {
		cout << "father name: " << getFather() << endl;
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
	Person Adam("Adam", gender::M);
	Person Eva("Eva", gender::FM);
	Person Svetlana = *Eva.giveBirth("Svetlana", gender::FM, &Adam);
	Person Artem = *Eva.giveBirth("Artem", gender::M, &Adam);
	Person Oxana = *Svetlana.giveBirth("Oxana", gender::FM, &Artem);
	Person Bogdan = *Oxana.giveBirth("Bogdan", gender::M);
	Adam.print(); cout << '\n';
	Eva.print(); cout << '\n';
	Svetlana.print(); cout << '\n';
	Artem.print(); cout << '\n';
	Oxana.print(); cout << '\n';
	Bogdan.print(); cout << '\n';
	return 0;
}
