#pragma once
#include "string"
#include <map>
#include <ctime>
#define TMap std::map
using FString = std::string;
using int32 = int;
enum class EGuessStatus
{
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
	Invalid_Status
};
struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};
class FBullCowGame {
public:
	FBullCowGame();
	void Reset() ;
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	FBullCowCount SubmitValidGuess(FString);
	void SetWordLength(int32);
	void SetSecretWord();

	
private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	int32 MyWordLength;
	FString MyHiddenWord;
	bool bIsGameWon = false;
	bool IsLowerCase(FString) const;
	bool IsIsogram(FString) const;
	TMap<int32, FString> ThreeLetterWords{ {0, "ape"},{1,"bag"},{2,"cup"},{3,"dog"},{4,"ear"},{5,"fog"},{6,"gym"},{7,""},{8,"hut"},{9,"ice"} };
	TMap<int32, FString> FourLetterWords{ { 0, "item" },{ 1,"junk" },{ 2,"kart" },{ 3,"lust" },{ 4,"math" },{ 5,"nest" },{ 6,"opal" },{ 7,"page" },{ 8,"quiz" },{ 9,"race" } };
	TMap<int32, FString> FiveLetterWords{ { 0, "bacon" },{ 1,"death" },{ 2,"flame" },{ 3,"habit" },{ 4,"knife" },{ 5,"night" },{ 6,"paint" },{ 7,"realm" },{ 8,"table" },{ 9,"vodka" } };
	TMap<int32, FString> SixLetterWords{ { 0, "planet" },{ 1,"beauty" },{ 2,"walrus" },{ 3,"utopia" },{ 4,"sailer" },{ 5,"pistol" },{ 6,"orgasm" },{ 7,"orphan" },{ 8,"insect" },{ 9,"nectar" } };
	
};