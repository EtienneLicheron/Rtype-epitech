# R-Type
# Compilation settings for Visual Studio
`CMakeSettings.json` is used to set the compilation settings for the project in Visual Studio.
```json
{
    "configurations": [
        {
            "name": "x64-Release",
            "generator": "Ninja",
            "configurationType": "Release",
            "inheritEnvironments": [ "msvc_x64_x64" ],
            "buildRoot": "${projectDir}\\out\\build\\${name}",
            "installRoot": "${projectDir}\\out\\install\\${name}",
            "cmakeCommandArgs": "",
            "buildCommandArgs": "",
            "ctestCommandArgs": ""
        }
    ]
}
```
