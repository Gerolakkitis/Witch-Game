#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"



int main(void) {
  int max_size = 200;

  enemy enemies[max_size];
  int numEnemies;
  numEnemies = PopulateEnemies(enemies, max_size);

  // enemy enemies[max_size];
  char name[30];
  int difficulty;
  int monsterDamagePerHit;
  // int* playerAttackDamage;
  int lives=3;
  int sword = 0; //If sword is 1, they have a sword. If not, then this is 0.
  int armor = 0; //If armor is 1, they have a armor. If not, then this is 0.
  int potions=0;
  int firstPath;
  int monster1;
  int monster2;
  int monster3;
  int monsterChoice;
  int fightWon = 1; //To comply with old c, 0 means false, 1 means true.
  time_t t;
  srand((unsigned) time(&t)); //unique seed
  // int secondPath;
  // int thirdPath;
  // int fourthPath;
  int numOfPaths=4;
  int userPathChoise;
  int usrGold = 5;
  int level = 0;
  int usrSword, usrArmor = 0;
  int userPathChoice;
  int userElementChoise;
  int monsterHealth;
  int playerHealth;
  int maxLevel=10;
  int playerLife;
  
  //Get user name, set difficulty, set monster Damage per hit
  GetIntroductionInfo(name, &difficulty, &monsterDamagePerHit);
  while(lives>0 && level < maxLevel){
	  if(fightWon == 1){
		srand(time(0));
		monster1 = GetRandomNum(numEnemies, 0);
		monster2 = GetRandomNum(numEnemies, 0);
		monster3 = GetRandomNum(numEnemies, 0);
	  }
	  if(level == 0){
	      printf("You are at the start of the catacombs.\n");
	  }
	  else{
	      printf("You are %d levels deep into the catacombs. (Total levels: %d)\n", level, maxLevel);
	  }
	  //Print instructions for 1st Path
	  PrintPath(monster1, monster2, monster3, enemies, numEnemies);
	  GetUserPathChoice(&userPathChoise);
	  switch (userPathChoise){
		  case 1:
			PrintEnemyPrompts(monster1, enemies);
      monsterChoice = monster1;
			//Fight function here
			break;
		  case 2:
			PrintEnemyPrompts(monster2, enemies);
      monsterChoice = monster2;
			break;
		  case 3:
			PrintEnemyPrompts(monster3, enemies);
      monsterChoice = monster3;
			break;
		  default:
			printf("This is not a valid path\n");
			while(userPathChoise != 1 && userPathChoise != 2 && userPathChoise != 3){
				GetUserPathChoice(&userPathChoise);
			}
	  }


    monsterHealth=100;
    playerHealth=100;
    while(1){
      printf("\nMonster health is: %d\n", monsterHealth);
      // if (armor==1){
      //   playerHealth+=10;
      // }  //Sandy fixing this bug
      printf("Player health is: %d\n", playerHealth);
      printf("Player available lives: %d\n\n\n", lives);

      //check if user wants to use a health potion if they have one available and their health is less than 100
      AskForHealthPotion(&playerHealth, &potions);

      //Print attack elements fire, water, earth, air and get userInput choice
      GetAndPrintUserAttackElementChoice(&userElementChoise);
            
      //*******************need to pass in CalcDamToMonster the damage type, emenyType, sword, and monsterHealth
      //we need to pass in the enemy Type to get correct damage
      CalculateDamageToMonster(&monsterHealth, userElementChoise, sword, enemies[monsterChoice]);

      int result = 2;

      CheckIfMonsterIsDead(monsterHealth, &result, &usrGold);
      if (result==1){
        level++;
        ShopKeeper(&usrGold, &sword, &potions, &armor, &lives);
        break;
      }

      CalculateDamageToPlayer(&playerHealth, difficulty, enemies[monsterChoice]);
      playerLife=CheckIfPlayerIsDead(playerHealth, &lives);
      
      //if lives>0 break out of the while loop
      if (playerLife==1){
        break;
      }
      //if lives=0 GAME OVER
      else if(playerLife==0){
        return 0;
      }
    printf("\n\n\n\n");
  }
  




////-------------------------------------------------- 
    

  // 	for(int x = 0; x<i; x++){
	// 	printf("Tunnel Hint: %s\n", enemies[x].tunnelHint);
	// 	printf("Enemy Name: %s\n", enemies[x].name);
	// 	printf("Enemy Element: %s\n", enemies[x].element);
	// 	printf("Prompt: %s\n", enemies[x].startingPrompt);
	// 	printf("Ascii art: \n");
	// 	int j = 0;
	// 	while(strcmp(enemies[x].asciiArt[j],"next") != 0){
	// 		printf("%s\n", enemies[x].asciiArt[j]);
	// 		j++;
	// 	}
	// }



  }
  BossFight(name, &lives, &potions, &sword, &playerHealth, difficulty, &armor, &usrGold);
  return 0;
}

