/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef GLUON_CREATOR_SCENEDOCKPLUGIN_H
#define GLUON_CREATOR_SCENEDOCKPLUGIN_H

#include <gluoncreator/dockplugin.h>

namespace Gluon {

namespace Creator {

class SceneDockPlugin : public Gluon::Creator::DockPlugin
{
  public:
    SceneDockPlugin(QWidget* parent, const QList<QVariant>& params);
    ~SceneDockPlugin();

    QAbstractItemModel* model();
    QItemSelectionModel* selectionModel();

  private:
    class SceneDockPluginPrivate;
    SceneDockPluginPrivate* d;
};

}

}

#endif // GLUON_CREATOR_SCENEDOCKPLUGIN_H
