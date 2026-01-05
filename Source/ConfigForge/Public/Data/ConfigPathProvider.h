// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ConfigPathProvider.generated.h"

/**
 * 
 */
UCLASS(blueprintable, BlueprintType)
class CONFIGFORGE_API UConfigPathProvider : public UObject
{
	GENERATED_BODY()

public:
	UConfigPathProvider(const FObjectInitializer& InObjectInitializer = FObjectInitializer::Get());

public:
	/**
	 * 
	 * @return Path to DIRECTORY (Folder)
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, BlueprintPure, Category="ConfigPathProvider")
	FString GetPath() const;

public:

};