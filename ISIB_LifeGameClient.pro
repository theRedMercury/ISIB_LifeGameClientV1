#-------------------------------------------------
#
# Project created by QtCreator 2016-03-01T13:00:54
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ISIB_LifeGameClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindowlifegame.cpp \
    mmapGpio.cpp

HEADERS  += mainwindowlifegame.h \
    mmapGpio.h

FORMS    += mainwindowlifegame.ui

isEmpty(TARGET_EXT) {
    win32 {
        TARGET_CUSTOM_EXT = .exe
    }
    macx {
        TARGET_CUSTOM_EXT = .app
    }
} else {
    TARGET_CUSTOM_EXT = $${TARGET_EXT}
}

win32 {
    DEPLOY_COMMAND = windeployqt
}
macx {
    DEPLOY_COMMAND = macdeployqt
}

CONFIG( debug, debug|release ) {
    # debug
    DEPLOY_TARGET = $$shell_quote($$shell_path($${OUT_PWD}/debug/$${TARGET}$${TARGET_CUSTOM_EXT}))
} else {
    # release
    DEPLOY_TARGET = $$shell_quote($$shell_path($${OUT_PWD}/release/$${TARGET}$${TARGET_CUSTOM_EXT}))
}

#  # Uncomment the following line to help debug the deploy command when running qmake
#  warning($${DEPLOY_COMMAND} $${DEPLOY_TARGET})

QMAKE_POST_LINK = $${DEPLOY_COMMAND} $${DEPLOY_TARGET}

RESOURCES += \
    data.qrc
