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
	defineLib(true, name, buildPath, targetDir, ignoreWarnings)
end

function defineDynamicLib(name, buildPath, targetDir, ignoreWarnings)
	defineLib(false, name, buildPath, targetDir, ignoreWarnings)
end

function defineLib(static, name, buildPath, targetDir, ignoreWarnings)
	project (name)
	location (buildPath)
	objdir(buildPath)
	if static then
		kind "StaticLib"
	else
		kind "SharedLib"
	end
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
