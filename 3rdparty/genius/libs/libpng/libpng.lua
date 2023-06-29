function copyFile(inFile, outFile)
    infile = io.open(inFile, "r")
    instr = infile:read("*a")
    infile:close()

    outfile = io.open(outFile, "w")
    outfile:write(instr)
    outfile:close()
end

function defineLibPNGLib(baseDir, zlibBaseDir)

copyFile(path.join(baseDir, "scripts/pnglibconf.h.prebuilt"), path.join(baseDir, "pnglibconf.h"))

defineStaticLib("libpng", ".", ".", true)

	configuration {}
	
	includedirs {
		baseDir,
		zlibBaseDir,
	}

	files {
		path.join(baseDir, "png.c"),
		path.join(baseDir, "pngerror.c"),
		path.join(baseDir, "pngget.c"),
		path.join(baseDir, "pngmem.c"),
		path.join(baseDir, "pngread.c"),
		path.join(baseDir, "pngpread.c"),
		path.join(baseDir, "pngrio.c"),
		path.join(baseDir, "pngrtran.c"),
		path.join(baseDir, "pngrutil.c"),
		path.join(baseDir, "pngset.c"),
		path.join(baseDir, "pngtrans.c"),
		path.join(baseDir, "pngwio.c"),
		path.join(baseDir, "pngwrite.c"),
		path.join(baseDir, "pngwtran.c"),
		path.join(baseDir, "pngwutil.c"),

		-- PRIVATE HEADERS
		path.join(baseDir, "pngpriv.h"),
		path.join(baseDir, "pngdebug.h"),
		path.join(baseDir, "pnginfo.h"),
		path.join(baseDir, "pngstruct.h"),

		-- PUBLIC HEADERS
		path.join(baseDir, "png.h"),
		path.join(baseDir, "pngconf.h"),
		path.join(baseDir, "pnglibconf.h"),
	}
end




