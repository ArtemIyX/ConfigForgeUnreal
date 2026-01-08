// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "UObject/Object.h"
#include "ConfigForgeAsyncSaveAllFilesNode.generated.h"

class UConfigForgeFileRuntime;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConfigForgeFilesSaved, bool, bAllSucess);

/**
 * 
 */
UCLASS()
class CONFIGFORGE_API UConfigForgeAsyncSaveAllFilesNode : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "ConfigForge|Async")
	static UConfigForgeAsyncSaveAllFilesNode* SaveConfigForgeFilesAsync(UObject* WorldContextObject);

protected:
	UPROPERTY()
	TWeakObjectPtr<UObject> WorldContextObject;

protected:
	UFUNCTION()
	void OnSaveComplete(bool bSuccess);

public:
	virtual void Activate() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnConfigForgeFilesSaved OnFinished;

};