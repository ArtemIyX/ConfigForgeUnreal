// CustomIniHandler.cpp
#include "Misc/ConfigForgeStaticIniHandler.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"

TSharedPtr<FConfigFile> FConfigForgeStaticIniHandler::LoadOrCreateConfigFile(const FString& FilePath)
{
	TSharedPtr<FConfigFile> ConfigFile = MakeShared<FConfigFile>();

	// Load existing file if it exists
	if (FPaths::FileExists(FilePath))
	{
		ConfigFile->Read(FilePath);
	}

	return ConfigFile;
}

bool FConfigForgeStaticIniHandler::SaveConfigFile(const FString& FilePath, const TSharedPtr<FConfigFile>& ConfigFile)
{
	if (!ConfigFile.IsValid())
	{
		return false;
	}

	// Ensure directory exists
	FString Directory = FPaths::GetPath(FilePath);
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (!PlatformFile.DirectoryExists(*Directory))
	{
		PlatformFile.CreateDirectoryTree(*Directory);
	}

	// Write to disk
	return ConfigFile->Write(FilePath);
}

bool FConfigForgeStaticIniHandler::SetString(const FString& FilePath, const FString& Section, const FString& Key, const FString& Value)
{
	TSharedPtr<FConfigFile> ConfigFile = LoadOrCreateConfigFile(FilePath);
	ConfigFile->SetString(*Section, *Key, *Value);
	return SaveConfigFile(FilePath, ConfigFile);
}

bool FConfigForgeStaticIniHandler::SetInt(const FString& FilePath, const FString& Section, const FString& Key, int32 Value)
{
	return SetString(FilePath, Section, Key, FString::FromInt(Value));
}

bool FConfigForgeStaticIniHandler::SetFloat(const FString& FilePath, const FString& Section, const FString& Key, float Value)
{
	return SetString(FilePath, Section, Key, FString::SanitizeFloat(Value));
}

bool FConfigForgeStaticIniHandler::SetBool(const FString& FilePath, const FString& Section, const FString& Key, bool Value)
{
	return SetString(FilePath, Section, Key, Value ? TEXT("True") : TEXT("False"));
}

bool FConfigForgeStaticIniHandler::SetVector(const FString& FilePath, const FString& Section, const FString& Key, const FVector& Value)
{
	FString VectorString = FString::Printf(TEXT("(X=%f,Y=%f,Z=%f)"), Value.X, Value.Y, Value.Z);
	return SetString(FilePath, Section, Key, VectorString);
}

bool FConfigForgeStaticIniHandler::SetArray(const FString& FilePath, const FString& Section, const FString& Key, const TArray<FString>& Values)
{
	TSharedPtr<FConfigFile> ConfigFile = LoadOrCreateConfigFile(FilePath);
	ConfigFile->SetArray(*Section, *Key, Values);
	return SaveConfigFile(FilePath, ConfigFile);
}

bool FConfigForgeStaticIniHandler::GetString(const FString& FilePath, const FString& Section, const FString& Key, FString& OutValue)
{
	if (!FPaths::FileExists(FilePath))
	{
		return false;
	}

	TSharedPtr<FConfigFile> ConfigFile = LoadOrCreateConfigFile(FilePath);
	return ConfigFile->GetString(*Section, *Key, OutValue);
}

bool FConfigForgeStaticIniHandler::GetInt(const FString& FilePath, const FString& Section, const FString& Key, int32& OutValue)
{
	FString StringValue;
	if (GetString(FilePath, Section, Key, StringValue))
	{
		OutValue = FCString::Atoi(*StringValue);
		return true;
	}
	return false;
}

bool FConfigForgeStaticIniHandler::GetFloat(const FString& FilePath, const FString& Section, const FString& Key, float& OutValue)
{
	FString StringValue;
	if (GetString(FilePath, Section, Key, StringValue))
	{
		OutValue = FCString::Atof(*StringValue);
		return true;
	}
	return false;
}

bool FConfigForgeStaticIniHandler::GetBool(const FString& FilePath, const FString& Section, const FString& Key, bool& OutValue)
{
	FString StringValue;
	if (GetString(FilePath, Section, Key, StringValue))
	{
		OutValue = StringValue.Equals(TEXT("True"), ESearchCase::IgnoreCase);
		return true;
	}
	return false;
}

bool FConfigForgeStaticIniHandler::GetVector(const FString& FilePath, const FString& Section, const FString& Key, FVector& OutValue)
{
	FString StringValue;
	if (GetString(FilePath, Section, Key, StringValue))
	{
		return OutValue.InitFromString(StringValue);
	}
	return false;
}

bool FConfigForgeStaticIniHandler::GetArray(const FString& FilePath, const FString& Section, const FString& Key, TArray<FString>& OutValues)
{
	if (!FPaths::FileExists(FilePath))
	{
		return false;
	}

	TSharedPtr<FConfigFile> ConfigFile = LoadOrCreateConfigFile(FilePath);
	TArray<FString> Values;
	ConfigFile->GetArray(*Section, *Key, Values);

	if (Values.Num() > 0)
	{
		OutValues = Values;
		return true;
	}

	return false;
}

/*
bool FCustomIniHandler::RemoveKey(const FString& FilePath, const FString& Section, const FString& Key)
{
	if (!FPaths::FileExists(FilePath))
	{
		return false;
	}

	TSharedPtr<FConfigFile> ConfigFile = LoadOrCreateConfigFile(FilePath);

	// Get the section
	const FConfigSection* ConfigSection = ConfigFile->FindSection(Section);
	if (!ConfigSection)
	{
		return false;
	}

	// Remove the key from the section
	int32 NumRemoved = ConfigSection->Remove(*Key);

	if (NumRemoved > 0)
	{
		return SaveConfigFile(FilePath, ConfigFile);
	}

	return false;
}
*/

bool FConfigForgeStaticIniHandler::DoesFileExist(const FString& FilePath)
{
	return FPaths::FileExists(FilePath);
}