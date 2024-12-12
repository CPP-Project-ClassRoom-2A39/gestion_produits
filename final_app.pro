QT       += core gui serialport
QT       += core gui charts
QT       += quick
QT       += quickwidgets
QT       += widgets printsupport
QT       += core gui multimedia multimediawidgets
QT       += sql
QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# Enable deprecated warnings
DEFINES += QT_DEPRECATED_WARNINGS
# Enable QZXing encoding support
DEFINES += QZXING_ENCODER_SUPPORT

# Source files
SOURCES += \
    Notifications/NotificationLayout.cpp \
    Notifications/NotificationWidget.cpp \
    Operation/Operation.cpp \
    QRCodeGenerator.cpp \
    Result/Result.cpp \
    client.cpp \
    connection.cpp \
    fournisseur.cpp \
    main.cpp \
    mainwindow.cpp \
    produit.cpp \
    smtp.cpp
HEADERS += \
    Notifications/NotificationLayout.h \
    Notifications/NotificationWidget.h \
    Operation/Operation.h \
    QRCodeGenerator.h \
    Result/Result.h \
    client.h \
    connection.h \
    fournisseur.h \
    mainwindow.h \
    produit.h \
    smtp.h

# UI forms
FORMS += \
    mainwindow.ui

# Resources
RESOURCES += \
    images/image.qrc \
    images/images.qrc


# Deployment rules
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
