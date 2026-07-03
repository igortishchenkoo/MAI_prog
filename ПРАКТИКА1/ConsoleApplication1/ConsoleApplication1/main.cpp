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

bool tryRoll(int percent) {
	std::uniform_int_distribution<int> dist(1, 100);
	return dist(rng) <= percent;
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

int dodgeChance(Armor a) {
	switch (a) {
	case Armor::Heavy: return 5;
	case Armor::Medium: return 15;
	case Armor::Light: return 30;
	}
	return 0;
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
		if (tryRoll(dodgeChance(target.armor))) {
			std::cout << target.getClassName() << " увернулся!\n";
			return;
		}

		int dmg = computeDamage(atk, target.armor);
		target.takeDamage(dmg);
		std::cout << getClassName() << " бьёт " << atk.name << " на " << dmg << "\n";
	}

	void listAttacks() const {
		for (const Attack& atk : attacks)
			std::cout << "- " << atk.name << "\n";
	}

	void showAttacks() const {
		int i = 0;
		for (const Attack& atk : attacks) {
			std::cout << i << ") " << atk.name << "\n";
			i++;
		}
	}

	void useAttack(int index, Character& target) {
		attackTarget(target, attacks[index]);
	}

protected:
	std::string name;
	int health;
	int maxHealth;
	Armor armor;
	std::vector<Attack> attacks;
};

class Warrior : public Character {
public:
	Warrior(std::string name, int health, Armor armor)
		: Character(name, health, armor) {
		attacks = {
			{ "Рубящий удар", 5, 15, 0.8, 1.0, 1.2 },
			{ "Сильный удар", 10, 20, 1.0, 1.2, 0.8 },
			{ "Мощный удар", 15, 25, 1.2, 0.8, 1.0 }
		};
	}

	std::string getClassName() const override { return "Воин"; }
};

class Mage : public Character {
public:
	Mage(std::string name, int health, Armor armor)
		: Character(name, health, armor) {
		attacks = {
			{ "Дождь ледяных осколков", 5, 15, 0.8, 1.0, 1.2 },
			{ "Ураган", 10, 20, 1.0, 1.2, 0.8 },
			{ "Огненный шар", 15, 25, 1.2, 0.8, 1.0 }
		};
	}
	std::string getClassName() const override { return "Маг"; }
};

int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	Warrior w("Александр", 120, Armor::Heavy);
	Mage m("Мерлин", 80, Armor::Light);

	while (w.isAlive() && m.isAlive()) {
		std::cout << "\n-- Ход: " << w.getClassName() << " --\n";
		w.print();
		m.print();
		w.showAttacks();
		int x;
		std::cin >> x;
		w.useAttack(x, m);

		if (!m.isAlive()) break;

		std::cout << "\n-- Ход: " << m.getClassName() << " --\n";
		m.print();
		w.print();
		m.showAttacks();
		std::cin >> x;
		m.useAttack(x, w);

		if (!w.isAlive()) break;
		}

	if  (w.isAlive()) 
		std::cout << w.getClassName() << " победил!\n";
	else
		std::cout << m.getClassName() << " победил!\n";
}