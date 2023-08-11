solution("nether")
	location "build"

dofile("3rdparty/genius/genius.lua")

defineSDLLib("3rdparty/sdl", "build")

defineSDLImageLib(
	"3rdparty/sdl-image",
	"3rdparty/sdl",
	"3rdparty/libpng",
	"3rdparty/zlib",
	"build"
)

defineLibPNGLib(
	"3rdparty/libpng",
	"3rdparty/zlib",
	"build")

defineZLib("3rdparty/zlib", "build")

function netherProject(projectName)
	project (projectName)
	kind "ConsoleApp"
	language "C++"
	configurations { "debug", "release" }
	platforms { "x32", "x64" }
	defines { "GLAD_GL_IMPLEMENTATION" }
	flags{ "CppLatest" }
	objdir("build")
	targetdir("build")
	debugdir(".")

	configuration {}
		links {
			"DelayImp",
			"gdi32",
			"psapi",
			"Winmm",
			"imm32",
			"version",
			"Setupapi",
			"opengl32",
			"libpng",
			"zlib",
			"sdl-image",
			"sdl"
		}
		includedirs {
			"src",
			"3rdparty/glad/include",
			"3rdparty/glm",
			"module/rztl/include",
			sdlIncludeDirs("3rdparty/sdl")
		}

		files {
			"src/**/*.h",
			"src/**/*.cpp"
		}

	-- https://support.microsoft.com/es-es/help/154753/description-of-the-default-c-and-c-libraries-that-a-program-will-link
	configuration { "vs20*", "debug" }
		links { "LIBCMTD" }

	configuration { "vs20*", "release" }
		links { "LIBCMT" }

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

netherProject("nether")