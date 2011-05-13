#-------------------------------------------------
#
# Project created by QtCreator 2011-04-25T14:17:15
#
#-------------------------------------------------

#CONFIG += static
QT += core gui webkit network script

TARGET = TelecaFacebook
TEMPLATE = app

HDR_DIR = ./hdr
DIALOGS_HDR_DIR = $$HDR_DIR/dialogs
QJSON_HDR_DIR = $$HDR_DIR/qjson

LIBS += -L./lib/ -lqjson

SRC_DIR = ./src
DIALOGS_SRC_DIR = $$SRC_DIR/dialogs
QJSON_SRC_DIR = $$SRC_DIR/qjson

RESOURCES_DIR = ./resources
TRANSLATION_DIR = $$RESOURCES/translate

Libs.path += lib/
INSTALLS += Libs

INCLUDEPATH += . $$DIALOGS_HDR_DIR $$HDR_DIR $$QJSON_HDR_DIR

HEADERS =   $$QJSON_HDR_DIR/parser.h                        \
            $$HDR_DIR/FacebookLogger.h                      \
            $$HDR_DIR/DialogEvent.h                         \
            $$HDR_DIR/FacebookDialog.h                      \
            $$HDR_DIR/DialogManager.h                       \
            $$HDR_DIR/ThreadSleep.h                         \
            $$HDR_DIR/FacebookNetwokClient_def.h            \
            $$HDR_DIR/FacebookNetwokManager.h               \
            $$HDR_DIR/HTMLButton.h                          \
                                                            \
            $$DIALOGS_HDR_DIR/DialogLogin.h                 \
            $$DIALOGS_HDR_DIR/DialogMainMenu.h              \
            $$DIALOGS_HDR_DIR/DialogMyFriends.h             \
            $$DIALOGS_HDR_DIR/DialogMyFriendsTableModel.h   \
            $$DIALOGS_HDR_DIR/DialogMyFriendsDetails.h      \
            $$DIALOGS_HDR_DIR/DialogGroupsTableModel.h      \
            $$DIALOGS_HDR_DIR/DialogGroups.h                \
            $$DIALOGS_HDR_DIR/DialogGroupsDetails.h         \
            $$DIALOGS_HDR_DIR/DialogNews.h                  \
            $$DIALOGS_HDR_DIR/DialogNewsListModel.h         \


SOURCES =   $$SRC_DIR/main.cpp                              \
            $$SRC_DIR/FacebookLogger.cpp                    \
            $$SRC_DIR/DialogEvent.cpp                       \
            $$SRC_DIR/FacebookDialog.cpp                    \
            $$SRC_DIR/DialogManager.cpp                     \
            $$SRC_DIR/FacebookNetwokManager.cpp             \
            $$DIALOGS_SRC_DIR/DialogLogin.cpp               \
            $$DIALOGS_SRC_DIR/DialogMainMenu.cpp            \
            $$DIALOGS_SRC_DIR/DialogMyFriends.cpp           \
            $$DIALOGS_SRC_DIR/DialogMyFriendsTableModel.cpp \
            $$DIALOGS_SRC_DIR/DialogGroups.cpp              \
            $$DIALOGS_SRC_DIR/DialogGroupsTableModel.cpp    \
            $$DIALOGS_SRC_DIR/DialogMyFriendsDetails.cpp    \
            $$DIALOGS_SRC_DIR/DialogGroupsDetails.cpp       \
            $$DIALOGS_SRC_DIR//DialogNews.cpp               \
            $$DIALOGS_SRC_DIR//DialogNewsListModel.cpp      \

# Supporting main application icon
RC_FILE = $$RESOURCES_DIR/telecaFacebook.rc

# Add new resource file for any independent dialog
RESOURCES = $$RESOURCES_DIR/dialog_resources.qrc

TRANSLATIONS = $$TRANSLATION_DIR/telecaFacebook.ts
