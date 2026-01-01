// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ConfigForgeFile.generated.h"

class UConfigForgeCategory;

/*UENUM(Blueprintable, BlueprintType)
enum class EConfigFileType : uint8
{
	Ini,
	Binary
};*/


UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class CONFIGFORGE_API UConfigForgeFile : public UObject
{
	GENERATED_BODY()

public:
	UConfigForgeFile(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString FileName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	TArray<TObjectPtr<UConfigForgeCategory>> Categories;

public:
	UFUNCTION(BlueprintCallable, Category="File")
	bool GetCategory(const FName& InCategoryName, UConfigForgeCategory*& OutCategory) const;
};