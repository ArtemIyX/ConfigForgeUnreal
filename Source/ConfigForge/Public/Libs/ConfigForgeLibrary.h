// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "Data/ConfigForgeSetup.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Misc/DynamicValue.h"
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

	#pragma region DynamicValue
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigForge", DisplayName="Make Dynamic Value (Int)")
	static FDynamicValue MakeDynamicValue_Int(int32 InValue);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigForge", DisplayName="Make Dynamic Value (Float)")
	static FDynamicValue MakeDynamicValue_Float(float InValue);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigForge", DisplayName="Make Dynamic Value (Double)")
	static FDynamicValue MakeDynamicValue_Double(double InValue);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigForge", DisplayName="Make Dynamic Value (Bool)")
	static FDynamicValue MakeDynamicValue_Bool(bool InValue);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigForge", DisplayName="Make Dynamic Value (Byte)")
	static FDynamicValue MakeDynamicValue_Byte(uint8 InValue);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigForge", DisplayName="Make Dynamic Value (Int64)")
	static FDynamicValue MakeDynamicValue_Int64(int64 InValue);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigForge", DisplayName="Make Dynamic Value (String)")
	static FDynamicValue MakeDynamicValue_String(const FString& InValue);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigForge", DisplayName="Get Dynamic Value (Int)")
	static void ParseDynamicValue_Int(const FDynamicValue& InDynamicValue, int32& OutInt, bool& bSuccess);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigForge", DisplayName="Get Dynamic Value (Float)")
	static void ParseDynamicValue_Float(const FDynamicValue& InDynamicValue, float& OutFloat, bool& bSuccess);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigForge", DisplayName="Get Dynamic Value (Double)")
	static void ParseDynamicValue_Double(const FDynamicValue& InDynamicValue, double& OutDouble, bool& bSuccess);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigForge", DisplayName="Get Dynamic Value (Bool)")
	static void ParseDynamicValue_Bool(const FDynamicValue& InDynamicValue, bool& OutBool, bool& bSuccess);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigForge", DisplayName="Get Dynamic Value (Byte)")
	static void ParseDynamicValue_Byte(const FDynamicValue& InDynamicValue, uint8& OutByte, bool& bSuccess);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigForge", DisplayName="Get Dynamic Value (Int64)")
	static void ParseDynamicValue_Int64(const FDynamicValue& InDynamicValue, int64& OutInt64, bool& bSuccess);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigForge", DisplayName="Get Dynamic Value (String)")
	static void ParseDynamicValue_String(const FDynamicValue& InDynamicValue, FString& OutString, bool& bSuccess);
	#pragma endregion
};