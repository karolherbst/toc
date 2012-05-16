/*
*  Copyright (c) by Karol Herbst <projects@karolherbst.de>
*
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 2 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software
*   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
*
*/

#include <toc/tocdb/StandardTypes.h>

const String NULLSTRING = CSTRING("NULL");

namespace TOC
{
	const String DBString = CSTRING("String");
	const String DBInt    = CSTRING("int");
	const String DBFloat  = CSTRING("float");
	const String DBText   = CSTRING("text");
	
	createAttTypeSymbols(NameAtt,         CSTRING("name"),        DBString, CSTRING("Name"),     32);
	createAttTypeSymbols(MailAtt,         CSTRING("email"),       DBString, CSTRING("EMail"),    64);
	createAttTypeSymbols(PasswordAtt,     CSTRING("pw"),          DBString, CSTRING("Password"), 32);
	createAttTypeSymbols(SessionTypeAtt,  CSTRING("sessiontype"), DBInt,    1,                    2);
	createAttTypeSymbols(ArgCountAtt,     CSTRING("argcount"),    DBInt,    0,                    2);
	createAttTypeSymbols(ArgAtt,          CSTRING("arg"),         DBString, CSTRING(""),          4);
	createAttTypeSymbols(ActionAtt,       CSTRING("action"),      DBInt,    1,                    2);
	createAttTypeSymbols(MajVersionAtt,   CSTRING("maj"),         DBInt,    0,                    3);
	createAttTypeSymbols(MinVersionAtt,   CSTRING("min"),         DBInt,    0,                    3);
	createAttTypeSymbols(RelVersionAtt,   CSTRING("rel"),         DBInt,    0,                    3);
	createAttTypeSymbols(BuildVersionAtt, CSTRING("build"),       DBInt,    0,                    6);
	createAttTypeSymbols(TextAtt,         CSTRING("text"),        DBText,   CSTRING(""),          0);
}
