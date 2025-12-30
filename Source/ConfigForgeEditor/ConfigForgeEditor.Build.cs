using UnrealBuildTool;

public class ConfigForgeEditor : ModuleRules
{
	public ConfigForgeEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", "ConfigForge"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
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