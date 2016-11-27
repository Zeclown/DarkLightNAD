// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "GeneralBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DARKLIGHTPROJECT_API UGeneralBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
		//Returns the ascii character associated with the int
		UFUNCTION(BlueprintCallable, Category = "General Function Library")
		static FString IntToASCII(int ASCIIChar);
		//Get the corresponding int value if it was in the specified range
		//I.E. Instead of clamping, it wraps around 
		UFUNCTION(BlueprintCallable, Category = "General Function Library")
		static int WrapToRange(int Value,int Min,int Max);
	
	
	
};
