#pragma once
#include <string>

#define TMap std::map
using FString = std::string;
using int32 = int;

static const int32 MAX_TRIES = 8;

struct FBullCowCount {
	int32 bulls = 0;
	int32 cows = 0;
};

enum class GuessStatus {
	INVALID,
	OK,
	WRONG_LENGHT,
	NOT_ISOGRAM,
	NOT_LOWERCASE,
};

enum class ResetStatus {
	OK
};

class FBullCowGame {
public:
	FBullCowGame();

	int32 getMaxTries() const;
	int32 getCurrentTry() const;
	size_t getHiddenWordLenght() const;

	GuessStatus checkGuessValidity(const FString& guess) const;
	bool isGameWon() const;
	void printGameSummary() const;

	ResetStatus reset();
	FBullCowCount submitVaidGuess(const FString& guess);

private:
	int32 currentTry = 1;
	FString hiddenWord;
	bool gameWon;

	bool isIsogram(const FString& guess) const;
	bool isLowercase(const FString& guess) const;
};
