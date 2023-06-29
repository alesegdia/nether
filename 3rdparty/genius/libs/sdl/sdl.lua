
dofile("sdl-files.lua")

function defineSDLLib(baseDir)
	defineStaticLib("sdl", ".", ".", true)

		includedirs {
			sdlIncludeDirs(baseDir)
		}

		files {
			sdlCommonSources(baseDir)
		}

		configuration { "linux*" }
			files {
				sdlLinuxSources(baseDir)
			}

		configuration { "vs20*" }
			files {
				sdlWinSources(baseDir)
			}
			defines {
				"SDL_VIDEO_DRIVER_DUMMY",
				"SDL_AUDIO_DRIVER_DUMMY",
			}
			defines {
				"HAVE_LIBC",
			}

		configuration { "mingw*" }
			files {
				sdlMingwSources(baseDir)
			}
end
