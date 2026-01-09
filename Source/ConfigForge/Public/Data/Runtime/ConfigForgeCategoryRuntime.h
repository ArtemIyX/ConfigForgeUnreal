// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.

#pragma once

#include "CoreMinimal.h"

#include "ConfigForgeCategoryRuntime.generated.h"

class UConfigForgeFileRuntime;
class UConfigForgeCategory;
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
	TMap<FString, TObjectPtr<UConfigValueObjectRuntime>> FieldsRuntime;

	UPROPERTY()
	TWeakObjectPtr<UConfigForgeFileRuntime> File;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Category")
	FORCEINLINE UConfigForgeFileRuntime* GetFile() const { return File.Get(); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Category")
	FORCEINLINE FName GetCategoryName() const { return CategoryName; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Category")
	FORCEINLINE UConfigForgeCategory* GetCategoryAsset() const { return CategoryAsset.Get(); }

	void GetFields(TArray<TWeakObjectPtr<UConfigValueObjectRuntime>>& OutResult) const;

	UFUNCTION(BlueprintCallable, DisplayName="Get All Fields", Category="Category")
	void BP_GetFields(TArray<UConfigValueObjectRuntime*>& OutResult) const;

	UFUNCTION(BlueprintCallable, Category="Category")
	bool GetField(const FString& InKey, UConfigValueObjectRuntime*& OutField) const;

public:
	void InitData(UConfigForgeCategory* InCategoryAsset);
	void SetFileOwner(UConfigForgeFileRuntime* InFile) { File = InFile; }

public:
	virtual void BeginDestroy() override;
};