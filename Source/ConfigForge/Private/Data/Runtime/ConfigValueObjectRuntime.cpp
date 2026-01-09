// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.


#include "Data/Runtime/ConfigValueObjectRuntime.h"
#include "Data/Asset/Value/ConfigValueObject.h"

void UConfigValueObjectRuntime::SetDynamicValue(const FDynamicValue& InValue)
{
	this->DynamicValue = InValue;
}

void UConfigValueObjectRuntime::SetToFile(const TSharedPtr<FConfigForgeIniFile>& InFilePtr, const FString& InSection)
{
	if (!Asset.IsValid())
		return;

	if (!InFilePtr.IsValid())
		return;

	// Value must be set to write to file
	if (!DynamicValue.IsSet())
		return;

	Asset->SetToFile(InFilePtr, InSection, DynamicValue);
}

bool UConfigValueObjectRuntime::GetFromFile(const TSharedPtr<FConfigForgeIniFile>& InFilePtr, const FString& InSection)
{
	if (!Asset.IsValid())
		return false;

	if (!InFilePtr.IsValid())
		return false;

	return Asset->GetFromFile(InFilePtr, InSection, DynamicValue);
}

void UConfigValueObjectRuntime::ApplyAsset(const TWeakObjectPtr<UConfigValueObject>& InAsset)
{
	Asset = InAsset;
	Asset->SetDefaultValue(DynamicValue);
}