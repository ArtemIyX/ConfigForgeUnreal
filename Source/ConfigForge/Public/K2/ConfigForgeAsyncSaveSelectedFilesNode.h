// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "Data/ConfigForgeSetup.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "UObject/Object.h"
#include "ConfigForgeAsyncSaveSelectedFilesNode.generated.h"

class UConfigForgeFileRuntime;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnConfigForgeSelectedFilesLoaded, const TArray<UConfigForgeFileRuntime*>&, LoadedFiles, bool, bAllSucess);

/**
 * 
 */
UCLASS()
class CONFIGFORGE_API UConfigForgeAsyncLoadSelectedFilesNode : public UBlueprintAsyncActionBase
{
public:
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "ConfigForge|Async")
	static UConfigForgeAsyncLoadSelectedFilesNode* LoadConfigForgeSelectedFilesAsync(UObject* WorldContextObject,
		const TArray<FConfigForgeFileData>& InFiles);
protected:
	UPROPERTY()
	TWeakObjectPtr<UObject> WorldContextObject;
	
	UPROPERTY()
	TArray<FConfigForgeFileData> Files;
protected:
	UFUNCTION()
	void OnLoadComplete(bool bSuccess, const TArray<UConfigForgeFileRuntime*>& InFiles);
public:

	virtual void Activate() override;
public:
	UPROPERTY(BlueprintAssignable)
	FOnConfigForgeSelectedFilesLoaded OnFinished;
};
