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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="File Data")
	TSubclassOf<UConfigPathProvider> PathProvider;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category="File Data")
	UConfigForgeFile* File;
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settigns")
	TArray<FConfigForgeFileData> Files;
};