#include<iostream>
#include"Admin.h"
#include "Superhero.h"

void AdminFunctionalities() {
    int choice;
    Admin admin;
    MyString name, surname, email, password;
    char PlayerEmail[50];
    char PlayerPassword[50];
    char playerName[50];
    unsigned int money;

    do {
        std::cout << "==== Menu ====" << std::endl;
        std::cout << "1. Add Another Admin" << std::endl;
        std::cout << "2. See Info of Admins" << std::endl;
        std::cout << "3. Add a superhero" << std::endl;
        std::cout << "4. Add a player" << std::endl;
        std::cout << "5. See info of players" << std::endl;
        std::cout << "6. Delete a player" << std::endl;
        std::cout << "7. See info of sold superheroes" << std::endl;
        std::cout << "8. exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            admin.addAnotherAdmin();
            break;
        case 2:
            admin.seeInfoOfAdmins();
            break;
        case 3:
            admin.addSuperhero();
            break;
        case 4:
            std::cout << "Enter player name: ";
            std::cin >> name;
            std::cout << "Enter player surname: ";
            std::cin >> surname;
            std::cout << "Enter player email: ";
            std::cin >> email;
            std::cout << "Enter player password: ";
            std::cin >> password;
            std::cout << "Enter player money: ";
            std::cin >> money;

            admin.addPlayers(name, surname, email, password, money);
            std::cout << "Player added successfully!" << std::endl;

            break;
        case 5:
            admin.seeInfoOfPlayers();//check this bc i need all the info
            break;
        case 6:
            admin.seeInfoOfPlayers();
            std::cout << "Enter name of player: ";
            std::cin >> playerName;
            std::cout << "Enter email of player: ";
            std::cin >> PlayerEmail;
            std::cout << "Enter password of player: ";
            std::cin >> PlayerPassword;

            admin.deletePlayer(PlayerEmail, PlayerPassword, playerName);
            break;
        case 7:
            admin.seeInfoOfSoldSuperheroes();
            break;
        case 8:
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }

        std::cout << std::endl;
    } while (choice != 8);

}
void displayMenuOFAdmin() {
    int choice;
    Admin admin;
    do {
        std::cout << "==== Menu ====" << std::endl;
        std::cout << "1.  Log In" << std::endl;
        std::cout << "2.Sign up" << std::endl;
        std::cout << "3. exit" << std::endl;
        std::cin >> choice;

        switch (choice) {
        case 1:
            if (admin.logIn()) {
                AdminFunctionalities();
            }
            else {
                std::cout << "Error.You can not have acces to this game functionalities.Try again..." << std::endl;
            }
            break;
        case 2:
            admin.signUp();
            std::cout << "You signed up successfully.Log in to gain more access to game." << std::endl;
            break;

        case 3:
            std::cout << "Exiting..." << std::endl;
            break;

        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }

        std::cout << std::endl;
    } while (choice != 3);




}

void PlayerFunctionalities(MyString email, MyString password, MyString name) {
    int choice;
    Player player;
    char superheroName[50];
    unsigned int money;
    bool bought = false;

    do {
        std::cout << "===== Player Menu =====" << std::endl;
        std::cout << "1. Delete profile." << std::endl;
        std::cout << "2. See player info" << std::endl;
        std::cout << "3. See superheroes" << std::endl;
        std::cout << "4. Buy a superhero" << std::endl;
        std::cout << "5. Change attack mode." << std::endl;
        std::cout << "6. Attack a superhero" << std::endl;
        std::cout << "7. Log out" << std::endl;
        std::cout << "=======================" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        //add for upgrade
        //fix the functions

        switch (choice) {
        case 1:
            player.deletePlayerProfile(email, password, name);//DONE
            return;
            break;
        case 2:
            player.PlayersPLUSSuperheroes();
            break;
        case 3:
            player.seeSuperheroes();
            break;
        case 4:
            player.seeSuperheroes();
            bought = player.checkIfPlayerhasPurchased(name);
            if (bought) {
                std::cout << "You already have a superhero." << std::endl;
            }
            else {
                player.buySuperhero();
            }
            break;
        case 5:
            std::cout << "Enter name of superhero " << std::endl;
            std::cin >> superheroName;
            player.setAttackingMode(superheroName);
            break;
        case 6:
            player.attack();
            break;
        case 7:
            std::cout << "You logged out!...Exiting..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }

        std::cout << std::endl;
    } while (choice != 7);

}


void displayMenuOfPlayer() {
    int choice;
    Player player;

    MyString email;
    MyString password;
    MyString name;
    /* char email[50];
     char password[50];
     char name[50];*/

    do {
        std::cout << "===== Player Menu =====" << std::endl;
        std::cout << "1. Log in" << std::endl;
        std::cout << "2. Exit" << std::endl;
        std::cout << "=======================" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter your name: ";
            std::cin >> name;
            std::cout << "Enter your email: ";
            std::cin >> email;
            std::cout << "Enter your password: ";
            std::cin >> password;
            if (player.logIn(email, password)) {
                PlayerFunctionalities(email, password, name);
            }
            else {
                std::cout << "Error.You can not have acces to this game functionalities.Try again..." << std::endl;
            }
            break;
        case 2:
            std::cout << "Exiting..." << std::endl;
            break;

        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }

        std::cout << std::endl;
    } while (choice != 2);

}


int main() {

    int choice;
    do {
        std::cout << "WELCOME TO SUPERHEROES GAME" << std::endl;
        std::cout << "===== MAIN MENU =====" << std::endl;
        std::cout << "1. Enter as an administrator" << std::endl;
        std::cout << "2. Enter as a player" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "=======================" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice) {
        case 1:
            displayMenuOFAdmin();
            break;
        case 2:
            displayMenuOfPlayer();
            break;
        case 3:
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
        std::cout << std::endl;
    } while (choice != 3);

    return 0;
}
