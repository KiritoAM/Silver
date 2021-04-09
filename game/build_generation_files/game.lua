
project (RUNTIME_NAME)
	location (project_directory(RUNTIME_NAME))
	objdir (INTERMEDIATE_DIR)
	targetname ( TARGET_NAME )
	objdir (INTERMEDIATE_DIR)
	kind "WindowedApp"
	staticruntime "On"
	conformancemode "On"
	defines{ SOLUTION_NAME .. "_" .. RUNTIME_NAME, API_GRAPHICS }
	
	includedirs 
    {
		RUNTIME_DIR,
		LIB_DIRECTORY
	}
	
	libdirs { TARGET_DIR_DEBUG }
	links
	{
		"core.lib",
		"engine.lib",
		"input.lib",
		"gui.lib",
	}
	
	dependson
	{
		"core",
		"engine",
		"input",
		"gui",		
	}
	
if PROJECT_TYPE == "editor" then
	links
	{
		"editor.lib"
	}
	
	dependson
	{
		"editor"
	}
end
	
	-- Files
	files 
	{
		RUNTIME_DIR .. "/**.h",
		RUNTIME_DIR .. "/**.cpp",
		RUNTIME_DIR .. "/**.hpp",
		RUNTIME_DIR .. "/**.inl"
	}
	
	--	"debug"
	filter "configurations:debug"
		targetdir (TARGET_DIR_DEBUG)
		debugdir (TARGET_DIR_DEBUG)
		debugformat (DEBUG_FORMAT)
			
	--	"release"
	filter "configurations:release"
		targetdir (TARGET_DIR_RELEASE)
		debugdir (TARGET_DIR_RELEASE)

	
