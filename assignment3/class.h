/*
 * File: class.h
 * -------------
 * Defines the interface for the GameCharacter class.
 */

#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

#include <string>

class GameCharacter {
public:
    // Declare the custom constructor
    GameCharacter(const std::string& name, int maxHp, int damege); // .h文件中只有声明

    // Declare the default constructor
    GameCharacter();

    // Declare the public getter functions (getName, getHp, isAlive)
    std::string getName() const; // 不修改字段的方法设为const
    int getHp() const;
    bool isAlive() const;

    // Declare the public action functions (takeDamage, attack)
    void takeDamage(int amount);
    void attack(GameCharacter& target) const; // 不会改变自己的字段
    void setM_damage(int damage);

private:
    // Declare the private member variables
    std::string m_name;
    int m_hp;
    int m_maxHp;
    int m_damage;
    bool m_isAlive;

    // Declare the private member function
    void die();
};

#endif // GAMECHARACTER_H