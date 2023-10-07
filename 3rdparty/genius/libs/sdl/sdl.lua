
dofile("sdl-files.lua")

function defineSDLLib(baseDir, buildPath)
	defineStaticLib("sdl", buildPath, ".", true)

		includedirs {
			sdlIncludeDirs(baseDir)
		}

		files {
			sdlCommonSources(baseDir)
		}

		links {

			"kernel32",
"user32",
"gdi32",
"winmm",
"imm32",
"ole32",
"oleaut32",
"version",
"uuid",
"advapi32",
"setupapi",
"shell32",
"dinput8",
"kernel32",
"user32",
"gdi32",
"winspool",
"shell32",
"ole32",
"oleaut32",
"uuid",
"comdlg32",
"advapi32",


		}

		configuration { "vs20*" }
			defines {
				"SDL_VIDEO_DRIVER_DUMMY",
				"SDL_AUDIO_DRIVER_DUMMY",
			}
			defines {
				"HAVE_LIBC",
			}

end
