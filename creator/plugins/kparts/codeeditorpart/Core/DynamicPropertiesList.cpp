/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "DynamicPropertiesList.h"

DynamicPropertiesList* DynamicPropertiesList::self = 0;

DynamicPropertiesList::DynamicPropertiesList( QObject* parent ): QObject( parent )
{

}


DynamicPropertiesList* DynamicPropertiesList::New()
{
    if( DynamicPropertiesList::self == 0 )
    {
        DynamicPropertiesList::self = new DynamicPropertiesList();
    }
    return DynamicPropertiesList::self;
}


void DynamicPropertiesList::addProperty( QObject* obj, QString name )
{

    Node* node = qobject_cast< Node* >( obj );
    if( node )
    {
        QMap< Graph*,  QMultiMap <QString, Node* > >::iterator multimap = _NodesProperties.find( node->graph() );
        if( multimap == _NodesProperties.end() ) //Not exist a graph yet
        {
            QMultiMap <QString, Node* > newMap;
            multimap = _NodesProperties.insert( node->graph(), newMap );
        }

        multimap.value().insert( name, node );

        return;
    }

    Edge* edge = qobject_cast< Edge* >( obj );
    if( edge )
    {
        QMap< Graph*,  QMultiMap <QString, Edge* > >::iterator multimap = _EdgesProperties.find( edge->graph() );
        if( multimap == _EdgesProperties.end() ) //Not exist a graph yet
        {
            QMultiMap <QString, Edge* > newMap;
            multimap = _EdgesProperties.insert( edge->graph(), newMap );
        }
        multimap.value().insert( name, edge );
        return;
    }

    Graph* graph = qobject_cast< Graph* >( obj );
    if( graph )
    {
        _GraphProperties.insert( name, graph );
        return;
    }
}


void DynamicPropertiesList::removeProperty( QObject* obj, QString name )
{
    Node* node = qobject_cast< Node* >( obj );
    if( node )
    {
        QMap< Graph*,  QMultiMap <QString, Node* > >::iterator multimap = _NodesProperties.find( node->graph() );
        if( multimap == _NodesProperties.end() ) //Not exist a graph yet
        {
            return;
        }
        multimap.value().remove( name, node );
        //    _NodesProperties.remove(name, node);
        return;
    }

    Edge* edge = qobject_cast< Edge* >( obj );
    if( edge )
    {
        QMap< Graph*,  QMultiMap <QString, Edge* > >::iterator multimap = _EdgesProperties.find( edge->graph() );
        if( multimap == _EdgesProperties.end() ) //Not exist a graph yet
        {
            return;
        }
        multimap.value().remove( name, edge );
        return;
    }

    Graph* graph = qobject_cast< Graph* >( obj );
    if( graph )
    {
        _GraphProperties.remove( name, graph );
        return;
    }
}

DynamicPropertyType DynamicPropertiesList::type( QObject* obj, QString name )
{
    Node* node = qobject_cast< Node* >( obj );
    if( node )
    {
        QMap< Graph*,  QMultiMap <QString, Node* > >::iterator multimap = _NodesProperties.find( node->graph() );
        if( multimap == _NodesProperties.end() ) //Not exist a graph yet
        {
            return None;
        }
        QList <Node*> list = multimap.value().values( name );

        if( node->graph()->nodes().size() == list.size() )
        {
            return Global;
        }
        switch( list.size() )
        {
            case 0 :
                return None;
            case 1 :
                return Unique;
            default :
                return Multiple;
        }
    }

    Edge* edge = qobject_cast< Edge* >( obj );
    if( edge )
    {
        QMap< Graph*,  QMultiMap <QString, Edge* > >::iterator multimap = _EdgesProperties.find( edge->graph() );
        if( multimap == _EdgesProperties.end() ) //Not exist a graph yet
        {
            return None;
        }
        QList <Edge*> list = multimap.value().values( name );
        if( edge->graph()->edges().size() == list.size() )
        {
            return Global;
        }
        switch( list.size() )
        {
            case 0 :
                return None;
            case 1 :
                return Unique;
            default :
                return Multiple;
        }
    }

    Graph* graph = qobject_cast< Graph* >( obj );
    if( graph )
    {
        if( _GraphProperties.values( name ).size() == 0 )
        {
            return None;
        }
        else
        {
            return Unique;
        }
    }
    return None;
}

QString DynamicPropertiesList::typeInText( QObject* obj, QString name )
{
    switch( type( obj, name ) )
    {
        case Unique:
            return i18nc( "The type of the text", "Unique" );
        case Multiple:
            return i18nc( "The type of the text", "Multiple" );
        case Global:
            return i18nc( "The type of the text", "Global" );
        case None:
        default:
            return i18nc( "The type of the text", "None" );
    }
}



void DynamicPropertiesList::clear( Graph* graph )
{
    if( graph != 0 )
    {
        _EdgesProperties.values( graph ).clear();
        foreach( const QString & name,  _GraphProperties.keys( graph ) )
        {
            _GraphProperties.remove( name, graph );
        }

        _NodesProperties.values( graph ).clear();
    }
    else
    {
        _EdgesProperties.clear();
        _GraphProperties.clear();
        _NodesProperties.clear();

    }
}


void DynamicPropertiesList::changePropertyName( QString name, QString newName, QObject* object )
{
    Node* node = qobject_cast< Node* >( object );
    if( node )
    {
        QMap< Graph*,  QMultiMap <QString, Node* > >::iterator multimap = _NodesProperties.find( node->graph() );
        if( multimap == _NodesProperties.end() ) //Not exist a graph yet
        {
            return;
        }
        foreach( node, multimap.value().values( name ) )
        {
            node->addDynamicProperty( newName, node->property( name.toUtf8() ) );
            node->removeDynamicProperty( name );
        }
    }
    Edge* edge = qobject_cast< Edge* >( object );
    if( edge )
    {
        QMap< Graph*,  QMultiMap <QString, Edge* > >::iterator multimap = _EdgesProperties.find( edge->graph() );
        if( multimap == _EdgesProperties.end() ) //Not exist a graph yet
        {
            return;
        }

        foreach( edge, multimap.value().values( name ) )
        {
            edge->addDynamicProperty( newName, edge->property( name.toUtf8() ) );
            edge->removeDynamicProperty( name );
        }
    }
    Graph* graph = qobject_cast<Graph*>( object );
    if( graph )
    {
        graph->addDynamicProperty( newName, graph->property( name.toUtf8() ) );
        graph->removeDynamicProperty( name );
    }

}
