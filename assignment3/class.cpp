/*
 * File: class.cpp
 * ---------------
 * Implements the GameCharacter class.
 */

#include "class.h"
#include <iostream> // For potential debug messages

// Use using namespace std; for simplicity as in lectures
using namespace std;

// Implement the custom constructor using a member initializer list.
GameCharacter::GameCharacter(const string& name, int maxHp, int damage):
m_name{name}, m_maxHp{maxHp}, m_damage{damage}, m_hp{maxHp}, m_isAlive{true} {};



// Implement the default constructor.
GameCharacter::GameCharacter(): 
m_name{"Goblin"}, m_maxHp{50}, m_damage{5}, m_hp{50}, m_isAlive{true} {};


// Implement the public getter functions.
string GameCharacter::getName() const {
    return m_name;
}

int GameCharacter::getHp() const {
    return m_hp;
}

bool GameCharacter::isAlive() const {
    return m_isAlive;
}


// Implement the takeDamage function.
// It should reduce hp and call the private die() function if hp drops to 0 or below.
void GameCharacter::takeDamage(int amount) {
    m_hp -= amount;
    if (m_hp <= 0) {
        die();
    }
}


// Implement the attack function.
// It should call the target's takeDamage method.
void GameCharacter::attack(GameCharacter& target) const {
    target.takeDamage(m_damage);
}

void GameCharacter::setM_damage(int damage) {
    m_damage = damage;
}


// Implement the private die function.
void GameCharacter::die() {
    m_hp = 0;
    m_isAlive = false;
}