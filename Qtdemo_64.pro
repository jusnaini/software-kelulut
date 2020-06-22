DEFINES += QWT_DLL
TEMPLATE = app
FORMS = analog_io.ui \
    digital_io.ui \
    eeprom.ui \
    qtdemo_64.ui
HEADERS = application.h \
    qtdemo_64.h \
    analog_io.h \
    digital_io.h \
    eeprom.h \
    plot.h \
    ui_analog_io.h \
    ui_digital_io.h \
    ui_eeprom.h \
    ui_qtdemo_64.h
SOURCES = application.cpp \
    main.cpp \
    qtdemo_64.cpp \
    analog_io.cpp \
    digital_io.cpp \
    eeprom.cpp \
    plot.cpp
#LIBS += -lavs \
#    -lqwt
LIBS += -lavs\
    -L/usr/local/qwt-6.1.4/lib -lqwt

QT += widgets network

#@CONFIG += c++11@
CONFIG += c++11

#unix:!macx: LIBS += -L$$PWD/../../../../../usr/local/lib/ -lavs

#INCLUDEPATH += $$PWD/../../../../../usr/local/include
#DEPENDPATH += $$PWD/../../../../../usr/local/include
