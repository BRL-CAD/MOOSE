/*                      P R I V A T E . H
 * BRL-CAD
 *
 * Copyright (c) 2016-2020 United States Government as represented by
 * the U.S. Army Research Laboratory.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this file; see the file named COPYING for more
 * information.
 */
/** @file private.h
 *
 *  BRL-CAD core C++ interface:
 *      private functions of the C++ interface implementation
 */


#ifndef PRIVATE_INCLUDED
#define PRIVATE_INCLUDED

struct rt_bot_internal;


rt_bot_internal* CloneBotInternal
(
    const rt_bot_internal& bot
);

void CleanUpBotInternal
(
    rt_bot_internal& bot
);


#endif // PRIVATE_INCLUDED
