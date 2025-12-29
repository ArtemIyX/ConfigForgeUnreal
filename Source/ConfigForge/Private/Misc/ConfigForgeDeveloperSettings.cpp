// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.


#include "Misc/ConfigForgeDeveloperSettings.h"

UConfigForgeDeveloperSettings::UConfigForgeDeveloperSettings(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer) {}

FName UConfigForgeDeveloperSettings::GetSectionName() const
{
	return FName(TEXT("Config Forge"));
}

#if WITH_EDITOR

FText UConfigForgeDeveloperSettings::GetSectionText() const
{
	return FText::FromString(FString(TEXT("Config Forge")));
}

#endif

const UConfigForgeDeveloperSettings* UConfigForgeDeveloperSettings::Get()
{
	return GetDefault<UConfigForgeDeveloperSettings>();
}