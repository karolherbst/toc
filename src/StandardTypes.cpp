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

const String NULLSTRING = "NULL";
namespace TOC
{
    const String DBString    = "String";
    const String DBInt       = "int";
    const String DBFloat     = "float";
    const String DBText      = "text";
    
    createAttTypeSymbols(NameAtt, "name", DBString, "Name", 32);
    createAttTypeSymbols(MailAtt, "email", DBString, "EMail", 64);
    createAttTypeSymbols(PasswordAtt, "pw", DBString, "Password", 32);
    createAttTypeSymbols(SessionTypeAtt, "sessiontype", DBInt, 1, 2);
    createAttTypeSymbols(ArgCountAtt, "argcount", DBInt, 0, 2);
    createAttTypeSymbols(ArgAtt, "arg", DBString, "", 4);
    createAttTypeSymbols(ActionAtt, "action", DBInt, 1, 2);
    createAttTypeSymbols(MajVersionAtt, "maj", DBInt, 0, 3);
    createAttTypeSymbols(MinVersionAtt, "min", DBInt, 0, 3);
    createAttTypeSymbols(RelVersionAtt, "rel", DBInt, 0, 3);
    createAttTypeSymbols(BuildVersionAtt, "build", DBInt, 0, 6);
    createAttTypeSymbols(TextAtt, "text", DBText, "", 0);
}
