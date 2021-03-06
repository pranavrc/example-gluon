/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Kim Jung Nissen <jungnissen@gmail.com>
 * Copyright (C) 2010 Laszlo Papp <djszapi@archlinux.us>
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
#ifndef INPUTBUFFER_H
#define INPUTBUFFER_H

#include "gluon_input_export.h"

#include <QtCore/QObject>
#include <QtCore/QSharedData>

namespace GluonInput
{
    class InputBufferPrivate;

    class GLUON_INPUT_EXPORT InputBuffer : public QObject
    {
            Q_OBJECT
        public:
            InputBuffer();
            ~InputBuffer();

            bool buttonState( int button );
            void setButtonState( int button, bool pressed );

        private:
            QSharedDataPointer<InputBufferPrivate> d;
    };
}

#endif
