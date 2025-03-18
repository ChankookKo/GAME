#include "game.h"

int main() {
    cout << "RPG 게임 시작!" << endl;

    shared_ptr<Character> player = chooseCharacter("당신의 캐릭터를 선택하세요:");
    shared_ptr<Character> enemy = chooseCharacter("상대 캐릭터를 선택하세요:");

    while (true) {
        BattleManager::startBattle(player, enemy);

        if (!player->isAlive()) {
            cout << "게임 종료!" << endl;
            break;
        }

        cout << "새로운 적과 싸우겠습니까? (y/n): ";
        char choice;
        cin >> choice;
        if (choice != 'y') break;

        enemy = chooseCharacter("새로운 적을 선택하세요:");
    }

    return 0;
}