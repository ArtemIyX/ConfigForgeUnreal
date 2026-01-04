// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "K2Node.h"
#include "K2Node_GetConfigForgeFile.generated.h"

/**
 * @brief Custom K2 Node for retrieving ConfigForge files with dropdown selection.
 * 
 * Provides a Blueprint node that calls UConfigForgeSubsystem::GetFile() with
 * a dropdown list of available file names.
 */
UCLASS()
class CONFIGFORGE_API UK2Node_GetConfigForgeFile : public UK2Node
{
	GENERATED_BODY()

public:
	UK2Node_GetConfigForgeFile();

	// UEdGraphNode interface
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;
	// End of UEdGraphNode interface

	// UK2Node interface
	virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	virtual FText GetMenuCategory() const override;
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	// End of UK2Node interface

	// Helper function to get available file names for dropdown
	TArray<TSharedPtr<FString>> GetFileNameOptions() const;

private:
	// Pin names
	static const FName PN_Execute;
	static const FName PN_Then;
	static const FName PN_FileName;
	static const FName PN_OutFileData;
	static const FName PN_ReturnValue;
};
