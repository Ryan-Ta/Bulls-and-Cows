// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    Isograms = GetValidWords(Words);
    InitGame(); //setup the game

    //PrintLine(TEXT("%i"), FMath::RandRange(0, 10));
    //PrintLine(TEXT("The number of possible words is %i."), Words.Num()); //Returns the number of words in the array
    //PrintLine(TEXT("The number of valid words is %i."), GetValidWords(Words).Num()); //Returns the number of valid words in the array
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    //Clears the screen on gameover and inits a new game
    if (bGameOver) {
        ClearScreen();
        InitGame();
    }       
    else {  
        ProcessGuess(PlayerInput);
    }
}

//Inits the game
void UBullCowCartridge::InitGame() {
    hiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)]; //TEXT macro allows for the string literal is encoded properly for UE4
    lives = hiddenWord.Len(); //Number of lives is equal to the number of letters in the hidden word
    bGameOver = false;
    //Welcomes the player
    PrintLine(TEXT("Welcome to Bull Cows!!!"));
    PrintLine(TEXT("Guess the %i letter word!"), hiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), lives);
    PrintLine(TEXT("Press tab, type in your guess,\n and press enter."));
    PrintLine(TEXT("The hidden word is: %s"), *hiddenWord);

}

//End game condition
//Sets the bGameOver bool to true and prompts them to press enter to play again
void UBullCowCartridge::EndGame() {
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again."));
}

//Checks the players guess
void UBullCowCartridge::ProcessGuess(const FString& guess) {
    //Win Condition
    if (guess.Equals(hiddenWord)) {
        PrintLine(TEXT("ez dubs\n"));
        EndGame();
        return;
    }
    //Not an isogram check
    if (!IsIsogram(guess)) {
        PrintLine(TEXT("No repeating letters, guess again"));
        return;
    }
    //Word is longer than the hidden words length
    if (guess.Len() != hiddenWord.Len()) {
        PrintLine(TEXT("The hidden word is %i letters long,\n try again! You have %i lives remaining."), hiddenWord.Len(), lives);
        return;
    }
    //Decrementing a life
    PrintLine(TEXT("Lost a life :("));
    --lives;
    PrintLine(TEXT("You have %i lives."), lives);
    //Lose condition
    if (lives <= 0) {
        ClearScreen();
        PrintLine(TEXT("You have no lives left!"));
        PrintLine(TEXT("The hidden word was: %s\n"), *hiddenWord);
        EndGame();
        return;
    }
    //Show the player Bulls and Cows
    int32 bulls, cows;
    GetBullCows(guess, bulls, cows);
    PrintLine(TEXT("You have %i Bulls and %i Cows\n"), bulls, cows);

}

//Checks whether or not the word guessed is an isogram
bool UBullCowCartridge::IsIsogram(const FString& word) const{
    for (int32 i = 0; i < word.Len(); i++) {
        for (int32 j = i + 1; j < word.Len(); j++) {
            if (word[i] == word[j]) {
                return false;
            }
        }
    }
    return true;
}

//Checks to see if a word is valid from the words list and puts it into the ValidWords array
TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const{
    TArray<FString> ValidWords;
    /*for (int32 i = 0; i < WordList.Num(); i++) {
        if (Words[i].Len() >= 4 && WordList[i].Len() <= 8 && IsIsogram(WordList[i])) {
            ValidWords.Emplace(WordList[i]); //Emplace used for FStrings to add to another array
        }
    }*/
    //For Each Loop version (Range based for loop). Used for iterating through a collection of something
    //Equivalent to the for loop above
    //Word is just the variable name. Checks each element in WordList and assigns it to Word to be checked
    for (FString Word : WordList) {
        if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word)) {
            ValidWords.Emplace(Word); //Emplace used for FStrings to add to another array
        }
    }
    return ValidWords;
}

//Letter in a guess and right place is a Bull
//Letter in a guess but wrong place is a Cow
void UBullCowCartridge::GetBullCows(const FString& guess,int32& bullCount,int32& cowCount)const{
    bullCount = 0;
    cowCount = 0;

    for (int32 i = 0; i < guess.Len(); i++) {
        if (guess[i] == hiddenWord[i]) {
            bullCount++;
            continue; //tells the outer for loop to increment and go on to the next iteration
        }

        for (int32 j = 0; j < hiddenWord.Len(); j++) {
            if (guess[i] == hiddenWord[j]) {
                cowCount++;
                break;
            }
        }
    }
}