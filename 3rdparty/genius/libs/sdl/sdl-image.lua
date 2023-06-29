
function defineSDLImageLib(baseDir, sdlBaseDir, libpngBaseDir, zlibBaseDir)
	defineStaticLib("sdl-image", ".", ".", true)

	configuration {}
	
	defines {
		"LOAD_PNG",
	}
	
	includedirs {
		baseDir,
		zlibBaseDir,
		libpngBaseDir,
		path.join(sdlBaseDir, "include"),
	}

	files {
		path.join(baseDir, "SDL_image.h"),
		path.join(baseDir, "IMG.c"),
		path.join(baseDir, "IMG_png.c"),
		path.join(baseDir, "IMG_bmp.c"),
		path.join(baseDir, "IMG_gif.c"),
		path.join(baseDir, "IMG_jpg.c"),
		path.join(baseDir, "IMG_lbm.c"),
		path.join(baseDir, "IMG_pcx.c"),
		path.join(baseDir, "IMG_pnm.c"),
		path.join(baseDir, "IMG_svg.c"),
		path.join(baseDir, "IMG_tga.c"),
		path.join(baseDir, "IMG_tif.c"),
		path.join(baseDir, "IMG_webp.c"),
		path.join(baseDir, "IMG_xcf.c"),
		path.join(baseDir, "IMG_xpm.c"),
		path.join(baseDir, "IMG_xv.c"),
		path.join(baseDir, "IMG_xxx.c"),
	}

	configuration { "vs20*" } 
		defines {
			"CRT_SECURE_NO_DEPRECATE"
		}

	configuration {}
end

