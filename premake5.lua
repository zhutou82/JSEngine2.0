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
IncludeDir["GLFW"]      = "JSEngine2.0/vendor/GLFW/include"
IncludeDir["Glad"]      = "JSEngine2.0/vendor/Glad/include"
IncludeDir["imgui"]     = "JSEngine2.0/vendor/imgui" 
IncludeDir["glm"]       = "JSEngine2.0/vendor/glm" 
IncludeDir["tinyXML"]   = "JSEngine2.0/vendor/tinyXML" 
IncludeDir["stb_image"] = "JSEngine2.0/vendor/stb_image" 
IncludeDir["box2D"]     = "JSEngine2.0/vendor/box2D/include" 

include "JSEngine2.0/vendor/GLFW"
include "JSEngine2.0/vendor/Glad"
include "JSEngine2.0/vendor/imgui"
include "JSEngine2.0/vendor/tinyXML"
include "JSEngine2.0/vendor/box2D"

project "JSEngine2.0"
    location "JSEngine2.0"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    
    -- Enable Visual Studio to use multiple compiler processes when building
    flags { "MultiProcessorCompile" }

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "PCH.h"
    pchsource "JSEngine2.0/src/JSEngine/PCH.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS",
        "GLFW_INCLUDE_NONE"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.tinyXML}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.box2D}"
    }

    links 
    { 
        "GLFW",
        "Glad",
        "imgui",
        "opengl32.lib",
		'tinyxml2',
        'box2D'
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "JSENGINE_PLATFORM_WINDOWS",
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
    
    -- Enable Visual Studio to use multiple compiler processes when building
    flags { "MultiProcessorCompile" }

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
        "%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.tinyXML}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.box2D}"
    }

    links
    {
        "JSEngine2.0"
    }

    filter "system:windows"
        systemversion "latest"
        defines
        {
            "JSENGINE_PLATFORM_WINDOWS",
            "GLFW_INCLUDE_NONE"
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