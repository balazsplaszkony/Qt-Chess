# chess.pro

QT += widgets

TARGET = chess
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    promotionwidget.cpp \
    square.cpp \
    game.cpp \
    board.cpp \
    piece.cpp \
    pawn.cpp \
    rook.cpp \
    knight.cpp \
    bishop.cpp \
    king.cpp \
    queen.cpp \
    position.cpp \

HEADERS += \
    mainwindow.h \
    promotionwidget.h \
    square.h \
    game.h \
    board.h \
    piece.h \
    pawn.h \
    rook.h \
    knight.h \
    bishop.h \
    king.h \
    queen.h \
    position.h \
    common.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    chess_hu_HU.ts
