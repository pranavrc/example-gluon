/*
* This file is part of the Gluon project.
* Copyright (C) 2009 Sacha Schutz <istdasklar@free.fr>
* Copyright (C) 2009 Guillaume Martres <smarter@ubuntu.com>
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

#include "engine.h"
#include "device_p.h"

#include <QtCore/QDebug>

#include <al.h>
#include <alc.h>
#include <alext.h>

using namespace GluonAudio;

template<> GLUON_AUDIO_EXPORT Engine *GluonCore::Singleton<Engine>::m_instance = 0;

Engine::Engine()
{
    //alutInitWithoutContext(0, 0);

    m_context = NULL;
    m_device = NULL;

    /*if (setDevice(deviceName)) {
        if (deviceName.isEmpty()) {
            qDebug() << "set device to default";
        } else {
            qDebug() << "set device to " << deviceName;
        }
    } else {
        qDebug() << "cannot set openAL device...";
    }*/
    setDevice("");

    qDebug() << alGetError();
}

/*Engine::Engine(Phonon::Category category, QObject *parent)
{
    m_phonon = new Phonon(this);
    m_phonon->setCategory(category);
}*/

Engine::~Engine()
{
    alcMakeContextCurrent(NULL);
    alcDestroyContext(m_context);
    alcCloseDevice(m_device);
}

QStringList Engine::deviceList()
{
    //TODO *Shudder* put this into engineprivate and rename the entire class to device. Or something.
    return Device::contextOption(ALC_ALL_DEVICES_SPECIFIER);
}

bool Engine::setDevice(const QString &deviceName)
{
    if (m_device) {
        alcMakeContextCurrent(NULL);
        alcDestroyContext(m_context);
    }

    if (!deviceName.isEmpty()) {
        m_device = alcOpenDevice(deviceName.toUtf8());
    } else {
        m_device = alcOpenDevice(0);
    }

    if (!m_device) {
        return false;
    }

    m_context = alcCreateContext(m_device, 0);

    if (!m_context) {
        return false;
    }

    if (!alcMakeContextCurrent(m_context)) {
        return false;
    }

    return true;
}