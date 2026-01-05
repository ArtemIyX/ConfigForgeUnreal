// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.


#include "Subsystems/ConfigForgeSubsystem.h"

#include "ConfigForge.h"
#include "Misc/ConfigForgeDeveloperSettings.h"
#include "Data/ConfigForgeCategory.h"
#include "Data/ConfigForgeFile.h"
#include "Data/ConfigForgeFileRuntime.h"
#include "Data/ConfigForgeSetup.h"
#include "Data/ConfigPathProvider.h"
#include "Data/Value/ConfigValueObject.h"


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


bool UConfigForgeSubsystem::LoadFileInternal(TSubclassOf<UConfigPathProvider> InPathProviderClass, const FGuid& InId, UConfigForgeFile* InTemplate, UConfigForgeFileRuntime*& OutFile)
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

	UE_LOG(LogConfigForge, Log, TEXT("%hs %s Loading file '%s'..."), __FUNCTION__,
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

	// Remove previous object if necessary
	if (RuntimeFiles.Contains(InId))
	{
		TObjectPtr<UConfigForgeFileRuntime>& filePtr = RuntimeFiles[InId];
		if (filePtr != nullptr)
		{
			filePtr->ConditionalBeginDestroy();
		}
		RuntimeFiles[InId] = nullptr;
		RuntimeFiles.Remove(InId);
	}

	if (!platformFile.FileExists(*directoryPath))
	{
		UE_LOG(LogConfigForge, Warning, TEXT("%hs Path provider '%s', file '%s' doesnt exist, trying to create default file"), __FUNCTION__,
			*GetNameSafe(pathProvider->GetClass()), *filePath);

		// Create default file
		runtimeFile->SaveTo(filePath);
	}

	UE_LOG(LogConfigForge, Log, TEXT("%hs %s Reading file '%s'..."), __FUNCTION__,
		*GetNameSafe(pathProvider->GetClass()), *filePath);

	// Read all possible data from file
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

	// Store file object in map
	RuntimeFiles.Add(InId, runtimeFile);

	OutFile = runtimeFile;

	return true;
}

bool UConfigForgeSubsystem::LoadSingleFile(const FConfigForgeFileData& InFileData, UConfigForgeFileRuntime*& OutFile)
{
	OutFile = nullptr;

	if (bLoadingFiles)
		return false;

	bLoadingFiles = true;

	bool bLoaded = LoadFileInternal(InFileData.PathProvider, InFileData.ID(), InFileData.File.Get(), OutFile);

	bLoadingFiles = false;

	return bLoaded;
}

void UConfigForgeSubsystem::LoadSingleFileAsync(const FConfigForgeFileData& InFileData, FLoadForgeFileDelegate Callback)
{
	if (bLoadingFiles)
	{
		Callback.ExecuteIfBound(false, nullptr);
		return;
	}

	bLoadingFiles = true;

	Async(EAsyncExecution::TaskGraph, [this, InFileData, Callback]() {
		UConfigForgeFileRuntime* runtimeFile;
		const bool bLoaded = LoadFileInternal(InFileData.PathProvider, InFileData.ID(), InFileData.File.Get(), runtimeFile);
		bLoadingFiles = false;
		if (bLoaded && runtimeFile != nullptr)
		{
			AsyncTask(ENamedThreads::GameThread, [this, runtimeFile, Callback]() {
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