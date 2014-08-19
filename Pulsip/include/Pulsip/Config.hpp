#ifndef PULSIP_CONFIG_HPP
#define PULSIP_CONFIG_HPP

#define PULSIP_VERSION_MAJOR 0
#define PULSIP_VERSION_MINOR 1

//Identify the operating system
#if defined(_WIN32) || defined(__WIN32__)
	
		// Windows
		#define PULSIP_SYSTEM_WINDOWS
	
#elif defined(linux) || defined(__linux)
	
		// Linux
		#define PULSIP_SYSTEM_LINUX
	
#elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)
	
	// MacOS
	#define PULSIP_SYSTEM_MACOS
	
#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
	
	// FreeBSD
	#define PULSIP_SYSTEM_FREEBSD
	
#else
	
	// Unsupported system
	#error This operating system is not supported by PULSIP library
	
#endif

#if !defined(PULSIP_STATIC)
	
	#if defined(PULSIP_SYSTEM_WINDOWS)
		
		// Windows compilers need specific (and different) keywords for export and import
	#define PULSIP_API_EXPORT __declspec(dllexport)
	#define PULSIP_API_IMPORT __declspec(dllimport)
		
		// For Visual C++ compilers, we also need to turn off this annoying C4251 warning
		#ifdef _MSC_VER
	
			#pragma warning(disable : 4251)
		
		#endif
	
	#else // Linux, FreeBSD, Mac OS X
	
		#if __GNUC__ >= 4
	
			// GCC 4 has special keywords for showing/hidding symbols,
			// the same keyword is used for both importing and exporting
			#define PULSIP_API_EXPORT __attribute__ ((__visibility__ ("default")))
			#define PULSIP_API_IMPORT __attribute__ ((__visibility__ ("default")))
	
		#else
	
			// GCC < 4 has no mechanism to explicitely hide symbols, everything's exported
			#define PULSIP_API_EXPORT
			#define PULSIP_API_IMPORT
	
		#endif
	
	#endif

#else

	// Static build doesn't need import/export macros
	#define PULSIP_API_EXPORT
	#define PULSIP_API_IMPORT

#endif

#ifdef PULSIP_EXPORTS
	#define PULSIP_API PULSIP_API_EXPORT
#else
	#define PULSIP_API PULSIP_API_IMPORT
#endif // PULSIP_EXPORTS

#endif
// !PULSIP_CONFIG_HPP
