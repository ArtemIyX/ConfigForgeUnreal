// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "Data/ConfigForgeCategoryRuntime.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ConfigForgeSubsystem.generated.h"

class UConfigForgeCategory;
class UConfigForgeCategoryRuntime;
class UConfigPathProvider;
class UConfigForgeFileRuntime;
class UConfigValueObject;
struct FConfigForgeFileData;
class UConfigForgeFile;
class UConfigForgeSetup;
class UConfigForgeDeveloperSettings;


DECLARE_DELEGATE_TwoParams(FLoadForgeFileDelegate, bool, UConfigForgeFileRuntime*);
DECLARE_DELEGATE_OneParam(FSaveForgeFileDelegate, bool);
DECLARE_DELEGATE_TwoParams(FLoadAllForgeFileDelegate, bool, const TArray<UConfigForgeFileRuntime*>&);
DECLARE_DELEGATE_OneParam(FSaveAllForgeFileDelegate, bool);
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

	// True if reading/writing files right now (for async)
	FThreadSafeBool bOperatingFiles;

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

	#pragma region Runtime

	/**
	 * @brief Retrieves a loaded runtime file instance by its unique ID.
	 *
	 * Searches the internal RuntimeFiles map for a valid UConfigForgeFileRuntime object
	 * associated with the given InUniqueFileId.
	 *
	 * @param InUniqueFileId The unique GUID of the file to retrieve.
	 * @param OutRuntimeFile [out] Pointer to the runtime file object if found and valid.
	 * @return true if a valid runtime file was found and returned; false otherwise
	 *         (file not loaded, invalid pointer, or data not valid via IsValidData()).
	 */
	UFUNCTION(BlueprintCallable, Category="Runtime")
	bool GetRuntimeFile(const FGuid& InUniqueFileId, UConfigForgeFileRuntime*& OutRuntimeFile) const;

	/**
	 * @brief Retrieves all runtime configuration files currently loaded in the subsystem.
	 * @param OutRuntimeFiles [out] Array that will be populated with pointers to all runtime files.
	 * @note The output array is cleared and repopulated with all valid runtime files.
	 */
	UFUNCTION(BlueprintCallable, Category="Runtime")
	void GetAllRuntimeFiles(TArray<UConfigForgeFileRuntime*>& OutRuntimeFiles) const;

	/**
	 * @brief Retrieves all categories from a specific runtime configuration file.
	 * @param InConfigFile Pointer to the runtime configuration file to query.
	 * @param OutCategories [out] Array that will be populated with pointers to all categories in the file.
	 * @return True if categories were found, false if the file is invalid or contains no categories.
	 */
	UFUNCTION(BlueprintCallable, Category="Runtime")
	bool GetRuntimeCategories(const UConfigForgeFileRuntime* InConfigFile, TArray<UConfigForgeCategoryRuntime*>& OutCategories);

	/**
	 * @brief Retrieves all categories from a runtime configuration file identified by its GUID.
	 * @param InFileId The unique identifier of the configuration file.
	 * @param OutCategories [out] Array that will be populated with pointers to all categories in the file.
	 * @return True if the file was found and categories were retrieved, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, DisplayName="Get Runtime Categories (By File ID)", Category="Runtime")
	bool GetRuntimeCategories_ID(const FGuid& InFileId, TArray<UConfigForgeCategoryRuntime*>& OutCategories);

	/**
	 * @brief Retrieves a specific category by name from a runtime configuration file.
	 * @param InConfigFile Pointer to the runtime configuration file to query.
	 * @param InCategoryName The name of the category to retrieve.
	 * @param OutCategory [out] Pointer to the retrieved category if found.
	 * @return True if the category was found, false if the file is invalid or the category doesn't exist.
	 */
	UFUNCTION(BlueprintCallable, Category="Runtime")
	bool GetRuntimeCategory(const UConfigForgeFileRuntime* InConfigFile, const FName& InCategoryName, UConfigForgeCategoryRuntime*& OutCategory);

	/**
	 * @brief Retrieves a specific category by name from a runtime configuration file identified by its GUID.
	 * @param InFileId The unique identifier of the configuration file.
	 * @param InCategoryName The name of the category to retrieve.
	 * @param OutCategory [out] Pointer to the retrieved category if found.
	 * @return True if the file and category were found, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, DisplayName="Get Runtime Category (By File ID)", Category="Runtime")
	bool GetRuntimeCategory_ID(const FGuid& InFileId, const FName& InCategoryName, UConfigForgeCategoryRuntime*& OutCategory);

	/**
	 * @brief Retrieves a specific field by key from a runtime category.
	 * @param InRuntimeCategory Pointer to the runtime category to query.
	 * @param InKey The key identifier of the field to retrieve.
	 * @param OutField [out] Pointer to the retrieved field value object if found.
	 * @return True if the field was found, false if the category is invalid or the field doesn't exist.
	 */
	UFUNCTION(BlueprintCallable, Category="Runtime")
	bool GetRuntimeField(const UConfigForgeCategoryRuntime* InRuntimeCategory, const FString& InKey, UConfigValueObjectRuntime*& OutField);

	/**
	 * @brief Retrieves a specific field by key from a category within a runtime configuration file.
	 * @param InConfigFile Pointer to the runtime configuration file to query.
	 * @param InCategoryName The name of the category containing the field.
	 * @param InKey The key identifier of the field to retrieve.
	 * @param OutField [out] Pointer to the retrieved field value object if found.
	 * @return True if the file, category, and field were found, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, DisplayName="Get Runtime Field (From File Object)", Category="Runtime")
	bool GetRuntimeField_File(const UConfigForgeFileRuntime* InConfigFile, const FName& InCategoryName, const FString& InKey, UConfigValueObjectRuntime*& OutField);

	/**
	 * @brief Retrieves a specific field by key from a category within a runtime configuration file identified by its GUID.
	 * @param InFileID The unique identifier of the configuration file.
	 * @param InCategoryName The name of the category containing the field.
	 * @param InKey The key identifier of the field to retrieve.
	 * @param OutField [out] Pointer to the retrieved field value object if found.
	 * @return True if the file, category, and field were found, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, DisplayName="Get Runtime Field (By File ID)", Category="Runtime")
	bool GetRuntimeField_ID(const FGuid& InFileID, const FName& InCategoryName, const FString& InKey, UConfigValueObjectRuntime*& OutField);

	/**
	 * @brief Retrieves all fields from a runtime category.
	 * @param InRuntimeCategory Pointer to the runtime category to query.
	 * @param OutFields [out] Array that will be populated with pointers to all field value objects in the category.
	 * @return True if the category is valid, false if the category pointer is null.
	 * @note Returns true even if the category contains no fields.
	 */
	UFUNCTION(BlueprintCallable, Category="Runtime")
	bool GetRuntimeFields(const UConfigForgeCategoryRuntime* InRuntimeCategory, TArray<UConfigValueObjectRuntime*>& OutFields);

	/**
	 * @brief Retrieves all fields from a category within a runtime configuration file.
	 * @param InConfigFile Pointer to the runtime configuration file to query.
	 * @param InCategoryName The name of the category containing the fields.
	 * @param OutFields [out] Array that will be populated with pointers to all field value objects in the category.
	 * @return True if the file and category were found, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, DisplayName="Get Runtime All Fields (From File Object)", Category="Runtime")
	bool GetRuntimeFields_File(const UConfigForgeFileRuntime* InConfigFile, const FName& InCategoryName, TArray<UConfigValueObjectRuntime*>& OutFields);

	/**
	 * @brief Retrieves all fields from a category within a runtime configuration file identified by its GUID.
	 * @param InFileID The unique identifier of the configuration file.
	 * @param InCategoryName The name of the category containing the fields.
	 * @param OutFields [out] Array that will be populated with pointers to all field value objects in the category.
	 * @return True if the file and category were found, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, DisplayName="Get Runtime All Fields (By File ID)", Category="Runtime")
	bool GetRuntimeFields_ID(const FGuid& InFileID, const FName& InCategoryName, TArray<UConfigValueObjectRuntime*>& OutFields);
	#pragma endregion

public:
	#pragma region IO

protected:
	/**
	 * @brief Internal function that loads (and creates) a config file from disk.
	 *
	 * This is the core implementation used by both synchronous and asynchronous load functions.
	 * It:
	 * - Creates the directory tree if it doesn't exist
	 * - Creates a new UConfigForgeFileRuntime instance
	 * - Initializes it with default values from the template asset
	 * - Replaces any previously loaded file with the same ID
	 * - Attempts to read data from disk; if that fails or file doesn't exist, saves defaults
	 *
	 * @param InPathProviderClass Class of the path provider determining where to read/write.
	 * @param InId Unique ID of the file to assign map key.
	 * @param InTemplate Template asset containing metadata (e.g., FileName) and default values.
	 * @param OutFile [out] The created/loaded runtime file object on success.
	 * @return true if the file was successfully set up and OutFile is valid.
	 */
	bool ReadFileInternal(TSubclassOf<UConfigPathProvider> InPathProviderClass, const FGuid& InId, UConfigForgeFile* InTemplate, UConfigForgeFileRuntime*& OutFile);

	/**
	 * @brief Internal function that writes a runtime file to disk.
	 *
	 * Ensures the directory and file exist, then calls SaveTo() on the runtime file.
	 * Note: The current implementation has a bug — it calls ReadFrom() instead of SaveTo().
	 * This function is intended to save the in-memory data to disk.
	 *
	 * @param InFile The runtime file to write.
	 * @return true if all preconditions passed and the save operation succeeded.
	 */
	bool WriteFileInternal(UConfigForgeFileRuntime* InFile);

	bool LoadAllFilesInternal(const TArray<FConfigForgeFileData>& InDataArr, TArray<UConfigForgeFileRuntime*>& OutFiles);

	bool WriteAllFilesInternal(const TArray<UConfigForgeFileRuntime*>& InFiles);

public:
	/**
	 * @brief Checks whether a file load/save operation is currently in progress.
	 *
	 * Used to prevent concurrent operations on the subsystem (reentrancy protection).
	 *
	 * @return true if a file operation is active.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="I/O")
	FORCEINLINE bool IsOperatingFiles() const { return bOperatingFiles; }

	/**
	 * @brief Synchronously loads a single config file from disk.
	 *
	 * Blocks the calling thread and uses ReadFileInternal().
	 * Fails immediately if another operation is already in progress (bOperatingFiles == true).
	 *
	 * @param InFileData Structure containing the path provider class, file ID, and template asset.
	 * @param OutFile [out] The loaded runtime file object on success.
	 * @return true if the file was successfully loaded/created.
	 */
	UFUNCTION(BlueprintCallable, Category="I/O")
	bool LoadSingleFile(const FConfigForgeFileData& InFileData, UConfigForgeFileRuntime*& OutFile);

	/**
	 * @brief Asynchronously loads a single config file from disk.
	 *
	 * Runs the heavy I/O on the task graph thread and delivers the result back on the game thread.
	 * If another operation is in progress, the callback is called immediately with failure.
	 *
	 * @param InFileData Structure containing the path provider class, file ID, and template asset.
	 * @param Callback Delegate called on the game thread with success flag and runtime file (or nullptr).
	 */
	void LoadSingleFileAsync(const FConfigForgeFileData& InFileData, FLoadForgeFileDelegate Callback);

	/**
	 * @brief Synchronously saves a single loaded config file to disk.
	 *
	 * Looks up the runtime file by ID, then calls WriteFileInternal().
	 * Fails immediately if another operation is in progress or the file is not loaded.
	 *
	 * @param InFileUniqueID The unique ID of the file to save.
	 * @return true if the file was successfully written to disk.
	 */
	UFUNCTION(BlueprintCallable, Category="I/O")
	bool SaveSingleFile(const FGuid& InFileUniqueID);

	/**
	 * @brief Asynchronously saves a single loaded config file to disk.
	 *
	 * Runs the save operation on the task graph thread and reports back on the game thread.
	 * If another operation is in progress or the file is not loaded, the callback is called immediately with failure.
	 *
	 * @param InFileUniqueID The unique ID of the file to save.
	 * @param Callback Delegate called on the game thread with success flag.
	 */
	void SaveSingleFileAsync(const FGuid& InFileUniqueID, FSaveForgeFileDelegate Callback);

	/**
	 * @brief Loads all configuration files synchronously.
	 *
	 * Clears the output array and attempts to load every file defined in the ConfigForge setup asset.
	 * The files are loaded into runtime objects (UConfigForgeFileRuntime*) that hold the parsed data.
	 *
	 * @param OutFiles [out] Array that will be populated with pointers to the loaded runtime file objects.
	 *                 The caller is responsible for managing the lifetime of these objects (they are owned by the subsystem).
	 * @return true if all files were successfully loaded, false otherwise (e.g., setup missing or already operating).
	 *
	 * @note This is a BlueprintCallable function.
	 * @note This function blocks the calling thread until completion.
	 * @note If another load/save operation is already in progress (bOperatingFiles == true), the function returns false immediately.
	 */
	UFUNCTION(BlueprintCallable, Category="I/O")
	bool LoadAllFiles(TArray<UConfigForgeFileRuntime*>& OutFiles);

	/**
	 * @brief Loads all configuration files asynchronously.
	 *
	 * Starts an asynchronous task on the task graph to load all files. When complete, the provided delegate
	 * is executed on the game thread with the results.
	 *
	 * @param Callback Delegate called when the operation finishes.
	 *                 Signature: void(bool bSuccess, const TArray<UConfigForgeFileRuntime*>& LoadedFiles)
	 *
	 * @note If another load/save operation is already in progress or the setup is invalid, the callback
	 *       is invoked immediately with failure.
	 * @note The runtime file objects in the result array are owned by the subsystem.
	 */
	void LoadAllFilesAsync(FLoadAllForgeFileDelegate Callback);

	UFUNCTION(BlueprintCallable, Category="I/O")
	bool LoadSelectedFiles(const TArray<FConfigForgeFileData>& InFiles, TArray<UConfigForgeFileRuntime*>& OutFiles);
	
	void LoadSelectedFilesAsync(const TArray<FConfigForgeFileData>& InFiles, FLoadAllForgeFileDelegate Callback);
	
	/**
	 * @brief Saves all currently loaded runtime configuration files synchronously.
	 *
	 * Retrieves all runtime file objects currently managed by the subsystem and writes them to disk.
	 *
	 * @return true if all files were successfully saved, false otherwise
	 *         (e.g., no files loaded, or another operation already in progress).
	 *
	 * @note This is a BlueprintCallable function.
	 * @note This function blocks the calling thread until completion.
	 */
	UFUNCTION(BlueprintCallable, Category="I/O")
	bool SaveAllFiles();

	/**
	 * @brief Saves all currently loaded runtime configuration files asynchronously.
	 *
	 * Starts an asynchronous task on the task graph to save all managed runtime files.
	 * When complete, the provided delegate is executed on the game thread.
	 *
	 * @param Callback Delegate called when the operation finishes.
	 *                 Signature: void(bool bSuccess)
	 *
	 * @note If no files are loaded or another operation is already in progress, the callback
	 *       is invoked immediately with failure.
	 */
	void SaveAllFilesAsync(FSaveAllForgeFileDelegate Callback);
	#pragma endregion
};