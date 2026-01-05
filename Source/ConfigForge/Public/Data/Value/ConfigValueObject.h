// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "Misc/ConfigForgeIniFile.h"
#include "UObject/Object.h"
#include "ConfigValueObject.generated.h"

/**
 *
 * 
 */
UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class CONFIGFORGE_API UConfigValueObject : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayPriority=1), Category="Data")
	FString Key;

public:
	
	virtual void SetToFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile,
		const FString& InSection);

	virtual bool GetFromFile(const TSharedPtr<FConfigForgeIniFile>& InConfigFile,
		const FString& InSection);

	virtual uint32 MakeHash() const;
};