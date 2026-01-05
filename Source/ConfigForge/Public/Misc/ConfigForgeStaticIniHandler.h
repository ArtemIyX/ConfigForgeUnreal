// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "Misc/ConfigCacheIni.h"

/**
 * @deprecated Use FConfigForgeIniFile
 * @see FConfigForgeIniFile
 */
class CONFIGFORGE_API FConfigForgeStaticIniHandler
{
public:
	// Write a value to any INI file at any path
	static bool SetString(const FString& FilePath, const FString& Section, const FString& Key, const FString& Value);
	static bool SetInt(const FString& FilePath, const FString& Section, const FString& Key, int32 Value);
	static bool SetFloat(const FString& FilePath, const FString& Section, const FString& Key, float Value);
	static bool SetBool(const FString& FilePath, const FString& Section, const FString& Key, bool Value);
	static bool SetVector(const FString& FilePath, const FString& Section, const FString& Key, const FVector& Value);
	static bool SetArray(const FString& FilePath, const FString& Section, const FString& Key, const TArray<FString>& Values);

	// Read a value from any INI file at any path
	static bool GetString(const FString& FilePath, const FString& Section, const FString& Key, FString& OutValue);
	static bool GetInt(const FString& FilePath, const FString& Section, const FString& Key, int32& OutValue);
	static bool GetFloat(const FString& FilePath, const FString& Section, const FString& Key, float& OutValue);
	static bool GetBool(const FString& FilePath, const FString& Section, const FString& Key, bool& OutValue);
	static bool GetVector(const FString& FilePath, const FString& Section, const FString& Key, FVector& OutValue);
	static bool GetArray(const FString& FilePath, const FString& Section, const FString& Key, TArray<FString>& OutValues);
	
	// Check if file exists
	static bool DoesFileExist(const FString& FilePath);

private:
	static TSharedPtr<FConfigFile> LoadOrCreateConfigFile(const FString& FilePath);
	static bool SaveConfigFile(const FString& FilePath, const TSharedPtr<FConfigFile>& ConfigFile);
};