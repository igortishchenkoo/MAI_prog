#include <iostream>
#include <string>
#include <windows.h>
#include <random>
#include <vector>

std::mt19937 rng(std::random_device{}());

int rollDamage(int minDmg, int maxDmg) {
	std::uniform_int_distribution<int> dist(minDmg, maxDmg);
	return dist(rng);
}

enum class  Armor { Heavy, Medium, Light };

std::string armorToString(Armor a) {
	switch (a) {
	case Armor::Heavy: return "тяжёлая";
	case Armor::Medium: return "средняя";
	case Armor::Light: return "лёгкая";
	}
	return "неизвестно";
}

struct Attack {
	std::string name;
	int minDmg;
	int maxDmg;
	double vsHeavy;
	double vsMedium;
	double vsLight;

	double multiplierVS(Armor targetArmor) const {
		switch (targetArmor) {
		case Armor::Heavy: return vsHeavy;
		case Armor::Medium: return vsMedium;
		case Armor::Light: return vsLight;
		}
		return 1.0;
	}
};

int computeDamage(Attack atk, Armor targetArmor) {
	int rolled = rollDamage(atk.minDmg, atk.maxDmg);   
	double mult = atk.multiplierVS(targetArmor);         
	return static_cast<int>(rolled * mult);               
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

	void attackTarget(Character& target, Attack atk) {
		int dmg = computeDamage(atk, target.armor);
		target.takeDamage(dmg);
		std::cout << getClassName() << " бьёт " << atk.name << " на " << dmg << "\n";
	}

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

	Warrior a("Александр", 120, Armor::Heavy);
	Mage b("Мерлин", 80, Armor::Light);

	Attack strike{ "Удар", 5, 15, 0.8, 1.0, 1.2 };

	b.print();
	a.attackTarget(b, strike);
	b.print();
}