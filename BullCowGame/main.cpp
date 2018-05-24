#include <iostream>
#include <string>

#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void printIntro();
void playGame();
FText getValidGuess();
void printGuess(const FText& guess);
bool askToPlayAgain();

FBullCowGame bcGame;

int main() {
	do {
		printIntro();
		playGame();
	}
	while (askToPlayAgain());

	return 0;
}

// introduce the game
void printIntro() {
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << bcGame.getHiddenWordLenght();
	std::cout << " letter isogram I'm thinking of?" << std::endl;
	std::cout << std::endl;
}

// loop for the number of turns asking for guesses
void playGame() {
	bcGame.reset();
	const int32 maxTries = bcGame.getMaxTries();

	while (!bcGame.isGameWon() && bcGame.getCurrentTry() <= maxTries) {
		FText guess = getValidGuess();

		FBullCowCount bullCowCount = bcGame.submitVaidGuess(guess);
		std::cout << "Bulls = " << bullCowCount.bulls;
		std::cout << ". Cows = " << bullCowCount.cows << '.';
		std::cout << std::endl;
		std::cout << std::endl;
	}

	bcGame.printGameSummary();
}
// get a guess from the player
FText getValidGuess() {
	GuessStatus status = GuessStatus::INVALID;
	FText guess = "";

	do {
		std::cout << "Try " << bcGame.getCurrentTry();
		std::cout << " of " << bcGame.getMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, guess);

		status = bcGame.checkGuessValidity(guess);
		switch (status) {
			case (GuessStatus::WRONG_LENGHT): {
				std::cout << "Please, enter a " << bcGame.getHiddenWordLenght() << " letter word." << std::endl << std::endl;
				break;
			}
			case (GuessStatus::NOT_ISOGRAM): {
				std::cout << "Please, enter an isogram." << std::endl << std::endl;
				break;
			}
			case (GuessStatus::NOT_LOWERCASE): {
				std::cout << "Please, use only lowercase letters." << std::endl << std::endl;
				break;
			}
			default: {
			}
		}
	} while (GuessStatus::OK != status);

	return guess;
}

// print the guess back to them
void printGuess(const FText& guess) {
	std::cout << "Your guess was: " << guess << std::endl;
	std::cout << std::endl;
}

bool askToPlayAgain() {
	std::cout << "Do you want to play again? (y/n)";
	FText response = "";
	std::getline(std::cin, response);
	char firstChar = response[0];
	
	return (firstChar == 'y' || firstChar == 'Y');
}
