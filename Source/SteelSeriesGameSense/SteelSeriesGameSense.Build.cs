/**
* Authors: sharkgoesmad
*
* Copyright (c) 2019 SteelSeries ApS. All Rights Reserved.
*/

using System.IO;

namespace UnrealBuildTool.Rules
{
    public class SteelSeriesGameSense : ModuleRules
    {
        public SteelSeriesGameSense(ReadOnlyTargetRules Target) : base(Target)
        {
            bEnforceIWYU = false;
            PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

            PublicDependencyModuleNames.AddRange(
                new string[]
                {
                    "Engine",
                    "Core",
                    "CoreUObject",
                    "Json",
                    "JsonUtilities",
                    "HTTP",
                    // ... add other public dependencies that you statically link with here ...
                }
                );

            PrivateDependencyModuleNames.AddRange(
                new string[]
                {
                    // ... add private dependencies that you statically link with here ...
                }
                );

            DynamicallyLoadedModuleNames.AddRange(
                new string[]
                {
                    // ... add any modules that your module loads dynamically here ...
                }
                );

            // New with UE 4.20 and above
            // https://www.unrealengine.com/en-US/marketplace-guidelines#263e
            PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));
            PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private"));
        }
    }
}
