// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ConfigForgeDeveloperSettings.generated.h"


class UConfigForgeFile;

USTRUCT(Blueprintable, BlueprintType)
struct CONFIGFORGE_API FConfigForgeDeveloperSettingsArray
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSoftObjectPtr<UConfigForgeFile>> Value;
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Config=Game, DefaultConfig)
class CONFIGFORGE_API UConfigForgeDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite)
	FConfigForgeDeveloperSettingsArray Files;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName="Get Config Forge DeveloperSettings", Category="ConfigForgeDeveloperSettings",
		meta=(Keywords="Get Config Forge Developer Settings"))
	static const UConfigForgeDeveloperSettings* Get();
};