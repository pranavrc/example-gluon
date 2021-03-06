
/* This file is part of Rocs,
   Copyright (C) 2008 by:
   Tomaz Canabrava <tomaz.canabrava@gmail.com>
   Ugo Sangiori <ugorox@gmail.com>

   Rocs is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   Rocs is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Step; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "AddTypedNode.h"
#include "GraphScene.h"
#include "graph.h"
#include "NodeItem.h"
#include "node.h"
#include <KLocale>
#include "graphDocument.h"
#include <KDebug>

AddTypedNodeAction::AddTypedNodeAction( GraphScene* scene, QObject* parent )
    : AbstractAction( scene, parent )
{
    setText( i18n( "Add Node" ) );
    setToolTip( i18n( "Creates a new node of selected type at the click position on the drawing area." ) );
    setIcon( KIcon( "gluonaddnode" ) );
    _name = "add-typed-node";
    _type = "";
}

AddTypedNodeAction::~AddTypedNodeAction()
{
    qDebug() << "Destroyed";
}

void AddTypedNodeAction::executePress( QPointF pos )
{
    if( _graph == 0 )
    {
        qDebug() << "Error, Graph == 0";
        return;
    }
    if( _graph->readOnly() ) return;

    if( pos.x() < 0 ) return;
    else if( pos.y() < 0 ) return;
    else if( pos.x() > _graphDocument->width() ) return;
    else if( pos.y() > _graphDocument->height() ) return;

    qDebug() << "Emitindo o addnode";
    if( _type != "base" && _type != "others" )
    {
        emit addNode( i18n( "untitled" ), QPointF( pos.x(), pos.y() ), _type );
    }
    else
    {
        emit iAmDisappoint();
    }
}

void AddTypedNodeAction::widgetTypeChanged( QString type )
{
    _type = type;
}

void AddTypedNodeAction::setActiveGraph( Graph* graph )
{
    if( _graph ) disconnect( this, 0, _graph, 0 );
    _graph = graph;
    connect( this, SIGNAL( addNode( QString, QPointF, QString ) ), _graph, SLOT( addNode( QString, QPointF, QString ) ) );
    connect( this, SIGNAL( iAmDisappoint() ), _graph, SIGNAL( iAmDisappoint() ) );
}

