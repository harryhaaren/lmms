/*
 * midi_control_listener.h - listens to MIDI source(s) for commands that
 *                           start/stops LMMS' transportation,
 *                           or toggles loop
 *
 * Copyright (c) 2009 Achim Settelmeier <lmms/at/m1.sirlab.de>
 *
 * This file is part of Linux MultiMedia Studio - http://lmms.sourceforge.net
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 */

#ifndef _MIDI_CONTROL_LISTENER_H
#define _MIDI_CONTROL_LISTENER_H

#include "midi_event_processor.h"
#include "midi_port.h"
#include "note.h"
#include <QString>
#include <QPair>
#include <QDomElement>

class QDomDocument;

class MidiControlListener : public MidiEventProcessor
{
public:
	typedef enum
	{
		ActionNone = 0,
		ActionControl,
		ActionPlay,
		ActionStop
	} EventAction;
	static const int numActions = 4;
	
	typedef QMap<int, EventAction> ActionMap;
	
	typedef struct
	{
		EventAction action;
		QString name;
		QString nameShort;
	} ActionNameMap;
	
	static const ActionNameMap actionNames[];
	
	static ActionNameMap action2ActionNameMap( EventAction _action );
	static ActionNameMap actionName2ActionNameMap( QString _actionName );
	
	static void rememberConfiguration( QDomDocument  &doc );

public:
	MidiControlListener( void );
	virtual ~MidiControlListener( void );

	virtual void processInEvent( const midiEvent & _me,
						const midiTime & _time );
	virtual void processOutEvent( const midiEvent & _me,
				     const midiTime & _time )
	{
	}

	void saveConfiguration( QDomDocument  &doc );
	
	void readConfiguration( void );
	
	inline bool getEnabled( void )
	{
		return m_listenerEnabled;
	}
	
	inline void setEnabled( bool _enabled )
	{
		m_listenerEnabled = _enabled;
		m_controlKeyCount = 0;
	}
	
	inline bool getUseControlKey( void )
	{
		return m_useControlKey;
	}
	
	inline void setUseControlKey( bool _useControlKey )
	{
		m_useControlKey = _useControlKey;
		m_controlKeyCount = 0;
	}
	
	inline int getChannel( void )
	{
		return m_channel;
	}
	
	inline void setChannel( int _Channel )
	{
		m_channel = _Channel;
		m_controlKeyCount = 0;
	}
	
	inline ActionMap getActionMapKeys( void )
	{
		return m_actionMapKeys;
	}
	
	inline void setActionMapKeys( ActionMap _keys )
	{
		m_actionMapKeys = _keys;
		m_controlKeyCount = 0;
	}
	
	inline ActionMap getActionMapControllers( void )
	{
		return m_actionMapControllers;
	}
	
	inline void setActionMapControllers( ActionMap _controllers )
	{
		m_actionMapControllers = _controllers;
		m_controlKeyCount = 0;
	}
	
private:
	static const QString configClass;
	static QDomElement s_configTree;

	void act( EventAction _action );


	midiPort m_port;

	int m_controlKeyCount;     // 0: no control key(s) pressed, 1-n: control keys pressed

	// configuration
	bool m_listenerEnabled;    // turns feature on/off
	int m_channel;             // number of channel (0 - 15) or -1 for all channels
	bool m_useControlKey;      // true: use control key (two key sequence); false: single key sequence
	ActionMap m_actionMapKeys;
	ActionMap m_actionMapControllers;
} ;

#endif
