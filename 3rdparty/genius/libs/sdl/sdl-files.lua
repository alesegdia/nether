function sdlIncludeDirs(baseDir)
	return {
		path.join(baseDir, "include"),
		path.join(baseDir, "src"),
		path.join(baseDir, "src/hidapi/hidapi"),
	}
end

function sdlCommonSources(baseDir)
	return {
		path.join(baseDir, "src/SDL.c"),
		path.join(baseDir, "src/SDL_assert.c"),
		path.join(baseDir, "src/SDL_error.c"),
		path.join(baseDir, "src/SDL_guid.c"),
		path.join(baseDir, "src/SDL_hints.c"),
		path.join(baseDir, "src/SDL_list.c"),
		path.join(baseDir, "src/SDL_log.c"),
		path.join(baseDir, "src/SDL_utils.c"),
		path.join(baseDir, "src/atomic/SDL_atomic.c"),
		path.join(baseDir, "src/atomic/SDL_spinlock.c"),
		path.join(baseDir, "src/audio/SDL_audio.c"),
		path.join(baseDir, "src/audio/SDL_audiocvt.c"),
		path.join(baseDir, "src/audio/SDL_audiodev.c"),
		path.join(baseDir, "src/audio/SDL_audioqueue.c"),
		path.join(baseDir, "src/audio/SDL_audioresample.c"),
		path.join(baseDir, "src/audio/SDL_audiotypecvt.c"),
		path.join(baseDir, "src/audio/SDL_mixer.c"),
		path.join(baseDir, "src/audio/SDL_wave.c"),
		path.join(baseDir, "src/core/SDL_runapp.c"),
		path.join(baseDir, "src/cpuinfo/SDL_cpuinfo.c"),
		path.join(baseDir, "src/dynapi/SDL_dynapi.c"),
		path.join(baseDir, "src/events/SDL_clipboardevents.c"),
		path.join(baseDir, "src/events/SDL_displayevents.c"),
		path.join(baseDir, "src/events/SDL_dropevents.c"),
		path.join(baseDir, "src/events/SDL_events.c"),
		path.join(baseDir, "src/events/SDL_keyboard.c"),
		path.join(baseDir, "src/events/SDL_keysym_to_scancode.c"),
		path.join(baseDir, "src/events/SDL_mouse.c"),
		path.join(baseDir, "src/events/SDL_quit.c"),
		path.join(baseDir, "src/events/SDL_scancode_tables.c"),
		path.join(baseDir, "src/events/SDL_touch.c"),
		path.join(baseDir, "src/events/SDL_windowevents.c"),
		path.join(baseDir, "src/events/imKStoUCS.c"),
		path.join(baseDir, "src/file/SDL_rwops.c"),
		path.join(baseDir, "src/haptic/SDL_haptic.c"),
		path.join(baseDir, "src/hidapi/SDL_hidapi.c"),
		path.join(baseDir, "src/joystick/SDL_gamepad.c"),
		path.join(baseDir, "src/joystick/SDL_joystick.c"),
		path.join(baseDir, "src/joystick/controller_type.c"),
		path.join(baseDir, "src/libm/e_atan2.c"),
		path.join(baseDir, "src/libm/e_exp.c"),
		path.join(baseDir, "src/libm/e_fmod.c"),
		path.join(baseDir, "src/libm/e_log.c"),
		path.join(baseDir, "src/libm/e_log10.c"),
		path.join(baseDir, "src/libm/e_pow.c"),
		path.join(baseDir, "src/libm/e_rem_pio2.c"),
		path.join(baseDir, "src/libm/e_sqrt.c"),
		path.join(baseDir, "src/libm/k_cos.c"),
		path.join(baseDir, "src/libm/k_rem_pio2.c"),
		path.join(baseDir, "src/libm/k_sin.c"),
		path.join(baseDir, "src/libm/k_tan.c"),
		path.join(baseDir, "src/libm/s_atan.c"),
		path.join(baseDir, "src/libm/s_copysign.c"),
		path.join(baseDir, "src/libm/s_cos.c"),
		path.join(baseDir, "src/libm/s_fabs.c"),
		path.join(baseDir, "src/libm/s_floor.c"),
		path.join(baseDir, "src/libm/s_modf.c"),
		path.join(baseDir, "src/libm/s_scalbn.c"),
		path.join(baseDir, "src/libm/s_sin.c"),
		path.join(baseDir, "src/libm/s_tan.c"),
		path.join(baseDir, "src/locale/SDL_locale.c"),
		path.join(baseDir, "src/misc/SDL_url.c"),
		path.join(baseDir, "src/power/SDL_power.c"),
		path.join(baseDir, "src/render/SDL_d3dmath.c"),
		path.join(baseDir, "src/render/SDL_render.c"),
		path.join(baseDir, "src/render/SDL_yuv_sw.c"),
		path.join(baseDir, "src/render/direct3d/SDL_render_d3d.c"),
		path.join(baseDir, "src/render/direct3d/SDL_shaders_d3d.c"),
		path.join(baseDir, "src/render/direct3d11/SDL_render_d3d11.c"),
		path.join(baseDir, "src/render/direct3d11/SDL_shaders_d3d11.c"),
		path.join(baseDir, "src/render/direct3d12/SDL_render_d3d12.c"),
		path.join(baseDir, "src/render/direct3d12/SDL_shaders_d3d12.c"),
		path.join(baseDir, "src/render/opengl/SDL_render_gl.c"),
		path.join(baseDir, "src/render/opengl/SDL_shaders_gl.c"),
		path.join(baseDir, "src/render/opengles2/SDL_render_gles2.c"),
		path.join(baseDir, "src/render/opengles2/SDL_shaders_gles2.c"),
		path.join(baseDir, "src/render/ps2/SDL_render_ps2.c"),
		path.join(baseDir, "src/render/psp/SDL_render_psp.c"),
		path.join(baseDir, "src/render/software/SDL_blendfillrect.c"),
		path.join(baseDir, "src/render/software/SDL_blendline.c"),
		path.join(baseDir, "src/render/software/SDL_blendpoint.c"),
		path.join(baseDir, "src/render/software/SDL_drawline.c"),
		path.join(baseDir, "src/render/software/SDL_drawpoint.c"),
		path.join(baseDir, "src/render/software/SDL_render_sw.c"),
		path.join(baseDir, "src/render/software/SDL_rotate.c"),
		path.join(baseDir, "src/render/software/SDL_triangle.c"),
		path.join(baseDir, "src/render/vitagxm/SDL_render_vita_gxm.c"),
		path.join(baseDir, "src/render/vitagxm/SDL_render_vita_gxm_memory.c"),
		path.join(baseDir, "src/render/vitagxm/SDL_render_vita_gxm_tools.c"),
		path.join(baseDir, "src/sensor/SDL_sensor.c"),
		path.join(baseDir, "src/stdlib/SDL_crc16.c"),
		path.join(baseDir, "src/stdlib/SDL_crc32.c"),
		path.join(baseDir, "src/stdlib/SDL_getenv.c"),
		path.join(baseDir, "src/stdlib/SDL_iconv.c"),
		path.join(baseDir, "src/stdlib/SDL_malloc.c"),
		path.join(baseDir, "src/stdlib/SDL_mslibc.c"),
		path.join(baseDir, "src/stdlib/SDL_qsort.c"),
		path.join(baseDir, "src/stdlib/SDL_stdlib.c"),
		path.join(baseDir, "src/stdlib/SDL_string.c"),
		path.join(baseDir, "src/stdlib/SDL_strtokr.c"),
		path.join(baseDir, "src/thread/SDL_thread.c"),
		path.join(baseDir, "src/timer/SDL_timer.c"),
		path.join(baseDir, "src/video/SDL_RLEaccel.c"),
		path.join(baseDir, "src/video/SDL_blit.c"),
		path.join(baseDir, "src/video/SDL_blit_0.c"),
		path.join(baseDir, "src/video/SDL_blit_1.c"),
		path.join(baseDir, "src/video/SDL_blit_A.c"),
		path.join(baseDir, "src/video/SDL_blit_N.c"),
		path.join(baseDir, "src/video/SDL_blit_auto.c"),
		path.join(baseDir, "src/video/SDL_blit_copy.c"),
		path.join(baseDir, "src/video/SDL_blit_slow.c"),
		path.join(baseDir, "src/video/SDL_bmp.c"),
		path.join(baseDir, "src/video/SDL_clipboard.c"),
		path.join(baseDir, "src/video/SDL_egl.c"),
		path.join(baseDir, "src/video/SDL_fillrect.c"),
		path.join(baseDir, "src/video/SDL_pixels.c"),
		path.join(baseDir, "src/video/SDL_rect.c"),
		path.join(baseDir, "src/video/SDL_shape.c"),
		path.join(baseDir, "src/video/SDL_stretch.c"),
		path.join(baseDir, "src/video/SDL_surface.c"),
		path.join(baseDir, "src/video/SDL_video.c"),
		path.join(baseDir, "src/video/SDL_vulkan_utils.c"),
		path.join(baseDir, "src/video/SDL_yuv.c"),
		path.join(baseDir, "src/video/yuv2rgb/yuv_rgb.c"),
		path.join(baseDir, "src/audio/dummy/SDL_dummyaudio.c"),
		path.join(baseDir, "src/audio/disk/SDL_diskaudio.c"),
		path.join(baseDir, "src/joystick/virtual/SDL_virtualjoystick.c"),
		path.join(baseDir, "src/video/dummy/SDL_nullevents.c"),
		path.join(baseDir, "src/video/dummy/SDL_nullframebuffer.c"),
		path.join(baseDir, "src/video/dummy/SDL_nullvideo.c"),
		path.join(baseDir, "src/core/windows/SDL_hid.c"),
		path.join(baseDir, "src/core/windows/SDL_immdevice.c"),
		path.join(baseDir, "src/core/windows/SDL_windows.c"),
		path.join(baseDir, "src/core/windows/SDL_xinput.c"),
		path.join(baseDir, "src/core/windows/pch.c"),
		path.join(baseDir, "src/misc/windows/SDL_sysurl.c"),
		path.join(baseDir, "src/audio/directsound/SDL_directsound.c"),
		path.join(baseDir, "src/audio/wasapi/SDL_wasapi.c"),
		path.join(baseDir, "src/audio/wasapi/SDL_wasapi_win32.c"),
		path.join(baseDir, "src/video/windows/SDL_windowsclipboard.c"),
		path.join(baseDir, "src/video/windows/SDL_windowsevents.c"),
		path.join(baseDir, "src/video/windows/SDL_windowsframebuffer.c"),
		path.join(baseDir, "src/video/windows/SDL_windowskeyboard.c"),
		path.join(baseDir, "src/video/windows/SDL_windowsmessagebox.c"),
		path.join(baseDir, "src/video/windows/SDL_windowsmodes.c"),
		path.join(baseDir, "src/video/windows/SDL_windowsmouse.c"),
		path.join(baseDir, "src/video/windows/SDL_windowsopengl.c"),
		path.join(baseDir, "src/video/windows/SDL_windowsopengles.c"),
		path.join(baseDir, "src/video/windows/SDL_windowsshape.c"),
		path.join(baseDir, "src/video/windows/SDL_windowsvideo.c"),
		path.join(baseDir, "src/video/windows/SDL_windowsvulkan.c"),
		path.join(baseDir, "src/video/windows/SDL_windowswindow.c"),
		path.join(baseDir, "src/thread/generic/SDL_syscond.c"),
		path.join(baseDir, "src/thread/generic/SDL_sysrwlock.c"),
		path.join(baseDir, "src/thread/windows/SDL_syscond_cv.c"),
		path.join(baseDir, "src/thread/windows/SDL_sysmutex.c"),
		path.join(baseDir, "src/thread/windows/SDL_sysrwlock_srw.c"),
		path.join(baseDir, "src/thread/windows/SDL_syssem.c"),
		path.join(baseDir, "src/thread/windows/SDL_systhread.c"),
		path.join(baseDir, "src/thread/windows/SDL_systls.c"),
		path.join(baseDir, "src/sensor/windows/SDL_windowssensor.c"),
		path.join(baseDir, "src/power/windows/SDL_syspower.c"),
		path.join(baseDir, "src/locale/windows/SDL_syslocale.c"),
		path.join(baseDir, "src/filesystem/windows/SDL_sysfilesystem.c"),
		path.join(baseDir, "src/timer/windows/SDL_systimer.c"),
		path.join(baseDir, "src/loadso/windows/SDL_sysloadso.c"),
		path.join(baseDir, "src/joystick/hidapi/SDL_hidapi_combined.c"),
		path.join(baseDir, "src/joystick/hidapi/SDL_hidapi_gamecube.c"),
		path.join(baseDir, "src/joystick/hidapi/SDL_hidapi_luna.c"),
		path.join(baseDir, "src/joystick/hidapi/SDL_hidapi_ps3.c"),
		path.join(baseDir, "src/joystick/hidapi/SDL_hidapi_ps4.c"),
		path.join(baseDir, "src/joystick/hidapi/SDL_hidapi_ps5.c"),
		path.join(baseDir, "src/joystick/hidapi/SDL_hidapi_rumble.c"),
		path.join(baseDir, "src/joystick/hidapi/SDL_hidapi_shield.c"),
		path.join(baseDir, "src/joystick/hidapi/SDL_hidapi_stadia.c"),
		path.join(baseDir, "src/joystick/hidapi/SDL_hidapi_steam.c"),
		path.join(baseDir, "src/joystick/hidapi/SDL_hidapi_switch.c"),
		path.join(baseDir, "src/joystick/hidapi/SDL_hidapi_wii.c"),
		path.join(baseDir, "src/joystick/hidapi/SDL_hidapi_xbox360.c"),
		path.join(baseDir, "src/joystick/hidapi/SDL_hidapi_xbox360w.c"),
		path.join(baseDir, "src/joystick/hidapi/SDL_hidapi_xboxone.c"),
		path.join(baseDir, "src/joystick/hidapi/SDL_hidapijoystick.c"),
		path.join(baseDir, "src/joystick/windows/SDL_dinputjoystick.c"),
		path.join(baseDir, "src/joystick/windows/SDL_rawinputjoystick.c"),
		path.join(baseDir, "src/joystick/windows/SDL_windows_gaming_input.c"),
		path.join(baseDir, "src/joystick/windows/SDL_windowsjoystick.c"),
		path.join(baseDir, "src/joystick/windows/SDL_xinputjoystick.c"),
		path.join(baseDir, "src/haptic/windows/SDL_dinputhaptic.c"),
		path.join(baseDir, "src/haptic/windows/SDL_windowshaptic.c"),
		path.join(baseDir, "src/haptic/windows/SDL_xinputhaptic.c"),
		path.join(baseDir, "src/video/offscreen/SDL_offscreenevents.c"),
		path.join(baseDir, "src/video/offscreen/SDL_offscreenframebuffer.c"),
		path.join(baseDir, "src/video/offscreen/SDL_offscreenopengles.c"),
		path.join(baseDir, "src/video/offscreen/SDL_offscreenvideo.c"),
		path.join(baseDir, "src/video/offscreen/SDL_offscreenwindow.c"),
	}
end

