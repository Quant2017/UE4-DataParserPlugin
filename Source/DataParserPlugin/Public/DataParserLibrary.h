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
	GENERATED_UCLASS_BODY()
	
    
public:
    UFUNCTION(BlueprintCallable, Category = "DataParser")
    static bool ParseFile(FString FileName);

    UFUNCTION(BlueprintCallable, Category = "DataParser")
    static int32 GetArraysCount();

    UFUNCTION(BlueprintCallable, Category = "DataParser")
    static TArray<float> & GetArray(int32 Index);


private:
    static TArray<TArray<float>> m_matrix;
};
