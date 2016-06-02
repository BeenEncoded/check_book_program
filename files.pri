#Files releavant to full builds (aka: release and debug builds)

#additionally, add the source diretcory to the list of includes:
QMAKE_CXXFLAGS += /IC:\Users\Jonathan\Documents\C++\Current_Projects\check_book_program\source

SOURCES += source/main.cpp \
			source/data/global.cpp \
            source/gui/MainWindow.cpp \
            source/gui/main_widgets/ManageAccounts.cpp \
            source/gui/information_dialogs/AccountInformation.cpp \
			source/gui/data_input/EditAccount.cpp \
            source/utility/filesystem.cpp \
            source/utility/stream_operations.cpp \
            source/utility/time_class.cpp \
            source/data/account.cpp \
			source/gui/data_input/NewTransaction.cpp \
			source/utility/file_loader.cpp \
			source/gui/data_input/MoneyTransfer.cpp \
			source/interface/mysql_account_interface.cpp \
			source/utility/database.cpp

HEADERS  += source/data/global.hpp \
			source/gui/MainWindow.hpp \
            source/gui/main_widgets/ManageAccounts.hpp \
            source/gui/information_dialogs/AccountInformation.hpp \
			source/gui/data_input/EditAccount.hpp \
            source/utility/filesystem.hpp \
            source/utility/stream_operations.hpp \
            source/utility/time_class.hpp \
            source/data/account.hpp \
			source/gui/data_input/NewTransaction.hpp \
			source/utility/file_loader.hpp \
			source/gui/data_input/MoneyTransfer.hpp \
			source/interface/mysql_account_interface.hpp \
			source/utility/database.hpp

FORMS    += source/gui/MainWindow.ui \
            source/gui/main_widgets/ManageAccounts.ui \
            source/gui/information_dialogs/AccountInformation.ui \
			source/gui/data_input/EditAccount.ui \
			source/gui/data_input/NewTransaction.ui \
			source/gui/data_input/MoneyTransfer.ui

#RESOURCES += 