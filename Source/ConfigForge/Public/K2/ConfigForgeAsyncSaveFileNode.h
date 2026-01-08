// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "UObject/Object.h"
#include "ConfigForgeAsyncSaveFileNode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConfigForgeFileSaved);

/**
 * 
 */
UCLASS()
class CONFIGFORGE_API UConfigForgeAsyncSaveFileNode : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	/**
	 * Asynchronously loads a ConfigForge file
	 * @param WorldContextObject - World context for getting the subsystem
	 * @param InFileUniqueID - The file ID to pick file and save
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "ConfigForge|Async")
	static UConfigForgeAsyncSaveFileNode* SaveConfigForgeFileAsync(UObject* WorldContextObject, const FGuid& InFileUniqueID);
protected:
	UPROPERTY()
	TWeakObjectPtr<UObject> WorldContextObject;

	UPROPERTY()
	FGuid FileID;

public:
	// UBlueprintAsyncActionBase interface
	virtual void Activate() override;

	UFUNCTION()
	void OnSaveComplete(bool bSuccess);

public:
	UPROPERTY(BlueprintAssignable)
	FOnConfigForgeFileSaved OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnConfigForgeFileSaved OnFailure;
};
