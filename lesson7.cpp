#include "lesson7.h"

class Player::State{
private:
    float _hp;
    int _speed;
public:
    State(float hp, int speed);

    ~State() = default;

    const float getHp() const;

    const int getSpeed() const;

    void setHp(float hp);

    void setSpeed(int speed);
};

Player::State::State(float hp, int speed) : _hp{ hp }, _speed{ speed } {}

const float Player::State::getHp() const {
    return _hp;
}

const int Player::State::getSpeed() const {
    return _speed;
}

void Player::State::setHp(float hp) {
    _hp = hp;
}

void Player::State::setSpeed(int speed) {
    _speed = speed;
}

Player::Player(const std::string& name, float hp, int speed):
    _name{ name }, _state{ new State(hp, speed) } {}

Player::~Player(){
    delete _state;
}

void Player::changeHp(float change){
    _state->setHp(_state->getHp() + change);
}

void Player::changeSpeed(int change){
    _state->setSpeed(_state->getSpeed() + change);
}

float Player::getHp() const {
    return _state->getHp();
}

int Player::getSpeed() const {
    return _state->getSpeed();
}

const std::string &Player::getName() const {
    return _name;
}

const Memento Player::createMemento(){
    return Memento(_state->getHp(), _state->getSpeed());
}

void Player::restoreFromMemento(const Memento &mem){
    _state->setHp(mem.getMem().first);
    _state->setSpeed(mem.getMem().second);
}


