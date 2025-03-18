#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <memory>
#include <string>
#include <random>
#include <thread>
#include <chrono>

using namespace std;

// 캐릭터 기본 클래스 (추상 클래스)
class Character {
protected:
    string name;
    int level;
    int health;
    int attackPower;
    int exp;
    int expToLevelUp;

public:
    Character(string n, int lvl, int hp, int atk);
    virtual ~Character() = default;

    virtual void attack(Character& target) = 0;
    virtual void specialAttack(Character& target) = 0;
    void takeDamage(int damage);
    bool isAlive() const;
    void showStatus() const;
    void resetHealth();
    string getName() const;

    void gainExp(int amount);
    void levelUp();
};

// 전사 클래스
class Warrior : public Character {
public:
    Warrior(string n);
    void attack(Character& target) override;
    void specialAttack(Character& target) override;
};

// 마법사 클래스
class Mage : public Character {
private:
    int mana;
public:
    Mage(string n);
    void attack(Character& target) override;
    void specialAttack(Character& target) override;
};

// 도적 클래스
class Rogue : public Character {
public:
    Rogue(string n);
    void attack(Character& target) override;
    void specialAttack(Character& target) override;
};

// 전투 관리 클래스
class BattleManager {
public:
    static void startBattle(shared_ptr<Character> player, shared_ptr<Character> enemy);
};

// 유틸리티 함수
int getRandomNumber(int min, int max);
void delay(int milliseconds);
shared_ptr<Character> chooseCharacter(const string& prompt);

#endif