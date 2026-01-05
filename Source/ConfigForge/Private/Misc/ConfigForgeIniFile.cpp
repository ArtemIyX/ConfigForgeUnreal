#include "Misc/ConfigForgeIniFile.h"

FConfigForgeIniFile::FConfigForgeIniFile(const FString& InFilePath, bool bAutoLoad)
	: FilePath(InFilePath)
	, bIsDirty(false)
{
	if (bAutoLoad)
	{
		Load();
	}
}

FConfigForgeIniFile::~FConfigForgeIniFile()
{
	// Optionally auto-save on destruction if dirty
	// if (bIsDirty)
	// {
	//     Save();
	// }
}

bool FConfigForgeIniFile::Load()
{
	ConfigFile = MakeShared<FConfigFile>();

	if (FPaths::FileExists(FilePath))
	{
		ConfigFile->Read(FilePath);
	}

	bIsDirty = false;
	return true;
}

bool FConfigForgeIniFile::Save()
{
	if (!ConfigFile.IsValid())
	{
		return false;
	}

	// Ensure directory exists
	const FString dir = FPaths::GetPath(FilePath);
	IPlatformFile& pf = FPlatformFileManager::Get().GetPlatformFile();
	if (!pf.DirectoryExists(*dir))
	{
		pf.CreateDirectoryTree(*dir);
	}

	// Write to disk
	bool bSuccess = ConfigFile->Write(FilePath);

	if (bSuccess)
	{
		bIsDirty = false;
	}

	return bSuccess;
}

void FConfigForgeIniFile::EnsureLoaded()
{
	if (!ConfigFile.IsValid())
	{
		Load();
	}
}

// Set operations
void FConfigForgeIniFile::SetString(const FString& Section, const FString& Key, const FString& Value)
{
	EnsureLoaded();
	ConfigFile->SetString(*Section, *Key, *Value);
	MarkDirty();
}

void FConfigForgeIniFile::SetInt32(const FString& Section, const FString& Key, int32 Value)
{
	EnsureLoaded();
	ConfigFile->SetInt64(*Section, *Key, Value);
	MarkDirty();
}

void FConfigForgeIniFile::SetInt64(const FString& Section, const FString& Key, int64 Value)
{
	EnsureLoaded();
	ConfigFile->SetInt64(*Section, *Key, Value);
	MarkDirty();
}

void FConfigForgeIniFile::SetFloat(const FString& Section, const FString& Key, float Value)
{
	EnsureLoaded();
	ConfigFile->SetFloat(*Section, *Key, Value);
	MarkDirty();
}

void FConfigForgeIniFile::SetDouble(const FString& Section, const FString& Key, double Value)
{
	EnsureLoaded();
	ConfigFile->SetDouble(*Section, *Key, Value);
	MarkDirty();
}

void FConfigForgeIniFile::SetBool(const FString& Section, const FString& Key, bool Value)
{
	EnsureLoaded();
	ConfigFile->SetBool(*Section, *Key, Value);
	MarkDirty();
}


void FConfigForgeIniFile::SetArray(const FString& Section, const FString& Key, const TArray<FString>& Values)
{
	EnsureLoaded();
	ConfigFile->SetArray(*Section, *Key, Values);
	MarkDirty();
}

// Get operations
bool FConfigForgeIniFile::GetString(const FString& Section, const FString& Key, FString& OutValue) const
{
	if (!ConfigFile.IsValid())
	{
		return false;
	}
	return ConfigFile->GetString(*Section, *Key, OutValue);
}

bool FConfigForgeIniFile::GetInt32(const FString& Section, const FString& Key, int32& OutValue)
{
	if (!ConfigFile.IsValid())
	{
		return false;
	}
	return ConfigFile->GetInt(*Section, *Key, OutValue);
}

bool FConfigForgeIniFile::GetInt64(const FString& Section, const FString& Key, int64& OutValue) const
{
	if (!ConfigFile.IsValid())
	{
		return false;
	}
	return ConfigFile->GetInt64(*Section, *Key, OutValue);
}

bool FConfigForgeIniFile::GetFloat(const FString& Section, const FString& Key, float& OutValue) const
{
	if (!ConfigFile.IsValid())
	{
		return false;
	}
	return ConfigFile->GetFloat(*Section, *Key, OutValue);
}

bool FConfigForgeIniFile::GetDouble(const FString& Section, const FString& Key, double& OutValue) const
{
	if (!ConfigFile.IsValid())
	{
		return false;
	}
	return ConfigFile->GetDouble(*Section, *Key, OutValue);
}

bool FConfigForgeIniFile::GetBool(const FString& Section, const FString& Key, bool& OutValue) const
{
	if (!ConfigFile.IsValid())
	{
		return false;
	}
	return ConfigFile->GetBool(*Section, *Key, OutValue);
}

bool FConfigForgeIniFile::GetArray(const FString& Section, const FString& Key, TArray<FString>& OutValues) const
{
	if (!ConfigFile.IsValid())
	{
		return false;
	}

	TArray<FString> Values;
	ConfigFile->GetArray(*Section, *Key, Values);

	if (Values.Num() > 0)
	{
		OutValues = Values;
		return true;
	}

	return false;
}


// Utility functions
bool FConfigForgeIniFile::HasSection(const FString& Section) const
{
	if (!ConfigFile.IsValid())
	{
		return false;
	}

	return ConfigFile->FindSection(Section) != nullptr;
}

bool FConfigForgeIniFile::HasKey(const FString& Section, const FString& Key) const
{
	if (!ConfigFile.IsValid())
	{
		return false;
	}

	const FConfigSection* ConfigSection = ConfigFile->FindSection(Section);
	if (!ConfigSection)
	{
		return false;
	}

	return ConfigSection->Find(*Key) != nullptr;
}

void FConfigForgeIniFile::GetAllSections(TArray<FString>& OutSections) const
{
	OutSections.Empty();
    
	if (!ConfigFile.IsValid())
	{
		return;
	}
    
	for (const TTuple<FString, FConfigSection>& Pair : AsConst(*ConfigFile))
	{
		OutSections.Add(Pair.Key);
	}
}

void FConfigForgeIniFile::GetKeysInSection(const FString& Section, TArray<FString>& OutKeys) const
{
	OutKeys.Empty();

	if (!ConfigFile.IsValid())
	{
		return;
	}

	const FConfigSection* configSection = ConfigFile->FindSection(Section);
	if (!configSection)
	{
		return;
	}

	for (const TTuple<FName, FConfigValue>& pair : *configSection)
	{
		OutKeys.Add(pair.Key.ToString());
	}
}

void FConfigForgeIniFile::Clear()
{
	if (ConfigFile.IsValid())
	{
		ConfigFile->Empty();
		bIsDirty = true;
	}
}