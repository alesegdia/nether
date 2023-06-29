function sdlIncludeDirs(baseDir)
	return {
		path.join(baseDir, "include"),
		path.join(baseDir, "src/hidapi/hidapi"),
	}
end

function sdlCommonSources(baseDir)
	return {
		path.join(baseDir, "include/*.h"),
		path.join(baseDir, "src/*.c"),
		path.join(baseDir, "src/**.h"),	
		path.join(baseDir, "src/atomic/*.c"),
		path.join(baseDir, "src/audio/*.c"),
		path.join(baseDir, "src/audio/dummy/*.c"),
		path.join(baseDir, "src/audio/disk/*.c"),
		path.join(baseDir, "src/cpuinfo/*.c"),
		path.join(baseDir, "src/dynapi/*.c"),
		path.join(baseDir, "src/events/*.c"),
		path.join(baseDir, "src/file/*.c"),
		path.join(baseDir, "src/haptic/*.c"),
		path.join(baseDir, "src/haptic/dummy/*.c"),
		path.join(baseDir, "src/joystick/*.c"),
		path.join(baseDir, "src/joystick/hidapi/*.c"),
		path.join(baseDir, "src/joystick/virtual/*.c"),
		path.join(baseDir, "src/power/*.c"),
		path.join(baseDir, "src/render/*.c"),
		path.join(baseDir, "src/render/software/*.c"),
		path.join(baseDir, "src/sensor/*.c"),
		path.join(baseDir, "src/sensor/dummy/*.c"),
		path.join(baseDir, "src/stdlib/*.c"),
		path.join(baseDir, "src/thread/*.c"),
		path.join(baseDir, "src/timer/*.c"),
		path.join(baseDir, "src/timer/dummy/*.c"),
		path.join(baseDir, "src/video/*.c"),
		path.join(baseDir, "src/video/dummy/*.c"),
		path.join(baseDir, "src/video/yuv2rgb/*.c"),
		path.join(baseDir, "src/locale/*.c"),
	}
end

function sdlLinuxSources(baseDir)
	return {
		path.join(baseDir, "config/sdl/linux/include/*.h"),
		path.join(baseDir, "src/audio/pulseaudio/*.c"),
		path.join(baseDir, "src/audio/dsp/*.c"),
		path.join(baseDir, "src/audio/alsa/*.c"),
		path.join(baseDir, "src/core/linux/*.c"),
		path.join(baseDir, "src/atomic/SDL_atomic.c"),
		path.join(baseDir, "src/atomic/SDL_spinlock.c"),
		path.join(baseDir, "src/haptic/linux/*.c"),
		path.join(baseDir, "src/joystick/linux/*.c"),
		path.join(baseDir, "src/joystick/steam/*.c"),
		path.join(baseDir, "src/power/linux/*.c"),
		path.join(baseDir, "src/filesystem/unix/*.c"),
		path.join(baseDir, "src/video/wayland/*.c"),
		path.join(baseDir, "src/video/x11/*.c"),
		path.join(baseDir, "src/render/opengl/*.c"),
		path.join(baseDir, "src/render/opengles/*.c"),
		path.join(baseDir, "src/render/opengles2/*.c"),
		path.join(baseDir, "src/libm/*.c"),
	}
end

function sdlWinSources(baseDir)
	return {
		path.join(baseDir, "src/audio/directsound/*.c"),
		path.join(baseDir, "src/audio/winmm/*.c"),
		path.join(baseDir, "src/audio/xaudio2/*.c"),
		path.join(baseDir, "src/audio/wasapi/*.c"),		
		path.join(baseDir, "src/haptic/windows/*.c"),
		path.join(baseDir, "src/hidapi/windows/*.c"),
		path.join(baseDir, "src/joystick/windows/*.c"),
		path.join(baseDir, "src/thread/windows/*.c"),
		path.join(baseDir, "src/thread/generic/SDL_syscond.c"),
		path.join(baseDir, "src/video/windows/*.c"),
		path.join(baseDir, "src/core/windows/*.c"),
		path.join(baseDir, "src/filesystem/windows/*.c"),
		path.join(baseDir, "src/loadso/windows/*.c"),
		path.join(baseDir, "src/power/windows/*.c"),
		path.join(baseDir, "src/timer/windows/*.c"),
		path.join(baseDir, "src/render/direct3d/*.c"),
		path.join(baseDir, "src/render/direct3d11/*.c"),
		path.join(baseDir, "src/render/opengl/*.c"),
	    path.join(baseDir, "src/render/opengles/*.c"),
	    path.join(baseDir, "src/render/opengles2/*.c"),
	    path.join(baseDir, "src/locale/windows/*.c"),
	    path.join(baseDir, "src/sensor/windows/*.c"),
		path.join(baseDir, "src/libm/*.c"),
		path.join(baseDir, "src/main/windows/*.c"),
	}
end

function sdlMingwSources(baseDir)
	return {
		path.join(baseDir, "src/audio/directsound/*.c"),
		path.join(baseDir, "src/audio/winmm/*.c"),
		path.join(baseDir, "src/audio/wasapi/*.c"),
		path.join(baseDir, "src/haptic/windows/*.c"),
		path.join(baseDir, "src/hidapi/windows/*.c"),
		path.join(baseDir, "src/joystick/windows/*.c"),
		path.join(baseDir, "src/thread/windows/*.c"),
		path.join(baseDir, "src/thread/generic/SDL_syscond.c"),
		path.join(baseDir, "src/video/windows/*.c"),
		path.join(baseDir, "src/core/windows/*.c"),
		path.join(baseDir, "src/filesystem/windows/*.c"),
		path.join(baseDir, "src/loadso/windows/*.c"),
		path.join(baseDir, "src/power/windows/*.c"),
		path.join(baseDir, "src/timer/windows/*.c"),
		path.join(baseDir, "src/render/direct3d/*.c"),
		path.join(baseDir, "src/render/opengl/*.c"),
	    path.join(baseDir, "src/render/opengles/*.c"),
	    path.join(baseDir, "src/render/opengles2/*.c"),		
		path.join(baseDir, "src/libm/*.c"),
	}
end