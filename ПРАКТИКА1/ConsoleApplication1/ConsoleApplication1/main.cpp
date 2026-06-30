#include <iostream>
#include <string>
#include <windows.h>	

enum class  Armor { Heavy, Medium, Light };

std::string armorToString(Armor a) {
	switch (a) {
	case Armor::Heavy: return "тяжёлая";
	case Armor::Medium: return "средняя";
	case Armor::Light: return "лёгкая";
	}
	return "неизвестно";
}

class Character {
public:
	Character(std::string name, int health, Armor armor)
		: name(name), health(health), maxHealth(health), armor(armor) {}

	void takeDamage(int amount) {
		health -= amount;
		if (health < 0) health = 0;
	}
	
	bool isAlive() const {
		return health > 0;
	}

	void print() const {
		std::cout << name << " | HP: " << health << " | броня: " << armorToString(armor) << "\n";
	}

	virtual ~Character() = default;

	virtual std::string getClassName() const { return "Боец"; }

protected:
	std::string name;
	int health;
	int maxHealth;
	Armor armor;
};

class Warrior : public Character {
public:
	Warrior(std::string name, int health, Armor armor)
		: Character(name, health, armor) {}
	std::string getClassName() const override { return "Воин"; }
};

class Mage : public Character {
public:
	Mage(std::string name, int health, Armor armor)
		: Character(name, health, armor) {}
	std::string getClassName() const override { return "Маг"; }
};

int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	Warrior a("Alex", 120, Armor::Heavy);
	Mage b("Merlin", 80, Armor::Light);

	std::cout << a.getClassName() << " ";
	a.print();
	std::cout << b.getClassName() << " ";
	b.print();

	std::cout << a.isAlive() << "\n";
}