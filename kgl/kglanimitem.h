/*
 * This file is part of the KGLEngine2D project.
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef KGLANIMITEM_H
#define KGLANIMITEM_H

#include "kglitem.h"

class QTimeLine;

class KGLAnimItem: public KGLItem
{
    Q_OBJECT
public:
    explicit KGLAnimItem(const GLint &texture, const int &nbFrame = 2, const int &duration = 500,
                         const QSizeF &dim = QSizeF(0.5, 0.5));

    // inline QTimeLine* timeLine() { return m_timeLine; }

public Q_SLOTS:
    void createFrame(int id = 0);

private:
    QTimeLine *m_timeLine;
};

#endif //KGLANIMITEM_H
