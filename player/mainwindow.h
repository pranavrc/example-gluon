/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Arjen Hiemstra <>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef GLUONPLAYER_MAINWINDOW_H
#define GLUONPLAYER_MAINWINDOW_H

#include <QtGui/QMainWindow>

namespace GluonPlayer
{
    class MainWindow : public QMainWindow
    {
            Q_OBJECT
        public:
            MainWindow(int argc, char** argv, QWidget* parent = 0, Qt::WindowFlags flags = 0);
            virtual void closeEvent(QCloseEvent* event);

        public slots:
            void openProject();
            void updateTitle();

        private:
            class MainWindowPrivate;
            MainWindowPrivate *d;
    };
}

#endif // GLUONPLAYER_MAINWINDOW_H