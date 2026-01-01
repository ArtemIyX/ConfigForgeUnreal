// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.


#include "Subsystems/ConfigForgeSubsystem.h"

#include "ConfigForge.h"
#include "Misc/ConfigForgeDeveloperSettings.h"
#include "Data/ConfigForgeCategory.h"
#include "Data/ConfigForgeFile.h"
#include "Data/ConfigForgeSetup.h"
#include "Data/Value/ConfigValueObject.h"

UConfigForgeSubsystem::UConfigForgeSubsystem() {}

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
	OutFiles.Empty();
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
	OutFiles.Reserve(n);
	for (int32 i = 0; i < n; ++i)
	{
		if (arr[i].File != nullptr)
		{
			OutFiles.Add(arr[i]);
		}
	}
	/*OutFiles = setup->Files;*/
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

	/*TArray<FConfigForgeFileData> files;
	GetFiles(files);
	const int32 n = files.Num();
	for (int32 i = 0; i < n; ++i)
	{
		if (files[i].File != nullptr)
		{
			if (files[i].File->FileName == InFileName)
			{
				
				return;
			}
		}
	}*/
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