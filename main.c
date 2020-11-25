/* This program is a game to guess a verse, either quran or bible.
 * There will be a randomly generated complete verse in the screen.
 * In the bottom of it, there will be two choices, just click the one that's right.
 * If right, the score is count +1, if false, nothing will count.
 * The program will quit if the user press 'q'
 *  then, the program displays the score and wrong answered question
 * 
 * Project title : GuessVerse
 * Name : Agung Sudrajat Supriatna
 * Year : 2020
 * City : Bandung
 * Country: Indonesia
 *
 */

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <unistd.h>
#include "uthash.h" //header file for hash table in C
#include "raylib.h"
#include <time.h>

#define MAXCHAR 1000
#define MAXQURANAYAT 22
#define MAXBIBLEAYAT 13
#define NUM_FRAMES 3

char line[MAXCHAR]; //max number of lines of koran
char lineBible[MAXCHAR]; //max number of lines of bible
char theAyat[MAXCHAR];
char theAyatBible[MAXCHAR];
char theSurah[MAXCHAR];
char theSurahBible[MAXCHAR];
char test[MAXCHAR];
char testBible[MAXCHAR];
/*struct theverse {
	char *verse_number; //the key
	char *verse;
	UT_hash_handle hh; //makes this structure hashable
}; */

int lineNumber = 0;
int lineNumberBible = 0;
int score = 0; //score initialize to 0
int userChoice;

int buttonChoice();
string cutTheVerseKoran();
string cutTheVerseBible();
void welcomeScreen();
string generateNameSurah();
string generateNameSurahBible();
string askUserBible();
void chooseAyatBible();
void updateScore();
string askUser();
void chooseAyatKoran();
int main(void)
{
	//struct theverse *my_ayat = NULL; //initialize to null

	int randomBible;
	int questionNumber = 0;
	

	
	//initialization
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "GuessVerse ver1.0 by Agung Sudrajat Supriatna");

	const char message[128] = "This is a guess verse game.\nYou have to guess the verse provided here. Once\ncorrect, you get +1 of score. Good luck! Enjoy!";

	int framesCounter = 0;

	SetTargetFPS(60);

	//main game
	while (!WindowShouldClose()) //if ESC then close
	{
		//update
		if (IsKeyDown(KEY_SPACE)) framesCounter += 8;
		else framesCounter++;

		if (IsKeyPressed(KEY_ENTER)) {
			framesCounter += 6;
			goto LOOP;
		}
		//draw
		BeginDrawing();
			ClearBackground(RAYWHITE);
			
			//draw the score:
			//string skor = (string)score;
			//DrawText(skor, 140,95,20,MAROON);

			DrawText(TextSubtext(message, 0, framesCounter/6), 150, 100, 20, MAROON);

			DrawText("PRESS [ENTER] TO BEGIN!", 240, 260, 20, LIGHTGRAY);
			DrawText("PRESS [SPACE] TO SPEED UP!", 239, 300, 20, LIGHTGRAY);
			DrawText("PRESS [ESC] TO QUIT!", 238, 340, 20, LIGHTGRAY);

			
		EndDrawing();

	}


	
	LOOP:
	for(;;)
	{

		

		//clear the screen
		//system("clear");
		ClearBackground(RAYWHITE);

		welcomeScreen();
		
		//number of question and current score
		printf("Number #%d\t\t\tScore: %d/%d\n", questionNumber + 1, score, questionNumber);
		
		//generate a random complete verse, either koran or bible from koran.txt or bible.txt
		
		//i think it is needed:
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

			/*char *test = malloc(strlen(line) + 1);
			if(test != NULL)
			{
				return 1;
			}*/
			
			int framesCounter = 0;
			SetTargetFPS(60);

			while(framesCounter/6 != strlen(line)) {
			//for the effect of animation
			framesCounter++;
			
				if(IsKeyPressed(KEY_SPACE)) {
					userChoice = 1;
				}

				if(IsKeyPressed(KEY_ENTER)) {
					userChoice = 2;
				}
			

			//draw
			BeginDrawing();
			  ClearBackground(RAYWHITE);
			  
			  //draw the score:
			  //DrawText((string)score,50,50,20,MAROON);
			  
			  //draw the score:
			  DrawText(TextFormat("Score: %i/%i", score, questionNumber), 30, 10, 20, SKYBLUE); 
			  
			  //processing the line to cut sentence if too long: (insert newline)
			  cutTheVerseKoran();

			  DrawText(TextSubtext(test, 0, framesCounter/3), 150, 40, 20, MAROON);

			  //draw the options:
			  DrawText("1. ",202,260,20,MAROON);
			  DrawText("2. ",201,300,20,MAROON);
				

			  DrawText("PRESS [space] TO CHOOSE 1!", 240, 340, 20, LIGHTGRAY);
			  DrawText("PRESS [ENTER] TO CHOOSE 2!", 239, 380, 20, LIGHTGRAY);
			  DrawText("PRESS [3] TO QUIT!", 238, 420, 20, LIGHTGRAY);
			  
			  
			  EndDrawing();
		
			}
			
			

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
			
			/*char *testBible = malloc(strlen(lineBible) + 1);
			if(testBible != NULL)
			{
				return 1;
			}*/
			
			int framesCounter = 0;
			SetTargetFPS(60);
			int lengthLineBible = strlen(lineBible);
			while(framesCounter/6 != lengthLineBible) {
			//for the effect of animation
			framesCounter++;
			//draw
			BeginDrawing();
			  ClearBackground(RAYWHITE);
			  //draw the score:
			  //DrawText((string)score, 50,50,20,MAROON);
			  
			  //draw the score:
			  DrawText(TextFormat("Score: %i/%i", score, questionNumber), 30, 10, 20, SKYBLUE); 
			  
			  cutTheVerseBible();
			  DrawText(TextSubtext(testBible, 0, framesCounter/3), 150, 40, 20, MAROON);

			  //draw the options:
			  DrawText("1. ",202,260,20,MAROON);
			  DrawText("2. ",201,300,20,MAROON);

			  DrawText("PRESS [space] TO CHOOSE 1!", 240, 340, 20, LIGHTGRAY);
			  DrawText("PRESS [ENTER] TO CHOOSE 2!", 239, 380, 20, LIGHTGRAY);
			  DrawText("PRESS [3] TO QUIT!", 238, 420, 20, LIGHTGRAY);
			EndDrawing();
			
			}
			generateNameSurahBible();
			//draw
			askUserBible();
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

	//deinitialization
	CloseWindow();

	return 0;
	//return 0;
}


//button sprite
int buttonChoice()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    //InitWindow(screenWidth, screenHeight, "raylib [textures] example - sprite button");

    InitAudioDevice();      // Initialize audio device

    Sound fxButton = LoadSound("buttonfx.wav");   // Load button sound
    Texture2D button = LoadTexture("button.png"); // Load button texture

    // Define frame rectangle for drawing
    int frameHeight = button.height/NUM_FRAMES;
    Rectangle sourceRec = { 0, 0, button.width, frameHeight };

    // Define button bounds on screen
    Rectangle btnBounds = { screenWidth/2 - button.width/2, screenHeight/2 - button.height/NUM_FRAMES/2, button.width, frameHeight };

    int btnState = 0;               // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
    bool btnAction = false;         // Button action should be activated

    Vector2 mousePoint = { 0.0f, 0.0f };

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        mousePoint = GetMousePosition();
        btnAction = false;

        // Check button state
        if (CheckCollisionPointRec(mousePoint, btnBounds))
        {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) btnState = 2;
            else btnState = 1;

            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) btnAction = true;
        }
        else btnState = 0;

        if (btnAction)
        {
            PlaySound(fxButton);

            // TODO: Any desired action
        }

        // Calculate button frame rectangle to draw depending on button state
        sourceRec.y = btnState*frameHeight;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTextureRec(button, sourceRec, (Vector2){ btnBounds.x, btnBounds.y }, WHITE); // Draw button frame

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(button);  // Unload button texture
    UnloadSound(fxButton);  // Unload sound

    CloseAudioDevice();     // Close audio device

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
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

string cutTheVerseKoran()
{
	
	//fill test with line:
	for(int i = 0, n = strlen(line); i < n; i++) {
		test[i] = line[i];		
	}

	//printf("panjangnya : %d", strlen(test));

	int checkProgress = 0;
	int step_awal = 50;
	int step_akhir = 0;
	int lengthString = strlen(line);
	//lakukan sampai checkProgress
	while(checkProgress < lengthString)
	{
		//utk step 50 pertama:
		for(int i = step_awal; i > step_akhir; i--) {
			//check adanya spasi, angka menurun:
			if(test[i] == ' ') {
				test[i] = '\n';
				break; //end the loop
			}
		}
		//step diubah ke +50, msng2
		step_awal += 50;
		step_akhir += 50;
		checkProgress += 50;
	}

	//print the test:
	//
	/*for(int i = 0, n = strlen(test); i < n; i++)
	{
		printf("%c", test[i]);
	}*/
	return test;
}

string cutTheVerseBible()
{

	//fill test with line:
	for(int i = 0, n = strlen(lineBible); i < n; i++) {
		testBible[i] = lineBible[i];		
	}

	//printf("panjangnya : %d", strlen(testBible));

	int checkProgress = 0;
	int step_awal = 50;
	int step_akhir = 0;
	int lengthString = strlen(lineBible);
	//lakukan sampai checkProgress
	while(checkProgress < lengthString)
	{
		//utk step 50 pertama:
		for(int i = step_awal; i > step_akhir; i--) {
			//check adanya spasi, angka menurun:
			if(testBible[i] == ' ') {
				testBible[i] = '\n';
				break; //end the loop
			}
		}
		//step diubah ke +50, msng2
		step_awal += 50;
		step_akhir += 50;
		checkProgress += 50;
	}

	//print the test:
	//
	/*for(int i = 0, n = strlen(test); i < n; i++)
	{
		printf("%c", test[i]);
	}*/
	//free(testBible);
	return testBible;
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
	int framesCounter = 0;
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

				DrawText(TextSubtext(line, 0, framesCounter/10), 210, 160, 20, MAROON);
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

string askUser()
{
	//ask the user:
	int userChoice;
	
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
		//string for answerKoran:
		char answerKoranString[1000];

		printf("1. ");
		//print the string:
		for(int i = firstIndex; i < secondIndex; i++) {
			printf("%c",answerKoran[i]);
			answerKoranString[i] = answerKoran[i];
		}

		char *answerKoranPtr = &answerKoranString[firstIndex];
		answerKoranString[secondIndex] = '\0';
		
		
			//update:
			if(IsKeyDown(KEY_SPACE)) {
				userChoice = 1;			
			} else if(IsKeyDown(KEY_ENTER)) {
				userChoice = 2;
			} else {
				//CloseWindow();
			}
		
			//draw choice:
			BeginDrawing();
		  	//for(int i = firstIndex; i < secondIndex; i++) {
		    		DrawText(TextFormat("    %s",answerKoranPtr),202,260,20,MAROON);
		    	//DrawText(" ",242,260,20,MAROON);
		  	//}
		  	//DrawText("2. ",243,300,20,MAROON);
			EndDrawing();

		


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
		
		//to hold the string
		char theSurahString[1000];

		//print theSurah:
		for(int i = 0, n = strlen(theSurah); i < n; i++)
		{
			printf("%c",theSurah[i]);
			theSurahString[i] = theSurah[i];
		}
		
		//to hold the string:
		char *theSurahPtr = NULL;
		theSurahPtr = theSurahString;
		theSurahString[strlen(theSurah)] = '\0';

		
			//update:
			if(IsKeyDown(KEY_SPACE)) {
				userChoice = 1;			
			} else if(IsKeyDown(KEY_ENTER)) {
				userChoice = 2;
			} else {
				//CloseWindow();
			}
			
			//draw choices:
			BeginDrawing();
			
			DrawText(TextFormat("    %d:%d ", surahChoice, ayatChoice), 201, 300, 20, MAROON);
			//name of surah:
			//for(int i = 0, n = strlen(theSurah); i < n; i++)
			//{
				DrawText(TextFormat("              %s", theSurahPtr), 201, 300, 20, MAROON);
		    	//	DrawText(" ",241,300,20,MAROON);
			//}

			EndDrawing();		

		
		//listen to keypressed:
		//if(IsKeyDown(KEY_SPACE)) score += 1;
		//else score = score;


		//return the value:
		//return theSurah;
		
		
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
		
		//string surahChoiceStr = (char)surahChoice;
		//string ayatChoiceStr = (char)ayatChoice;
		
		//draw the options:
		//DrawText("1. ",242,260,20,MAROON);
		//DrawText("2. ",241,300,20,MAROON);
		//draw choices:
		//printf("%d:%d ",surahChoice, ayatChoice);

		//to hold the string:
		//
		char theSurahString[1000];
		//print theSurah with pointer:
		char *ptrTheSurah = NULL;
		ptrTheSurah = theSurah;

		for(int i = 0, n = strlen(theSurah); i < n; i++) {
			while(*ptrTheSurah != '\n') {
				printf("%c", *ptrTheSurah);
				//theSurahString[i] = theSurah[i];
				ptrTheSurah++;
			}
		}
		printf("\n");
		
		//point to the first index of theSurah:
		ptrTheSurah = theSurah;
		//adding null in the end
		theSurah[strlen(theSurah)] = '\0';
		
		
			//update:
			if(IsKeyDown(KEY_SPACE)) {
				userChoice = 1;			
			} else if(IsKeyDown(KEY_ENTER)) {
				userChoice = 2;
			} else {
				//CloseWindow();
			}
			//draw choices (ngarang):
			BeginDrawing();
			
				DrawText(TextFormat("    %d:%d ", surahChoice, ayatChoice), 202, 260, 20, MAROON);
			//name of surah:
			//while(*ptrTheSurah != '\n')
			//{
				DrawText(TextFormat("             %s", ptrTheSurah), 202, 260, 20, MAROON);
		    	//	DrawText(" ",242,260,20,MAROON);
			//	ptrTheSurah++;
			//}

			EndDrawing();		
		
		
		
		char answerKoranString[1000];
		//printf the answerKoran:
		printf("2. ");
		for(int i = firstIndex; i < secondIndex; i++) {
			printf("%c",answerKoran[i]);
			answerKoranString[i] = answerKoran[i];
		}
		
		/*//print answerKoran with pointer
		char *ptrAnswerKoran = answerKoran;
		while(*ptrAnswerKoran != '\0') {
			printf("%c", *ptrAnswerKoran);
			ptrAnswerKoran++;
		}*/

		//draw choice:
		char space[2] = " ";
			char *answerKoranPtr = NULL;
		answerKoranPtr = &answerKoran[firstIndex];
		answerKoran[secondIndex] = '\0';
		
		
			//update:
			if(IsKeyDown(KEY_SPACE)) {
				userChoice = 1;			
			} else if(IsKeyDown(KEY_ENTER)) {
				userChoice = 2;
			} else {
				//CloseWindow();
			}
			BeginDrawing();
		    
			//for(int i = firstIndex; i < secondIndex; i++) {
				DrawText(TextFormat("    %s",answerKoranPtr),201,300,20,MAROON);
		    
		    	//DrawText(TextFormat("%c",space),241,300,20,MAROON);
		  	//DrawText("2. ",243,300,20,MAROON);
			//}
			EndDrawing();
		

		printf("\n");

		//listen to keypressed:
		//if (IsKeyDown(KEY_SPACE)) score += 1;
		//else score = score;

		//if (IsKeyDown(KEY_ENTER)) score += 0;


	}


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
		/*printf("Loading next verse");
		for (int i = 0; i < 4; i++) {
			printf(".");
			fflush(stdout);
			sleep(1);
		}*/
	} 
	else
	{
		printf("Sorry, the right answer is: %d\n", setAnswer);
		printf("Loading next verse");
		/*for (int i = 0; i < 4; i++) {
			printf(".");
			fflush(stdout);
			sleep(1);
		}*/
	}

	//listen the answers:
	/*if(IsKeyDown(KEY_SPACE) && setAnswer == 1) {
		score += 1;
		//update user choice:
		userChoice = 1;
	} else if(IsKeyDown(KEY_ENTER) && setAnswer == 2) {
		score += 1;
		userChoice = 2;
	} else {
		WindowShouldClose();
	}*/


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

void displayString(char str[])
{
	puts(str);
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


string askUserBible()
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
		char answerBibleString[1000];

		//print the string:
		for(int i = firstIndex; i < secondIndex; i++) {
			printf("%c",answerBible[i]);
			answerBibleString[i] = answerBible[i];
		}
		
		char *answerBiblePtr = &answerBible[firstIndex];
		answerBible[secondIndex] = '\0';

		//draw choice:
		BeginDrawing();
			DrawText(TextFormat("    %s",answerBiblePtr),242,260,20,MAROON);
		EndDrawing();

		/*//print string using pointer
		
		char *ptrAnswerBible = NULL;
		ptrAnswerBible = answerBible;
		while(*ptrAnswerBible != '\0') {
			for(int i = 0, n = strlen(answerBible); i < n; i++) {
				printf("%c", *ptrAnswerBible);
				ptrAnswerBible++;
				answerBibleString[i] = answerBible[i];
			}
		
		}
		
		//pointer to answerBibleString:
		char *ptrAnswerBibleString = NULL;
		ptrAnswerBibleString = answerBibleString;
		//adding null to answerBibleString to end:
		answerBibleString[strlen(answerBible)] = '\0';

		
		//draw choice:
		BeginDrawing();
		  //while(*ptrAnswerBible != '\0') {
		    DrawText(TextFormat("    %s", ptrAnswerBibleString), 201,260,20,MAROON);
		  //  DrawText(" ",242,260,20,MAROON);
		  //  ptrAnswerBible++;
		//}
		EndDrawing();
		*/

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
		char theSurahString[1000];
		char *ptrTheSurahBible = NULL;
		ptrTheSurahBible = theSurahBible;

		//print theSurahBible using pointer
		for(int i = 0, n = strlen(theSurahBible); i < n; i++) {
			while(*ptrTheSurahBible != '\n') {
			 	printf("%c", *ptrTheSurahBible);

				//move pointer to the next location
				ptrTheSurahBible++;
				//theSurahBibleString[i] = theSurahBible[i];
			}
		}
		printf("\n");
		
		//point to first index again
		ptrTheSurahBible = &theSurahBible[0];
		theSurahBible[strlen(theSurahBible)] = '\0';

		//draw choice:
		BeginDrawing();
		  //it is working:
		  DrawText(TextFormat("    %d:%d ", surahChoice, ayatChoice),201,300,20,MAROON);
		  //while(*ptrSurahBible != '\n') {
		  	DrawText(TextFormat("             %s", ptrTheSurahBible),201,300,20,MAROON);
		    	//DrawText(" ",241,300,20,MAROON);
			//ptrSurahBible++;
		  //}
		  //DrawText(theSurah,243,300,20,MAROON);
		EndDrawing();
		
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
		char theSurahString[1000];
		char *ptrTheSurahBible = theSurahBible;

		for(int i = 0, n = strlen(theSurahBible); i < n; i++) {
			while(*ptrTheSurahBible != '\n') {
				printf("%c", *ptrTheSurahBible);
				ptrTheSurahBible++;
				//theSurahBibleString[i] = theSurahBible[i];
			}
		}	
		printf("\n");
		
		//point to:
		ptrTheSurahBible = &theSurahBible[0];
		theSurahBible[strlen(theSurahBible)] = '\0';
		//draw choice:
		BeginDrawing();
		  
		  //it is working:
		  DrawText(TextFormat("    %d:%d ", surahChoice, ayatChoice),202,260,20,MAROON);
		  //while(*ptrTheSurahBible != '\n') {
		  	DrawText(TextFormat("             %s", ptrTheSurahBible),202,260,20,MAROON);
		    	//DrawText(" ",242,260,20,MAROON);
			//ptrTheSurahBible++;
		  //}
		  //DrawText(theSurah,243,300,20,MAROON);
		EndDrawing();

		//printf the answerKoran:
		char answerBibleString[1000];
		printf("2. ");	
		for(int i = firstIndex; i < secondIndex; i++) {
			printf("%c",answerBible[i]);
			answerBibleString[i] = answerBible[i];
			//return answerBibleString;
		}
		printf("\n");

		char *answerBibleStringPtr = &answerBible[firstIndex];
		answerBible[secondIndex] = '\0';

		//draw choice:
		BeginDrawing();
		  //for(int i = firstIndex; i < secondIndex; i++) {
		    DrawText(TextFormat("    %s",answerBibleStringPtr), 201,300,20,MAROON);
		    //DrawText(" ",241,300,20,MAROON);
		  //}
		EndDrawing();

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
		/*for (int i = 0; i < 4; i++) {
			printf(".");
			fflush(stdout);
			sleep(1);
		}*/
	} 
	else
	{
		printf("Sorry, the right answer is: %d\n", setAnswer);
		printf("Loading next verse");
		/*for (int i = 0; i < 4; i++) {
			printf(".");
			fflush(stdout);
			sleep(1);
		}*/
	}
	printf("\n");


	//listen the answers:
	if(IsKeyDown(KEY_SPACE) && setAnswer == 1) {
		score += 1;
		//update user choice:
		userChoice = 1;
	} else if(IsKeyDown(KEY_ENTER) && setAnswer == 2) {
		score += 1;
		userChoice = 2;
	} else {	
		WindowShouldClose();
	}	

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

