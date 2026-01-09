// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.


#include "Data/Asset/ConfigForgeCategory.h"

#include "Data/Asset/Value/ConfigValueObject.h"

UConfigForgeCategory::UConfigForgeCategory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {}

uint32 UConfigForgeCategory::MakeHash() const
{
	uint32 hash = GetTypeHash(FString(TEXT("ConfigForgeCategory")));
	hash = HashCombine(hash, GetTypeHash(Name));
	hash = HashCombine(hash, GetTypeHash(Fields.Num()));
	for (int32 i = 0; i < Fields.Num(); ++i)
	{
		if (Fields[i])
		{
			hash = HashCombine(hash, Fields[i]->MakeHash());
		}
	}
	return hash;
}