
PROJECT_TYPE				= _ARGS[3]
SOLUTION_NAME				= "Silver" .. PROJECT_TYPE
RUNTIME_NAME				= "game"
TARGET_NAME					= SOLUTION_NAME -- Name of executable
DEBUG_FORMAT				= "c7"
ROOT_DIRECTORY				= path.getabsolute("../")
RUNTIME_DIR					= path.join(ROOT_DIRECTORY, RUNTIME_NAME)
LIB_DIRECTORY				= path.join(ROOT_DIRECTORY, "libs")
EDITOR_NAME					= "editor"
EDITOR_DIR					= path.join(LIB_DIRECTORY, EDITOR_NAME)
IGNORE_FILES				= {}
ADDITIONAL_INCLUDES			= {}
ADDITIONAL_LIBRARIES		= {}
ADDITIONAL_LIBRARIES_DBG	= {}
INTERMEDIATE_DIR			= path.getabsolute("../build_output/intermediate")
TARGET_DIR_RELEASE  		= path.getabsolute("../build_output/release")
TARGET_DIR_DEBUG    		= path.getabsolute("../build_output/debug")
API_GRAPHICS				= _ARGS[1]
PLATFORM_NAME				= _ARGS[2]

-- Compute graphics api specific variables
if API_GRAPHICS == "d3d11" then
	API_GRAPHICS	= "API_GRAPHICS_D3D11"
	--TARGET_NAME		= TARGET_NAME .. "_d3d11"
end

-- Solution
solution (SOLUTION_NAME)
	location ".."
	systemversion "latest"
	cppdialect "C++17"
	language "C++"
	platforms "x64"
	configurations { "release", "debug" }
	
	forceincludes
	{
		"stdint.h"
	}
	
	-- Defines
	defines
	{
		"Silver_RUNTIME_STATIC=1",
		"Silver_RUNTIME_SHARED=0"
	}
	
	filter { "platforms:x64" }
		system "Windows"
		architecture "x64"
		defines { "PLATFORM_WINDOWS" }
		
	
if PROJECT_TYPE == "editor" then
	defines{ "EDITOR" }
end

	defines{ "GUI_AVAILABLE" }
	defines{ "INPUT_AVAILABLE" }

	--	"debug"
	filter "configurations:debug"
		defines { "DEBUG" }
		--flags { "MultiProcessorCompile", "LinkTimeOptimization" }
		symbols "On"		
		
	--	"release"	
	filter "configurations:release"
		defines { "RELEASE" }
		flags { "MultiProcessorCompile" }
		symbols "Off"	
		optimize "Full"




dofile (LIB_DIRECTORY .. "/core/build_generation_files/shared.lua")

if PROJECT_TYPE == "editor" then
group "Editor"
	dofile (EDITOR_DIR .. "/build_generation_files/editor.lua")
end

group "Libraries"
	dofile (LIB_DIRECTORY .. "/core/build_generation_files/core.lua")
	dofile (LIB_DIRECTORY .. "/engine/build_generation_files/engine.lua")
	
	dofile (LIB_DIRECTORY .. "/input/build_generation_files/input.lua")
	dofile (LIB_DIRECTORY .. "/gui/build_generation_files/gui.lua")

group "App"
	-- Runtime -------------------------------------------------------------------------------------------------
	dofile (RUNTIME_DIR .. "/build_generation_files/game.lua")
