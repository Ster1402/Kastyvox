QT += widgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RC_FILE = ic.rc

SOURCES += \
    dialog.cpp \
    fenetre.cpp \
    gestion_db.cpp \
    main.cpp \
    script.cpp

HEADERS += \
    dialog.h \
    fenetre.h \
    script.h

TRANSLATIONS += \
    KASTYVOX_fr_CM.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
