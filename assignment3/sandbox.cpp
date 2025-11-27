/*
 * CS106L Assignment 3: Make a Class
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */

/*
 * File: sandbox.cpp
 * -----------------
 * This is a sandbox file for you to test your GameCharacter class.
 */

#include "class.h"
#include <iostream>

using namespace std;

void sandbox() {
    // Construct an instance of your class!
    cout << "--- Creating characters ---" << endl;
    GameCharacter hero("Aragon", 150, 25);
    GameCharacter monster; // Using the default constructor

    cout << hero.getName() << " HP: " << hero.getHp() << endl;
    cout << monster.getName() << " HP: " << monster.getHp() << endl;
    cout << "-------------------------" << endl;

    cout << "\n--- Battle Begins! ---" << endl;
    hero.attack(monster);
    cout << monster.getName() << " takes damage! New HP: " << monster.getHp() << endl;

    monster.attack(hero);
    cout << hero.getName() << " takes damage! New HP: " << hero.getHp() << endl;

    // Let's see who wins...
    while (hero.isAlive() && monster.isAlive()) {
        hero.attack(monster);
        cout << hero.getName() << " attacks " << monster.getName() << ". "
             << monster.getName() << "'s HP: " << monster.getHp() << endl;
        if (monster.isAlive()) {
            monster.attack(hero);
            cout << monster.getName() << " attacks " << hero.getName() << ". "
                 << hero.getName() << "'s HP: " << hero.getHp() << endl;
        }
    }
    cout << "--- Battle Over! ---" << endl;

    if (hero.isAlive()) {
        cout << hero.getName() << " is victorious!" << endl;
    } else {
        cout << monster.getName() << " is victorious!" << endl;
    }
}