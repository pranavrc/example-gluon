/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Giulio Camuffo <giuliocamuffo@gmail.com>
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

#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <QtCore/QObject>
#include "glheaders.h"

namespace GluonGraphics
{
    class VertexAttribute;
    class MaterialInstance;

    /**
     * \brief A class to render geometries with OpenGL.
     *
     * VertexBuffer takes any number of VertexAttribute and uses them
     * to create and draw a GL vertex buffer .
     *
     * <b>Creating a VertexBuffer</b>
     *
     * This code snippet creates a VertexBuffer object and fills in with
     * the necessary data to render two triangles.
     *\code
     VertexBuffer* buffer = new VertexBuffer();

     VertexAttribute vertices( "vertex", 3);
     vertices << -1.f << -1.f << 0.f;
     vertices << -1.f <<  1.f << 0.f;
     vertices <<  1.f <<  1.f << 0.f;
     vertices <<  1.f << -1.f << 0.f;
     buffer->addAttribute( vertices );

     VertexAttribute uvs( "uv0", 2 );
     uvs << 0.f << 0.f;
     uvs << 0.f << 1.f;
     uvs << 1.f << 1.f;
     uvs << 1.f << 0.f;
     buffer->addAttribute( uvs );

     QVector<uint> indices;
     indices << 0 << 1 << 2
             << 0 << 2 << 3;

     buffer->setIndices( indices );
     buffer->initialize();
     * \endcode
     * To render the buffer simply call render(), passing it the wanted render mode.
     * \note This requires a render target to be bound, be it RenderWidget or RenderTarget.
     * \code
     buffer->render( VertexBuffer::RM_TRIANGLES );
     * \endcode
     */
    class VertexBuffer : public QObject
    {
            Q_OBJECT
        public:
            /**
             * This enumeration lists the various render modes that can be used to render a buffer.
             */
            enum RenderMode
            {
                RM_POINTS,          /**< Draws points. Every vertex specified is a point. */
                RM_LINES,           /**< Draws lines. Every two vertices specified compose a line. */
                RM_LINE_LOOP,       /**< Draws connected lines. The last vertex specified is
                                         connected to first vertex. */
                RM_LINE_STRIP,      /**< Draws connected lines. Every vertex specified after
                                         first two are connected.*/
                RM_TRIANGLES,       /**< Draws triangles. Every three vertices specified compose
                                         a triangle. */
                RM_TRIANGLE_STRIP,  /**< Draws connected triangles. Every vertex specified after
                                         first three vertices creates a triangle.*/
                RM_TRIANGLE_FAN,    /**< Draws connected triangles like RM_TRIANGLE_STRIP, except
                                         draws triangles in fan shape. */
            };

            /**
             * Constructs an empty vertex buffer object.
             */
            VertexBuffer( QObject* parent = 0 );

            /**
             * Destroys the buffer.
             */
            ~VertexBuffer();

            /**
             * Add a vertex attribute to the list of attributes that will
             * be used by initialize() to create the buffer.
             *
             * \param attribute The attribute to be added.
             */
            void addAttribute( const VertexAttribute& attribute );

            /**
             * Sets the vertex indices to be used when rendering.
             * The indices are a list of references to the vertices which
             * make up the geometry.
             *
             * \param indices The indices array.
             */
            void setIndices( const QVector<uint>& indices );

            /**
             * Create an OpenGL buffer and store the previously added attributes.
             *
             * \see isInitialized
             */
            void initialize();

            /**
             * Render the local OpenGL buffer.
             *
             * \param mode The OpenGL mode to use, for example GL_TRIAGLES.
             * \param material The material to get attribute locations from.
             */
            void render( RenderMode mode, GluonGraphics::MaterialInstance* material );

            /**
             * Returns true if initialize was called.
             *
             * \see initialize
             **/
            bool isInitialized() const;

        private:
            class VertexBufferPrivate;
            VertexBufferPrivate* const d;
    };
};

#endif
