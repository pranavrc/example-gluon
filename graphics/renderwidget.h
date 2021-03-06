/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Rivo Laks <rivolaks@hot.ee>
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#ifndef GLUONGRAPHICS_RENDERWIDGET_H
#define GLUONGRAPHICS_RENDERWIDGET_H

#include "gluon_graphics_export.h"

#ifdef Q_OS_WIN
#include <windows.h>
#include <GL/glee.h>
#endif

#include <QtOpenGL/QGLWidget>

namespace GluonGraphics
{
    class GLUON_GRAPHICS_EXPORT RenderWidget : public QGLWidget
    {
            Q_OBJECT
        public:
            explicit RenderWidget( QWidget* parent = 0, const QGLWidget* shareWidget = 0, Qt::WindowFlags f = 0 );
            virtual ~RenderWidget();

            virtual void initializeGL();
            virtual void paintGL();
            virtual void resizeGL( int w, int h );

        private:
            class RenderWidgetPrivate;
            RenderWidgetPrivate* const d;
    };
}


#endif // GLUON_GRAPHICS_RENDERWIDGET_H
