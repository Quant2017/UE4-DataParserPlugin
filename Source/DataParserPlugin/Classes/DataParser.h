#pragma once

#include "Object.h"
#include "DataParser.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(DataParser, All, All)


UCLASS(Blueprintable)
class DATAPARSERPLUGIN_API UDataParser : public UObject
{
    GENERATED_BODY()
    
public:
    UDataParser();
    
    UFUNCTION(BlueprintImplementableEvent, Category = "DataParser")
    void OnStart();
    
    UFUNCTION(BlueprintCallable, Category = "DataParser")
    bool ParseFile(FString FileName);
    
    UFUNCTION(BlueprintCallable, Category = "DataParser")
    int32 GetArraysCount();
    
    UFUNCTION(BlueprintCallable, Category = "DataParser")
    TArray<float> & GetArray(int32 Index);
    
    
private:
    TArray<TArray<float>> m_matrix;
    
};
