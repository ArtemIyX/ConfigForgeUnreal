// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "Data/ConfigForgeSetup.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ConfigForgeLibrary.generated.h"

/**
 * @brief Blueprint function library for ConfigForge operations.
 * @note Used in K2 nodes
 */
UCLASS()
class CONFIGFORGE_API UConfigForgeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * @brief Retrieves a specific configuration file by name using world context.
	 * 
	 * @param WorldContextObject Object to get world context from.
	 * @param InFileName The name of the file to search for (must match exactly).
	 * @param OutFileData [out] The file data structure to populate if found.
	 * @return bool True if the file was found, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category="ConfigForge", DisplayName="Get Config Forge File (Static Lib)", meta=(WorldContext="WorldContextObject"))
	static bool GetConfigForgeFile(const UObject* WorldContextObject, const FString& InFileName, FConfigForgeFileData& OutFileData);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigForge", DisplayName="Get Config Forge File GUID (Static Lib)")
	static FGuid GetForgeFileID(const FConfigForgeFileData& InData);
	
};