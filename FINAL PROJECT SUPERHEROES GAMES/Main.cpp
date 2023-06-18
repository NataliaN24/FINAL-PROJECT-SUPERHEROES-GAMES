#include<iostream>
#include"Admin.h"
#include "Superhero.h"

void AdminFunctionalities()
{
    int choice;
    Admin admin;
    MyString name, surname, email, password;
    MyString PlayerEmail;
    MyString  PlayerPassword;
    MyString playerName;
    unsigned int money;

    do
    {
        std::cout << "==== Menu ====" << std::endl;
        std::cout << "1. Add Another Admin" << std::endl;
        std::cout << "2. See Info of Admins" << std::endl;
        std::cout << "3. Add a superhero" << std::endl;
        std::cout << "4. Add a player" << std::endl;
        std::cout << "5. See info of players" << std::endl;
        std::cout << "6. Delete a player" << std::endl;
        std::cout << "7. See info of sold superheroes" << std::endl;
        std::cout << "8. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            admin.addAnotherAdmin();
            break;

        case 2:
            admin.seeInfo("admin.txt");
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
            admin.seeInfoOfPlayers();
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

void displayMenuOFAdmin() 
{
    int choice;
    Admin admin;
    MyString name;
    MyString email;
    MyString password;
    MyString surname;

    do
    {
        std::cout << "==== Menu ====" << std::endl;
        std::cout << "1.Log In" << std::endl;
        std::cout << "2.Sign up" << std::endl;
        std::cout << "3.Exit" << std::endl;
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            std::cout << "Enter your email: ";
            std::cin >> email;
            std::cout << "Enter your password: ";
            std::cin >> password;
            if (admin.logIn(email, password, "admin.txt")) 
            {
                AdminFunctionalities();
            }
            else 
            {
                std::cout << "Error.You can not have access to this game functionalities.Try again..." << std::endl;
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

void PlayerFunctionalities(MyString email, MyString password, MyString name)
{
    int choice;
    Player player;
    MyString superheroName;
    unsigned int money = 0;
    bool bought = false;
    int  buyingInput;
    unsigned moneyPlayer = 0;

    do
    {
        std::cout << "===== Player Menu =====" << std::endl;
        std::cout << "1. Delete profile." << std::endl;
        std::cout << "2. See player info" << std::endl;
        std::cout << "3. See superheroes" << std::endl;
        std::cout << "4. Buy a superhero" << std::endl;
        std::cout << "5. Change attack mode." << std::endl;
        std::cout << "6. Attack a superhero" << std::endl;
        std::cout << "7. Upgrade a superhero" << std::endl;
        std::cout << "8. Log out" << std::endl;
        std::cout << "=======================" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
    
        try 
        {
            switch (choice) 
            {
            case 1:
                player.deletePlayerProfile(email, password, name);
                return;
                break;

            case 2:
                player.seeInfoByPlayers();
                break;

            case 3:
                player.seeSuperheroes();
                break;

            case 4:
                player.seeSuperheroes();
                bought = player.checkIfPlayerhasPurchased(name);
                if (bought) 
                {
                    std::cout << "You already have a superhero.If you want to buy a new superhero ,would you like to delete the old one?Type 1-yes or 0-no." << std::endl;
                    std::cin >> buyingInput;
                    if (buyingInput == 1)
                    {
                        player.deleteFromPurchase(name);
                        std::cout << "Now you can buy a new superhero" << std::endl;
                    }
                    else if(buyingInput==0)
                    {
                        break;
                    }
                }
                else 
                {
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
                player.upgradeSuperhero(50, name);
                break;

            case 8:
                moneyPlayer = player.showBalance(email);
                moneyPlayer += 50;
                player.storeMoney(name, moneyPlayer);
                if (player.checkIfPlayerhasPurchased(name))
                {
                    player.storeMoneyInPurchase(name, moneyPlayer);
                }
                std::cout << "You logged out!...Exiting..." << std::endl;
                break;
            default:            
                throw std::runtime_error("Invalid choice. Please try again.");
                break;
            }
        }
        catch (const std::exception& e)
        {
            std::cout << "Exception occurred: " << e.what() << std::endl;
        }
        std::cout << std::endl;
    } while (choice != 8);

}


void displayMenuOfPlayer() 
{
    int choice;
    Player player;

    MyString email;
    MyString password;
    MyString name;


    do
    {
        std::cout << "===== Player Menu =====" << std::endl;
        std::cout << "1.Sign up" << std::endl;
        std::cout << "2.Log in" << std::endl;
        std::cout << "3.Exit" << std::endl;
        std::cout << "=======================" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) 
        {
        case 1:
            player.signUp();
            std::cout << "You signed up successfully.Log in to gain more access to game." << std::endl;
            break;

        case 2:
            std::cout << "Enter your name: ";
            std::cin >> name;
            std::cout << "Enter your email: ";
            std::cin >> email;
            std::cout << "Enter your password: ";
            std::cin >> password;
            if (player.logIn(email, password, "player.txt")) 
            {
                PlayerFunctionalities(email, password, name);
            }
            else 
            {
                std::cout << "Error.You can not have acces to this game functionalities.Try again..." << std::endl;
            }
            break;

        case 3:
            std::cout << "Exiting..." << std::endl;
            break;

        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }

        std::cout << std::endl;
    } while (choice != 2);

}


int main() 
{
    int choice;
    do 
    {
        std::cout << "WELCOME TO SUPERHEROES GAME" << std::endl;
        std::cout << "===== MAIN MENU =====" << std::endl;
        std::cout << "1. Enter as an administrator" << std::endl;
        std::cout << "2. Enter as a player" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "=======================" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice) 
        {
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