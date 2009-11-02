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

#ifndef GLUON_GLUONOBJECT_H
#define GLUON_GLUONOBJECT_H

#include <QtCore/QObject>
#include <QtCore/QSharedData>
#include "gluonobjectfactory.h"

namespace Gluon
{
    class GluonObjectPrivate;
    
    class GluonObject : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString name READ name WRITE setName)
        
        public:
            GluonObject(QObject * parent = 0);
            virtual ~GluonObject();

            virtual GluonObject * instantiate();
            
            QString name() const;
            void setName(const QString &newName);
            
            virtual void setPropertyFromString(const QString &propertyName, const QString &propertyValue);
            virtual QString getStringFromProperty(const QString &propertyName);
            
            virtual void sanitize();
        private:
            QSharedDataPointer<GluonObjectPrivate> d;
    };
}


#endif				// GLUON_GLUONOBJECT_H