// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.


#include "Data/ConfigForgeFile.h"

#include "Data/ConfigForgeCategory.h"

UConfigForgeFile::UConfigForgeFile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {}

bool UConfigForgeFile::GetCategory(const FName& InCategoryName, UConfigForgeCategory*& OutCategory) const
{
	OutCategory = nullptr;

	const int32 n = Categories.Num();
	for (int32 i = 0; i < n; ++i)
	{
		if (Categories[i] != nullptr)
		{
			if (Categories[i]->Name == InCategoryName)
			{
				OutCategory = Categories[i].Get();
				return true;
			}
		}
	}

	return false;
}

uint32 UConfigForgeFile::MakeHash() const
{
	uint32 hash = GetTypeHash(FString(TEXT("ConfigForgeFile")));
	hash = HashCombine(hash, GetTypeHash(FileName));
	const int32 n = Categories.Num();
	hash = HashCombine(hash, GetTypeHash(n));
	for (int32 i = 0; i < n; ++i)
	{
		if (Categories[i])
		{
			hash = HashCombine(hash, Categories[i]->MakeHash());
		}
	}
	return hash;
}