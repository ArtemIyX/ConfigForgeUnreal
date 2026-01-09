// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "Misc/DynamicValue.h"
#include "UObject/Object.h"
#include "ConfigValueObjectRuntime.generated.h"

class UConfigForgeCategoryRuntime;
class FConfigForgeIniFile;
class UConfigValueObject;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class CONFIGFORGE_API UConfigValueObjectRuntime : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString Key;

	// Read only
	UPROPERTY()
	TWeakObjectPtr<UConfigValueObject> Asset;

	UPROPERTY()
	FDynamicValue DynamicValue;

	UPROPERTY()
	TWeakObjectPtr<UConfigForgeCategoryRuntime> Category;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigValue")
	FORCEINLINE UConfigForgeCategoryRuntime* GetCategory() const { return Category.Get(); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigValue")
	FORCEINLINE FString GetKey() const { return Key; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigValue")
	FORCEINLINE UConfigValueObject* GetAsset() const { return Asset.Get(); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigValue")
	FORCEINLINE FDynamicValue GetDynamicValue() const { return DynamicValue; }

	UFUNCTION(BlueprintCallable, Category="ConfigValue")
	virtual void SetDynamicValue(const FDynamicValue& InValue);

public:
	virtual void SetToFile(const TSharedPtr<FConfigForgeIniFile>& InFilePtr, const FString& InSection);
	virtual bool GetFromFile(const TSharedPtr<FConfigForgeIniFile>& InFilePtr, const FString& InSection);
	virtual void ApplyAsset(const TWeakObjectPtr<UConfigValueObject>& InAsset);
};