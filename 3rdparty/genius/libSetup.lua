function commonFlags()
		configuration {}
		flags {
			"StaticRuntime"
		}

	configuration { "debug" }
		flags {
			"Symbols"
		}

	configuration { "release" }
		flags {
			"Optimize",
			"OptimizeSize",
			"OptimizeSpeed"
		}

	configuration {}
end

function defineStaticLib(name, buildPath, targetDir, ignoreWarnings)
	project (name)
	location (buildPath)
	objdir(buildPath)
	kind "SharedLib"
	language "C"
	configurations { "debug", "release" }
	platforms { "x32", "x64" }
	targetdir (buildPath)
	commonFlags()
	if ignoreWarnings == true then
		flags(
		{
			"MinimumWarnings"
		})
	end
end
