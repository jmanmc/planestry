platform = os.get():gsub("^%l", string.upper)
action = _ACTION or ""
platformdef = ""
platformname = ""
RootDir = os.getcwd() .. "../../../"

if platform == "Windows" then
	platformdef = "_WIN32"
	platformname = "win32"
elseif platform == "Linux" then
	platformdef = "_LINUX"
	platformname = "linux"
end

os.chdir(RootDir)

solution "demo2"
	location "build"
	configurations {"Debug" .. platform, "Release" .. platform}
	
	project "demo2"
		kind "ConsoleApp"
		language "C++"
		location "build"
		
		links { "SDL", 
				"SDLmain", 
				"glu32", 
				"opengl32", 
				"curllib" }
		
	files { "src/**.cpp", "src/**.c", 
			"include/**.h", "include/**.hpp"}
	
	configuration { "Debug" .. platform}
		defines   { "DEBUG", platformdef, "CURL_STATICLIB" }
		flags     { "Symbols" }
		
		libdirs   { "lib", "lib/" .. platformname .. "/Debug"}
		includedirs { "include", "include/" .. platformname .. "/Debug", "include/curl", "include/sdl"}
		
		targetdir ("Debug-" .. platformname)
		objdir ("Debug-" .. platformname)
		
	configuration { "Release" .. platform}
		defines   { "NDEBUG", platformdef, "CURL_STATICLIB" }
		flags     { "Optimize" }
		links { "Irrlicht" }
		
		libdirs   { "lib", "lib/" .. platformname .. "/Release"}
		includedirs { "include", "include/" .. platformname .. "/Release", "include/curl", "include/sdl"}
		
		targetdir ("Release-" .. platformname)
		objdir ("Release-" .. platformname)
		
		
	configuration "linux"
		links { "dl" }
		
		-- includedirs{ "include/", "include/" .. platformname, "include/" .. platformname .. "/**"}
		
		-- files { "include/*.h", "src/*.cpp"}
		-- files { "include/" .. platformname .. "/**.h", "src/" .. platformname .. "/**.cpp" }

-- if _ACTION == "clean" then
	--	os.rmdir("bin")
	--	os.rmdir("build")
-- end