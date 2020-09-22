// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

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

	// Your declarations go below!
	private:
		FString hiddenWord;
		int32 lives;
		bool bGameOver;
		bool isIsogram;
		TArray<FString> Isograms;
};
