// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "UObject/Object.h"
#include "ConfigForgeAsyncLoadAllFilesNode.generated.h"

class UConfigForgeFileRuntime;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnConfigForgeFilesLoaded, const TArray<UConfigForgeFileRuntime*>&, LoadedFiles, bool, bAllSucess);

/**
 * 
 */
UCLASS()
class CONFIGFORGE_API UConfigForgeAsyncLoadAllFilesNode : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "ConfigForge|Async")
	static UConfigForgeAsyncLoadAllFilesNode* LoadConfigForgeFilesAsync(UObject* WorldContextObject);
protected:
	UPROPERTY()
	TWeakObjectPtr<UObject> WorldContextObject;

protected:
	UFUNCTION()
	void OnLoadComplete(bool bSuccess, const TArray<UConfigForgeFileRuntime*>& InFiles);
public:

	virtual void Activate() override;
public:
	UPROPERTY(BlueprintAssignable)
	FOnConfigForgeFilesLoaded OnFinished;
};