// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "ConfigForgeCategory.h"
#include "ConfigForgeCategoryRuntime.generated.h"

class UConfigValueObjectRuntime;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class CONFIGFORGE_API UConfigForgeCategoryRuntime : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TWeakObjectPtr<UConfigForgeCategory> CategoryAsset;

	UPROPERTY()
	FName CategoryName;

	UPROPERTY()
	TArray<TObjectPtr<UConfigValueObjectRuntime>> FieldsRuntime;

public:
	UFUNCTION(BlueprintCallable, Category="Category")
	FORCEINLINE FName GetCategoryName() const { return CategoryName; }

	UFUNCTION(BlueprintCallable, Category="Category")
	FORCEINLINE UConfigForgeCategory* GetCategoryAsset() const { return CategoryAsset.Get(); }

	void GetFields(TArray<TWeakObjectPtr<UConfigValueObjectRuntime>>& OutResult) const;

	UFUNCTION(BlueprintCallable, Category="Category")
	void BP_GetFields(TArray<UConfigValueObjectRuntime*>& OutResult) const;
public:
	void InitData(UConfigForgeCategory* InCategoryAsset);

public:
	virtual void BeginDestroy() override;
};