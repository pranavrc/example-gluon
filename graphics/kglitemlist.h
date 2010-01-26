/*
 * This file is part of the Gluon library.
 * Copyright 2008 Sacha Schutz <istdasklar@free.fr>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef KGLITEM_LIST_H
#define KGLITEM_LIST_H

#include <QtCore/QList>

#include "kgl_export.h"
#include "kglitem.h"

/**
 * \defgroup KGL KGL
 */
//@{

class KGL_EXPORT KGLItemList: public QList<KGLItem*>
{
    public:
        KGLItemList();
        ~KGLItemList();
};

//@}
#endif // KGLITEM_LIST_H