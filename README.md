# FINAL PROJECT SUPERHEROES GAMES
_This is a game model for playing with superheroes.The language of programming used for it is C++_

**Joro and his friends are big fans of superheroes and comics. He wants to create his own superhero game, where different players can buy superheroes, attack other users' superheroes, or put their superheroes in protected mode. Each player is allowed a maximum of 3 moves per game entry. The results are calculated according to the funds (money) that a player has.**

 ## USERS
                           Joro decides that he will need two types of users:
- Admins who will have rights to add new players, delete player profiles and add superheroes to the market.
- Players who will play the game.
Both types of users are characterized by two names, an email, a username and a password, but players also have a balance of virtual funds (money) available during the game.

## ADMINISTRATOR FUNCTIONALITIES 
| **ADMIN** | 
|----------|
| - Add new admin   | 
| - Add new player   | 
| - Add add new superheroes to the "market". In the event that there are no superheroes on the "market", the administrator must add at least 3 superheroes upon logging in   | 
| - Delete player profiles.  | 
| - See all information about players |
|- See the names and email of other administrators|
|- See sold superheroes |

##  PLAYER FUNCTIONALITIES
| **PLAYER** | 
|----------|
| - Delete their profile   | 
| - See list of players:username,money ,superheroes  | 
| - See market of superheroes  | 
| - Purchase a superhero and remove the hero from the market after purchase  | 
| - Attack a superhero |
|- Change the position from deffense mode to attack mode or opposite|

##  DESCRIBING SUPERHEROES 
**A superhero has:**
* Two names
* A superhero nickname
* A power type (fire, water, or earth) 
* A  power (in points, a positive number)
* A purchase price
* Attacking mode (0 for deffense mode ,1 for attack mode)

# THE  WAY OF PLAYING THE GAME AND HOW TO DETERMINE IF AN ATTCK IS SUCCESSFUL ?
* When a player attacks another player, they must either choose whose superhero to attack, or have one chosen at random.
* If a player attacks another player who does not have any superheroes, the attacked player's money is reduced by the number of attack points that the attacking superhero had (in case the attacked player has less money than the attacking superhero's power, then his balance becomes $0), and the attacking player wins x amount of money.
* If a player attacks another player's superhero, their power types are first compared. Each type of power defeats another as follows: Fire->Earth->Water->Fire(FIRE IS MORE DOMINANT THAN EARTH ,EARTH THAN WATER AND WATER THAN FIRE)
*  If the attacking player has a dominant power type, then their superhero points in that battle are doubled and the power comparison rules listed below apply. In case the attacking player has the dominant power type, then the opposing superhero's points are doubled and the superheroes' power is compared again.
* ->> In case the power types match and the attacked player's superhero is in attack mode, the power of the superheroes is compared. A defeated superhero is always destroyed by the defeated player's collection. The strength comparison is as follows:
* ->> If the attacking player's superhero has more power than his opponent's, then the attacked player loses money equal to the power difference of the competing superheroes, and the attacking player wins an amount equal to the same difference.
* ->> If the attacking player's superhero has less power than the attacked, then the attacked wins an amount z and the attacker loses money worth 2 times the difference in the powers of the competing superheroes.
* ->> If the superheroes are of equal strength, then the attacked player does not change and loses money, but the attacker loses an amount k.
* ->> In case the attacking player attacks a superhero who is in defensive mode, then the attacked player does not lose any money (but may lose their hero) and scoring a winner is as above.
### ADDITIONAL
* Players, apart from fighting, also get money j periodically.A time period is one cycle in which all players are logged in.**The way that I have implemented it is ,that after player chooses to log out the money is stored automatically in his datas**
* When adding a new player, he starts with an amount of m.**The amount is choosen by the admin who adds the player .Otherwise if the player signs up ,a default  amount of money is stored automatically in his money balance**
* Players can  upgrade their superheroes by paying money.**They can upgrade superheroes if they have enough money**
 
### RUN THE PROGRAM
When user enters the program the _Main Menu_ is appeared where he has to choose 3 commands:
* To enter as an administrator
* To enter as a player
* To exit the program

 _in the first case ,if he  chooses to enter as an admin ,again he has to choose 3 commands,to sign up,log in,or exit_
  1.After signing up he must log in to see and perform admin functionalities.
  2.After logging in ,the  list of admin functionalities that is listed above  appears and admin has to choose one of the commands to perform.
  
 ![Screenshot 2023-06-18 130757](https://github.com/NataliaN24/FINAL-PROJECT-SUPERHEROES-GAMES/assets/115610226/d6f607e1-739d-4bcd-afbb-ebaa4c010681)

_in the second  case ,if user   chooses to enter as a player ,again he has to choose 3 commands,to sign up,log in,or exit_

![Screenshot 2023-06-18 130757](https://github.com/NataliaN24/FINAL-PROJECT-SUPERHEROES-GAMES/assets/115610226/4e24c4f5-f788-4087-a881-6f3098641d39)

_When player chooses to log out he will gain money in his balance._






