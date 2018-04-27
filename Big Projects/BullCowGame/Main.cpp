

#include "string"
#include "iostream"
#include "FBullCowGame.h"
#pragma once
using int32 = int;
using FText = std::string;
void PrintIntro();
void PlayGame();
void PrintGameSummary();
bool AskToPlayAgain();
void AskNumberOfLetters();
FText GetValidGuess();
void TypeBackBullsAndCows(FBullCowCount FBullCowCount);

FBullCowGame BCGame;
int main()
{
	
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
		
	} while (bPlayAgain);

    return 0;
}

void PlayGame()
{
	AskNumberOfLetters();
	BCGame.Reset();
	int32 HiddenWordLength = BCGame.GetHiddenWordLength();
	int32 MaxTries = BCGame.GetMaxTries();
	FText Guess = "";
	std::cout << "You have " << MaxTries << " tries.\n";
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		Guess = GetValidGuess();
		FBullCowCount FBullCowCount = BCGame.SubmitValidGuess(Guess);
		TypeBackBullsAndCows(FBullCowCount);
	}
	PrintGameSummary();
	return;
}

void PrintIntro() {
	std::cout << "\n\nWeclome to Bulls and Cows\n";
	
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the isogram I'm thinking of?\nBull means that you got a letter in the right spot! \nCow means that you got the letter right, but it is in the wrong place!\nGood Luck!\n\n";
	
	return;
}
FText GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "\nTry " << CurrentTry << ". ";
		std::cout << "Make a guess:";
		getline(std::cin, Guess);

	 Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter a word using only lower case.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram(Letters can't be repeated)\n";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;
}
void TypeBackBullsAndCows(FBullCowCount FBullCowCount) 
{
	std::cout << "Bulls = " << FBullCowCount.Bulls << std::endl;
	std::cout << "Cows = " << FBullCowCount.Cows<< std::endl;
	return;
}
bool AskToPlayAgain() 
{
	FText Response = "";
	std::cout << "\nDo you want to play again with another word?(y/n):";
	getline(std::cin, Response);
	system("cls");
	if(Response[0] == 'y' || Response[0] == 'Y')
	return true;
	if (Response[0] == 'n' || Response[0] == 'N')
	return false;
	return false;
}
void AskNumberOfLetters()
{
	FString NumberOfLettersString = "";
	int32 NumberOfLetters = 0;
	std::cout << "How many letters would you like to have in the word?";
	while (NumberOfLetters > 6 || NumberOfLetters < 3 || NumberOfLetters == NULL)
	{
		std::cout << "Please enter a number from 3 to 6:";
		getline(std::cin, NumberOfLettersString);
		NumberOfLetters = atoi(NumberOfLettersString.c_str());
	}
	BCGame.SetWordLength(NumberOfLetters);
}
void PrintGameSummary()
{
	if (BCGame.IsGameWon()) std::cout << "\nGood Job! You won!\n";
	else std::cout << "\nBetter Luck next time.\n";
	return;
}
