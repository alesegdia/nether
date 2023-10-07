
function defineSDLImageLib(baseDir, sdlBaseDir, libpngBaseDir, zlibBaseDir, buildPath)
	defineStaticLib("sdl-image", buildPath, ".", true)

	configuration {}
	
	defines {
		"LOAD_PNG",
	}
	
	includedirs {
		baseDir,
		zlibBaseDir,
		libpngBaseDir,
		path.join(sdlBaseDir, "include"),
		path.join(baseDir, "include"),
	}

	files {
		path.join(baseDir, "src/IMG.c"),
		path.join(baseDir, "src/IMG_WIC.c"),
		path.join(baseDir, "src/IMG_avif.c"),
		path.join(baseDir, "src/IMG_bmp.c"),
		path.join(baseDir, "src/IMG_gif.c"),
		path.join(baseDir, "src/IMG_jpg.c"),
		path.join(baseDir, "src/IMG_jxl.c"),
		path.join(baseDir, "src/IMG_lbm.c"),
		path.join(baseDir, "src/IMG_pcx.c"),
		path.join(baseDir, "src/IMG_png.c"),
		path.join(baseDir, "src/IMG_pnm.c"),
		path.join(baseDir, "src/IMG_qoi.c"),
		path.join(baseDir, "src/IMG_stb.c"),
		path.join(baseDir, "src/IMG_svg.c"),
		path.join(baseDir, "src/IMG_tga.c"),
		path.join(baseDir, "src/IMG_tif.c"),
		path.join(baseDir, "src/IMG_webp.c"),
		path.join(baseDir, "src/IMG_xcf.c"),
		path.join(baseDir, "src/IMG_xpm.c"),
		path.join(baseDir, "src/IMG_xv.c"),
		path.join(baseDir, "src/IMG_xxx.c"),
		path.join(baseDir, "include/SDL3_image/SDL_image.h")
	}

	configuration { "vs20*" } 
		defines {
			"CRT_SECURE_NO_DEPRECATE"
		}

	configuration {}
end

