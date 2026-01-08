// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "Misc/DynamicValue.h"
#include "UObject/Object.h"
#include "ConfigValueObjectRuntime.generated.h"

class FConfigForgeIniFile;
class UConfigValueObject;
/**
 * 
 */
UCLASS(NotBlueprintable, NotBlueprintType)
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
public:
	virtual void SetToFile(const TSharedPtr<FConfigForgeIniFile>& InFilePtr, const FString& InSection);
	virtual bool GetFromFile(const TSharedPtr<FConfigForgeIniFile>& InFilePtr, const FString& InSection);
	virtual void ApplyAsset(const TWeakObjectPtr<UConfigValueObject>& InAsset);
};