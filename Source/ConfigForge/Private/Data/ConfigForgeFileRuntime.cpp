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
			CategoriesRuntime.Add(runtimeCategory->GetCategoryName(), runtimeCategory);
		}
	}
}

bool UConfigForgeFileRuntime::GetCategory(const FName& InCategoryName, UConfigForgeCategoryRuntime*& OutCategory) const
{
	if (!CategoriesRuntime.Contains(InCategoryName))
		return false;

	OutCategory = CategoriesRuntime[InCategoryName];
	return IsValid(OutCategory);
}

void UConfigForgeFileRuntime::GetCategories(TArray<UConfigForgeCategoryRuntime*>& OutCategories) const
{
	OutCategories.Empty();
	OutCategories.Reserve(CategoriesRuntime.Num());
	for (const TPair<FName, TObjectPtr<UConfigForgeCategoryRuntime>>& pair : CategoriesRuntime)
	{
		OutCategories.Add(pair.Value.Get());
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

	TArray<FName> keys;
	const int32 n = keys.Num();
	CategoriesRuntime.GetKeys(keys);
	for (int32 i = 0; i < n; ++i)
	{
		TObjectPtr<UConfigForgeCategoryRuntime>* itemPtr = CategoriesRuntime.Find(keys[i]);
		if (itemPtr)
		{
			TObjectPtr<UConfigForgeCategoryRuntime> item = *itemPtr;
			if (item)
			{
				item->ConditionalBeginDestroy();
			}
		}
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

	for (const TPair<FName, TObjectPtr<UConfigForgeCategoryRuntime>>& pair : CategoriesRuntime)
	{
		if (TObjectPtr<UConfigForgeCategoryRuntime> ptr = pair.Value)
		{
			const FName categoryName = ptr->GetCategoryName();

			TArray<TWeakObjectPtr<UConfigValueObjectRuntime>> fieldRuntime;
			ptr->GetFields(fieldRuntime);
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
	for (const TPair<FName, TObjectPtr<UConfigForgeCategoryRuntime>>& pair : CategoriesRuntime)
	{
		if (TObjectPtr<UConfigForgeCategoryRuntime> ptr = pair.Value)
		{
			const FName categoryName = ptr->GetCategoryName();

			TArray<TWeakObjectPtr<UConfigValueObjectRuntime>> fieldRuntime;
			ptr->GetFields(fieldRuntime);
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