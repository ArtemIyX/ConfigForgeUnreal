using UnrealBuildTool;

public class ConfigForgeEditor : ModuleRules
{
	public ConfigForgeEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", "ConfigForge", "Engine"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"BlueprintGraph",
				"PropertyEditor",
				"EditorStyle",
				"Kismet",
				"KismetCompiler",
				"InputCore",
				"GraphEditor",
				"Slate",
				"SlateCore",
				"UnrealEd",
				"Projects",
				"AssetTools",
				"GameplayTagsEditor",
				"GameplayTags",
				"UMG"
			}
		);
	}
}