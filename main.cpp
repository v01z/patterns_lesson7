#include <iostream>
#include "lesson7.h"

int main() {

    auto infoLamda { [](const Player &pl, const std::string &infoStr) {
        std::printf("\n*** Состояние игрока %s %s: ***\n",
            pl.getName().c_str(), infoStr.c_str());
        std::printf("Здоровье: %.2f\n", pl.getHp());
        std::printf("Скорость: %d\n", pl.getSpeed());
    }};

    //Обычное состояние игрока
    Player player("Подопытный", 85.55, 70);

    infoLamda(player, "до опытов над собой");

    Memento memento { player.createMemento() };

    Caretaker caretaker { "save_state.dat", memento };
    caretaker.printMemento();

    //Сохраним текущие параметры здоровья и скорости
    if (!caretaker.serialize())
        std::cout << "Состояние игрока сохранить не удалось.";

    //У игрока имзенилось здоровье и скорость
    player.changeHp(51.12);
    player.changeSpeed(81);

    infoLamda(player, "после приёма волшебной пилюли");

    //Вернём игроку исходное состояние. Ремарка: Если не получится прочитать
    //сохранённый файл, то игрок останется убер-имбой навсегда.
    if (caretaker.deserialize())
        player.restoreFromMemento(memento);

    infoLamda(player, "после прихода в себя");

    	return 0;
}
