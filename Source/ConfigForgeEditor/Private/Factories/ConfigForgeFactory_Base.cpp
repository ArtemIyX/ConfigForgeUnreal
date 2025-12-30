// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.


#include "Factories/ConfigForgeFactory_Base.h"

#include "ClassViewerModule.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Kismet2/SClassPickerDialog.h"

UConfigForgeFactory_Base::UConfigForgeFactory_Base()
{
	SupportedClass = UObject::StaticClass();
}

UObject* UConfigForgeFactory_Base::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	UBlueprint* blueprintObject = FKismetEditorUtilities::CreateBlueprint(SelectedByUserClass, InParent, InName, BPTYPE_Normal, CallingContext);
	return blueprintObject;
}

bool UConfigForgeFactory_Base::ConfigureProperties()
{
	// Fill in options
	FClassViewerInitializationOptions Options;
	Options.Mode = EClassViewerMode::ClassPicker;
	Options.DisplayMode = EClassViewerDisplayMode::TreeView;
	Options.bShowObjectRootClass = true;
	Options.NameTypeToDisplay = EClassViewerNameTypeToDisplay::Dynamic;

	// Prevent creating blueprints of classes that require special setup (they'll be allowed in the corresponding factories / via other means)
	TSharedPtr<FForgeConfigClassViewFilter> Filter = MakeShareable(new FForgeConfigClassViewFilter());
	Filter->AllowedChildrenOfClasses.Add(SupportedClass);
	Options.ClassFilters.Add(Filter.ToSharedRef());

	const FText TitleText = FText::FromString(TEXT("Pick Parent Class"));
	UClass* ChosenClass = nullptr;
	const bool bPressedOk = SClassPickerDialog::PickClass(TitleText, Options, ChosenClass, UBlueprint::StaticClass());

	if (bPressedOk)
	{
		SelectedByUserClass = ChosenClass;
		FEditorDelegates::OnFinishPickingBlueprintClass.Broadcast(SelectedByUserClass);
	}

	return bPressedOk;
};