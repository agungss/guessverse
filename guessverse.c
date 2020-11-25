/* This program is a game to guess a verse, either quran or bible.
 * There will be a randomly generated complete verse in the screen.
 * In the bottom of it, there will be two choices, just click the one that's right.
 * If right, the score is count +1, if false, nothing will count.
 * The program will quit if the user press 'q'
 *  then, the program displays the score and wrong answered question
 */

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <unistd.h>
#include "uthash.h" //header file for hash table in C
//#include "raylib.h"
#include <time.h>

#define MAXCHAR 1000
#define MAXQURANAYAT 22
#define MAXBIBLEAYAT 13

char line[MAXCHAR]; //max number of lines of koran
char lineBible[MAXCHAR]; //max number of lines of bible
char theAyat[MAXCHAR];
char theAyatBible[MAXCHAR];
char theSurah[MAXCHAR];
char theSurahBible[MAXCHAR];
/*struct theverse {
	char *verse_number; //the key
	char *verse;
	UT_hash_handle hh; //makes this structure hashable
}; */

int lineNumber = 0;
int lineNumberBible = 0;
int score = 0; //score initialize to 0

void welcomeScreen();
string generateNameSurah();
string generateNameSurahBible();
void askUserBible();
void chooseAyatBible();
void updateScore();
void askUser();
void chooseAyatKoran();
int main(void)
{
	//struct theverse *my_ayat = NULL; //initialize to null

	int randomBible;
	int questionNumber = 0;

	
	for(;;)
	{
		//clear the screen
		system("clear");
		welcomeScreen();
		
		//number of question and current score
		printf("Number #%d\t\t\tScore: %d/%d\n", questionNumber + 1, score, questionNumber);
	//generate a random complete verse, either koran or bible from koran.txt or bible.txt
	
		srand(time(0));

	//random between koran or bible, with the probability 2 for koran and 1 for bible:
		randomBible = rand() % 3; //choose from 0 to 2

		//67% chance to generate koran verse
		if(randomBible == 0 || randomBible == 1)
		{	
			//choose koran verse
			
			//load koran.txt and take a verse, randomly:
			//printf("Koran is choosen");
			//loadKoran();
			chooseAyatKoran();
			generateNameSurah();
			askUser();
			//then check for answer
			//checkAnswer();
			//updateScore();

		}
		
		//33% chance to generate bible verse
		if(randomBible == 2)
		{
			
			//choose bible verse
			//printf("Bible is choosen");
			//loadBible();
			chooseAyatBible();
			generateNameSurahBible();
			askUserBible(line);
			//then check for answer
			//checkAnswer();
			//updateScore();

		}

	//do this until user hit 'q':
	/*printf("\n(q: quit/else: repeat): ");
	scanf(" %c",&keyPressed);
	if (keyPressed == 'q')
		return 0;*/

	questionNumber++;
	}

	//return 0;
}


void welcomeScreen()
{
	printf("GuessVerse ver 1.0\n");
	printf("------------------\n");
	printf("There will be a verse, selected ramdomly either Bible or Koran\n");
	printf("You have to choose what verse it is\n");
	printf("Just choose either 1 or 2. Type the other number will quit the game. If correct, you get score +1\n");
	printf("Good luck! Enjoy!\n\n\n");
	
}

//load koran to a table
//key: verse number
//value: the verse
int loadKoran()
{
	//load the koran
	FILE *fp;
	char str[MAXCHAR];
	char* filename = "koran.txt";

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("The koran file could not be opened\n");
		return 1;
	}

	while(fgets(str, MAXCHAR, fp) != NULL)
		printf("%s", str);
	fclose(fp);
	return 0;
}

//load bible to a table
//key: verse number
//value: the verse
int loadBible()
{
	//load the bible
	FILE *fp;
	char str[MAXCHAR];
	char* filename = "bible.txt";

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("The bible file could not be opened\n");
		return 1;
	}

	while(fgets(str, MAXCHAR, fp) != NULL)
		printf("%s", str);
	fclose(fp);
	return 0;
}

//choose ayat and display it to the screen
void chooseAyatKoran()
{
	const char s[2] = "_";
	char *token = NULL;
	
	int x = 0; // just initialize to 0
	x = rand() % MAXQURANAYAT; //between 0 to 2
	//printf("x = %d\n",x);
	//printf("chooseAyat() is processed\n");

	//choose ayat, randomly
	lineNumber = 0; //just initialize
	lineNumber = x;

	static const char filename[] = "koran.txt";
	FILE *file = fopen(filename, "r");
	int count = 0;
	if (file != NULL)
	{
		
		while (fgets(line, sizeof line, file) != NULL) // read a line
		{
			if (count == lineNumber)
			{
				
				//show the ayat
				//printf("%s",line);

				//input the ayat :
				for(int i = 0, n = strlen(line); i < n; i++)
				{
					theAyat[i] = line[i];
				}

				token = strtok(line, s);
				printf("The Verse:\n");
				printf("\n%s\n\n", line);
				//then go out
				break;
				
				//fclose(file);
				
				
			}
			else
			{
				count++;
			}
		}
		//fclose(file);
	}
	else
	{
		//file doesn't exist
	}
	//printf("End of chooseAyat()\n");
	fclose(file);
}

string generateNameSurah()
{
	const char s[2] = ")"; //the sign to check
	char *token = NULL;

	int x = 0;
	x = rand() % 144; //number of surah in koran

	int lineSurah = 0;
	lineSurah = x;

	static const char filename[] = "koran_nm.txt";
	FILE *file = fopen(filename, "r");
	int count = 0;
	if (file != NULL)
	{
		while(fgets(line, sizeof line, file) != NULL)
		{
			if (count == lineSurah)
			{
				for (int i = 0, n = strlen(line); i < n; i++)
				{
					theSurah[i] = line[i];
				}
				token = strtok(line, s);
				//printf("isi line surah:\n");
				//printf("\n%s\n", line);
				//then go out
				break;
			}
			else
			{
				count++;
			}
		}
	}
	else
	{
		//file doesnt exist
	}
	fclose(file);

	return theSurah;
}

void askUser()
{
	//ask user on the ayat
	//the key is the same linenumber
	int firstIndex = 0, secondIndex = 0;
	char strKoran[MAXCHAR];
	char answerKoran[MAXCHAR];
	
	//assigning the str:
	for(int i = 0, n = strlen(theAyat); i < n; i++)
	{
		strKoran[i] = theAyat[i];
		
	}

	//test str[i] value:
	//
	/*printf("Ini isi str[i]:\n");
	for(int i = 0, n = strlen(str); i < n; i++)
	{
		printf("%c",str[i]);
	}*/

	for(int i = 0, n = strlen(strKoran); i < n; i++)
	{
		if (strKoran[i] == '_')
		{
			//if found "_"
			firstIndex = i + 1;
			//printf("got the first index: %d\n", firstIndex);
			//printf("str[i] = %c\n",str[firstIndex]);
			break;
		}
	
	}

	//check second index for "_"
	for (int i = firstIndex, n = strlen(strKoran); i < n; i++)
	{
		if (strKoran[i] == '_')
		{
			//if found "_"
			secondIndex = i;
			//printf("got second index: %d\n", secondIndex);
			//printf("str[i] = %c\n",str[secondIndex]);
			break;
		}
	}

	//initialized answerKoran:
	//answerKoran = '\0';
	
	//print the str from index:
	for (int i = firstIndex; i < secondIndex; i++)
	{
		//take the strKoran
		//printf("%c",strKoran[i]);
		answerKoran[i] = strKoran[i];
		//printf("%c",answerKoran[i]);
	}

	//random choices of answers: (two choices)
	//generate random number 0 or 1:
	int choice = 0;
	choice = rand() % 2; //0 or 1
	
	//set the answer
	int setAnswer = 0;
	setAnswer = choice + 1; //to set to 1 or 2 index
	
	

	//display the choices:
	if (1 == setAnswer)
	{
		printf("1. ");
		
		//print the string:
		for(int i = firstIndex; i < secondIndex; i++) {
			printf("%c",answerKoran[i]);
		}

		printf("\n");
		//generate wrong choice:
		//surah:ayat format. Max surah = 144, max ayat = 286
		int surahChoice = 0;
		surahChoice = (int)((rand() % 144) + 1);
		int ayatChoice = 0;
		ayatChoice = (int)((rand() % 286) + 1);
		
		//printf("surahChoice : %d\n",surahChoice);
		//printf("ayatChoice : %d\n",ayatChoice);
		printf("2. %d:%d ", surahChoice, ayatChoice);
		//print theSurah:
		for(int i = 0, n = strlen(theSurah); i < n; i++)
		{
			printf("%c",theSurah[i]);
		}
		
		
	}
	else //setAnswer == 2
	{
		int surahChoice = 0;
		surahChoice = (rand() % 144) + 1;
		int ayatChoice = 0;
		ayatChoice = (rand() % 286) + 1;

		printf("1. %d:%d ", surahChoice, ayatChoice);
		//print theSurah:
		/*for(int i = 0, n = strlen(theSurah); i < n; i++)
		{
			printf("%c",theSurah[i]);
		}*/


		//print theSurah with pointer:
		char *ptrTheSurah = theSurah;
		while(*ptrTheSurah != '\n') {
			printf("%c", *ptrTheSurah);
			ptrTheSurah++;
		}
		printf("\n");

		//printf the answerKoran:
		printf("2. ");	
		for(int i = firstIndex; i < secondIndex; i++) {
			printf("%c",answerKoran[i]);
		}
		
		/*//print answerKoran with pointer
		char *ptrAnswerKoran = answerKoran;
		while(*ptrAnswerKoran != '\0') {
			printf("%c", *ptrAnswerKoran);
			ptrAnswerKoran++;
		}*/

		printf("\n");

	}


	//ask the user:
	int userChoice;
	printf("\nWhat verse is that (1/2) ?");
	scanf("%d",&userChoice);

	//if not 1 and 2 then quit:
	if(!(userChoice == 1 || userChoice == 2))
		exit(0);
	
	//check the userChoice
	if(userChoice == setAnswer)
	{
		score++;
		printf("Correct! Your score: %d\n",score);
		printf("Loading next verse");
		for (int i = 0; i < 4; i++) {
			printf(".");
			fflush(stdout);
			sleep(1);
		}
	} 
	else
	{
		printf("Sorry, the right answer is: %d\n", setAnswer);
		printf("Loading next verse");
		for (int i = 0; i < 4; i++) {
			printf(".");
			fflush(stdout);
			sleep(1);
		}
	}

	//return answerKoran;
	printf("\n");
/*

	const char s[2] = "_";
	char *token;

	 get the first token 
	token = strtok(str, s);

	 walk through other tokens 
	while(token != NULL)
	{
		
			printf(" %s\n", token);
			token = strtok(NULL, s);
		
	}

	return 0;

	*/
}

void chooseAyatBible()
{
	const char s[2] = "_";
	char *token = NULL;
	
	int x = 0; //just initialize to 0
	x = rand() % MAXBIBLEAYAT; //input the number of line in file: bible.txt --from 0 to MAXBIBLEAYAT-1 
	//printf("x = %d\n",x);
	//printf("chooseAyat() is processed\n");

	//choose ayat, randomly
	lineNumber = 0; //just initialize to 0
	lineNumber = x;

	static const char filename[] = "bible.txt";
	FILE *fileBible = fopen(filename, "r");
	int count = 0;
	if (fileBible != NULL)
	{
		
		while (fgets(lineBible, sizeof lineBible, fileBible) != NULL) // read a line
		{
			if (count == lineNumber)
			{
				
				//show the ayat
				//printf("%s",line);

				//input the ayat :
				for(int i = 0, n = strlen(lineBible); i < n; i++)
				{
					theAyatBible[i] = lineBible[i];
				}

				token = strtok(lineBible, s);
				printf("The Verse:\n");
				printf("\n%s\n\n", lineBible);
				//then go out:
				break;
				
				//fclose(fileBible);
				
				
			}
			else
			{
				count++;
			}
		}
		//fclose(fileBible);
	}
	else
	{
		//file doesn't exist
	}
	//printf("End of chooseAyat()\n");
	fclose(fileBible);

}


void askUserBible()
{
	//ask user on the ayat
	//the key is the same linenumber
	int firstIndex = 0, secondIndex = 0;
	char strBible[MAXCHAR];
	char answerBible[MAXCHAR];

	//assigning the str:
	for(int i = 0, n = strlen(theAyatBible); i < n; i++)
	{
		strBible[i] = theAyatBible[i];
		
	}

	//test str[i] value:
	//
	/*printf("Ini isi str[i]:\n");
	for(int i = 0, n = strlen(str); i < n; i++)
	{
		printf("%c",str[i]);
	}*/

	for(int i = 0, n = strlen(strBible); i < n; i++)
	{
		if (strBible[i] == '_')
		{
			//if found "_"
			firstIndex = i + 1;
			//printf("got the first index: %d\n", firstIndex);
			//printf("str[i] = %c\n",str[firstIndex]);
			break;
		}
	
	}

	//check second index for "_"
	for (int i = firstIndex, n = strlen(strBible); i < n; i++)
	{
		if (strBible[i] == '_')
		{
			//if found "_"
			secondIndex = i;
			//printf("got second index: %d\n", secondIndex);
			//printf("str[i] = %c\n",str[secondIndex]);
			break;
		}
	}

	//print the str from index:
	for (int i = firstIndex; i < secondIndex; i++)
	{
		//print the answer of ayat
		//printf("%c",strBible[i]);
		answerBible[i] = strBible[i];
	}

	int choice = 0;
	choice = rand() % 2;

	int setAnswer = 0;
	setAnswer = choice + 1;

	//display the choices:
	if (1 == setAnswer)
	{
		printf("1. ");
		
		//print the string:
		for(int i = firstIndex; i < secondIndex; i++) {
			printf("%c",answerBible[i]);
		}
		
		printf("\n");
		//generate wrong choice:
		//surah:ayat format. Max surah = 144, max ayat = 286
		int surahChoice = 0;
		surahChoice = (int)((rand() % 144) + 1);
		int ayatChoice = 0;
		ayatChoice = (int)((rand() % 286) + 1);
		
		//printf("surahChoice : %d\n",surahChoice);
		//printf("ayatChoice : %d\n",ayatChoice);
		printf("2. %d:%d ", surahChoice, ayatChoice);
	       	//print theSurah
		/*for(int i = 0, n = strlen(theSurahBible); i < n; i++)
		{
			printf("%c",theSurahBible[i]);
		}*/
		
		char *ptrSurahBible = theSurahBible;
		//print theSurahBible using pointer
		while(*ptrSurahBible != '\n') {
			printf("%c", *ptrSurahBible);

			//move pointer to the next location
			ptrSurahBible++;
		}
		printf("\n");
		
	}
	else //setAnswer == 2
	{
		int surahChoice = 0;
		surahChoice = (rand() % 144) + 1;
		int ayatChoice = 0;
		ayatChoice = (rand() % 286) + 1;

		printf("1. %d:%d ", surahChoice, ayatChoice);
		//print theSurah:
		/*for (int i = 0, n = strlen(theSurah); i < n; i++)
		{
			printf("%c",theSurahBible[i]);
		}*/

		//print theSurahBible using pointer:
		char *ptrTheSurahBible = theSurahBible;
		while(*ptrTheSurahBible != '\n') {
			printf("%c", *ptrTheSurahBible);
			ptrTheSurahBible++;
		}
		printf("\n");

		//printf the answerKoran:
		printf("2. ");	
		for(int i = firstIndex; i < secondIndex; i++) {
			printf("%c",answerBible[i]);
		}
		printf("\n");

	}


	//ask the user:
	int userChoice;
	printf("\nWhat verse is that (1/2) ?");
	scanf("%d",&userChoice);
	
	//if not 1 and 2 then quit:
	if(!(userChoice == 1 || userChoice == 2))
		exit(0);
	
	//check the userChoice
	if(userChoice == setAnswer)
	{
		score++;
		printf("Correct! Your score: %d\n",score);
		printf("Loading next verse");
		for (int i = 0; i < 4; i++) {
			printf(".");
			fflush(stdout);
			sleep(1);
		}
	} 
	else
	{
		printf("Sorry, the right answer is: %d\n", setAnswer);
		printf("Loading next verse");
		for (int i = 0; i < 4; i++) {
			printf(".");
			fflush(stdout);
			sleep(1);
		}
	}
	printf("\n");


	//return answerKoran;
	//printf("\n");



	//return firstIndex;

	//printf("\n");
	//printf("itulah ayat biblenya\n");

/*

	const char s[2] = "_";
	char *token;

	 get the first token 
	token = strtok(str, s);

	 walk through other tokens 
	while(token != NULL)
	{
		
			printf(" %s\n", token);
			token = strtok(NULL, s);
		
	}

	return 0;

*/

}

string generateNameSurahBible()
{
	const char s[2] = ")"; //the sign to check
	char *token = NULL;

	int x = 0;
	x = rand() % 3; //number of surah in bible

	int lineSurah = 0;
	lineSurah = x;

	static const char filename[] = "bible_nm.txt";
	FILE *file = fopen(filename, "r");
	int count = 0;
	if (file != NULL)
	{
		while(fgets(line, sizeof line, file) != NULL)
		{
			if (count == lineSurah)
			{
				for (int i = 0, n = strlen(line); i < n; i++)
				{
					theSurahBible[i] = line[i];
				}
				token = strtok(line, s);
				//printf("isi line surah:\n");
				//printf("\n%s\n", line);
				//then go out
				break;
			}
			else
			{
				count++;
			}
		}
	}
	else
	{
		//file doesnt exist
	}
	fclose(file);

	return theSurahBible;
}


//check the answer, correct or not
bool checkAnswer()
{
	//check the answer of the user
	


	return false;
}

//update score
void updateScore()
{
	//update the score.
	//If corrent, add +1, wrong 0:
	
}

/*
void add_ayat(string certain_verse_number, string the_verse)
{
	struct theverse *s;

	s = malloc(sizeof(struct theverse));
	s->verse_number = certain_verse_number;
	strcpy(s->verse, the_verse);
	HASH_ADD_STR(my_ayat, verse_number, s);
}*/

