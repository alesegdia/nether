
function defineRZTL(baseDir, buildPath)
	defineStaticLib("zlib", buildPath, ".", true)

		configuration {}

		includedirs {
			path.join(baseDir, "rztl/include"),
		}

		files {
			path.join(baseDir, "rztl/include/**.h"),
		}

end