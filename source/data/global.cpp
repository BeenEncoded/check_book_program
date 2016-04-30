#include <boost/filesystem.hpp>
#include <QDir>

#include "global.hpp"

namespace global
{
	using boost::filesystem::path;

	path root{path{QDir::homePath().toStdWString()} / path{".Checkbook_Program"}};
	QMainWindow *main_window{nullptr};
}