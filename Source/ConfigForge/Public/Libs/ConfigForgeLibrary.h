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

	/**
	 * @brief Retrieves the unique GUID identifier from a ConfigForge file data structure.
	 * @param InData The ConfigForge file data structure to extract the GUID from.
	 * @return FGuid The unique identifier for the ConfigForge file.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigForge", DisplayName="Get Config Forge File GUID (Static Lib)")
	static FGuid GetForgeFileID(const FConfigForgeFileData& InData);

	#pragma region DynamicValue

	/**
	 * @brief Creates a dynamic value wrapper containing a 32-bit signed integer.
	 * @param InValue The integer value to wrap.
	 * @return FDynamicValue A dynamic value containing the integer.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigForge", DisplayName="Make Dynamic Value (Int)")
	static FDynamicValue MakeDynamicValue_Int(int32 InValue);

	/**
	 * @brief Creates a dynamic value wrapper containing a single-precision floating point number.
	 * @param InValue The float value to wrap.
	 * @return FDynamicValue A dynamic value containing the float.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigForge", DisplayName="Make Dynamic Value (Float)")
	static FDynamicValue MakeDynamicValue_Float(float InValue);

	/**
	 * @brief Creates a dynamic value wrapper containing a double-precision floating point number.
	 * @param InValue The double value to wrap.
	 * @return FDynamicValue A dynamic value containing the double.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigForge", DisplayName="Make Dynamic Value (Double)")
	static FDynamicValue MakeDynamicValue_Double(double InValue);

	/**
	 * @brief Creates a dynamic value wrapper containing a boolean value.
	 * @param InValue The boolean value to wrap.
	 * @return FDynamicValue A dynamic value containing the boolean.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigForge", DisplayName="Make Dynamic Value (Bool)")
	static FDynamicValue MakeDynamicValue_Bool(bool InValue);

	/**
	 * @brief Creates a dynamic value wrapper containing an unsigned 8-bit integer (byte).
	 * @param InValue The byte value to wrap.
	 * @return FDynamicValue A dynamic value containing the byte.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigForge", DisplayName="Make Dynamic Value (Byte)")
	static FDynamicValue MakeDynamicValue_Byte(uint8 InValue);

	/**
	 * @brief Creates a dynamic value wrapper containing a 64-bit signed integer.
	 * @param InValue The 64-bit integer value to wrap.
	 * @return FDynamicValue A dynamic value containing the int64.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigForge", DisplayName="Make Dynamic Value (Int64)")
	static FDynamicValue MakeDynamicValue_Int64(int64 InValue);

	/**
	 * @brief Creates a dynamic value wrapper containing a string.
	 * @param InValue The string value to wrap.
	 * @return FDynamicValue A dynamic value containing the string.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigForge", DisplayName="Make Dynamic Value (String)")
	static FDynamicValue MakeDynamicValue_String(const FString& InValue);

	/**
	 * @brief Attempts to extract a 32-bit signed integer from a dynamic value.
	 * @param InDynamicValue The dynamic value to parse.
	 * @param OutInt [out] The extracted integer value if successful.
	 * @param bSuccess [out] True if the value was successfully extracted, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigForge", DisplayName="Get Dynamic Value (Int)")
	static void ParseDynamicValue_Int(const FDynamicValue& InDynamicValue, int32& OutInt, bool& bSuccess);

	/**
	 * @brief Attempts to extract a single-precision floating point number from a dynamic value.
	 * @param InDynamicValue The dynamic value to parse.
	 * @param OutFloat [out] The extracted float value if successful.
	 * @param bSuccess [out] True if the value was successfully extracted, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigForge", DisplayName="Get Dynamic Value (Float)")
	static void ParseDynamicValue_Float(const FDynamicValue& InDynamicValue, float& OutFloat, bool& bSuccess);

	/**
	 * @brief Attempts to extract a double-precision floating point number from a dynamic value.
	 * @param InDynamicValue The dynamic value to parse.
	 * @param OutDouble [out] The extracted double value if successful.
	 * @param bSuccess [out] True if the value was successfully extracted, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigForge", DisplayName="Get Dynamic Value (Double)")
	static void ParseDynamicValue_Double(const FDynamicValue& InDynamicValue, double& OutDouble, bool& bSuccess);

	/**
	 * @brief Attempts to extract a boolean value from a dynamic value.
	 * @param InDynamicValue The dynamic value to parse.
	 * @param OutBool [out] The extracted boolean value if successful.
	 * @param bSuccess [out] True if the value was successfully extracted, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigForge", DisplayName="Get Dynamic Value (Bool)")
	static void ParseDynamicValue_Bool(const FDynamicValue& InDynamicValue, bool& OutBool, bool& bSuccess);

	/**
	 * @brief Attempts to extract an unsigned 8-bit integer (byte) from a dynamic value.
	 * @param InDynamicValue The dynamic value to parse.
	 * @param OutByte [out] The extracted byte value if successful.
	 * @param bSuccess [out] True if the value was successfully extracted, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigForge", DisplayName="Get Dynamic Value (Byte)")
	static void ParseDynamicValue_Byte(const FDynamicValue& InDynamicValue, uint8& OutByte, bool& bSuccess);

	/**
	 * @brief Attempts to extract a 64-bit signed integer from a dynamic value.
	 * @param InDynamicValue The dynamic value to parse.
	 * @param OutInt64 [out] The extracted int64 value if successful.
	 * @param bSuccess [out] True if the value was successfully extracted, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigForge", DisplayName="Get Dynamic Value (Int64)")
	static void ParseDynamicValue_Int64(const FDynamicValue& InDynamicValue, int64& OutInt64, bool& bSuccess);

	/**
	 * @brief Attempts to extract a string from a dynamic value.
	 * @param InDynamicValue The dynamic value to parse.
	 * @param OutString [out] The extracted string value if successful.
	 * @param bSuccess [out] True if the value was successfully extracted, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ConfigForge", DisplayName="Get Dynamic Value (String)")
	static void ParseDynamicValue_String(const FDynamicValue& InDynamicValue, FString& OutString, bool& bSuccess);

	#pragma endregion
};