// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.


#include "Data/Runtime/ConfigForgeCategoryRuntime.h"

#include "Data/Asset/ConfigForgeCategory.h"
#include "Data/Asset/Value/ConfigValueObject.h"
#include "Data/Runtime/ConfigValueObjectRuntime.h"

void UConfigForgeCategoryRuntime::GetFields(TArray<TWeakObjectPtr<UConfigValueObjectRuntime>>& OutResult) const
{
	OutResult.Empty();
	const int32 n = FieldsRuntime.Num();
	OutResult.Reserve(n);
	for (const TPair<FString, TObjectPtr<UConfigValueObjectRuntime>>& pair : FieldsRuntime)
	{
		if (pair.Value)
		{
			OutResult.Add(pair.Value);
		}
	}
}

void UConfigForgeCategoryRuntime::BP_GetFields(TArray<UConfigValueObjectRuntime*>& OutResult) const
{
	OutResult.Empty();
	const int32 n = FieldsRuntime.Num();
	OutResult.Reserve(n);
	for (const TPair<FString, TObjectPtr<UConfigValueObjectRuntime>>& pair : FieldsRuntime)
	{
		if (pair.Value)
		{
			OutResult.Add(pair.Value);
		}
	}
}

bool UConfigForgeCategoryRuntime::GetField(const FString& InKey, UConfigValueObjectRuntime*& OutField) const
{
	const TObjectPtr<UConfigValueObjectRuntime>* itemPtr = FieldsRuntime.Find(InKey);
	if (itemPtr == nullptr)
		return false;

	OutField = *itemPtr;
	return IsValid(OutField);
}

void UConfigForgeCategoryRuntime::InitData(UConfigForgeCategory* InCategoryAsset)
{
	FieldsRuntime.Empty();
	CategoryName = InCategoryAsset->Name;
	CategoryAsset = InCategoryAsset;

	const int32 n = InCategoryAsset->Fields.Num();
	FieldsRuntime.Reserve(n);
	for (int32 i = 0; i < n; ++i)
	{
		UConfigValueObject* fieldAsset = InCategoryAsset->Fields[i];
		if (fieldAsset)
		{
			UConfigValueObjectRuntime* runtimeFieldObject = NewObject<UConfigValueObjectRuntime>(this);
			runtimeFieldObject->Key = fieldAsset->Key;
			runtimeFieldObject->Category = this;
			// Set asset, set default value
			runtimeFieldObject->ApplyAsset(fieldAsset);

			FieldsRuntime.Add(fieldAsset->Key, TObjectPtr<UConfigValueObjectRuntime>(runtimeFieldObject));
		}
	}
}

void UConfigForgeCategoryRuntime::BeginDestroy()
{
	const int32 n = FieldsRuntime.Num();
	for (TPair<FString, TObjectPtr<UConfigValueObjectRuntime>> pair : FieldsRuntime)
	{
		if (pair.Value)
		{
			pair.Value->ConditionalBeginDestroy();
		}
	}
	FieldsRuntime.Empty();
	Super::BeginDestroy();

}