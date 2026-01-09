// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.


#include "Subsystems/ConfigForgeSubsystem.h"

#include "ConfigForge.h"
#include "Data/Asset/ConfigForgeCategory.h"
#include "Data/Asset/ConfigForgeFile.h"
#include "Data/Asset/ConfigForgeSetup.h"
#include "Data/Runtime/ConfigForgeCategoryRuntime.h"
#include "Data/Runtime/ConfigForgeFileRuntime.h"
#include "Data/User/ConfigPathProvider.h"
#include "Misc/ConfigForgeDeveloperSettings.h"


UConfigForgeSubsystem::UConfigForgeSubsystem() {}

#pragma region Get

const UConfigForgeDeveloperSettings* UConfigForgeSubsystem::GetSettings() const
{
	return GetDefault<UConfigForgeDeveloperSettings>();
}

TSoftObjectPtr<UConfigForgeSetup> UConfigForgeSubsystem::GetSetupAsset() const
{
	return GetSettings()->ConfigSetup;
}

bool UConfigForgeSubsystem::GetFile(const FString& InFileName, FConfigForgeFileData& OutFileData) const
{
	OutFileData = {};

	TArray<FConfigForgeFileData> files;
	GetFiles(files);
	const int32 n = files.Num();
	for (int32 i = 0; i < n; ++i)
	{
		if (files[i].File != nullptr)
		{
			if (files[i].File->FileName == InFileName)
			{
				OutFileData = files[i];
				return true;
			}
		}
	}

	return false;
}

void UConfigForgeSubsystem::GetFiles(TArray<FConfigForgeFileData>& OutFiles) const
{
	GetFilesStatic(GetSetupAsset().LoadSynchronous(), OutFiles);
}

void UConfigForgeSubsystem::GetFilesStatic(UConfigForgeSetup* InSetupFile, TArray<FConfigForgeFileData>& OutFiles)
{
	OutFiles.Empty();

	if (InSetupFile == nullptr)
	{
		UE_LOG(LogConfigForge, Error, TEXT("%hs %d Setup asset is invalid. Please select asset in Project Settings -> Config Forge -> 'ConfigSetup'"),
			__FUNCTION__, __LINE__);
		return;
	}

	if (InSetupFile->Files.IsEmpty())
	{
		UE_LOG(LogConfigForge, Warning, TEXT("%hs %d Setup Asset has no files"),
			__FUNCTION__, __LINE__);
		return;
	}

	const TArray<FConfigForgeFileData>& arr = InSetupFile->Files;
	const int32 n = arr.Num();
	OutFiles.Reserve(n);
	for (int32 i = 0; i < n; ++i)
	{
		if (arr[i].File != nullptr)
		{
			OutFiles.Add(arr[i]);
		}
	}
}

void UConfigForgeSubsystem::GetFileNames(TArray<FString>& OutNames) const
{
	OutNames.Empty();
	UConfigForgeSetup* setup = GetSetupAsset().LoadSynchronous();
	if (setup == nullptr)
	{
		UE_LOG(LogConfigForge, Error, TEXT("%hs %d Setup asset is invalid. Please select asset in Project Settings -> Config Forge -> 'ConfigSetup'"),
			__FUNCTION__, __LINE__);
		return;
	}

	if (setup->Files.IsEmpty())
	{
		UE_LOG(LogConfigForge, Warning, TEXT("%hs %d Setup Asset has no files"),
			__FUNCTION__, __LINE__);
		return;
	}

	const TArray<FConfigForgeFileData>& arr = setup->Files;
	const int32 n = arr.Num();
	OutNames.Reserve(n);
	for (int32 i = 0; i < n; ++i)
	{
		if (arr[i].File == nullptr)
		{
			UE_LOG(LogConfigForge, Warning, TEXT("%hs %d Setup Asset file[%d] is null"),
				__FUNCTION__, __LINE__, i);
			continue;
		}
		OutNames.Add(arr[i].File->FileName);
	}
}


void UConfigForgeSubsystem::GetFileCategoriesByName(const FString& InFileName, TArray<FName>& OutCategories)
{
	OutCategories.Empty();

	FConfigForgeFileData fileData;
	if (!GetFile(InFileName, fileData))
	{
		UE_LOG(LogConfigForge, Error, TEXT("%hs %d Setup Asset has no file '%s'"),
			__FUNCTION__, __LINE__, *InFileName);
		return;
	}
	GetFileCategories(fileData, OutCategories);
}

void UConfigForgeSubsystem::GetFileCategories(const FConfigForgeFileData& InFileData, TArray<FName>& OutCategories)
{
	OutCategories.Empty();
	if (InFileData.File == nullptr)
	{
		UE_LOG(LogConfigForge, Error, TEXT("%hs %d invalid file"),
			__FUNCTION__, __LINE__);
		return;;
	}

	const TArray<TObjectPtr<UConfigForgeCategory>>& arr = InFileData.File->Categories;
	if (arr.IsEmpty())
	{
		UE_LOG(LogConfigForge, Warning, TEXT("%hs %d file '%s' has no categories"),
			__FUNCTION__, __LINE__, *InFileData.File->FileName);
		return;
	}
	const int32 n = arr.Num();
	OutCategories.Reserve(n);
	for (int32 i = 0; i < n; ++i)
	{
		if (arr[i] != nullptr)
		{
			OutCategories.Add(arr[i]->Name);
		}
	}
}

void UConfigForgeSubsystem::GetCategoryProperties(const FString& InFileName, const FName& InCategoryName, TArray<UConfigValueObject*>& OutProperties)
{
	OutProperties.Empty();

	FConfigForgeFileData fileData;
	if (!GetFile(InFileName, fileData))
	{
		UE_LOG(LogConfigForge, Error, TEXT("%hs %d file setup has no file '%s'"),
			__FUNCTION__, __LINE__, *InFileName);
		return;
	}

	if (fileData.File == nullptr)
		return;

	UConfigForgeCategory* category;
	if (!fileData.File->GetCategory(InCategoryName, category))
	{
		UE_LOG(LogConfigForge, Error, TEXT("%hs %d file '%s' has no category '%s'"),
			__FUNCTION__, __LINE__, *InFileName, *InCategoryName.ToString());
		return;
	}

	if (category == nullptr)
		return;

	const TArray<UConfigValueObject*>& arr = category->Fields;
	const int32 n = category->Fields.Num();
	OutProperties.Reserve(n);
	for (int32 i = 0; i < n; ++i)
	{
		if (arr[i] != nullptr)
		{
			OutProperties.Add(arr[i]);
		}
	}
}


#pragma endregion

#pragma region Runtme

bool UConfigForgeSubsystem::GetRuntimeFile(const FGuid& InUniqueFileId, UConfigForgeFileRuntime*& OutRuntimeFile) const
{
	OutRuntimeFile = nullptr;

	const TObjectPtr<UConfigForgeFileRuntime>* itemPtr = RuntimeFiles.Find(InUniqueFileId);
	if (itemPtr == nullptr)
		return false;

	const TObjectPtr<UConfigForgeFileRuntime> item = *itemPtr;
	if (item == nullptr)
		return false;

	// Additional validity check - ensures data was properly initialized/read
	if (!item->IsValidData())
		return false;

	OutRuntimeFile = item.Get();
	return true;
}

void UConfigForgeSubsystem::GetAllRuntimeFiles(TArray<UConfigForgeFileRuntime*>& OutRuntimeFiles) const
{
	TArray<TObjectPtr<UConfigForgeFileRuntime>> values;
	RuntimeFiles.GenerateValueArray(values);
	const int32 n = values.Num();
	OutRuntimeFiles.Empty();
	OutRuntimeFiles.Reserve(n);
	for (int32 i = 0; i < n; ++i)
	{
		OutRuntimeFiles.Add(values[i].Get());
	}
}

bool UConfigForgeSubsystem::GetRuntimeCategories(const UConfigForgeFileRuntime* InConfigFile, TArray<UConfigForgeCategoryRuntime*>& OutCategories) const
{
	if (!InConfigFile)
		return false;

	OutCategories.Empty();
	InConfigFile->GetCategories(OutCategories);

	return OutCategories.Num() > 0;
}

bool UConfigForgeSubsystem::GetRuntimeCategories_ID(const FGuid& InFileId, TArray<UConfigForgeCategoryRuntime*>& OutCategories) const
{
	UConfigForgeFileRuntime* runtimeFile;
	if (!GetRuntimeFile(InFileId, runtimeFile))
		return false;

	if (runtimeFile == nullptr)
		return false;

	return GetRuntimeCategories(runtimeFile, OutCategories);
}

bool UConfigForgeSubsystem::GetRuntimeCategory(const UConfigForgeFileRuntime* InConfigFile, const FName& InCategoryName, UConfigForgeCategoryRuntime*& OutCategory) const
{
	if (!InConfigFile)
		return false;
	return InConfigFile->GetCategory(InCategoryName, OutCategory);
}

bool UConfigForgeSubsystem::GetRuntimeCategory_ID(const FGuid& InFileId, const FName& InCategoryName, UConfigForgeCategoryRuntime*& OutCategory) const
{
	UConfigForgeFileRuntime* runtimeFile;
	if (!GetRuntimeFile(InFileId, runtimeFile))
		return false;

	if (runtimeFile == nullptr)
		return false;

	return GetRuntimeCategory(runtimeFile, InCategoryName, OutCategory);
}

bool UConfigForgeSubsystem::GetRuntimeField(const UConfigForgeCategoryRuntime* InRuntimeCategory, const FString& InKey, UConfigValueObjectRuntime*& OutField) const
{
	if (InRuntimeCategory == nullptr)
		return false;

	return InRuntimeCategory->GetField(InKey, OutField);
}

bool UConfigForgeSubsystem::GetRuntimeField_File(const UConfigForgeFileRuntime* InConfigFile, const FName& InCategoryName, const FString& InKey, UConfigValueObjectRuntime*& OutField) const
{
	if (InConfigFile == nullptr)
		return false;

	UConfigForgeCategoryRuntime* category;
	if (!GetRuntimeCategory(InConfigFile, InCategoryName, category))
		return false;

	return GetRuntimeField(category, InKey, OutField);
}

bool UConfigForgeSubsystem::GetRuntimeField_ID(const FGuid& InFileID, const FName& InCategoryName, const FString& InKey, UConfigValueObjectRuntime*& OutField) const
{
	UConfigForgeFileRuntime* file;
	if (!GetRuntimeFile(InFileID, file))
		return false;

	UConfigForgeCategoryRuntime* category;
	if (!GetRuntimeCategory(file, InCategoryName, category))
		return false;

	return GetRuntimeField(category, InKey, OutField);
}

bool UConfigForgeSubsystem::GetRuntimeFields(const UConfigForgeCategoryRuntime* InRuntimeCategory, TArray<UConfigValueObjectRuntime*>& OutFields) const
{
	if (InRuntimeCategory == nullptr)
		return false;

	InRuntimeCategory->BP_GetFields(OutFields);
	return true;
}

bool UConfigForgeSubsystem::GetRuntimeFields_File(const UConfigForgeFileRuntime* InConfigFile, const FName& InCategoryName, TArray<UConfigValueObjectRuntime*>& OutFields) const
{
	if (InConfigFile == nullptr)
		return false;

	UConfigForgeCategoryRuntime* category;
	if (!GetRuntimeCategory(InConfigFile, InCategoryName, category))
		return false;

	return GetRuntimeFields(category, OutFields);
}

bool UConfigForgeSubsystem::GetRuntimeFields_ID(const FGuid& InFileID, const FName& InCategoryName, TArray<UConfigValueObjectRuntime*>& OutFields) const
{
	UConfigForgeFileRuntime* file;
	if (!GetRuntimeFile(InFileID, file))
		return false;

	UConfigForgeCategoryRuntime* category;
	if (!GetRuntimeCategory(file, InCategoryName, category))
		return false;

	return GetRuntimeFields(category, OutFields);
}

bool UConfigForgeSubsystem::GetRuntimeField_Full(
	const FGuid& InFiledId,
	const FName& InCategoryName,
	const FString& InFieldName,
	UConfigForgeFileRuntime*& OutFile,
	UConfigForgeCategoryRuntime*& OutCategory,
	UConfigValueObjectRuntime*& OutField) const
{
	OutFile = nullptr;
	OutCategory = nullptr;
	OutField = nullptr;

	UConfigForgeFileRuntime* file;
	if (!GetRuntimeFile(InFiledId, file))
		return false;

	UConfigForgeCategoryRuntime* category;
	if (!GetRuntimeCategory(file, InCategoryName, category))
		return false;

	UConfigValueObjectRuntime* field;
	if (!GetRuntimeField(category, InFieldName, field))
		return false;

	OutFile = file;
	OutCategory = category;
	OutField = field;

	return IsValid(OutFile) && IsValid(OutCategory) && OutField;
}

#pragma endregion

#pragma region IO

bool UConfigForgeSubsystem::ReadFileInternal(TSubclassOf<UConfigPathProvider> InPathProviderClass, const FGuid& InId, UConfigForgeFile* InTemplate, UConfigForgeFileRuntime*& OutFile)
{
	OutFile = nullptr;
	if (!InTemplate)
		return false;

	if (!InPathProviderClass)
		return false;

	UConfigPathProvider* pathProvider = NewObject<UConfigPathProvider>(this, InPathProviderClass);
	if (!pathProvider)
		return false;

	const FString directoryPath = pathProvider->GetPath();
	IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();

	UE_LOG(LogConfigForge, Log, TEXT("%hs %s Reading file '%s'..."), __FUNCTION__,
		*GetNameSafe(pathProvider->GetClass()), *directoryPath);

	if (!platformFile.DirectoryExists(*directoryPath))
	{
		UE_LOG(LogConfigForge, Warning, TEXT("%hs Path provider '%s' directory '%s' doesnt exist, trying to create it..."), __FUNCTION__,
			*GetNameSafe(pathProvider->GetClass()), *directoryPath);
		const bool bCreated = platformFile.CreateDirectoryTree(*directoryPath);
		if (!bCreated)
		{
			UE_LOG(LogConfigForge, Error, TEXT("%hs Path provider '%s' failed to create directory '%s'"), __FUNCTION__,
				*GetNameSafe(pathProvider->GetClass()),
				*directoryPath);
			pathProvider->ConditionalBeginDestroy();
			pathProvider = nullptr;
			return false;
		}
	}

	const FString fileName = InTemplate->FileName;
	FString filePath = directoryPath / fileName;
	if (FPaths::IsRelative(filePath))
	{
		filePath = FPaths::ConvertRelativePathToFull(filePath);
	}

	UConfigForgeFileRuntime* runtimeFile = NewObject<UConfigForgeFileRuntime>(this);

	runtimeFile->SetPathProvider(pathProvider);
	runtimeFile->SetFileAsset(InTemplate);
	runtimeFile->SetFileName(fileName);
	runtimeFile->SetFullPath(filePath);
	runtimeFile->SetFileID(InId);

	// Put default values
	runtimeFile->InitDefaultData();

	// Replace any previously loaded version of the same file
	if (RuntimeFiles.Contains(InId))
	{
		TObjectPtr<UConfigForgeFileRuntime>& filePtr = RuntimeFiles[InId];

		// Properly clean up old instance
		if (filePtr != nullptr)
		{
			filePtr->ConditionalBeginDestroy();
		}
		RuntimeFiles[InId] = nullptr;
		RuntimeFiles.Remove(InId);
	}

	// If file doesn't exist on disk, create it with defaults
	if (!platformFile.FileExists(*filePath))
	{
		UE_LOG(LogConfigForge, Warning, TEXT("%hs Path provider '%s', file '%s' doesnt exist, trying to create default file"), __FUNCTION__,
			*GetNameSafe(pathProvider->GetClass()), *filePath);

		// Create default file
		runtimeFile->SaveTo(filePath);
	}

	UE_LOG(LogConfigForge, Log, TEXT("%hs %s Reading file '%s'..."), __FUNCTION__,
		*GetNameSafe(pathProvider->GetClass()), *filePath);

	// Attempt to read; on failure, overwrite with current (default) data
	if (runtimeFile->ReadFrom(filePath))
	{
		UE_LOG(LogConfigForge, Log, TEXT("%hs %s File '%s has been reed successfully!"), __FUNCTION__,
			*GetNameSafe(pathProvider->GetClass()), *filePath);
	}
	else
	{
		UE_LOG(LogConfigForge, Warning, TEXT("%hs %s File '%s failed to read correctly; trying to save to make default view"), __FUNCTION__,
			*GetNameSafe(pathProvider->GetClass()), *filePath);
		// Write everything else to file
		runtimeFile->SaveTo(filePath);
	}

	// Store for later retrieval
	RuntimeFiles.Add(InId, runtimeFile);

	OutFile = runtimeFile;

	return true;
}

bool UConfigForgeSubsystem::WriteFileInternal(UConfigForgeFileRuntime* InFile)
{
	if (!IsValid(InFile))
		return false;

	if (!InFile->IsValidData())
		return false;

	UConfigPathProvider* pathProvider = InFile->GetPathProvider();
	if (!pathProvider)
		return false;

	const FString directoryPath = pathProvider->GetPath();
	IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();

	UE_LOG(LogConfigForge, Log, TEXT("%hs %s Reading file '%s'..."), __FUNCTION__,
		*GetNameSafe(pathProvider->GetClass()), *directoryPath);

	// Ensure directory exist
	if (!platformFile.DirectoryExists(*directoryPath))
	{
		UE_LOG(LogConfigForge, Warning, TEXT("%hs Path provider '%s' directory '%s' doesnt exist, trying to create it..."), __FUNCTION__,
			*GetNameSafe(pathProvider->GetClass()), *directoryPath);
		const bool bCreated = platformFile.CreateDirectoryTree(*directoryPath);
		if (!bCreated)
		{
			UE_LOG(LogConfigForge, Error, TEXT("%hs Path provider '%s' failed to create directory '%s'"), __FUNCTION__,
				*GetNameSafe(pathProvider->GetClass()),
				*directoryPath);
			return false;
		}
	}

	UConfigForgeFile* asset = InFile->GetFileAsset();
	if (!asset)
		return false;

	const FString fileName = asset->FileName;
	FString filePath = directoryPath / fileName;
	if (FPaths::IsRelative(filePath))
	{
		filePath = FPaths::ConvertRelativePathToFull(filePath);
	}

	// Ensure file exists
	if (!platformFile.FileExists(*filePath))
	{
		UE_LOG(LogConfigForge, Warning, TEXT("%hs Path provider '%s' file '%s' doesnt exist, trying to create it..."), __FUNCTION__,
			*GetNameSafe(pathProvider->GetClass()), *filePath);

		const bool bCreated = FFileHelper::SaveStringToFile(FString(TEXT("")), *filePath);
		if (!bCreated)
		{
			UE_LOG(LogConfigForge, Error, TEXT("%hs Path provider '%s' failed to create file '%s'"), __FUNCTION__,
				*GetNameSafe(pathProvider->GetClass()),
				*filePath);
			return false;
		}
	}

	return InFile->SaveTo(filePath);
}

bool UConfigForgeSubsystem::LoadAllFilesInternal(const TArray<FConfigForgeFileData>& InDataArr, TArray<UConfigForgeFileRuntime*>& OutFiles)
{
	OutFiles.Empty();
	bool bSuccess = true;

	OutFiles.Reserve(InDataArr.Num());
	for (const FConfigForgeFileData& fd : InDataArr)
	{
		UConfigForgeFileRuntime* runtimeFile;
		bSuccess &= ReadFileInternal(fd.PathProvider, fd.ID(), fd.File.Get(), runtimeFile);
		if (runtimeFile)
		{
			OutFiles.Add(runtimeFile);
		}
	}

	return bSuccess;
}

bool UConfigForgeSubsystem::WriteAllFilesInternal(const TArray<UConfigForgeFileRuntime*>& InFiles)
{
	bool bSuccess = true;

	for (int32 i = 0; i < InFiles.Num(); ++i)
	{
		if (InFiles[i])
		{
			bSuccess &= WriteFileInternal(InFiles[i]);
		}
	}
	return bSuccess;
}

bool UConfigForgeSubsystem::LoadSingleFile(const FConfigForgeFileData& InFileData, UConfigForgeFileRuntime*& OutFile)
{
	OutFile = nullptr;

	// Prevent reentrancy - only one file operation at a time
	if (bOperatingFiles)
		return false;

	bOperatingFiles = true;

	bool bLoaded = ReadFileInternal(InFileData.PathProvider, InFileData.ID(), InFileData.File.Get(), OutFile);

	bOperatingFiles = false;

	OnFileLoaded.Broadcast(OutFile);

	return bLoaded;
}

void UConfigForgeSubsystem::LoadSingleFileAsync(const FConfigForgeFileData& InFileData, FLoadForgeFileDelegate Callback)
{
	// Prevent reentrancy - only one file operation at a time
	if (bOperatingFiles)
	{
		Callback.ExecuteIfBound(false, nullptr);
		return;
	}

	bOperatingFiles = true;

	Async(EAsyncExecution::TaskGraph, [this, InFileData, Callback]() {
		UConfigForgeFileRuntime* runtimeFile;
		const bool bLoaded = ReadFileInternal(InFileData.PathProvider, InFileData.ID(), InFileData.File.Get(), runtimeFile);
		bOperatingFiles = false;
		if (bLoaded && runtimeFile != nullptr)
		{
			AsyncTask(ENamedThreads::GameThread, [this, runtimeFile, Callback]() {
				OnFileLoaded.Broadcast(runtimeFile);
				Callback.ExecuteIfBound(true, runtimeFile);
			});
		}
		else
		{
			AsyncTask(ENamedThreads::GameThread, [this, Callback]() {
				Callback.ExecuteIfBound(false, nullptr);
			});
		}
	});
}

bool UConfigForgeSubsystem::SaveSingleFile(const FGuid& InFileUniqueID)
{
	// Prevent reentrancy - only one file operation at a time
	if (bOperatingFiles)
		return false;

	UConfigForgeFileRuntime* runtimeFile;
	if (!GetRuntimeFile(InFileUniqueID, runtimeFile))
		return false;

	bOperatingFiles = true;

	const bool bWrote = WriteFileInternal(runtimeFile);

	bOperatingFiles = false;

	OnFileSaved.Broadcast(runtimeFile);

	return bWrote;
}

void UConfigForgeSubsystem::SaveSingleFileAsync(const FGuid& InFileUniqueID, FSaveForgeFileDelegate Callback)
{
	// Prevent reentrancy - only one file operation at a time
	if (bOperatingFiles)
	{
		Callback.ExecuteIfBound(false);
		return;
	}

	UConfigForgeFileRuntime* runtimeFile;
	if (!GetRuntimeFile(InFileUniqueID, runtimeFile))
	{
		Callback.ExecuteIfBound(false);
		return;
	}

	bOperatingFiles = true;

	Async(EAsyncExecution::TaskGraph, [this, runtimeFile, Callback]() {
		const bool bWrote = WriteFileInternal(runtimeFile);
		bOperatingFiles = false;
		AsyncTask(ENamedThreads::GameThread, [this, bWrote, Callback, runtimeFile]() {
			OnFileSaved.Broadcast(runtimeFile);
			Callback.ExecuteIfBound(bWrote);
		});
	});
}

bool UConfigForgeSubsystem::LoadAllFiles(TArray<UConfigForgeFileRuntime*>& OutFiles)
{
	OutFiles.Empty();

	if (bOperatingFiles)
		return false;

	UConfigForgeSetup* setup = GetSettings()->ConfigSetup.LoadSynchronous();
	if (!setup)
		return false;

	bOperatingFiles = true;

	const bool bSuccess = LoadAllFilesInternal(setup->Files, OutFiles);

	bOperatingFiles = false;

	for (int32 i = 0; i < OutFiles.Num(); ++i)
	{
		OnFileLoaded.Broadcast(OutFiles[i]);
	}
	OnAllFilesLoaded.Broadcast();

	return bSuccess;
}

void UConfigForgeSubsystem::LoadAllFilesAsync(FLoadAllForgeFileDelegate Callback)
{
	if (bOperatingFiles)
	{
		Callback.ExecuteIfBound(false, {});
		return;
	}

	UConfigForgeSetup* setup = GetSettings()->ConfigSetup.LoadSynchronous();
	if (!setup)
	{
		Callback.ExecuteIfBound(false, {});
		return;
	}

	TArray<FConfigForgeFileData> arr = setup->Files;

	bOperatingFiles = true;
	Async(EAsyncExecution::TaskGraph, [this, arr, Callback]() {
		TArray<UConfigForgeFileRuntime*> res;
		const bool bSuccess = LoadAllFilesInternal(arr, res);
		bOperatingFiles = false;
		AsyncTask(ENamedThreads::GameThread, [this, res, bSuccess, Callback]() {
			for (int32 i = 0; i < res.Num(); ++i)
			{
				OnFileLoaded.Broadcast(res[i]);
			}
			OnAllFilesLoaded.Broadcast();
			Callback.ExecuteIfBound(bSuccess, res);
		});
	});
}

bool UConfigForgeSubsystem::LoadSelectedFiles(const TArray<FConfigForgeFileData>& InFiles, TArray<UConfigForgeFileRuntime*>& OutFiles)
{
	OutFiles.Empty();

	if (bOperatingFiles)
		return false;

	bOperatingFiles = true;
	const bool bSuccess = LoadAllFilesInternal(InFiles, OutFiles);
	bOperatingFiles = false;

	const int32 n = OutFiles.Num();
	for (int32 i = 0; i < n; ++i)
	{
		OnFileLoaded.Broadcast(OutFiles[i]);
	}

	return bSuccess;
}

void UConfigForgeSubsystem::LoadSelectedFilesAsync(const TArray<FConfigForgeFileData>& InFiles, FLoadAllForgeFileDelegate Callback)
{
	if (bOperatingFiles)
	{
		Callback.ExecuteIfBound(false, {});
		return;
	}

	TArray<FConfigForgeFileData> arr = InFiles;
	bOperatingFiles = true;

	Async(EAsyncExecution::TaskGraph, [this, arr, Callback]() {
		TArray<UConfigForgeFileRuntime*> res;
		const bool bSuccess = LoadAllFilesInternal(arr, res);
		bOperatingFiles = false;
		AsyncTask(ENamedThreads::GameThread, [this, res, bSuccess, Callback]() {
			const int32 n = res.Num();
			for (int32 i = 0; i < n; ++i)
			{
				OnFileLoaded.Broadcast(res[i]);
			}
			Callback.ExecuteIfBound(bSuccess, res);
		});
	});
}

bool UConfigForgeSubsystem::SaveAllFiles()
{
	if (bOperatingFiles)
		return false;

	TArray<UConfigForgeFileRuntime*> arr;
	GetAllRuntimeFiles(arr);

	if (arr.Num() == 0)
	{
		return false;
	}

	bOperatingFiles = true;
	bool bSuccess = WriteAllFilesInternal(arr);
	bOperatingFiles = false;

	for (int i = 0; i < arr.Num(); ++i)
	{
		OnFileSaved.Broadcast(arr[i]);
	}

	OnAllFilesSaved.Broadcast();
	return bSuccess;
}

void UConfigForgeSubsystem::SaveAllFilesAsync(FSaveAllForgeFileDelegate Callback)
{
	if (bOperatingFiles)
	{
		Callback.ExecuteIfBound(false);
		return;
	}

	TArray<UConfigForgeFileRuntime*> arr;
	GetAllRuntimeFiles(arr);

	if (arr.Num() == 0)
	{
		Callback.ExecuteIfBound(false);
		return;
	}

	bOperatingFiles = true;
	Async(EAsyncExecution::TaskGraph, [this, arr, Callback]() {
		bool bSuccess = WriteAllFilesInternal(arr);
		bOperatingFiles = false;
		AsyncTask(ENamedThreads::GameThread, [this,arr, bSuccess, Callback]() {
			for (int i = 0; i < arr.Num(); ++i)
			{
				OnFileSaved.Broadcast(arr[i]);
			}
			OnAllFilesSaved.Broadcast();
			Callback.ExecuteIfBound(bSuccess);
		});
	});

}

bool UConfigForgeSubsystem::SaveSelectedFiles(const TArray<FGuid>& InFiles)
{
	if (InFiles.Num() == 0)
		return false;

	if (bOperatingFiles)
		return false;

	TArray<UConfigForgeFileRuntime*> files;
	int32 n = InFiles.Num();
	files.Reserve(n);
	for (int32 i = 0; i < n; ++i)
	{
		UConfigForgeFileRuntime* file;
		if (GetRuntimeFile(InFiles[i], file))
		{
			files.Add(file);
		}
	}

	if (files.Num() == 0)
		return false;

	bOperatingFiles = true;
	const bool bSuccess = WriteAllFilesInternal(files);
	bOperatingFiles = false;

	n = files.Num();
	for (int i = 0; i < n; ++i)
	{
		OnFileSaved.Broadcast(files[i]);
	}

	return bSuccess;
}

void UConfigForgeSubsystem::SaveSelectedFiles(const TArray<FGuid>& InFiles, FLoadAllForgeFileDelegate Callback)
{
	if (InFiles.Num() == 0)
	{
		Callback.ExecuteIfBound(false, {});
		return;
	}

	if (bOperatingFiles)
	{
		Callback.ExecuteIfBound(false, {});
		return;
	}

	TArray<UConfigForgeFileRuntime*> files;
	int32 n = InFiles.Num();
	files.Reserve(n);
	for (int32 i = 0; i < n; ++i)
	{
		UConfigForgeFileRuntime* file;
		if (GetRuntimeFile(InFiles[i], file))
		{
			files.Add(file);
		}
	}

	if (files.Num() == 0)
	{
		Callback.ExecuteIfBound(false, {});
		return;
	}

	bOperatingFiles = true;
	Async(EAsyncExecution::TaskGraph, [this, files, Callback]() {
		const bool bSuccess = WriteAllFilesInternal(files);
		AsyncTask(ENamedThreads::GameThread, [this, bSuccess, files, Callback]() {
			bOperatingFiles = false;

			const int32 n = files.Num();
			for (int i = 0; i < n; ++i)
			{
				OnFileSaved.Broadcast(files[i]);
			}

			Callback.ExecuteIfBound(bSuccess, files);
		});
	});

}

#pragma endregion