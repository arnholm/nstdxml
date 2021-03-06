-- premake5 script, generated by Code::Blocks plugin premake5cb by cacb

function build_location()
   -- _ACTION is the premake5 action, e.g. gmake2, vs2019 etc.
   return "build/".._ACTION
end

function file_exists(name)
   local f=io.open(name,"r")
   if f~=nil then io.close(f) return true else return false end
end

function external_dependencies()
    if file_exists("NSTDXML_external_dependencies.lua") then
       include "NSTDXML_external_dependencies.lua"
       print ("including 'NSTDXML_external_dependencies.lua'")
    end
end

function post_build_copy()
   postbuildcommands ( "{MKDIR} %{wks.location}/%{cfg.shortname}" ) 
   postbuildcommands ( "{COPYFILE} %{cfg.buildtarget.directory}/* %{wks.location}/%{cfg.shortname}" ) 
end

workspace "NSTDXML"
	location ( build_location() )
	external_dependencies()
	post_build_copy()
	configurations { "debug","release" } 

	project "nstdxml"
		location ( build_location().."/nstdxml" )
		architecture  ( "x86_64" ) 
		cppdialect  ( "c++17" ) 
		defines ( "NSTDXML_IMPLEMENTATION" ) 
		exceptionhandling  ( "on" ) 
		includedirs ( "nstdxml" ) 
		language  ( "c++" ) 
		pic  ( "on" ) 
		rtti  ( "on" ) 
		staticruntime  ( "off" ) 

		-- 'files' paths are relative to premake file
		files {
			"nstdxml/nstdxml.h"
			,"nstdxml/nstdxml_config.h"
			,"nstdxml/xmlParser/xmlParser.cpp"
			,"nstdxml/xmlParser/xmlParser.h"
			,"nstdxml/xml_node.cpp"
			,"nstdxml/xml_node.h"
			,"nstdxml/xml_tree.cpp"
			,"nstdxml/xml_tree.h"
			}

		filter { "configurations:debug" }
			cppdialect ( "c++11" ) 
			defines  ( "DEBUG" ) 
			kind ( "SharedLib" ) 
			symbols  ( "on" ) 
			targetname ( "nstdxmld" ) 
		filter { }

		filter { "configurations:release" }
			cppdialect ( "c++11" ) 
			defines  ( "NDEBUG" ) 
			kind ( "SharedLib" ) 
			optimize  ( "on" ) 
			targetname ( "nstdxml" ) 
		filter { }

	project "nstdxml_test"
		location ( build_location().."/nstdxml_test" )
		architecture  ( "x86_64" ) 
		cppdialect  ( "c++17" ) 
		dependson ( "nstdxml" ) 
		exceptionhandling  ( "on" ) 
		includedirs { ".","nstdxml","nstdxml_test" } 
		language  ( "c++" ) 
		pic  ( "on" ) 
		rtti  ( "on" ) 
		staticruntime  ( "off" ) 

		-- 'files' paths are relative to premake file
		files {
			"nstdxml_test/main.cpp"
			,"nstdxml_test/test_data/csg_wikipedia.h"
			}

		filter { "configurations:debug" }
			cppdialect ( "c++11" ) 
			defines  ( "DEBUG" ) 
			kind ( "ConsoleApp" ) 
			-- When linking within workspace, 'links' refer to project name.
			links ( "nstdxml" ) 
			symbols  ( "on" ) 
			targetname ( "nstdxml_testd" ) 
		filter { }

		filter { "configurations:release" }
			cppdialect ( "c++11" ) 
			defines  ( "NDEBUG" ) 
			kind ( "ConsoleApp" ) 
			-- When linking within workspace, 'links' refer to project name.
			links ( "nstdxml" ) 
			optimize  ( "on" ) 
			targetname ( "nstdxml_test" ) 
		filter { }
