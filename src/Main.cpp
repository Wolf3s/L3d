
// ===============================================================================================================
// -*- C++ -*-
//
// Main.cpp - Application entry point.
//
// Copyright (c) 2012 Guilherme R. Lampert
// guilherme.ronaldo.lampert@gmail.com
//
// This code is licenced under the MIT license.
//
// This software is provided "as is" without express or implied
// warranties. You may freely copy and compile this source into
// applications you distribute provided that the copyright text
// above is included in the resulting source code.
//
// ===============================================================================================================

#include <QtGui/QApplication>
#include <QMessageBox>
#include "EditorWidget.hpp"

#include <cstdlib>
#include <string>
#include <stdexcept>

int main(int argc, char * argv[])
{
    int mainRet;
    QApplication app(argc, argv);

    try
    {
        l3d::EditorWidget editor;
        editor.showMaximized();
        editor.initUI();
        mainRet = app.exec();
    }
    catch (std::exception & e)
    {
        QMessageBox::critical(0, "Unhandled Exception!", e.what());
        mainRet = EXIT_FAILURE;
    }

    return mainRet;
}
