#include <vector>
#include <fstream>
#include <iostream>

class Memento{
private:
    float _hpMem;
    int _speedMem;

    //Так как класс Player не предусматривает смену Player::_name,
    //то поле std::string не будем сюда добавлять

public:
    Memento(float hp = 0.00f, int speed = 0) :
        _hpMem{ hp }, _speedMem{ speed } {}

    std::pair<float, int> getMem()const{
        return std::make_pair(_hpMem, _speedMem);
    }
};

class Player{
private:
    class State;
    State* _state;
    std::string _name;

public:
    Player(const std::string&, float, int);

    ~Player();

    void changeHp(float change);

    void changeSpeed(int change);

    float getHp() const;

    int getSpeed() const;

    const std::string &getName() const;

    const Memento createMemento();

    void restoreFromMemento(const Memento&);
};

class Caretaker{
private:
    std::string _filePath;
    Memento _memento;
public:
    Caretaker(const std::string &filePath, const Memento &memento) :
        _filePath(filePath), _memento(memento) {}

        void printMemento()const{
            std::cout << "\nПроверим, что будем сохранять:\n";
            std::cout << _memento.getMem().first << std::endl;
            std::cout << _memento.getMem().second << std::endl;
    }

    bool serialize(){
        std::ofstream out(_filePath, std::ios::binary);

        if (!out.write(reinterpret_cast<char*>(&_memento), sizeof(Memento)))
        {
            std::cerr << "Ошибка записи файла " << _filePath;
            return false;
        }

        return true;
    }

    bool deserialize(){
        std::ifstream in(_filePath, std::ios::binary);

        if (!in.read(reinterpret_cast<char*>(&_memento), sizeof (Memento)))
        {
            std::cerr << "Ошибка чтения файла " << _filePath;
            return false;
        }

        return true;
    }
};

