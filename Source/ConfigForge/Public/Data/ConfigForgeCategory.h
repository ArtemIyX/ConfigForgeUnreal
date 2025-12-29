// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ConfigForgeCategory.generated.h"


class UConfigValueObject;

UCLASS(Blueprintable, BlueprintType)
class CONFIGFORGE_API UConfigForgeCategory : public UObject
{
	GENERATED_BODY()

public:
	UConfigForgeCategory(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Category Name", Category = "Category")
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Category Properties", Category = "Category")
	TArray<UConfigValueObject*> Fields;
};