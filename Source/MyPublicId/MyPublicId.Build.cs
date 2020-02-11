// Copyright 2019 MyPublicId LLC. All Rights Reserved.

using UnrealBuildTool;

public class MyPublicId : ModuleRules
{
    public MyPublicId(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "HTTP",
                "Json",
                "JsonUtilities"
            }
        );

        if (Target.bBuildEditor)
        {
            PrivateDependencyModuleNames.Add("Engine");
        }
    }
}
