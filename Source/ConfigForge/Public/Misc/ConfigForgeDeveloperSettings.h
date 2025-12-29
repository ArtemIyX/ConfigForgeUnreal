// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ConfigForgeDeveloperSettings.generated.h"


class UConfigForgeSetup;


/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Config=Game, DefaultConfig)
class CONFIGFORGE_API UConfigForgeDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UConfigForgeDeveloperSettings(const FObjectInitializer& InObjectInitializer = FObjectInitializer::Get());

public:
	virtual FName GetSectionName() const override;

	#if WITH_EDITOR
virtual FText GetSectionText() const override;
	#endif
	
public:
	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category="Setup")
	TSoftObjectPtr<UConfigForgeSetup> ConfigSetup;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName="Get Config Forge DeveloperSettings", Category="ConfigForgeDeveloperSettings",
		meta=(Keywords="Get Config Forge Developer Settings"))
	static const UConfigForgeDeveloperSettings* Get();
};