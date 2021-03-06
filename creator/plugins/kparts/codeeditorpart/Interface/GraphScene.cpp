/***************************************************************************
 * main.cpp
 * This file is part of the KDE project
 * copyright (C)2004-2007 by Tomaz Canabrava (tomaz.canabrava@gmail.com)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 * You should have received a copy of the GNU Library General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 ***************************************************************************/

#include "GraphScene.h"
#include "AbstractAction.h"

#include "node.h"
#include "edge.h"
#include "graphDocument.h"
#include "NodeItem.h"
#include "OrientedEdgeItem.h"
#include "graph.h"
#include "NodePropertiesWidget.h"
#include "MainWindow.h"
#include "edgepropertieswidget.h"

#include <KDE/KInputDialog>
#include <KDE/KLineEdit>
#include <KDE/KDebug>

#include <QtGui/QGraphicsItem>
#include <QtGui/QGraphicsSceneMouseEvent>
#include <QtGui/QGraphicsSceneWheelEvent>
#include <QtGui/QKeyEvent>

GraphScene::GraphScene( QObject* parent ) : QGraphicsScene( parent )
{
    _graphDocument = 0;
    _hideEdges = false;
    _nodePropertiesWidget = new NodePropertiesWidget( 0 );
    _edgePropertiesWidget = new EdgePropertiesWidget( 0 );
    _action = 0;
    _parent = parent;
}

bool GraphScene::hideEdges()
{
    return _hideEdges;
}

void GraphScene::setHideEdges( bool h )
{
    _hideEdges = h;
    if( ! _hideEdges )
    {
        foreach( QGraphicsItem * i, _hidedEdges )
        {
            i->update();
        }
    }
}

void GraphScene::setActiveGraph( Graph* g )
{
    kDebug() << "Active Graph Set";
    _graph = g;
    disconnect( SIGNAL( forceUpdate() ) );
    connect( this, SIGNAL( forceUpdate() ), _graph, SIGNAL( forceUpdate() ) );
}

QAction* GraphScene::action()
{
    return _action;
}

void GraphScene::updateAfter( QGraphicsItem* item )
{
    if( _hidedEdges.contains( item ) ) return;
    _hidedEdges << item;
}

void GraphScene::hideGraph( Graph* g, bool visibility )
{
    QList<QGraphicsItem*> list = _hashGraphs.values( g );
    foreach( QGraphicsItem * i, list )
    {
        i->setVisible( visibility );
    }
}


void GraphScene::setAction( QAction* action )
{
    _action = qobject_cast<AbstractAction*>( action );
}

void GraphScene::setActiveGraphDocument( GraphDocument* gd )
{
    _graphDocument = gd;
    if( gd == 0 )
    {
        return;
    }

    setSceneRect( QRectF( 0, 0, gd->width(), gd->height() ) );
    QGraphicsRectItem* n = new QGraphicsRectItem( 0, 0, gd->width(), gd->height() );
    n->setFlag( QGraphicsItem::ItemIsSelectable, false );
    n->setZValue( -1000 );
    addItem( n );

    int size = _graphDocument->size();
    if( size == 0 ) kDebug() << "############## SIZE = 0 ################";
    for( int i = 0; i < size; i++ )
    {
        kDebug() << "Updating Graph at position: " << i;
        updateGraph( _graphDocument->at( i ) );
        connectGraphSignals( _graphDocument->at( i ) );
        kDebug() << "Graph Updated.";
    }
    connect( _graphDocument, SIGNAL( graphCreated( Graph* ) ), this, SLOT( connectGraphSignals( Graph* ) ) );
    kDebug() << "Graph Document Set" << _graphDocument -> name();
}
void GraphScene::createItems()
{
    kDebug() << "Creating the graph items.";
    int size = _graphDocument->size();
    for( int i = 0; i < size; i++ )
    {
        Graph* g = _graphDocument->at( i );
        kDebug() << "Creating " << g->nodes().size() << "nodes";
        for( int n = 0; n < g->nodes().size(); n++ )
        {
            createNode( g->nodes()[n] );
        }
        kDebug() << "Creating" << g->edges().size() << "edges";
        for( int v = 0; v < g->edges().size(); v++ )
        {
            createEdge( g->edges()[v] );
        }
    }
}

void GraphScene::connectGraphSignals( Graph* g )
{
    connect( g, SIGNAL( nodeCreated( Node* ) ), this, SLOT( createNode( Node* ) ) );
    connect( g, SIGNAL( edgeCreated( Edge* ) ), this, SLOT( createEdge( Edge* ) ) );
}

QGraphicsItem* GraphScene::createNode( Node* n )
{
    NodeItem* nItem = new NodeItem( n );
    addItem( nItem );
    kDebug() << "Node Item Created";
    return nItem;
}

QGraphicsItem* GraphScene::createEdge( Edge* e )
{
    QGraphicsItem* edgeItem = 0;
    edgeItem = new OrientedEdgeItem( e );

    addItem( edgeItem );
    kDebug() << "Edge Created";
    return edgeItem;
}

void GraphScene::mouseDoubleClickEvent( QGraphicsSceneMouseEvent* mouseEvent )
{
    mouseEvent->accept();
}

void GraphScene::wheelEvent( QGraphicsSceneWheelEvent* wheelEvent )
{
    kDebug() << "Entering on Whell Event";
    NodeItem* nitem = qgraphicsitem_cast<NodeItem*>( itemAt( wheelEvent->scenePos() ) );
    if( !nitem )
    {
        kDebug() << "No Node Item to Spand";
        wheelEvent->ignore();
        return;
    }

    Node* movableNode = nitem->node();
    int numDegrees = wheelEvent->delta();
    if( wheelEvent->orientation() == Qt::Vertical )
    {
        kDebug() << "Upgrading node size";
        if( numDegrees > 0 )
        {
            movableNode->setWidth( movableNode->width() + 0.25 );
            nitem->update();
        }
        else if( movableNode->width() > 0.5 )
        {
            movableNode->setWidth( movableNode->width() - 0.25 );
            nitem->update();
        }
    }
    wheelEvent->accept();
}

void GraphScene::mouseMoveEvent( QGraphicsSceneMouseEvent* mouseEvent )
{
    _action->executeMove( mouseEvent->scenePos() );
}

void GraphScene::mousePressEvent( QGraphicsSceneMouseEvent* mouseEvent )
{
    qDebug() << "Entrou aqui." << _action;
    if( mouseEvent->button() == Qt::MidButton )
    {
        NodeItem* nitem = qgraphicsitem_cast<NodeItem*>( itemAt( mouseEvent->scenePos() ) );
        if( !nitem ) return;
        Node* movableNode = nitem->node();
        movableNode->setWidth( 1 );
    }
    else if( mouseEvent->button() == Qt::RightButton )
    {
        QListIterator<QGraphicsItem*>  list( items( mouseEvent->scenePos() ) );
        NodeItem* nItem = 0;
        while( list.hasNext() )
        {
            QGraphicsItem* item = list.next();
            if( item->type() == 65578 ) nItem = qgraphicsitem_cast<NodeItem*>( item );
        }
        if( nItem && nItem->node()->type() == "if" )
        {
            //eew yuck, popup windows!
            bool ok;
            QString response = KInputDialog::getText( qobject_cast<QWidget*>( _parent ), "Change If Test", "New If Test:", QLineEdit::Normal, nItem->node()->value().toString(), &ok );
            if( ok && !response.isEmpty() )
            {
                nItem->node()->setValue( response );
                emit forceUpdate();
            }
        }
        /* QGraphicsItem *i = itemAt(mouseEvent->scenePos());
            if (NodeItem *nItem = qgraphicsitem_cast<NodeItem*>(i)){
                _nodePropertiesWidget->setNode(nItem, mouseEvent->screenPos());
            }
            else if (OrientedEdgeItem *eItem = qgraphicsitem_cast<OrientedEdgeItem*>(i)){
                _edgePropertiesWidget->setEdge(eItem->edge(), mouseEvent->screenPos());
            }*/
    }
    else if( mouseEvent -> button() == Qt::LeftButton )
    {
        qDebug() << "Executando a ação";
        _action->executePress( mouseEvent->scenePos() );
    }
}

void GraphScene::mouseReleaseEvent( QGraphicsSceneMouseEvent* mouseEvent )
{
    qDebug() << "Entrou no release Action";
    if( mouseEvent->button() == Qt::LeftButton )
    {
        _action->executeRelease( mouseEvent->scenePos() );
    }
}

void GraphScene::keyPressEvent( QKeyEvent* )
{

}

void GraphScene::updateGraph( Graph* g )
{
    kDebug() << "Removed Graph from the hash";

    kDebug() << "Creating" << g->nodes().size() << "nodes";
    QList<Node*> nodes = g->nodes();
    foreach( Node * n, nodes )
    {
        n->setName( n->name() ); // just a dummy update trigger;
    }

    kDebug() << "Creating" << g->nodes().size() << "edges";
    QList<Edge*> edges = g->edges();
    foreach( Edge * e, edges )
    {
        e->setName( e->name() ); // just a dummy update trigger.
    }
}

void GraphScene::updateDocument()
{
    if( _graphDocument == 0 )
    {
        kDebug() << "Graph Document is null. Please hit the developer.";
        return;
    }

    clear();
    kDebug() << "Graph Document Size: " << _graphDocument->size();
    int size = _graphDocument->size();

    for( int i = 0; i < size; i++ )
    {
        updateGraph( _graphDocument->at( i ) );
        kDebug() << "updated Graph at " << i;
    }
}
