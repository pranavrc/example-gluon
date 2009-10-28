/*
* This file is part of the Gluon project.
* Copyright (C) 2007 Laurent Gomila <laurent.gom@gmail.com>
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

#ifndef KALSOUND_H
#define KALSOUND_H

#include "kal_export.h"

#include <QtCore/QObject>

#include <al.h>
#include <Eigen/Geometry>

class KALBuffer;

/**
 * @class kal/kalsound.h <KAL/KALSound>
 *
 * @short The base sound player class
 *
 * KALSound provide a simple player which allow you to play small wav or ogg file.
 *
 * You can initialize the class with a pathName or a buffer. For example :
 * @code
 * KALSound * sound = new KALSound("explosion.ogg");
 * sound->play();
 * @endcode
 * You can apply some properties by call for example, setVolume, setVelocity, setPosition ...
 * For more information, see openAL doc. You can retrieve openAL value, by calling source() for the ALint source and
 * buffer() for the ALint buffer;
 */



/**
 * \defgroup KAL KAL
 */
//@{
class KALSoundPrivate;
/**
* @class KALSound kalsource.h <KALSound>
* KALSound lets you play an audio file in a separate thread
*/
class KAL_EXPORT KALSound : public QObject
{
    Q_OBJECT

public:
    KALSound(QObject * parent=0);
    /**
    * This is the default constructor
    * @param soundFile the path of the file to play
    */
    KALSound(const QString &soundFile, QObject * parent = 0);
    /**
    * This is the default constructor
    * @param KALBuffer the buffer
    */
    KALSound(KALBuffer *buffer, QObject * parent = 0);
    /**
    * This is the default constructor
    * @param ALuint the buffer
    */
    KALSound(ALuint buffer, QObject * parent = 0);

    void load (const QString &soundFile);
    void load(KALBuffer * buffer);
    void load(ALuint buffer);

    /**
    * Destructor
    */
    ~KALSound();

    /**
    * @return the time since the sound started playing
    */
    ALfloat elapsedTime()const ;

    /**
    * @return the sound status
    */
    ALint status()const ;

    /**
    * @todo this function isn't defined!
    * @return the last error reported
    */
    QString lastError()const ;

    /**
    * @return the position of the listener
    * @see setPosition, x ,y ,z
    */
    Eigen::Vector3f position() const;

    /**
    * @return the x position of the listener
    * @see setPosition, y, z
    */
    ALfloat x()const ;

    /**
    * @return the y position of the listener
    * @see setPosition, x, z
    */
    ALfloat y()const ;

    /**
    * @return the z position of the listener
    * @see setPosition, x, y
    */
    ALfloat z()const ;

    /**
    * @return the volume currently applied
    * @see setvolume
    */
    ALfloat volume()const ;

    /**
    * @return the pitch currently applied
    * @see setPitch
    */
    ALfloat pitch()const ;


    ALfloat duration()const ;

    ALuint source()const ;

  protected:
    void init();

public Q_SLOTS:
    /**
    * Plays the sound file from the beginning or from the moment
    * pause() was called
    * @see pause, stop, rewind
    */
    void play();
    /**
    * Pauses the sound currently played
    * @see play, stop, rewind
    */
    void pause();

    /**
    * Stops the sound currently played
    * @see play, pause, rewind
    */
    void stop();

    /**
    * If the sound was paused, this will rewind it so that next time
    * play() is called, it will play from the start
    */
    void rewind();

    /**
    * Makes the sound play in a loop when play() is called
    * @p enabled play in a loop if set to true
    * @see play
    */
    void setLoop(bool enabled = true);

    /**
    * Set the position of the listener, this is used to create
    * 3D sounds using effects to artificially change sound origin
    * The three scalars of the vector correspond to x, y and z in
    * the coordinate system.
    * The OpenAL documentation defines the underlying variable as:
    * Specify the current location in three dimensional space.
    * OpenAL, like OpenGL, uses a right handed coordinate system,
    * where in a frontal default view x (thumb) points right,
    * y points up (index finger), and z points towards the
    * viewer/camera (middle finger).
    * To switch from a left handed coordinate system, flip the
    * sign on the Z coordinate.
    * Listener position is always in the world coordinate system.
    */
    void setPosition(Eigen::Vector3f position);

    /**
    * @overload setPosition()
    * Set the position of the listener using the coordinates
    * (@p x, @p y, @p z)
    */
    void setPosition(ALfloat x = 0.0, ALfloat y = 0.0, ALfloat z = 0.0);

    /**
    * Change the volume (volume amplification) applied
    * The OpenAL documentation defines the underlying variable as:
    * A value of 1.0 means un-attenuated/unchanged.
    * Each division by 2 equals an attenuation of -6dB.
    * Each multiplicaton with 2 equals an amplification of +6dB.
    * A value of 0.0 is meaningless with respect to a logarithmic
    *  scale; it is interpreted as zero volume - the channel
    *  is effectively disabled.
    * @see volume
    */
    void setVolume(ALfloat volume = 1.0f);

    /**
    * Specify the pitch to be applied, either at source,
    * or on mixer results, at listener.
    * @param pitch a value between 0.5 and 2.0
    */
    void setPitch(ALfloat pitch = 1.0f);

   /**
    * Specify the minimum index value of the volume,
    * @param min is 0 by default
    */
    void setMinVolume(ALfloat min = 0.0f);

   /**
    * Specify the maximum index value of the volume,
    * @param max is 10.0f by default
    */
    void setMaxVolume(ALfloat max = 10.0f);
    void setVelocity(ALfloat vx, ALfloat vy, ALfloat vz);
    void setDirection(ALfloat dx, ALfloat dy, ALfloat dz);

       /**
    * Specify the current time position.
    * @param time must be inferior than duration.
    * @see duration()
    */
    void setTimePosition(ALfloat time);
protected:
    void setupSource();
private:
    Q_DISABLE_COPY(KALSound)

    KALSoundPrivate *d;
};

//@}
#endif // KALSOURCE_H
