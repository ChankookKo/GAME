#include "game.h"

// 난수 생성 함수
int getRandomNumber(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

// 딜레이 함수
void delay(int milliseconds) {
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

// 캐릭터 기본 클래스 구현
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
    cout << name << " (레벨 " << level << ") - HP: " << health
        << " | EXP: " << exp << "/" << expToLevelUp << endl;
}

void Character::resetHealth() {
    health = 100 + (level - 1) * 10; // 레벨이 오를수록 체력이 증가
    health = maxHealth;
    cout << name << "의 체력이 회복되었습니다! (HP: " << health << " )" << endl;
}

string Character::getName() const {
    return name;
}

// 경험치 획득 함수
void Character::gainExp(int amount) {
    exp += amount;
    cout << name << "이(가) 경험치 " << amount << "을(를) 획득했습니다!" << endl;

    while (exp >= expToLevelUp) {
        levelUp();
    }
}

// 레벨업 함수
void Character::levelUp() {
    exp -= expToLevelUp;
    level++;
    expToLevelUp += 20; // 다음 레벨업에 필요한 경험치 증가
    maxHealth += 10;       // 체력 증가
    health = maxHealth;    // 체력 완전 회복
    attackPower += 2;   // 공격력 증가
    cout << name << "이(가) 레벨업! (Lv: " << level << ", HP: " << maxHealth << ", ATK: " << attackPower << ")" << endl;    resetHealth();
}

// 전사 클래스 구현
Warrior::Warrior(string n) : Character(n, 1, 100, 15) {}

void Warrior::attack(Character& target) {
    cout << name << "이(가) " << target.getName() << "을(를) 공격합니다!" << endl;
    target.takeDamage(attackPower);
}

void Warrior::specialAttack(Character& target) {
    cout << name << "이(가) 강력한 일격을 사용합니다!" << endl;
    target.takeDamage(attackPower * 2);
    takeDamage(5);
}

// 마법사 클래스 구현
Mage::Mage(string n) : Character(n, 1, 80, 18), mana(100) {}

void Mage::attack(Character& target) {
    cout << name << "이(가) " << target.getName() << "을(를) 공격합니다!" << endl;
    target.takeDamage(attackPower);
}

void Mage::specialAttack(Character& target) {
    if (mana >= 20) {
        cout << name << "이(가) 파이어볼을 사용합니다!" << endl;
        target.takeDamage(attackPower * 1.5);
        mana -= 20;
    }
    else {
        cout << "마나가 부족합니다!" << endl;
    }
}

// 도적 클래스 구현
Rogue::Rogue(string n) : Character(n, 1, 90, 12) {}

void Rogue::attack(Character& target) {
    cout << name << "이(가) " << target.getName() << "을(를) 공격합니다!" << endl;
    target.takeDamage(attackPower);
}

void Rogue::specialAttack(Character& target) {
    if (getRandomNumber(1, 100) <= 70) {
        cout << name << "이(가) 급습을 성공시켰습니다!" << endl;
        target.takeDamage(attackPower * 3);
    }
    else {
        cout << name << "의 급습이 실패했습니다." << endl;
    }
}

// 전투 관리 클래스 구현
void BattleManager::startBattle(shared_ptr<Character> player, shared_ptr<Character> enemy) {
    cout << "전투 시작!" << endl;
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
        cout << player->getName() << "이(가) 승리했습니다!" << endl;
        player->gainExp(30);  // 승리 시 경험치 획득
    }
    else {
        cout << enemy->getName() << "이(가) 승리했습니다!" << endl;
    }
}


// 사용자 캐릭터 선택 함수
shared_ptr<Character> chooseCharacter(const string& prompt) {
    int choice;
    cout << prompt << endl;
    cout << "1. 전사(Warrior)  2. 마법사(Mage)  3. 도적(Rogue)" << endl;
    cin >> choice;

    switch (choice) {
    case 1: return make_shared<Warrior>("전사");
    case 2: return make_shared<Mage>("마법사");
    case 3: return make_shared<Rogue>("도적");
    default:
        cout << "잘못된 선택입니다. 기본값(전사)으로 설정합니다." << endl;
        return make_shared<Warrior>("전사");
    }
}