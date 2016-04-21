HEADERS += \
    Board.h \
    Stone.h \
    Step.h \
    SingleGame.h \
    CalScoreWidget.h \
    NetGame.h

SOURCES += \
    Board.cpp \
    main.cpp \
    Stone.cpp \
    Step.cpp \
    SingleGame.cpp \
    CalScoreWidget.cpp \
    NetGame.cpp


QT += widgets gui network

RESOURCES += \
    myres.qrc

DISTFILES += \
    style.qss \
    res/css.qss
