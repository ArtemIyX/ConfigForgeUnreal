// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.


#include "Data/Asset/Value/ConfigValueObject.h"

void UConfigValueObject::SetToFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile, const FString& InSection,
	const FDynamicValue& InDynamicValue)
{
	// Implement in child
}

bool UConfigValueObject::GetFromFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile, const FString& InSection,
	FDynamicValue& InDynamicValue)
{
	// Implement in child
	return false;
}

void UConfigValueObject::SetDefaultValue(FDynamicValue& InDynamicValue)
{
	// Implement in child
}

uint32 UConfigValueObject::MakeHash() const
{
	uint32 keyHash = GetTypeHash(Key);
	return keyHash;
}