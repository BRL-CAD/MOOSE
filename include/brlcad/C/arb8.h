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


BRLCAD_MOOSE_EXPORT BrlArb8     BrlNewArb8(void);
BRLCAD_MOOSE_EXPORT BrlArb8     BrlNewArb8AsArb4(double point1X, double point1Y, double point1Z,
                                                 double point2X, double point2Y, double point2Z,
                                                 double point3X, double point3Y, double point3Z,
                                                 double point4X, double point4Y, double point4Z);
BRLCAD_MOOSE_EXPORT BrlArb8     BrlNewArb8AsArb5(double point1X, double point1Y, double point1Z,
                                                 double point2X, double point2Y, double point2Z,
                                                 double point3X, double point3Y, double point3Z,
                                                 double point4X, double point4Y, double point4Z,
                                                 double point5X, double point5Y, double point5Z);
BRLCAD_MOOSE_EXPORT BrlArb8     BrlNewArb8AsArb6(double point1X, double point1Y, double point1Z,
                                                 double point2X, double point2Y, double point2Z,
                                                 double point3X, double point3Y, double point3Z,
                                                 double point4X, double point4Y, double point4Z,
                                                 double point5X, double point5Y, double point5Z,
                                                 double point6X, double point6Y, double point6Z);
BRLCAD_MOOSE_EXPORT BrlArb8     BrlNewArb8AsArb7(double point1X, double point1Y, double point1Z,
                                                 double point2X, double point2Y, double point2Z,
                                                 double point3X, double point3Y, double point3Z,
                                                 double point4X, double point4Y, double point4Z,
                                                 double point5X, double point5Y, double point5Z,
                                                 double point6X, double point6Y, double point6Z,
                                                 double point7X, double point7Y, double point7Z);
BRLCAD_MOOSE_EXPORT BrlArb8     BrlNewArb8AsArb8(double point1X, double point1Y, double point1Z,
                                                 double point2X, double point2Y, double point2Z,
                                                 double point3X, double point3Y, double point3Z,
                                                 double point4X, double point4Y, double point4Z,
                                                 double point5X, double point5Y, double point5Z,
                                                 double point6X, double point6Y, double point6Z,
                                                 double point7X, double point7Y, double point7Z,
                                                 double point8X, double point8Y, double point8Z);
BRLCAD_MOOSE_EXPORT BrlArb8     BrlNewArb8AsRectengularParallelPiped(double point1X, double point1Y, double point1Z,
                                                                     double point2X, double point2Y, double point2Z);

BRLCAD_MOOSE_EXPORT int         BrlArb8NumberOfVertices(BrlArb8 arb8);

BRLCAD_MOOSE_EXPORT BrlVector3D BrlArb8Point(BrlArb8 arb8,
                                             int number);
BRLCAD_MOOSE_EXPORT void        BrlArb8SetPoint(BrlArb8 arb8,
                                                int number,
                                                double pointX, double pointY, double pointZ);

BRLCAD_MOOSE_EXPORT BrlVector3D BrlArb8RawPoint(BrlArb8 arb8,
                                                int index);
BRLCAD_MOOSE_EXPORT void        BrlArb8SetRawPoint(BrlArb8 arb8,
                                                   int index,
                                                   double pointX, double pointY, double pointZ);

BRLCAD_MOOSE_EXPORT void        BrlArb8SetPointsAsArb4(BrlArb8 arb8,
                                                       double point1X, double point1Y, double point1Z,
                                                       double point2X, double point2Y, double point2Z,
                                                       double point3X, double point3Y, double point3Z,
                                                       double point4X, double point4Y, double point4Z);
BRLCAD_MOOSE_EXPORT void        BrlArb8SetPointsAsArb5(BrlArb8 arb8,
                                                       double point1X, double point1Y, double point1Z,
                                                       double point2X, double point2Y, double point2Z,
                                                       double point3X, double point3Y, double point3Z,
                                                       double point4X, double point4Y, double point4Z,
                                                       double point5X, double point5Y, double point5Z);
BRLCAD_MOOSE_EXPORT void        BrlArb8SetPointsAsArb6(BrlArb8 arb8,
                                                       double point1X, double point1Y, double point1Z,
                                                       double point2X, double point2Y, double point2Z,
                                                       double point3X, double point3Y, double point3Z,
                                                       double point4X, double point4Y, double point4Z,
                                                       double point5X, double point5Y, double point5Z,
                                                       double point6X, double point6Y, double point6Z);
BRLCAD_MOOSE_EXPORT void        BrlArb8SetPointsAsArb7(BrlArb8 arb8,
                                                       double point1X, double point1Y, double point1Z,
                                                       double point2X, double point2Y, double point2Z,
                                                       double point3X, double point3Y, double point3Z,
                                                       double point4X, double point4Y, double point4Z,
                                                       double point5X, double point5Y, double point5Z,
                                                       double point6X, double point6Y, double point6Z,
                                                       double point7X, double point7Y, double point7Z);
BRLCAD_MOOSE_EXPORT void        BrlArb8SetPointsAsArb8(BrlArb8 arb8,
                                                       double point1X, double point1Y, double point1Z,
                                                       double point2X, double point2Y, double point2Z,
                                                       double point3X, double point3Y, double point3Z,
                                                       double point4X, double point4Y, double point4Z,
                                                       double point5X, double point5Y, double point5Z,
                                                       double point6X, double point6Y, double point6Z,
                                                       double point7X, double point7Y, double point7Z,
                                                       double point8X, double point8Y, double point8Z);
BRLCAD_MOOSE_EXPORT void        BrlArb8SetPointsAsRectengularParallelPiped(BrlArb8 arb8,
                                                                           double point1X, double point1Y, double point1Z,
                                                                           double point2X, double point2Y, double point2Z);


#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_ARB8_INCLUDED
