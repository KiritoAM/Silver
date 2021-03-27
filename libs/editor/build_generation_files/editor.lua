

create_static_library("editor")
	
	includedirs 
    {
		LIB_DIRECTORY
	}
	
	-- Source
	files 
	{ 
		"../**.h",
		"../**.cpp",
		"../**.hpp",
		"../**.inl"
	}
	
	libdirs { TARGET_DIR_DEBUG }
	links
	{
		"core.lib",
		"engine.lib",
		"input.lib"
	}
	
	dependson
	{
		"engine",
		"input",
		"gui"
	}
	
	-- "debug"
	filter "configurations:debug"
		targetdir (TARGET_DIR_DEBUG)	
		debugdir (TARGET_DIR_DEBUG)
		debugformat (DEBUG_FORMAT)		
				
	-- "release"
	filter "configurations:release"
		targetdir (TARGET_DIR_RELEASE)
		debugdir (TARGET_DIR_RELEASE)