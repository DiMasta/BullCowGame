#include "FBullCowGame.h"

#include <iostream>
#include <map>

FBullCowGame::FBullCowGame() {
	reset();
}

ResetStatus FBullCowGame::reset() {
	currentTry = 1;
	gameWon = false;

	const FString HIDDEN_WORD = "pla";
	hiddenWord = HIDDEN_WORD;

	return ResetStatus::OK;
}

int32 FBullCowGame::getCurrentTry() const {
	return currentTry;
}

size_t FBullCowGame::getHiddenWordLenght() const {
	return hiddenWord.length();
}

bool FBullCowGame::isGameWon() const {
	return gameWon;
}

int32 FBullCowGame::getMaxTries() const {
	TMap<int32, int32> wordLenghtToMaxTries {
		{3, 4},
		{4, 7},
		{5, 10},
		{6, 15},
		{7, 20}
	};

	return wordLenghtToMaxTries[hiddenWord.length()];
}

void FBullCowGame::printGameSummary() const {
	if (gameWon) {
		std::cout << "You won :)" << std::endl;
	}
	else {
		std::cout << "Bad luck, better next time." << std::endl;
	}
}

bool FBullCowGame::isIsogram(const FString& guess) const {
	bool res = true;
	TMap<char, bool> letterSeen;

	for (auto letter : guess) {
		letter = tolower(letter);
		bool& charUsed = letterSeen[letter];

		if (charUsed) {
			res = false;
			break;
		}
		else {
			charUsed = true;
		}
	}

	return res;
}

bool FBullCowGame::isLowercase(const FString& guess) const {
	bool res = true;

	for (auto letter : guess) {
		if (!islower(letter)) {
			res = false;
			break;
		}
	}

	return res;
}

GuessStatus FBullCowGame::checkGuessValidity(const FString& guess) const {
	if (!isIsogram(guess)) {
		return GuessStatus::NOT_ISOGRAM;
	}
	else if (!isLowercase(guess)) {
		return GuessStatus::NOT_LOWERCASE;
	}
	else if (guess.length() != hiddenWord.length()) {
		return GuessStatus::WRONG_LENGHT;
	}
	else {
		return GuessStatus::OK;
	}
}

FBullCowCount FBullCowGame::submitVaidGuess(const FString& guess) {
	++currentTry;

	FBullCowCount bullCowCount;
	const size_t hiddenWordLenght = hiddenWord.length();
	for (size_t hiddenWordCharIdx = 0; hiddenWordCharIdx < hiddenWord.length(); ++hiddenWordCharIdx) {
		for (size_t guessCharIdx = 0; guessCharIdx < hiddenWordLenght; ++guessCharIdx) {
			if (guess[hiddenWordCharIdx] == hiddenWord[guessCharIdx]) {
				if (hiddenWordCharIdx == guessCharIdx) {
					++bullCowCount.bulls;
				}
				else {
					++bullCowCount.cows;
				}
			}
		}
	}

	if (hiddenWordLenght == bullCowCount.bulls) {
		gameWon = true;
	}

	return bullCowCount;
}
