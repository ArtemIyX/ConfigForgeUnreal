// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.


#include "Data/ConfigForgeFileRuntime.h"

#include "Data/ConfigForgeCategoryRuntime.h"
#include "Data/ConfigPathProvider.h"
#include "Data/Value/ConfigValueObjectRuntime.h"
#include "Misc/ConfigForgeIniFile.h"

UConfigForgeFileRuntime::UConfigForgeFileRuntime() {}


bool UConfigForgeFileRuntime::IsValidData() const
{
	return FileAsset.IsValid() &&
		PathProvider != nullptr
		&& !FullPath.IsEmpty()
		&& !FileName.IsEmpty();
}

void UConfigForgeFileRuntime::InitDefaultData()
{
	if (!IsValidData())
		return;

	CategoriesRuntime.Empty();

	const int32 n = FileAsset->Categories.Num();
	CategoriesRuntime.Reserve(n);

	for (int32 i = 0; i < n; ++i)
	{
		if (FileAsset->Categories[i])
		{
			UConfigForgeCategoryRuntime* runtimeCategory = NewObject<UConfigForgeCategoryRuntime>(this);
			runtimeCategory->InitData(FileAsset->Categories[i]);
			CategoriesRuntime.Add(runtimeCategory);
		}
	}
}

void UConfigForgeFileRuntime::BeginDestroy()
{
	FileAsset.Reset();
	if (PathProvider)
	{
		PathProvider->ConditionalBeginDestroy();
		PathProvider = nullptr;
	}
	const int32 n = CategoriesRuntime.Num();
	for (int32 i = 0; i < n; i++)
	{
		if (CategoriesRuntime[i])
		{
			CategoriesRuntime[i]->ConditionalBeginDestroy();
		}
		CategoriesRuntime[i] = nullptr;
	}
	CategoriesRuntime.Empty();
	UObject::BeginDestroy();
}


bool UConfigForgeFileRuntime::SaveTo(const FString& InPath)
{
	if (!IsValidData())
		return false;

	TSharedPtr<FConfigForgeIniFile> file = MakeShareable(new FConfigForgeIniFile(InPath, false));

	// Just create FConfigObject instance, even if file exists
	file->Load();

	const int32 categoryNum = CategoriesRuntime.Num();
	for (int32 i = 0; i < categoryNum; ++i)
	{
		if (CategoriesRuntime[i])
		{
			const FName categoryName = CategoriesRuntime[i]->GetCategoryName();

			TArray<TWeakObjectPtr<UConfigValueObjectRuntime>> fieldRuntime;
			CategoriesRuntime[i]->GetFields(fieldRuntime);
			for (int32 j = 0; j < fieldRuntime.Num(); ++j)
			{
				if (fieldRuntime[j].IsValid())
				{
					// Set some data to file
					fieldRuntime[j]->SetToFile(file, categoryName.ToString());
				}
			}
		}
	}

	// Then save the data to the file
	const bool bSaved = file->Save();
	file.Reset();

	return bSaved;
}

bool UConfigForgeFileRuntime::ReadFrom(const FString& InPath)
{
	if (!IsValidData())
		return false;

	TSharedPtr<FConfigForgeIniFile> file = MakeShareable(new FConfigForgeIniFile(InPath, false));

	if (!file)
		return false;
	
	// Just create FConfigObject instance, even if file exists
	file->Load();

	const int32 categoryNum = CategoriesRuntime.Num();

	bool bSuccess = true;
	for (int32 i = 0; i < categoryNum; ++i)
	{
		if (CategoriesRuntime[i])
		{
			const FName categoryName = CategoriesRuntime[i]->GetCategoryName();

			TArray<TWeakObjectPtr<UConfigValueObjectRuntime>> fieldRuntime;
			CategoriesRuntime[i]->GetFields(fieldRuntime);
			for (int32 j = 0; j < fieldRuntime.Num(); ++j)
			{
				if (fieldRuntime[j].IsValid())
				{
					// READ from file and set to properties
					if (!fieldRuntime[j]->GetFromFile(file, categoryName.ToString()))
					{
						// If failed reading -> return false in future
						bSuccess = false;
					}
				}
			}
		}
	}
	

	file.Reset();
	return bSuccess;
}