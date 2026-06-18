/*                      A R B 8 . H
 * BRL-CAD
 *
 * Copyright (c) 2026 United States Government as represented by
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
/** @file arb8.h
 *
 *  BRL-CAD core simplified C interface:
 *      declares a handle and functions for Arb8 solid handling
 */

#ifndef BRLCAD_C_ARB8_INCLUDED
#define BRLCAD_C_ARB8_INCLUDED

#include <brlcad/C/object.h>

#include <brlcad/C/vector.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef BrlObject BrlArb8;


BRLCAD_MOOSE_EXPORT BrlArb8 BrlNewArb8(void);
BRLCAD_MOOSE_EXPORT BrlArb8 BrlNewArb8AsArb4(double point1X, double point1Y, double point1Z,
                                             double point2X, double point2Y, double point2Z,
                                             double point3X, double point3Y, double point3Z,
                                             double point4X, double point4Y, double point4Z);
BRLCAD_MOOSE_EXPORT BrlArb8 BrlNewArb8AsArb8(double point1X, double point1Y, double point1Z,
                                             double point2X, double point2Y, double point2Z,
                                             double point3X, double point3Y, double point3Z,
                                             double point4X, double point4Y, double point4Z,
                                             double point5X, double point5Y, double point5Z,
                                             double point6X, double point6Y, double point6Z,
                                             double point7X, double point7Y, double point7Z,
                                             double point8X, double point8Y, double point8Z);
BRLCAD_MOOSE_EXPORT BrlArb8 BrlNewArb8AsRectengularParallelPiped(double point1X, double point1Y, double point1Z,
                                                                 double point2X, double point2Y, double point2Z);

BRLCAD_MOOSE_EXPORT int     BrlArb8NumberOfVertices(BrlArb8 arb8);

BRLCAD_MOOSE_EXPORT BrlVector3D    BrlArb8Point(BrlArb8 arb8, int number);
BRLCAD_MOOSE_EXPORT BrlVector3D    BrlArb8RawPoint(BrlArb8 arb8, int index);

BRLCAD_MOOSE_EXPORT void    BrlArb8SetPoint(BrlArb8 arb8, int number, double x, double y, double z);
BRLCAD_MOOSE_EXPORT void    BrlArb8SetRawPoint(BrlArb8 arb8, int index, double x, double y, double z);

BRLCAD_MOOSE_EXPORT void    BrlArb8SetPoints2(BrlArb8 arb8,
                                              double p1x, double p1y, double p1z,
                                              double p2x, double p2y, double p2z);
BRLCAD_MOOSE_EXPORT void    BrlArb8SetPoints4(BrlArb8 arb8,
                                               double p1x, double p1y, double p1z, double p2x, double p2y, double p2z,
                                               double p3x, double p3y, double p3z, double p4x, double p4y, double p4z);
BRLCAD_MOOSE_EXPORT void    BrlArb8SetPoints5(BrlArb8 arb8,
                                              double p1x, double p1y, double p1z, double p2x, double p2y, double p2z,
                                              double p3x, double p3y, double p3z, double p4x, double p4y, double p4z,
                                              double p5x, double p5y, double p5z);
BRLCAD_MOOSE_EXPORT void    BrlArb8SetPoints6(BrlArb8 arb8,
                                              double p1x, double p1y, double p1z, double p2x, double p2y, double p2z,
                                              double p3x, double p3y, double p3z, double p4x, double p4y, double p4z,
                                              double p5x, double p5y, double p5z, double p6x, double p6y, double p6z);
BRLCAD_MOOSE_EXPORT void    BrlArb8SetPoints7(BrlArb8 arb8,
                                              double p1x, double p1y, double p1z, double p2x, double p2y, double p2z,
                                              double p3x, double p3y, double p3z, double p4x, double p4y, double p4z,
                                              double p5x, double p5y, double p5z, double p6x, double p6y, double p6z,
                                              double p7x, double p7y, double p7z);
BRLCAD_MOOSE_EXPORT void    BrlArb8SetPoints8(BrlArb8 arb8,
                                              double p1x, double p1y, double p1z, double p2x, double p2y, double p2z,
                                              double p3x, double p3y, double p3z, double p4x, double p4y, double p4z,
                                              double p5x, double p5y, double p5z, double p6x, double p6y, double p6z,
                                              double p7x, double p7y, double p7z, double p8x, double p8y, double p8z);


#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_ARB8_INCLUDED
