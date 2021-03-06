/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2009 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#ifndef GLUON_CORE_SINGLETON
#define GLUON_CORE_SINGLETON

#include <QtCore/QObject>
#include <QtCore/QtGlobal>

namespace GluonCore
{
    template <typename T>
    class Singleton : public QObject
    {
        public:
            static T* instance()
            {
                if( !m_instance )
                {
                    m_instance = new T;
                }
                return m_instance;
            }

        protected:
            static T* m_instance;
    };
}

#ifdef Q_OS_WIN
#define GLUON_DEFINE_SINGLETON(Type) template<> Type* GluonCore::Singleton<Type>::m_instance = 0;
#else
#define GLUON_DEFINE_SINGLETON(Type) template<> Q_DECL_EXPORT Type* GluonCore::Singleton<Type>::m_instance = 0;
#endif

#endif //GLUON_CORE_SINGLETON
