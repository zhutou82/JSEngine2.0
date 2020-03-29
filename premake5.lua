workspace "JSEngine2.0"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }
    

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"]  = "JSEngine2.0/vendor/GLFW/include"
IncludeDir["Glad"]  = "JSEngine2.0/vendor/Glad/include"
IncludeDir["imgui"] = "JSEngine2.0/vendor/imgui"

include "JSEngine2.0/vendor/GLFW"
include "JSEngine2.0/vendor/Glad"
include "JSEngine2.0/vendor/imgui"

project "JSEngine2.0"
    location "JSEngine2.0"
    kind "SharedLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    -- pchheader "JSpch.h"
    -- pchsource "JSEngine2.0/src/JSpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.imgui}"
    }

    links 
    { 
        "GLFW",
        "Glad",
        "imgui",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "JSENGINE_PLATFORM_WINDOWS",
            "JSENGINE_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
           ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}


    filter "configurations:Debug"
        defines "JS_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "JS_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "JS_DIST"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "JSEngine2.0/vendor/spdlog/include",
        "JSEngine2.0/src",
        "JSEngine2.0/vendor",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.imgui}"
    }

    links
    {
        "JSEngine2.0"
    }

    filter "system:windows"
        systemversion "latest"
        defines
        {
            "JSENGINE_PLATFORM_WINDOWS"
        }
        
    filter "configurations:Debug"
        defines "JS_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "JS_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "JS_DIST"
        runtime "Release"
        optimize "on"