// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "ConfigForgeFile.h"
#include "ConfigForgeFileRuntime.generated.h"

class FConfigForgeIniFile;
class UConfigForgeCategoryRuntime;
class UConfigPathProvider;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class CONFIGFORGE_API UConfigForgeFileRuntime : public UObject
{
	GENERATED_BODY()

public:
	UConfigForgeFileRuntime();

protected:
	// Read only
	UPROPERTY()
	TWeakObjectPtr<UConfigForgeFile> FileAsset;

	UPROPERTY()
	TObjectPtr<UConfigPathProvider> PathProvider;

	UPROPERTY()
	FString FullPath;

	UPROPERTY()
	FString FileName;

	UPROPERTY()
	TArray<TObjectPtr<UConfigForgeCategoryRuntime>> CategoriesRuntime;

	UPROPERTY()
	FGuid UniqueFileID;

protected:

public:
	virtual void BeginDestroy() override;

public:
	#pragma region IO

	bool SaveTo(const FString& InPath);
	bool ReadFrom(const FString& InPath);

	#pragma endregion

	#pragma region Defaults

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Get")
	bool IsValidData() const;

	void InitDefaultData();

	#pragma endregion

	#pragma region Get

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Get")
	FORCEINLINE FString GetFileName() const { return FileName; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Get")
	FORCEINLINE FString GetFullPath() const { return FullPath; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Get")
	FORCEINLINE UConfigPathProvider* GetPathProvider() const { return PathProvider; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Get")
	FORCEINLINE UConfigForgeFile* GetFileAsset() const { return FileAsset.Get(); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Get")
	FORCEINLINE FGuid GetFileID() const { return UniqueFileID; }
	#pragma endregion

	#pragma region Set

	void SetFileName(const FString& InFileName) { this->FileName = InFileName; }
	void SetFullPath(const FString& InFilePath) { this->FullPath = InFilePath; }
	void SetPathProvider(UConfigPathProvider* InPathProvider) { PathProvider = InPathProvider; }
	void SetFileAsset(UConfigForgeFile* InFileAsset) { this->FileAsset = InFileAsset; }
	void SetFileID(const FGuid& InId) { this->UniqueFileID = InId; }

	#pragma endregion
};