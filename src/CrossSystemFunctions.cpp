#include <CrossSystemFunctions.hpp>

void CSF::adjustPath(std::string &path)
{
	#ifdef _WIN32
		std::replace( path.begin(), path.end(), '/', '\\');
	#else
		std::replace( path.begin(), path.end(), '\\', '/');
	#endif
}
