#ifndef game_h
#define game_h
typedef struct enemy_struct{
	char tunnelHint[100];
	char name[50];
	char element[50];
	char startingPrompt[999];
	char asciiArt[50][200];
} enemy;




int PopulateEnemies(enemy enemies[], int max_size);
void GetIntroductionInfo(char userName[], int *userDifficulty, int *monsterDamage);
void GetUserPathChoice(int *pathChoise);
void PrintEnemyPrompts(int enemyNum, enemy enemies[]);
int SetDifficulty(int userDif);
int GetRandomNum(int numUpTo, int startAtNum);
void PrintPath(int monster1, int monster2, int monster3, enemy enemies[], int numEnemies);
int ShopKeeper(int *gold, int *sword, int *potions, int *armor, int *lives);
void PrintAttackElements();

void GetUserAttackElementChoice(int* elementChoice);

void GetAndPrintUserAttackElementChoice(int* elementChoise);
void PrintDamageMonsterTook(int *numDamageType);
void CalculateDamageToMonster(int *monsterHealthUpdate, int userElement, int sword, enemy enemytype);
void CalculateDamageToPlayer(int *playerHealthUpdate, int difficulty, enemy enemyName);
// void PrintDamageMonsterTook(int *numDamageType);
void CalculateDamageToMonster(int *monsterHealthUpdate, int userElement, int sword, enemy enemyType);
int DamageToMonsters(int damageType, enemy enemyType, int sword);
void RandomGold(int *gold);
void BossFight(char name[], int *lives, int *potions, int *sword, int *health, int difficulty, int *armor, int *gold);
void PrintUserDigitOptions(int min, int max);
void GetValidateUserInputDigit(int* myInput, int lowerRange, int higherRange);
void AskForHealthPotion(int * playerHealth, int * potions);
void CheckIfMonsterIsDead(int monsterHealth, int * fightWon, int *userGold);
int CheckIfPlayerIsDead(int playerHealth, int *lives);
#endif
