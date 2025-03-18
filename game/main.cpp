#include "game.h"

int main() {
    cout << "RPG ���� ����!" << endl;

    shared_ptr<Character> player = chooseCharacter("����� ĳ���͸� �����ϼ���:");
    shared_ptr<Character> enemy = chooseCharacter("��� ĳ���͸� �����ϼ���:");

    while (true) {
        BattleManager::startBattle(player, enemy);

        if (!player->isAlive()) {
            cout << "���� ����!" << endl;
            break;
        }

        player->resetHealth(); // �÷��̾� ü�� ȸ��

        cout << "���ο� ���� �ο�ڽ��ϱ�? (y/n): ";
        char choice;
        cin >> choice;
        if (choice != 'y') break;

        enemy = chooseCharacter("���ο� ���� �����ϼ���:");
        enemy->resetHealth(); // �� ü�� ȸ��
    }

    return 0;
}