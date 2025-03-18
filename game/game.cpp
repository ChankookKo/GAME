#include "game.h"

// ���� ���� �Լ�
int getRandomNumber(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

// ������ �Լ�
void delay(int milliseconds) {
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

// ĳ���� �⺻ Ŭ���� ����
Character::Character(string n, int lvl, int hp, int atk)
    : name(n), level(lvl), health(hp), maxHealth(hp), attackPower(atk), exp(0), expToLevelUp(50) {
}

void Character::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
}

bool Character::isAlive() const {
    return health > 0;
}

void Character::showStatus() const {
    cout << name << " (���� " << level << ") - HP: " << health
        << " | EXP: " << exp << "/" << expToLevelUp << endl;
}

void Character::resetHealth() {
    health = 100 + (level - 1) * 10; // ������ �������� ü���� ����
    health = maxHealth;
    cout << name << "�� ü���� ȸ���Ǿ����ϴ�! (HP: " << health << " )" << endl;
}

string Character::getName() const {
    return name;
}

// ����ġ ȹ�� �Լ�
void Character::gainExp(int amount) {
    exp += amount;
    cout << name << "��(��) ����ġ " << amount << "��(��) ȹ���߽��ϴ�!" << endl;

    while (exp >= expToLevelUp) {
        levelUp();
    }
}

// ������ �Լ�
void Character::levelUp() {
    exp -= expToLevelUp;
    level++;
    expToLevelUp += 20; // ���� �������� �ʿ��� ����ġ ����
    maxHealth += 10;       // ü�� ����
    health = maxHealth;    // ü�� ���� ȸ��
    attackPower += 2;   // ���ݷ� ����
    cout << name << "��(��) ������! (Lv: " << level << ", HP: " << maxHealth << ", ATK: " << attackPower << ")" << endl;    resetHealth();
}

// ���� Ŭ���� ����
Warrior::Warrior(string n) : Character(n, 1, 100, 15) {}

void Warrior::attack(Character& target) {
    cout << name << "��(��) " << target.getName() << "��(��) �����մϴ�!" << endl;
    target.takeDamage(attackPower);
}

void Warrior::specialAttack(Character& target) {
    cout << name << "��(��) ������ �ϰ��� ����մϴ�!" << endl;
    target.takeDamage(attackPower * 2);
    takeDamage(5);
}

// ������ Ŭ���� ����
Mage::Mage(string n) : Character(n, 1, 80, 18), mana(100) {}

void Mage::attack(Character& target) {
    cout << name << "��(��) " << target.getName() << "��(��) �����մϴ�!" << endl;
    target.takeDamage(attackPower);
}

void Mage::specialAttack(Character& target) {
    if (mana >= 20) {
        cout << name << "��(��) ���̾�� ����մϴ�!" << endl;
        target.takeDamage(attackPower * 1.5);
        mana -= 20;
    }
    else {
        cout << "������ �����մϴ�!" << endl;
    }
}

// ���� Ŭ���� ����
Rogue::Rogue(string n) : Character(n, 1, 90, 12) {}

void Rogue::attack(Character& target) {
    cout << name << "��(��) " << target.getName() << "��(��) �����մϴ�!" << endl;
    target.takeDamage(attackPower);
}

void Rogue::specialAttack(Character& target) {
    if (getRandomNumber(1, 100) <= 70) {
        cout << name << "��(��) �޽��� �������׽��ϴ�!" << endl;
        target.takeDamage(attackPower * 3);
    }
    else {
        cout << name << "�� �޽��� �����߽��ϴ�." << endl;
    }
}

// ���� ���� Ŭ���� ����
void BattleManager::startBattle(shared_ptr<Character> player, shared_ptr<Character> enemy) {
    cout << "���� ����!" << endl;
    player->showStatus();
    enemy->showStatus();

    while (player->isAlive() && enemy->isAlive()) {
        delay(1000);
        player->attack(*enemy);
        if (!enemy->isAlive()) break;

        delay(1000);
        enemy->attack(*player);
        player->showStatus();
        enemy->showStatus();
    }

    if (player->isAlive()) {
        cout << player->getName() << "��(��) �¸��߽��ϴ�!" << endl;
        player->gainExp(30);  // �¸� �� ����ġ ȹ��
    }
    else {
        cout << enemy->getName() << "��(��) �¸��߽��ϴ�!" << endl;
    }
}


// ����� ĳ���� ���� �Լ�
shared_ptr<Character> chooseCharacter(const string& prompt) {
    int choice;
    cout << prompt << endl;
    cout << "1. ����(Warrior)  2. ������(Mage)  3. ����(Rogue)" << endl;
    cin >> choice;

    switch (choice) {
    case 1: return make_shared<Warrior>("����");
    case 2: return make_shared<Mage>("������");
    case 3: return make_shared<Rogue>("����");
    default:
        cout << "�߸��� �����Դϴ�. �⺻��(����)���� �����մϴ�." << endl;
        return make_shared<Warrior>("����");
    }
}