// UK2Node_GetConfigForgeFile.cpp
#include "K2/K2Node_GetConfigForgeFile.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "K2Node_CallFunction.h"
#include "KismetCompiler.h"
#include "Data/ConfigForgeFile.h"
#include "Data/ConfigForgeSetup.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/ConfigForgeSubsystem.h"
#include "Engine/GameInstance.h"
#include "Libs/ConfigForgeLibrary.h"
#include "Misc/ConfigForgeDeveloperSettings.h"

// Define pin names
const FName UK2Node_GetConfigForgeFile::PN_Execute(TEXT("Execute"));
const FName UK2Node_GetConfigForgeFile::PN_Then(TEXT("Then"));
const FName UK2Node_GetConfigForgeFile::PN_FileName(TEXT("FileName"));
const FName UK2Node_GetConfigForgeFile::PN_OutFileData(TEXT("OutFileData"));
const FName UK2Node_GetConfigForgeFile::PN_ReturnValue(TEXT("ReturnValue"));

UK2Node_GetConfigForgeFile::UK2Node_GetConfigForgeFile() {}

void UK2Node_GetConfigForgeFile::AllocateDefaultPins()
{
	// Create execution pins
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, PN_Execute);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, PN_Then);

	// Create FileName input pin (String)
	UEdGraphPin* FileNamePin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_String, PN_FileName);
	FileNamePin->DefaultValue = TEXT("");

	// Create OutFileData output pin
	UEdGraphPin* OutFileDataPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Struct,
		FConfigForgeFileData::StaticStruct(), PN_OutFileData);

	// Create return value pin (bool)
	UEdGraphPin* ReturnPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Boolean, PN_ReturnValue);

	Super::AllocateDefaultPins();
}

FText UK2Node_GetConfigForgeFile::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(TEXT("K2: Get Config File"));
}

FText UK2Node_GetConfigForgeFile::GetTooltipText() const
{
	return FText::FromString(TEXT("Retrieves a specific configuration file by name from the ConfigForge subsystem."));
}

FLinearColor UK2Node_GetConfigForgeFile::GetNodeTitleColor() const
{
	return FLinearColor(0.2f, 0.6f, 1.0f); // Blue color for data nodes
}

FSlateIcon UK2Node_GetConfigForgeFile::GetIconAndTint(FLinearColor& OutColor) const
{
	OutColor = FLinearColor::White;
	return FSlateIcon("EditorStyle", "Kismet.AllClasses.FunctionIcon");
}

void UK2Node_GetConfigForgeFile::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	/*Super::ExpandNode(CompilerContext, SourceGraph);

	// Get our pins
	UEdGraphPin* ExecPin = FindPinChecked(PN_Execute, EGPD_Input);
	UEdGraphPin* ThenPin = FindPinChecked(PN_Then, EGPD_Output);
	UEdGraphPin* FileNamePin = FindPinChecked(PN_FileName);
	UEdGraphPin* OutFileDataPin = FindPinChecked(PN_OutFileData);
	UEdGraphPin* ReturnPin = FindPinChecked(PN_ReturnValue);

	// Create a "Get Game Instance" node (pure function, no exec pins)
	UK2Node_CallFunction* GetGameInstanceNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	GetGameInstanceNode->FunctionReference.SetExternalMember(GET_FUNCTION_NAME_CHECKED(UGameplayStatics, GetGameInstance), UGameplayStatics::StaticClass());
	GetGameInstanceNode->AllocateDefaultPins();

	// We need to provide a world context - create a self context node or leave it unconnected
	// For now, we'll leave WorldContextObject unconnected (it will use the calling context)

	// Create a "Get Subsystem" node (also pure)
	UK2Node_CallFunction* GetSubsystemNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	GetSubsystemNode->FunctionReference.SetExternalMember(
		GET_FUNCTION_NAME_CHECKED(UGameInstance, GetSubsystemBase),
		UGameInstance::StaticClass()
	);
	GetSubsystemNode->AllocateDefaultPins();

	// Connect Game Instance output to Subsystem self pin
	UEdGraphPin* GameInstanceOutput = GetGameInstanceNode->GetReturnValuePin();
	UEdGraphPin* SubsystemSelfPin = GetSubsystemNode->FindPinChecked(UEdGraphSchema_K2::PN_Self);
	GameInstanceOutput->MakeLinkTo(SubsystemSelfPin);

	// Set subsystem class
	UEdGraphPin* SubsystemClassPin = GetSubsystemNode->FindPinChecked(TEXT("Class"));
	SubsystemClassPin->DefaultObject = UConfigForgeSubsystem::StaticClass();

	// Create the "GetFile" function call node
	UK2Node_CallFunction* GetFileNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	GetFileNode->FunctionReference.SetExternalMember(
		GET_FUNCTION_NAME_CHECKED(UConfigForgeSubsystem, GetFile),
		UConfigForgeSubsystem::StaticClass()
	);
	GetFileNode->AllocateDefaultPins();

	// Connect subsystem output to GetFile self pin
	UEdGraphPin* SubsystemOutput = GetSubsystemNode->GetReturnValuePin();
	UEdGraphPin* GetFileSelfPin = GetFileNode->FindPinChecked(UEdGraphSchema_K2::PN_Self);
	SubsystemOutput->MakeLinkTo(GetFileSelfPin);

	// Connect execution pins (only GetFile has exec pins)
	CompilerContext.MovePinLinksToIntermediate(*ExecPin, *GetFileNode->FindPinChecked(UEdGraphSchema_K2::PN_Execute));
	CompilerContext.MovePinLinksToIntermediate(*ThenPin, *GetFileNode->FindPinChecked(UEdGraphSchema_K2::PN_Then));

	// Connect our input pins to the GetFile function
	UEdGraphPin* GetFileNamePin = GetFileNode->FindPinChecked(TEXT("InFileName"));
	CompilerContext.MovePinLinksToIntermediate(*FileNamePin, *GetFileNamePin);

	// Connect output pins
	UEdGraphPin* GetFileOutDataPin = GetFileNode->FindPinChecked(TEXT("OutFileData"));
	CompilerContext.MovePinLinksToIntermediate(*OutFileDataPin, *GetFileOutDataPin);

	UEdGraphPin* GetFileReturnPin = GetFileNode->GetReturnValuePin();
	CompilerContext.MovePinLinksToIntermediate(*ReturnPin, *GetFileReturnPin);

	// Break all links to this node since we've moved them to intermediate nodes
	BreakAllNodeLinks();*/

	Super::ExpandNode(CompilerContext, SourceGraph);

	// Get our pins
	UEdGraphPin* ExecPin = FindPinChecked(PN_Execute, EGPD_Input);
	UEdGraphPin* ThenPin = FindPinChecked(PN_Then, EGPD_Output);
	UEdGraphPin* FileNamePin = FindPinChecked(PN_FileName);
	UEdGraphPin* OutFileDataPin = FindPinChecked(PN_OutFileData);
	UEdGraphPin* ReturnPin = FindPinChecked(PN_ReturnValue);

	// Create a call to our static library function
	UK2Node_CallFunction* CallFunctionNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	CallFunctionNode->FunctionReference.SetExternalMember(
		GET_FUNCTION_NAME_CHECKED(UConfigForgeLibrary, GetConfigForgeFile),
		UConfigForgeLibrary::StaticClass()
	);
	CallFunctionNode->AllocateDefaultPins();

	// Connect execution pins
	CompilerContext.MovePinLinksToIntermediate(*ExecPin, *CallFunctionNode->FindPinChecked(UEdGraphSchema_K2::PN_Execute));
	CompilerContext.MovePinLinksToIntermediate(*ThenPin, *CallFunctionNode->FindPinChecked(UEdGraphSchema_K2::PN_Then));

	// Get the WorldContextObject pin and set it to use self
	UEdGraphPin* WorldContextPin = CallFunctionNode->FindPinChecked(TEXT("WorldContextObject"));
	CompilerContext.GetSchema()->SetPinAutogeneratedDefaultValueBasedOnType(WorldContextPin);

	// Connect FileName pin
	UEdGraphPin* FunctionFileNamePin = CallFunctionNode->FindPinChecked(TEXT("InFileName"));
	CompilerContext.MovePinLinksToIntermediate(*FileNamePin, *FunctionFileNamePin);

	// Connect OutFileData pin
	UEdGraphPin* FunctionOutFileDataPin = CallFunctionNode->FindPinChecked(TEXT("OutFileData"));
	CompilerContext.MovePinLinksToIntermediate(*OutFileDataPin, *FunctionOutFileDataPin);

	// Connect return value pin
	UEdGraphPin* FunctionReturnPin = CallFunctionNode->GetReturnValuePin();
	CompilerContext.MovePinLinksToIntermediate(*ReturnPin, *FunctionReturnPin);

	// Break all links to this node
	BreakAllNodeLinks();
}

FText UK2Node_GetConfigForgeFile::GetMenuCategory() const
{
	return FText::FromString(TEXT("ConfigForge"));
}

void UK2Node_GetConfigForgeFile::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	UClass* ActionKey = GetClass();
	if (ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(NodeSpawner != nullptr);

		ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}

TArray<TSharedPtr<FString>> UK2Node_GetConfigForgeFile::GetFileNameOptions() const
{
	TArray<TSharedPtr<FString>> Options;

	const UConfigForgeDeveloperSettings* developerSettings = GetDefault<UConfigForgeDeveloperSettings>();
	if (developerSettings)
	{
		TArray<FConfigForgeFileData> files;
		UConfigForgeSubsystem::GetFilesStatic(developerSettings->ConfigSetup.LoadSynchronous(), files);

		for (const FConfigForgeFileData& FileData : files)
		{
			Options.Add(MakeShared<FString>(FileData.File->FileName));
		}
	}

	if (Options.Num() == 0)
	{
		Options.Add(MakeShared<FString>(TEXT("No files available")));
	}

	return Options;
}