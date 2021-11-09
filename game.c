#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "game.h"

void PrintDifficulty(int userDif);
void GetValidateUserInputDigit(int* myInput, int lowerRange, int higherRange);
int minDif=1; //min count for difficulty - starts at 1 - Beginner
int maxDif=3; //max count for difficulty - ends at 1 - Advanced
void PrintUserDigitOptions(int min, int max);
int GetMonsterDamage(int difficulty);
void PrintAttackElements(int min, int max);
void PrintDamageMonsterTook(int *numDamageType);

void GetIntroductionInfo(char userName[], int *userDifficulty, int *monsterDamage){
  printf("Hello adventurer, what is your name?\n");
  scanf("%s", userName);
  // strcpy(userName, "Elenie"); //for testing only
  printf("\nNice to meet you %s.\nYou have been called here to explore these vast catacombs in search of great treasure and riches.\n\n", userName);
  printf("What difficulty would you like?\n");
  printf("--------------------------\n");
  printf("1. Beginner\n2. Intermediate\n3. Advanced\n");
  printf("--------------------------\n");
  PrintUserDigitOptions(minDif, maxDif);
  GetValidateUserInputDigit(userDifficulty, minDif, maxDif);
  // userDifficulty=1; //for testing only
  printf("\n");
  //Print difficulty, Set damage taken by monster based on level
  PrintDifficulty(* userDifficulty);
  // * monsterDamage=GetMonsterDamage(* userDifficulty);
  // printf("Monster Damage per hit is: %d\n", * monsterDamage);
  printf("\n");
}

// Based off the defined user difficulty, pads damage output based off the difficulty and basedamage variable
//  damage is range based generated randomly from rand/srand
int GetMonsterDamage(int difficulty){
  int damage;
  int baseDamage=20;

  //damage range 0-20
  if (difficulty==1){
    damage = GetRandomNum(baseDamage, 0);
  }
  //damage range 10-30
  else if (difficulty==2){
    damage = GetRandomNum(baseDamage, 10);
  }
  else{
    //damage range 20-40
    damage = GetRandomNum(baseDamage , 20);
  }
  printf("\n");
  return damage;
}

//print level difficulty
void PrintDifficulty(int userDif){
  if (userDif==1){
    printf("You Chose Beginner");
  }
  else if (userDif == 2){
    printf("You Chose Intermediate");
  }
  else if (userDif == 3){
    printf("You chose Advanced");
  }
  printf("\n");
}




void GetUserPathChoice(int *pathChoice){
  int minPathChoice=1;
  int maxPathChoice=3;
  
  PrintUserDigitOptions(minPathChoice, maxPathChoice);
  
  GetValidateUserInputDigit(pathChoice, minPathChoice, maxPathChoice);
  printf("\n");

}


//GET RANDOM PATH
void srand(unsigned int seed);

int GetRandomNum(int numUpTo, int startAtNum){
  int myRandomNum;
  myRandomNum = (rand() % numUpTo)+startAtNum; //ex. (rand() % 4)+1  - get numbers 1 to 4
  //  Get random numbers 1-4
  return myRandomNum;
}


void PrintEnemyPrompts(int enemyNum, enemy enemies[]){
	printf("%s\n\n\n", enemies[enemyNum].startingPrompt);
		int j = 0;
		while(strcmp(enemies[enemyNum].asciiArt[j],"next") != 0){
		printf("%s\n", enemies[enemyNum].asciiArt[j]);
		j++;
	}
}

void PrintPath(int monster1, int monster2, int monster3, enemy enemies[], int numEnemies)
{
  printf("Pick a path ('1', '2', or '3').\n");
  printf("---------------------------------\n");
  printf(" 1. Left - %s\n", enemies[monster1].tunnelHint);
  printf(" 2. Straight - %s\n", enemies[monster2].tunnelHint);
  printf(" 3. Right - %s\n", enemies[monster3].tunnelHint);
  printf("---------------------------------\n");
}

void RandomGold(int *gold) {
	/*
	 * Simple gold generator, invoke on monster death or mon health <= 0
	 * gives gold min 10 max 25 and adds to gold purse.
	*/
	int goldInc = GetRandomNum(50, 10);
	*gold += goldInc;
	printf("You search the monster's corpse and find %d pieces of gold!\n", goldInc);



}

int ShopKeeper(int *gold, int *sword, int *potions, int *armor, int *lives) {
	/*
	 * Takes input fold from the user and sword boolean int, if purchase is made
	 * gold is automatically subtracted
	 * Sword is permenant item once bought and gives slight attack dmg increase
	 * the armoring is a health buff item that can be purchased multiples times to make HP over 100
	 * health restore is a full health restoring potion if health is below base max of 100
	*/
	if(*gold >= 10){
	    printf("Welcome to the shop, traveller, see my wares below or enter q to exit!\n");
	}
	char prompt = ' ';

	while(prompt != 'q' && *gold >= 10) {
	    //printf("\e[1;1H\e[2J");
	    printf("You have %d gold\n", *gold);
	    printf("You have %d potions\n", *potions);
	    printf("You have %d lives\n\n", *lives);
	    if(*sword==0){
	        printf("A. Sword(+10 dmg)\n");
		    printf("Gold cost: 10\n");
	    }
	    else{
	        printf("A. Lootbox\n");
	        printf("Gold cost: 10\n");
	    }
	    if(*armor==0){
	        printf("B. Armor(+10 HP)\n");
	    }
	    else{
	        printf("B. Extra life\n");
	    }
		printf("Gold cost: 20\n");
		printf("C. Life Potion(restores health)\n");
		printf("Gold cost: 30\n");
		scanf(" %c", &prompt);
    printf("\n");
		if (prompt == 'A' || prompt == 'a') {
			if (*sword != 1 && *gold >= 10) {
				printf("You have purchased the sword\n");
				*sword = 1;
				*gold-=10;
			}
			else if(*gold >=10){
			    printf("You have purchased the lootbox\n");
			    int itemR = GetRandomNum(4, 0);
			    if(itemR == 0){
			        printf("You received a potion from the lootbox!\n");
			        *potions=*potions+1;
			    }
			    else if(itemR == 1){
			        printf("You received an extra life from the lootbox!\n");
			        *lives=*lives+1;
			    }
			    else if(itemR == 1){
			        printf("You received an extra life from the lootbox!\n");
			    }
			    else{
			        printf("Guess you weren't that lucky! You received nothing from the lootbox! ;(\n");
			    }
			    *gold-=10;
			}
			else {
				printf("You do not have enough gold!\n");
			}
		}
		else if (prompt == 'B' || prompt == 'b') {
		        if(*gold >=20 && *armor !=1){
				    printf("You have purchased armor\n");
				    *gold-=20;
				    *armor = 1;
		        }
		        else if(*gold >= 20){
		            printf("You have purchased an extra life\n");
		            *lives=*lives + 1;
		            *gold-=20;
		        }
		        else{
		            printf("You do not have enough gold!\n");
		        }
		}
		else if (prompt == 'C' || prompt == 'c') {
		    if(*gold >= 30){
			    printf("You have purchased the potion and your health is fully restored\n");
			    *potions=*potions+1;
			    *gold-=30;
		    }
		    else{
		        printf("You do not have enough gold!\n");
		    }
		}
		if(*gold < 10){
	        printf("You are too broke to buy anything. Come back when you have more money.\n");
	        printf("You are left with %d gold.\n", *gold);
          printf("*** HINT: you can get more gold by killing monsters ***\n");
          printf("=======================================\n");
          printf("=======================================\n");
          printf("=======================================\n\n");
	    }
	    else{
          printf("=======================================");
	        printf("\n\nWould you like to make another purchase? \nEnter 'q' to quit.\n");
	    }
		printf("\n");
	}
	return *gold;
}

int DamageToMonsters(int damageType, enemy enemyType, int sword) {
	/*
	 * Simple damage function that looks like struct enemy element and then assigns damage accordingly
	 * currently set to be static can be converted to dynamic depending on difficulty etc...
	*/
	int monsterDamage;
  
	if (damageType == 1 || damageType == 2 || damageType == 3 || damageType == 4) {
	if (damageType == 1) {
		if (strcmp(enemyType.element, "Air\n") == 0) {
			monsterDamage = 40;
		}
		else if (strcmp(enemyType.element, "Water\n") == 0) {
			monsterDamage = 10;
		}
		else {
			monsterDamage = 20;
		}
	}
	else if (damageType == 2) {
			if (strcmp(enemyType.element, "Fire\n") == 0) {
				monsterDamage = 40;
			}
			else if (strcmp(enemyType.element, "Earth\n") == 0) {
			    monsterDamage = 10;
		    }
			else {
				monsterDamage = 20;
			}
		}
	else if (damageType == 3) {
			if (strcmp(enemyType.element, "Water\n") == 0) {
				monsterDamage = 40;
			}
			else if (strcmp(enemyType.element, "Air\n") == 0) {
			    monsterDamage = 10;
		    }
			else {
				monsterDamage = 20;
			}
		}
	else {
			if (strcmp(enemyType.element, "Earth\n") == 0) {
				monsterDamage = 40;
			}
			else if (strcmp(enemyType.element, "Fire\n") == 0) {
			    monsterDamage = 10;
		    }
			else {
				monsterDamage = 20;
			}
		}
	}
	if (sword == 1) {
			monsterDamage += 10;
		}
	return monsterDamage;
  }
int DamageToBoss(int damageType, int enemyDamageType, int sword) {
	/*
	 * Simple damage function that looks like struct enemy element and then assigns damage accordingly
	 * currently set to be static can be converted to dynamic depending on difficulty etc...
	*/
	int monsterDamage;

	if (damageType == 1 || damageType == 2 || damageType == 3 || damageType == 4) {
	if (damageType == 1) {
		if (enemyDamageType == 4) {
			monsterDamage = 40;
		}
		else if (enemyDamageType == 2) {
			monsterDamage = 10;
		}
		else {
			monsterDamage = 20;
		}
	}
	else if (damageType == 2) {
			if (enemyDamageType == 1) {
				monsterDamage = 40;
			}
			else if (enemyDamageType == 3) {
			    monsterDamage = 10;
		    }
			else {
				monsterDamage = 20;
			}
		}
	else if (damageType == 3) {
			if (enemyDamageType == 2) {
				monsterDamage = 40;
			}
			else if (enemyDamageType == 4) {
			    monsterDamage = 10;
		    }
			else {
				monsterDamage = 20;
			}
		}
	else {
			if (enemyDamageType == 3) {
				monsterDamage = 40;
			}
			else if (enemyDamageType == 1) {
			    monsterDamage = 10;
		    }
			else {
				monsterDamage = 20;
			}
		}
	}
	if (sword == 1) {
			monsterDamage += 10;
		}
	return monsterDamage;
  }
void GameOver(int lives, int playerHealth) { //Function to determine Game Over
    while (lives > 0) {
        if (playerHealth <= 0) {
            lives = lives - 1; //Decrement lives from game
            if (lives <= 0) {
                printf("Game Over");
            }
        }
     }
}

/**
 * Function to populate an array of enemies with data from file.
 * 
 * @param enemies An array of enemies to populate.
 * @param max_size Maximum size of the array to populate.
 * @return The number of enemies.
 */
int PopulateEnemies(enemy enemies[], int max_size){
	FILE *fptr; //Declare a file to open.
	char *line = NULL;  //Declare a line variable to read in a file line by line.
	size_t len = 0; //Declare a length variable to read in length of a line in a file.
	size_t read; //Variable to determine if end of file is reached.
	fptr = fopen("enemy.txt", "r"); //Open enemy.config for reading in contents.
	//Loop to read in contents of enemy.config line by line and create and populate the struct array with enemies.
	int i = 0;
	read = getline(&line, &len, fptr);
	while(read != -1 && i < max_size){
		strcpy(enemies[i].tunnelHint, line);
		read = getline(&line, &len, fptr); //Read in another line for enemy name.
		strcpy(enemies[i].name, line);
		read = getline(&line, &len, fptr); //Read in another line for element.
		strcpy(enemies[i].element, line);
		read = getline(&line, &len, fptr); //Read in another line for starting prompt.
		strcpy(enemies[i].startingPrompt, line);
		read = getline(&line, &len, fptr); //Read in another line for ascii art.
		int j = 0;
		line[strcspn(line, "\r\n")] = 0;
		while(strcmp(line, "next") != 0 && j < 49){
			strcpy(enemies[i].asciiArt[j], line);
			read = getline(&line, &len, fptr); //Read in another line for ascii art.
			line[strcspn(line, "\r\n")] = 0;
			j++;
		}
		strcpy(enemies[i].asciiArt[j], "next");
		read = getline(&line, &len, fptr);
		i++;
	}
	fclose(fptr);
    return i;
}



//function that prints Fire, Water,Earth, Air
void PrintAttackElements(int min, int max){
  printf("Choose which element to attack with:\n");
  printf("--------------------------\n");
  printf("1. Fire\n2. Water\n3. Earth\n4. Air\n");
  printf("--------------------------\n");
  PrintUserDigitOptions(min, max);
}


//Print attack elements fire, water, earth, air and get userInput choice
void GetAndPrintUserAttackElementChoice(int *elementChoice){

  int elementNum=4;
  int minNum = 1;

  PrintAttackElements(minNum, elementNum);

  GetValidateUserInputDigit(elementChoice, minNum, elementNum);
}


//Print: Type 1, 2 or 3    (changes depending on min or max)                   
void PrintUserDigitOptions(int min, int max){
  int i;
  printf("Type ");
  for (i=min; i<max; i++){
    printf("%d, ", i);
  }
  printf("or %d: ", max);
}

void GetValidateUserInputDigit(int* myInput, int lowerRange, int higherRange){
    scanf("%d", myInput);
      //check if user input is within range. 
      //Program breaks if user input anything other than a number (infinite loop)
    while ( *myInput >higherRange || *myInput <lowerRange){
          printf("******ERROR*****\n");
          printf("You have selected %d which is out of range, please select an option between %d and %d\n", *myInput, lowerRange, higherRange);
          printf("Enter here: ");
          scanf("%d", myInput);
          printf("\n");
    }

}


void GetDamageTypeMonsterTook(int *numDamageType){
  char *damageType[10];
  if (*numDamageType==1){
      *damageType="Fire";
  }
  else if(*numDamageType==2){
    *damageType="Water";
  }
  else if(*numDamageType==3){
    *damageType="Earth";
  }
  else{
    *damageType="Air";
  }
   printf("\nYour %s attack was", *damageType);
}

//display text for damage amount
void GetPowerType(char *type[], int damage){
  if (damage<10){
    *type=" very weak";
  }
  else if(damage<20){
    *type="weak";
  }
  else if(damage<35){
    *type="effective";
  }
  else{
    *type="super effective";
  }
  
}

//Calculate Damage done to the monster
void CalculateDamageToMonster(int *monsterHealthUpdate, int userElement, int sword, enemy enemyType){
  GetDamageTypeMonsterTook(&userElement);
  int damage;
  // damage=20;   // needs to be removed and calculated with the function below
  damage=DamageToMonsters(userElement, enemyType, sword);
  char *powerType;
  GetPowerType(&powerType, damage);
  printf(" %s and did ", powerType);
  *monsterHealthUpdate-=damage;
  printf("%d damage.\n", damage);
}

void CalculateDamageToPlayer(int *playerHealthUpdate, int difficulty, enemy enemyName){
  int damageTaken=GetMonsterDamage(difficulty);
  *playerHealthUpdate-=damageTaken;
  printf("The %sIt blasted you and did %d damage!\n", enemyName.name ,damageTaken);
}

//check if user wants to use a health potion if they have one available and their health is less than 100
void AskForHealthPotion(int * playerHealth,int * potions){
   if (*playerHealth<60 && *potions>0){
          int answer;
          printf("Your health is low! Would you like to use a health potion? 1 for yes, 2 for no");
          PrintUserDigitOptions(1, 2);
          GetValidateUserInputDigit(&answer, 1, 2);
          if (answer==1){
            printf("Your health regenerated from %d to 100",* playerHealth);
            *potions=*potions-1;
          }
      }
}


void CheckIfMonsterIsDead(int monsterHealth, int * fightWon, int *userGold){
        if (monsterHealth<=0){
          printf("\n=======================================\n");
          printf("=======================================\n");
          printf("=======================================\n");
          printf("Congrats you have destroyed the monster and advanced a level\n");
          RandomGold(userGold);
          *fightWon=1;
          printf("\n\n\n");

        }
}


int CheckIfPlayerIsDead(int playerHealth, int *lives){
  int result=2; //I just don't want it to be 0 or 1
  if (playerHealth<=0){
          printf("You have lost all your health\n");
          *lives=*lives-1;
          if (*lives>0){
            printf("Available lives: %d\n\n\n", *lives);
            result=1; //break
          }
          else{
            printf("\n\n\n");
            printf("-----------------------------------\n");
            printf("-----------------------------------\n");
            printf("--------- G A M E   O V E R ---------\n");
            printf("-----------------------------------\n");
            printf("-----------------------------------\n");
            result=0; //return 0
          }
      }
    return result;
}

void BossFight(char name[], int *lives, int *potions, int *sword, int *health, int difficulty, int *armor, int *gold){
    int countdownTimer=2;
    printf("The tunnel you're travelling down ends into a longer tunnel!\n");
    sleep(countdownTimer);
    printf("You take the longer tunnel towards a light, which leads into a huge cavern!\n");
    sleep(countdownTimer);
    printf("The cavern is huge, but in the back looks like the way out!\n");
    sleep(countdownTimer);
    printf("You start running for the light, ready to feel the cool breeze on your back.\n");
    sleep(countdownTimer);
    printf("Then, you smack into something. It is your mother.\n");
    sleep(countdownTimer);
    printf("Mom: \"Hello dear. What are you doing in this cave?\"\n");
    sleep(countdownTimer);
    printf("%s: I thought I would find treasure here, but I was repeatedly attacked.\n", name);
    sleep(countdownTimer);
    printf("Mom: \"You know exploring a cave like this is dangerous.\"\n");
    sleep(countdownTimer);
    printf("%s: I know mom.\n", name);
    sleep(countdownTimer);
    printf("Your mother gets closer. She hugs you tight! Something doesn't feel right.\n");
    sleep(countdownTimer);
    printf("This woman doesn't feel like your mother. You look up at her face and it is not the same.\n");
    sleep(countdownTimer);
    printf("%s: Woah there! You're not my mother.\n", name);
    sleep(countdownTimer);
    printf("Witch: \"NOOOoooo, you've seen through my disguise! You must be a true sorcerer!\"\n");
    sleep(countdownTimer);
    printf("Witch: \"Regardless, I won't let you leave here alive! Prepare to die!\"\n");
    printf("                                      __,,,\n");
    printf("                                 _.--'    /\n");
    printf("                              .-'        /\n");
    printf("                            .'          |\n");
    printf("                          .'           /\n");
    printf("                         /_____________|\n");
    printf("                       /`~~~~~~~~~~~~~~/\n");
    printf("                     /`               /\n");
    printf("      ____,....----'/_________________|---....,___\n");
    printf(",--""`             `~~~~~~~~~~~~~~~~~~`           `""--,\n");
    printf("`'----------------.----,------------------------,-------'`\n");
    printf("               _,'.--. \\                         \\\n");
    printf("             .'  (o   ) \\                        |\n");
    printf("            c   , '--'  |                        /\n");
    printf("           /    )'-.    \\                       /\n");
    printf("          |  .-;        \\                       |\n");
    printf("          \\_/  |___,'    |                    .-'\n");
    printf("         .---.___|_      |                   /\n");
    printf("        (          `     |               .--'\n");
    printf("         '.         __,-'\\             .'\n");
    printf("           `'-----'`      \\        __.'\n");
    printf("                           `-..--'`\n");
    if(*armor == 1){
        *health = 110;
    }
    else{
        *health = 100;
    }
    int witchHealth = 200;
    int element;
    int elementNum=4;
    int minNum = 1;
    while(witchHealth > 0 && *lives > 0){
        int attk;
        int dmgB;
        int dmgU;
        char potChoice[10];
        printf("\nWitch health is: %d\n", witchHealth);
        printf("Player health is: %d \nPlayer available lives: %d\n\n", *health, *lives);
        PrintAttackElements(minNum, elementNum);
        element = GetRandomNum(elementNum, 0); //The witch's element changes.
        GetValidateUserInputDigit(&attk, minNum, elementNum);
        dmgU = DamageToBoss(attk, element, *sword);
        printf("Your attack did %d damage against the witch, which changes elements.\n", dmgU);
        witchHealth -= dmgU;
        if(witchHealth > 0){
            printf("The witch's health is %d\n", witchHealth);
            dmgB = (GetMonsterDamage(difficulty)*GetRandomNum(4, 1)/2);
            printf("The witch did %d damage!\n", dmgB);
            *health -= dmgB;
        }
        if(*health <= 0){
            printf("Witch: \"I GOT YOU!!! BAHAHAHAHAAHAHAHAHA!!!!!\"\n");
            witchHealth = 200;
            *lives -= 1;
            if(*lives > 0){
                ShopKeeper(gold, sword, potions, armor, lives);
                printf("You respawn with full health.\n");
                printf("The witch also regenerates her health!\n");
            }
            else{
                printf("Game Over");
            }
            if(*armor == 1){
                *health = 110;
            }
            else{
                *health = 100;
            }
        }
        else if(*potions > 0 && witchHealth > 0){
            printf("You have %d potions and have %d health. Would you like to use one (y\\n)?\n", *potions, *health);
            scanf("%s", potChoice);
            if(strcmp(potChoice, "y")==0){
                *potions=*potions-1;
                if(*armor == 1){
                    *health = 110;
                }
                else{
                    *health = 100;
                }
            }
        }
        else{
            //The game continues
        }
        
        
    }
    if(*lives>0){
        printf("Witch: \"NoO0oO0oOoo!!!!!\"\n");
        sleep(2);
        printf("%s: I vanquish you from these sacred catacombs!\n", name);
        sleep(2);
        printf("The witch melts into a treasure chest full of gold! You did it, you got the treasure!\n");
    }
}
