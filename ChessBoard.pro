HEADERS += \
    Board.h \
    Stone.h \
    Step.h \
    SingleGame.h \
    CalScoreWidget.h \
    NetGame.h \
    ChessDlg.h \
    MulitiGame.h

SOURCES += \
    Board.cpp \
    main.cpp \
    Stone.cpp \
    Step.cpp \
    SingleGame.cpp \
    CalScoreWidget.cpp \
    NetGame.cpp \
    ChessDlg.cpp \
    MulitiGame.cpp


QT += widgets gui network

RESOURCES += \
    myres.qrc

DISTFILES += \
    style.qss \
    res/css.qss
