// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.

#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"
#include "ConfigForgeSetup.generated.h"

class UConfigForgeFile;
class UConfigPathProvider;

USTRUCT(Blueprintable, BlueprintType)
struct CONFIGFORGE_API FConfigForgeFileData
{
	GENERATED_BODY()

public:
	FConfigForgeFileData();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, NoClear, Category="File Data")
	TSubclassOf<UConfigPathProvider> PathProvider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, meta=(ShowOnlyInnerProperties), Category="File Data")
	TObjectPtr<UConfigForgeFile> File;

public:
	FGuid ID() const;
	static FGuid MakeID(const FConfigForgeFileData& InFileData);
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class CONFIGFORGE_API UConfigForgeSetup : public UObject
{
	GENERATED_BODY()

public:
	UConfigForgeSetup(const FObjectInitializer& InObjectInitializer = FObjectInitializer::Get());

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ShowOnlyInnerProperties), Category = "Settigns")
	TArray<FConfigForgeFileData> Files;
};