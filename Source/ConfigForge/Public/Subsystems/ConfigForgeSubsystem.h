// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ConfigForgeSubsystem.generated.h"

class UConfigPathProvider;
class UConfigForgeFileRuntime;
class UConfigValueObject;
struct FConfigForgeFileData;
class UConfigForgeFile;
class UConfigForgeSetup;
class UConfigForgeDeveloperSettings;


DECLARE_DELEGATE_TwoParams(FLoadForgeFileDelegate, bool, UConfigForgeFileRuntime*);

/**
 * @class UConfigForgeSubsystem
 * @brief Game instance subsystem for managing configuration files and categories in the ConfigForge plugin.
 * 
 * UConfigForgeSubsystem provides a centralized interface for accessing and querying configuration
 * data organized in a hierarchical structure of Files -> Categories -> Properties. It serves as
 * the main API entry point for the ConfigForge system within a game instance.
 * 
 * The subsystem manages access to:
 * - Developer settings and setup assets
 * - Configuration file data and metadata
 * - Category information within files
 * - Property value objects within categories
 * 
 * @section hierarchy Data Hierarchy
 * The ConfigForge system uses a three-level hierarchy:
 * 1. **Files** (UConfigForgeFile): Top-level containers identified by file names
 * 2. **Categories** (UConfigForgeCategory): Logical groupings within files, identified by FName
 * 3. **Properties** (UConfigValueObject): Individual configuration values within categories
 * 
 * @section setup Setup Requirements
 * Before using this subsystem, you must configure the setup asset in:
 * Project Settings -> Config Forge -> 'ConfigSetup'
 * 
 * The setup asset (UConfigForgeSetup) must contain at least one file with valid categories
 * and properties for the subsystem to function properly.
 * 
 * @section usage Usage Example
 * @code
 * // Get the subsystem
 * UConfigForgeSubsystem* Subsystem = UGameInstance->GetSubsystem<UConfigForgeSubsystem>();
 * 
 * // Get all file names
 * TArray<FString> FileNames;
 * Subsystem->GetFileNames(FileNames);
 * 
 * // Get categories from a specific file
 * TArray<FName> Categories;
 * Subsystem->GetFileCategoriesByName("GameSettings", Categories);
 * 
 * // Get properties from a category
 * TArray<UConfigValueObject*> Properties;
 * Subsystem->GetCategoryProperties("GameSettings", "Graphics", Properties);
 * @endcode
 * 
 * @section threading Thread Safety
 * This subsystem performs synchronous asset loading operations and should be called
 * from the game thread only. All getter methods are const-correct but load assets
 * synchronously, which may cause hitches if called frequently.
 * 
 * @section logging Logging
 * The subsystem uses the LogConfigForge logging category for all error and warning messages:
 * - Errors: Invalid setup assets, missing files, missing categories
 * - Warnings: Empty file lists, null file entries, empty categories
 * 
 * @see UGameInstanceSubsystem
 * @see UConfigForgeSetup
 * @see UConfigForgeFile
 * @see UConfigForgeCategory
 * @see UConfigValueObject
 * @see FConfigForgeFileData
 * 
 * @author Wellsaik
 * @date 01.01.2025
 */
UCLASS()
class CONFIGFORGE_API UConfigForgeSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UConfigForgeSubsystem();

protected:
	// Unique File id -> Runtime file object instance
	TMap<FGuid, TObjectPtr<UConfigForgeFileRuntime>> RuntimeFiles;

	// True if loading files right now (for async)
	FThreadSafeBool bLoadingFiles;

public:
	#pragma region Get
	/**
	 * @brief Gets the developer settings for the ConfigForge system.
	 * 
	 * Retrieves the default instance of UConfigForgeDeveloperSettings from the project settings.
	 * This provides access to the plugin's configuration options.
	 *
	 * @note Never returns null as it always returns the default object.
	 * 
	 * @return const UConfigForgeDeveloperSettings* Pointer to the default developer settings instance.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Get|Settings")
	const UConfigForgeDeveloperSettings* GetSettings() const;

	/**
	 * @brief Retrieves the setup asset reference from developer settings.
	 * 
	 * Returns a soft object pointer to the UConfigForgeSetup asset that is configured
	 * in Project Settings -> Config Forge -> 'ConfigSetup'. This asset contains all
	 * file and category configurations for the system.
	 *
	 * @note May be invalid if not configured in project settings.
	 * 
	 * @return TSoftObjectPtr<UConfigForgeSetup> Soft reference to the setup asset.
	 *         
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Get|Settings")
	TSoftObjectPtr<UConfigForgeSetup> GetSetupAsset() const;

	/**
	 * @brief Retrieves a specific configuration file by name.
	 * 
	 * Searches through all files in the setup asset and returns the file data
	 * matching the specified file name. The search is case-sensitive and performs
	 * a linear search through all available files.
	 * 
	 * @param InFileName The name of the file to search for (must match exactly).
	 * @param OutFileData [out] The file data structure to populate if found.
	 *                    Will be empty if file is not found.
	 * 
	 * @note OutFileData will be reset to empty values before searching.
	 * @note Only files with non-null File pointers are searched.
	 * @return bool True if the file was found, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category="Get|File")
	bool GetFile(const FString& InFileName, FConfigForgeFileData& OutFileData) const;

	/**
	 * @brief Retrieves all valid configuration files from the setup asset.
	 * 
	 * Loads the setup asset synchronously and populates the output array with all
	 * files that have valid (non-null) File pointers. Null entries in the setup
	 * asset are automatically filtered out.
	 *
	 * @note Logs an error if the setup asset is invalid or not configured.
	 * @note Logs a warning if the setup asset contains no files.
	 * @note Performs synchronous loading of the setup asset.
	 * 
	 * @param OutFiles [out] Array to populate with valid file data. Will be emptied
	 *                 before population.
	 */
	UFUNCTION(BlueprintCallable, Category="Get|File")
	void GetFiles(TArray<FConfigForgeFileData>& OutFiles) const;

	static void GetFilesStatic(UConfigForgeSetup* InSetupFile, TArray<FConfigForgeFileData>& OutFiles);

	/**
	 * @brief Retrieves the names of all configuration files in the setup asset.
	 * 
	 * Extracts and returns only the file names from all valid files in the setup asset.
	 * This is more efficient than GetFiles() when only names are needed.
	 * 
	 * @param OutNames [out] Array to populate with file names. Will be emptied before
	 *                 population.
	 * 
	 * @note Logs an error if the setup asset is invalid or not configured.
	 * @note Logs a warning if the setup asset contains no files.
	 * @note Logs a warning for each null file entry encountered (with index).
	 * @note Performs synchronous loading of the setup asset.
	 */
	UFUNCTION(BlueprintCallable, Category="Get|File")
	void GetFileNames(TArray<FString>& OutNames) const;

	/**
	 * @brief Retrieves all category names from a file specified by name.
	 * 
	 * Convenience function that first looks up the file by name, then extracts
	 * all category names from that file. This combines GetFile() and GetFileCategories()
	 * operations.
	 * 
	 * @param InFileName The name of the file to retrieve categories from.
	 * @param OutCategories [out] Array to populate with category names. Will be emptied
	 *                      before population.
	 * 
	 * @note Logs an error if the specified file is not found in the setup asset.
	 * @note OutCategories will be empty if the file is not found or has no categories.
	 */
	UFUNCTION(BlueprintCallable, Category="Get|Category")
	void GetFileCategoriesByName(const FString& InFileName, TArray<FName>& OutCategories);

	/**
	 * @brief Retrieves all category names from a file data structure.
	 * 
	 * Extracts the names of all valid (non-null) categories from the provided file data.
	 * Only categories with valid pointers are included in the result.
	 * 
	 * @param InFileData The file data structure containing categories to extract.
	 * @param OutCategories [out] Array to populate with category names. Will be emptied
	 *                      before population.
	 * 
	 * @note Logs an error if InFileData.File is null.
	 * @note Logs a warning if the file contains no categories.
	 * @note Only non-null category entries are added to the output array.
	 */
	UFUNCTION(BlueprintCallable, Category="Get|Category")
	void GetFileCategories(const FConfigForgeFileData& InFileData, TArray<FName>& OutCategories);

	/**
	 * @brief Retrieves all property value objects from a specific category within a file.
	 * 
	 * Looks up a file by name, finds the specified category within that file, and
	 * returns all configuration property value objects (Fields) defined in that category.
	 * 
	 * @param InFileName The name of the file containing the category.
	 * @param InCategoryName The name of the category to retrieve properties from.
	 * @param OutProperties [out] Array to populate with property value objects. Will be
	 *                      emptied before population.
	 * 
	 * @note Logs an error if the file is not found in the setup.
	 * @note Logs an error if the specified category is not found in the file.
	 * @note Only non-null property objects are added to the output array.
	 * @note Early returns with empty array if file or category lookups fail.
	 */
	UFUNCTION(BlueprintCallable, Category="Get|Category")
	void GetCategoryProperties(const FString& InFileName, const FName& InCategoryName, TArray<UConfigValueObject*>& OutProperties);

	#pragma endregion

protected:
	bool LoadFileInternal(TSubclassOf<UConfigPathProvider> InPathProviderClass, const FGuid& InId, UConfigForgeFile* InTemplate, UConfigForgeFileRuntime*& OutFile);

public:
	#pragma region IO
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="I/O")
	FORCEINLINE bool IsLoadingFiles() const { return bLoadingFiles; }

	UFUNCTION(BlueprintCallable, Category="I/O")
	bool LoadSingleFile(const FConfigForgeFileData& InFileData, UConfigForgeFileRuntime*& OutFile);

	void LoadSingleFileAsync(const FConfigForgeFileData& InFileData, FLoadForgeFileDelegate Callback);

	#pragma endregion
};