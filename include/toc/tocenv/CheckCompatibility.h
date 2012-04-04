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

#ifndef TOCENV_CHECK
#define TOCENV_CHECK 1

#define GCC_VERSION (__GNUC__ * 10000 \
                   + __GNUC_MINOR__ * 100 \
                   + __GNUC_PATCHLEVEL__)

#ifdef __GXX_EXPERIMENTAL_CXX0X__

  // check for scoped enums
  #if GCC_VERSION >= 40400
    #define CAN_CXX0X_SCOPED_ENUMS 1
  #endif

  //check for forward enums
  #if GCC_VERSION >= 40600
    #define CAN_CXX0X_FORWARD_ENUMS 1
  #endif

#endif

#endif //TOCENV_CHECK
