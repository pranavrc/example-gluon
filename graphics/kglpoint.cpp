/*
 * This file is part of the Gluon library.
 * Copyright 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright 2008 Charles Huet <packadal@gmail.com>
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

#include "kglpoint.h"
#include <QtCore/QDebug>

KGLPoint::KGLPoint()
{
    m_x = 0;
    m_y = 0;
    m_r = 1;
    m_g = 1;
    m_b = 1;
    m_a = 1;
    m_tx= 0;
    m_ty= 0;
}

KGLPoint::KGLPoint(const QPointF &p, const QColor &c, const QPointF &t)
{
    m_x = p.x();
    m_y = p.y();
    m_r = c.redF();
    m_g = c.greenF();
    m_b = c.blueF();
    m_a = c.alphaF();
    m_tx= t.x();
    m_ty= t.y();
}

KGLPoint::KGLPoint(float x, float y, const QColor &c, const QPointF &t)
{
    m_x = x;
    m_y = y;
    m_r = c.redF();
    m_g = c.greenF();
    m_b = c.blueF();
    m_a = c.alphaF();
    m_tx= t.x();
    m_ty= t.y();
}

//=========================================

KGLPointList::KGLPointList()
    : QVector <KGLPoint>()
{
}