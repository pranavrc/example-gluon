/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "gluonobjectfactory.h"
#include "gluonobject.h"
#include "component.h"
#include "asset.h"
#include "debughelper.h"

#include <QtCore/QDir>
#include <QtGui/QApplication>
#include <QtCore/QPluginLoader>

using namespace Gluon;

template<> GluonObjectFactory* KSingleton<GluonObjectFactory>::m_instance = 0;

QStringList
GluonObjectFactory::objectTypeNames() const
{
    QStringList theNames;

    QHash<QString, GluonObject*>::const_iterator i;
    for (i = m_objectTypes.constBegin(); i != m_objectTypes.constEnd(); ++i)
        theNames << i.key();

    return theNames;
}

QHash< QString, GluonObject* > GluonObjectFactory::objectTypes() const
{
    return m_objectTypes;
}


void
GluonObjectFactory::registerObjectType(GluonObject * newObjectType)
{
    DEBUG_BLOCK
    if(newObjectType)
    {
        DEBUG_TEXT(QString("Registering object type %1").arg(newObjectType->metaObject()->className()));
        m_objectTypes[newObjectType->metaObject()->className()] = newObjectType;
    }
    else
        DEBUG_TEXT(QString("Attempted to register a NULL object type"));
}

GluonObject *
GluonObjectFactory::instantiateObjectByName(const QString& objectTypeName)
{
    DEBUG_BLOCK
    QString fullObjectTypeName(objectTypeName);
    if(!objectTypeName.contains("::"))
         fullObjectTypeName = QString("Gluon::") + fullObjectTypeName;

    if(m_objectTypes.keys().indexOf(fullObjectTypeName) > -1)
        return m_objectTypes[fullObjectTypeName]->instantiate();

    DEBUG_TEXT(QString("Object type name not found in factory!"));

    return 0;
}

void
GluonObjectFactory::loadPlugins()
{
    DEBUG_FUNC_NAME
    QList<QDir> pluginDirs;

    QDir pluginDir(QApplication::applicationDirPath());

#if defined(Q_OS_WIN)
    if (pluginDir.dirName().tolower() == "debug" || pluginDir.dirName().tolower() == "release")
        pluginDir.cdUp();
#elif defined(Q_OS_MAC)
    if (pluginDir.dirName() == "MacOS")
    {
        pluginDir.cdUp();
        pluginDir.cdUp();
        pluginDir.cdUp();
    }
#endif
    if(pluginDir.cd("plugins"))
        pluginDirs.append(pluginDir);

    if(pluginDir.cd("/usr/lib/gluon"))
        pluginDirs.append(pluginDir);

    if(pluginDir.cd(QDir::homePath() + "/gluonplugins"))
        pluginDirs.append(pluginDir);

    DEBUG_TEXT(QString("Number of plugin locations: %1").arg(pluginDirs.count()));
    foreach(const QDir &theDir, pluginDirs)
    {
        DEBUG_TEXT(QString("Looking for pluggable components in %1").arg(theDir.absolutePath()));
        DEBUG_TEXT(QString("Found %1 potential plugins. Attempting to load...").arg(theDir.count() - 2));

        foreach (QString fileName, theDir.entryList(QDir::Files))
        {
            QPluginLoader loader(theDir.absoluteFilePath(fileName));
            if(Component* loaded = qobject_cast<Component*>(loader.instance()))
                m_pluggedComponents.append(loaded);
            else if(Asset* loaded = qobject_cast<Asset*>(loader.instance()))
                m_pluggedAssets.append(loaded);
            else
                DEBUG_TEXT(loader.errorString());
        }
    }
}

#include "gluonobjectfactory.moc"
