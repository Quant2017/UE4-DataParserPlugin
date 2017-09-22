# UE4-DataParserPlugin
Simple plugin to provide data parsed from xlsx files.

API
bool ParseFile(FString FilePath) - parse file "FilePath" and return true if successful
int32 GetArraysCount() - return number of data arrays
TArray<float> & GetArray(int32 Index) - return requested array
