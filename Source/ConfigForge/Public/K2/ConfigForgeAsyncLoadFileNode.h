// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.


#pragma once

#include "CoreMinimal.h"
#include "Data/ConfigForgeSetup.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Subsystems/ConfigForgeSubsystem.h"
#include "ConfigForgeAsyncLoadFileNode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConfigForgeFileLoaded, UConfigForgeFileRuntime*, LoadedFile);

/**
 * Async Blueprint node for loading ConfigForge files
 */
UCLASS()
class CONFIGFORGE_API UConfigForgeAsyncLoadFileNode : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnConfigForgeFileLoaded OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnConfigForgeFileLoaded OnFailure;

	/**
	 * Asynchronously loads a ConfigForge file
	 * @param WorldContextObject - World context for getting the subsystem
	 * @param FileData - The file data to load
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "ConfigForge|Async")
	static UConfigForgeAsyncLoadFileNode* LoadConfigForgeFileAsync(UObject* WorldContextObject, const FConfigForgeFileData& FileData);

	// UBlueprintAsyncActionBase interface
	virtual void Activate() override;

private:
	UPROPERTY()
	TWeakObjectPtr<UObject> WorldContextObject;

	UPROPERTY()
	FConfigForgeFileData FileData;

	UFUNCTION()
	void OnLoadComplete(bool bSuccess, UConfigForgeFileRuntime* LoadedFile);
};