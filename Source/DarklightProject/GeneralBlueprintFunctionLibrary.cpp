// Fill out your copyright notice in the Description page of Project Settings.

#include "DarklightProject.h"
#include "GeneralBlueprintFunctionLibrary.h"
#include<string>
FString UGeneralBlueprintFunctionLibrary::IntToASCII(int ASCIIChar)
{
	char rando = ASCIIChar;
	std::string AsciiString;
	AsciiString = rando;
	return FString(AsciiString.c_str());
}

int UGeneralBlueprintFunctionLibrary::WrapToRange(int Value, int Min, int Max)
{
	check(Min<Max);
	int RangeSize = Max - Min;
	if (Value < Min)
		return  Value+ RangeSize * ((Min - Value) / RangeSize + 1);
	return Min + (Value - Min) % RangeSize;
}
