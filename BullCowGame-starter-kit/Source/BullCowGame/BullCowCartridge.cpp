// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    InitGame(); //setup the game
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver) {
        ClearScreen();
        InitGame();
    }
    else {
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::InitGame() {
    hiddenWord = TEXT("boi"); //TEXT macro allows for the string literal is encoded properly for UE4
    lives = hiddenWord.Len();
    bGameOver = false;
    //Welcomes the player
    PrintLine(TEXT("Welcome to Bull Cows!!!"));
    PrintLine(TEXT("Guess the %i letter word!"), hiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), lives);
    PrintLine(TEXT("Press tab, type in your guess,\n and press enter."));


    //const TCHAR 
}

void UBullCowCartridge::EndGame() {
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again."));
}

void UBullCowCartridge::ProcessGuess(FString guess) {
    if (guess.Equals(hiddenWord)) {
        PrintLine(TEXT("ez dubs"));
        EndGame();
        return;
    }
    if (!IsIsogram(guess)) {
        PrintLine(TEXT("No repeating letters, guess again"));
        return;
    }
    if (guess.Len() != hiddenWord.Len()) {
        PrintLine(TEXT("The hidden word is %i letters long,\n try again! You have %i lives remaining."), hiddenWord.Len(), lives);
        return;
    }
    PrintLine(TEXT("Lost a life :("));
    --lives;
    if (lives <= 0) {
        ClearScreen();
        PrintLine(TEXT("You have no lives left!"));
        PrintLine(TEXT("The hidden word was: %s\n"), *hiddenWord);
        EndGame();
        return;
    }
}

bool UBullCowCartridge::IsIsogram(FString word) const{
    for (int32 i = 0; i < word.Len(); i++) {
        for (int32 j = i + 1; j < word.Len(); j++) {
            if (word[i] == word[j]) {
                return false;
            }
        }
    }
    return true;
}