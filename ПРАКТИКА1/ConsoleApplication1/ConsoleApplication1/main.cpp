#include <iostream>
#include <string>
#include <windows.h>
#include <random>
#include <vector>
#include <cstdlib>

void clearScreen() {
	system("cls");
}

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

std::string healthBar(int cur, int max) {
	int total = 10;
	int filled = cur * total / max;
	std::string bar = "[";
	for (int i = 0; i < total; i++)
		bar += (i < filled) ? '#' : '-';
	bar += "]";
	return bar;
}

int dodgeChance(Armor a) {
	switch (a) {
	case Armor::Heavy: return 5;
	case Armor::Medium: return 15;
	case Armor::Light: return 30;
	}
	return 0;
}

double damageResist(Armor a) {
	switch (a) {
	case Armor::Heavy: return 0.2;
	case Armor::Medium: return 0.1;
	case Armor::Light: return 0.0;
	}
	return 0.0;
}

struct Attack {
	std::string name;
	int minDmg;
	int maxDmg;
	double vsHeavy;
	double vsMedium;
	double vsLight;
	int cost;

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
	double resist = damageResist(targetArmor);
	return static_cast<int>(rolled * mult * (1 - resist));               
}

class Character {
public:
	Character(std::string name, int health, Armor armor)
		: name(name), health(health), maxHealth(health), armor(armor) {}

	void takeDamage(int amount) {
		health -= amount;
		if (health < 0) health = 0;
		onTakeDamage(amount);
	}
	
	bool isAlive() const {
		return health > 0;
	}

	void print() const {
		std::cout << name << " " << healthBar(health, maxHealth) << " HP: " << health << "/" << maxHealth <<
			" | броня: " << armorToString(armor) << "\n";
	}

	virtual ~Character() = default;

	virtual std::string getClassName() const { return "Боец"; }

	virtual void showResource() const {}

	virtual bool canAfford(const Attack& atk) const { return true; }
	virtual void  payFor(const Attack& atk) {}

	virtual void onDealDamage(int dmg) {}
	virtual void onTakeDamage(int dmg) {}

	virtual void onTurnStart() {}

	void attackTarget(Character& target, Attack atk) {
		if (tryRoll(dodgeChance(target.armor))) {
			std::cout << target.getClassName() << " увернулся!\n";
			return;
		}

		int dmg = computeDamage(atk, target.armor);
		target.takeDamage(dmg);
		onDealDamage(dmg);
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
		payFor(attacks[index]);
		attackTarget(target, attacks[index]);
	}

	int askAttackIndex() const {
		int index;
		while (true) {
			std::cin >> index;
			if (index < 0 || index >= static_cast<int>(attacks.size())) {
				std::cout << "Нет такой атаки, ещё раз: ";
				continue;
			}
			if (!canAfford(attacks[index])) {
				std::cout << "Недостаточно ресурсов, выбери что то ещё: ";
				continue;
			}
			return index;
		}
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
			{ "Обыкновенный удар мечом", 5, 10, 1.0, 1.0, 1.0, 0 },
			{ "Рубящий удар", 5, 15, 0.8, 1.0, 1.2, 0 },
			{ "Сильный удар", 10, 20, 1.0, 1.2, 0.8, 0 },
			{ "Ультимативано мощный удар", 15, 40, 1.2, 0.8, 1.0, 50 }
		};
	}

	std::string getClassName() const override { return "Воин"; }

	void showResource() const override { std::cout << "Ярость: " << rage << "\n"; }

	void onDealDamage(int dmg) override { addRage(5); }
	void onTakeDamage(int dmg) override { addRage(10); }

	bool canAfford(const Attack& atk) const override { return rage >= atk.cost; }
	void payFor(const Attack& atk) override { rage -= atk.cost; }

private:
	int rage = 0;

	void addRage(int amount) {
		rage += amount;
		if (rage > 50) rage = 50;
	}
};

class Mage : public Character {
public:
	Mage(std::string name, int health, Armor armor)
		: Character(name, health, armor) {
		attacks = {
			{ "Удар посохом по яйцам", 5, 8, 1.0, 1.0, 1.0, 0 },
			{ "Дождь ледяных осколков", 5, 15, 0.8, 1.0, 1.2, 12 },
			{ "Ураган", 10, 20, 1.0, 1.2, 0.8, 18 },
			{ "Огненный шар", 15, 25, 1.2, 0.8, 1.0, 25 }
		};
	}
	std::string getClassName() const override { return "Маг"; }

	bool canAfford(const Attack& atk) const override {
		return mana >= atk.cost;
	}
	void payFor(const Attack& atk) override {
		mana -= atk.cost;
	}

	void showResource() const override { std::cout << "Мана: " << mana << "\n"; }

	void onTurnStart() override {
		mana += 7;
		if (mana > 100) mana = 100;
	}

private:
	int mana = 100;
};

void drawBoard(const Character& p1, const Character& p2) {
	clearScreen();
	std::cout << "==================================================\n";
	std::cout << " ИГРОК 1:  ";  p1.print();
	std::cout << "           ";  p1.showResource();
	std::cout << "--------------------------------------------------\n";
	std::cout << " ИГРОК 2:  ";  p2.print();
	std::cout << "           ";  p2.showResource();
	std::cout << "==================================================\n";
}

void runBattle(Character& p1, Character& p2) {
	while (p1.isAlive() && p2.isAlive()) {
		p1.onTurnStart();
		drawBoard(p1, p2);
		std::cout << "\n-- Ход Игрока 1 (" << p1.getClassName() << ") --\n";
		p1.showAttacks();
		int x = p1.askAttackIndex();
		p1.useAttack(x, p2);

		if (!p2.isAlive()) break;

		p2.onTurnStart();
		drawBoard(p1, p2);
		std::cout << "\n-- Ход Игрока 2 (" << p2.getClassName() << ") --\n";
		p2.showAttacks();
		x = p2.askAttackIndex();
		p2.useAttack(x, p1);

		if (!p1.isAlive()) break;
	}

	drawBoard(p1, p2);
	if (p1.isAlive())
		std::cout << "\nПобедил Игрок 1 (" << p1.getClassName() << ")!\n";
	else
		std::cout << "\nПобедил Игрок 2 (" << p2.getClassName() << ")!\n";
}

Character* createFighter() {
	std::cout << "Выберите класс:\n0) Воин\n1) Маг\n";
	int cls;
	std::cin >> cls;

	if (cls == 0) {
		std::cout << "Броня:\n0) Тяжёлая\n1) Средняя\n";
		int ar;
		std::cin >> ar;
		Armor armor = (ar == 0) ? Armor::Heavy : Armor::Medium;
		return new Warrior("Воин", 95, armor);
	} else {
		std::cout << "Броня:\n0) Средняя\n1) Лёгкая\n";
		int ar;
		std::cin >> ar;
		Armor armor = (ar == 0) ? Armor::Medium : Armor::Light;
		return new Mage("Маг", 85, armor);
	}
}

int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	Character* p1 = createFighter();
	Character* p2 = createFighter();

	runBattle(*p1, *p2);

	delete p1;
	delete p2;
}