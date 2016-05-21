#ifndef DATA_GLOBAL_HPP_INCLUDED
#define DATA_GLOBAL_HPP_INCLUDED
#include <boost/filesystem.hpp>
#include <QMainWindow>

namespace global
{
	//some global literals:
	constexpr const char* const letters{"qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM"};
	constexpr const char* const numbers{"1234567890"};
	constexpr const char* const specials{"`~!@#$%^&*()-_=+[{]}\\|;:\'\",<.>/?\t"};
	constexpr const char* const chars{"qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890`~!@#$%^&*()-_=+[{]}\\|;:\'\",<.>/?\t"};

	//global variables:
	extern boost::filesystem::path root;
	extern QMainWindow *main_window;
}

#endif