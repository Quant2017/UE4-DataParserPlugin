// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataParserLibrary.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(DataParserLibrary, Display, All)


/**
 * 
 */
UCLASS()
class DATAPARSERPLUGIN_API UDataParserLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
    
public:
    UFUNCTION(BlueprintCallable, Category = "DataParserLibrary")
    bool ParseFile(FString FileName);

    UFUNCTION(BlueprintCallable, Category = "DataParserLibrary")
    int32 GetArraysCount();

    UFUNCTION(BlueprintCallable, Category = "DataParserLibrary")
    TArray<float> & GetArray(int32 Index);


private:
    TArray<TArray<float>> m_matrix;
};
