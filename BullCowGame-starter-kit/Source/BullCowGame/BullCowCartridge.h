// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

//Struct later used to store the data for the bull and cow counts
struct FBullCowCount {
	int32 bulls = 0;
	int32 cows = 0;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& PlayerInput) override;
	void InitGame();
	void EndGame();
	void ProcessGuess(const FString& guess);
	bool IsIsogram(const FString& word) const;
	TArray<FString> GetValidWords(const TArray<FString>& WordList) const;
	//void GetBullCows(const FString& guess, int32& bullCount, int32& cowCount) const;//Out parameters are referenced but not const. bullCount and cowCount are examples of that
	FBullCowCount GetBullCows(const FString& guess) const;

	// Your declarations go below!
	private:
		FString hiddenWord;
		int32 lives;
		bool bGameOver;
		bool isIsogram;
		TArray<FString> Isograms;
};
