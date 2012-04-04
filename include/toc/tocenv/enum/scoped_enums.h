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

#ifndef TOCENV_SCOPED_ENUMS
#define TOCENV_SCOPED_ENUMS 1

#ifdef CAN_CXX0X_SCOPED_ENUMS
    #define SCOPED_ENUM(name, type) enum struct name : type
    #define SCOPED_ENUM_VALUE(parent, child) parent::child
#else
    #define SCOPED_ENUM(name, t) enum name
    #define SCOPED_ENUM_VALUE(p, child) child
#endif //CAN_CXX0X_SCOPED_ENUMS

#endif //TOCENV_SCOPED_ENUM
