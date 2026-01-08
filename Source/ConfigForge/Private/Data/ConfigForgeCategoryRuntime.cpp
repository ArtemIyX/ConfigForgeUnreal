// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.


#include "Data/ConfigForgeCategoryRuntime.h"

#include "Data/Value/ConfigValueObject.h"
#include "Data/Value/ConfigValueObjectRuntime.h"

void UConfigForgeCategoryRuntime::GetFields(TArray<TWeakObjectPtr<UConfigValueObjectRuntime>>& OutResult) const
{
	OutResult.Empty();
	const int32 n = FieldsRuntime.Num();
	OutResult.Reserve(n);
	for (int32 i = 0; i < n; ++i)
	{
		if (FieldsRuntime[i])
		{
			OutResult.Add(TWeakObjectPtr<UConfigValueObjectRuntime>(FieldsRuntime[i].Get()));
		}
	}
}

void UConfigForgeCategoryRuntime::BP_GetFields(TArray<UConfigValueObjectRuntime*>& OutResult) const
{
	OutResult.Empty();
	const int32 n = FieldsRuntime.Num();
	OutResult.Reserve(n);
	for (int32 i = 0; i < n; ++i)
	{
		if (FieldsRuntime[i])
		{
			OutResult.Add(FieldsRuntime[i].Get());
		}
	}
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

			// Set asset, set default value
			runtimeFieldObject->ApplyAsset(fieldAsset);

			FieldsRuntime.Add(TObjectPtr<UConfigValueObjectRuntime>(runtimeFieldObject));
		}
	}
}

void UConfigForgeCategoryRuntime::BeginDestroy()
{
	const int32 n = FieldsRuntime.Num();
	for (int i = 0; i < n; ++i)
	{
		if (FieldsRuntime[i])
		{
			FieldsRuntime[i]->ConditionalBeginDestroy();
		}
		FieldsRuntime[i] = nullptr;
	}
	FieldsRuntime.Empty();
	Super::BeginDestroy();

}