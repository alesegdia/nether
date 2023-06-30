
function defineZLib(baseDir, buildPath)
	defineStaticLib("zlib", buildPath, ".", true)

		configuration {}
		
		includedirs {
			path.join(baseDir, ""),
		}

		files {
			-- PUBLIC HEADERS
			path.join(baseDir, "zconf.h"),
			path.join(baseDir, "zlib.h"),

			-- PRIVATE HEADERS
			path.join(baseDir, "crc32.h"),
			path.join(baseDir, "deflate.h"),
			path.join(baseDir, "gzguts.h"),
			path.join(baseDir, "inffast.h"),
			path.join(baseDir, "inffixed.h"),
			path.join(baseDir, "infflate.h"),
			path.join(baseDir, "inftrees.h"),
			path.join(baseDir, "trees.h"),
			path.join(baseDir, "zutil.h"),

			-- SOURCES
			path.join(baseDir, "adler32.c"),
			path.join(baseDir, "compress.c"),
			path.join(baseDir, "crc32.c"),
			path.join(baseDir, "deflate.c"),
			path.join(baseDir, "gzclose.c"),
			path.join(baseDir, "gzlib.c"),
			path.join(baseDir, "gzread.c"),
			path.join(baseDir, "gzwrite.c"),
			path.join(baseDir, "inflate.c"),
			path.join(baseDir, "infback.c"),
			path.join(baseDir, "inftrees.c"),
			path.join(baseDir, "inffast.c"),
			path.join(baseDir, "trees.c"),
			path.join(baseDir, "uncompr.c"),
			path.join(baseDir, "zutil.c"),
		}

end