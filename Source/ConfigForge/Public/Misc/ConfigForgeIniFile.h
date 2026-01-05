#pragma once

#include "CoreMinimal.h" 


/**
 * A wrapper class for handling INI file operations with batched I/O.
 * Loads the file once, allows multiple operations, then saves once.
 */
class CONFIGFORGE_API FConfigForgeIniFile
{
public:
	// Constructor - optionally load file immediately
	explicit FConfigForgeIniFile(const FString& InFilePath, bool bAutoLoad = true);
	// Destructor
	~FConfigForgeIniFile();

private:
	FString FilePath;
	TSharedPtr<FConfigFile> ConfigFile;
	bool bIsDirty;

protected:
	void MarkDirty() { bIsDirty = true; }
	void EnsureLoaded();

public:
	// Load the INI file from disk
	bool Load();

	// Save the INI file to disk
	bool Save();

	// Check if file is loaded
	bool IsLoaded() const { return ConfigFile.IsValid(); }

	// Get the file path
	const FString& GetFilePath() const { return FilePath; }

	// Set operations
	void SetString(const FString& Section, const FString& Key, const FString& Value);
	void SetInt32(const FString& Section, const FString& Key, int32 Value);
	void SetInt64(const FString& Section, const FString& Key, int64 Value);
	void SetFloat(const FString& Section, const FString& Key, float Value);
	void SetDouble(const FString& Section, const FString& Key, double Value);
	void SetBool(const FString& Section, const FString& Key, bool Value);
	void SetArray(const FString& Section, const FString& Key, const TArray<FString>& Values);

	// Get operations
	bool GetString(const FString& Section, const FString& Key, FString& OutValue) const;
	bool GetInt32(const FString& Section, const FString& Key, int32& OutValue);
	bool GetInt64(const FString& Section, const FString& Key, int64& OutValue) const;
	bool GetFloat(const FString& Section, const FString& Key, float& OutValue) const;
	bool GetDouble(const FString& Section, const FString& Key, double& OutValue) const;
	bool GetBool(const FString& Section, const FString& Key, bool& OutValue) const;
	bool GetArray(const FString& Section, const FString& Key, TArray<FString>& OutValues) const;

	// Utility
	bool HasSection(const FString& Section) const;
	bool HasKey(const FString& Section, const FString& Key) const;
	void GetAllSections(TArray<FString>& OutSections) const;
	void GetKeysInSection(const FString& Section, TArray<FString>& OutKeys) const;

	// Clear all data without saving
	void Clear();
};