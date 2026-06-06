/*                      A R B 8 . C P P
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
/** @file arb8.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      implements a handle and functions for Arb8 solid handling
 */

#include <brlcad/Database/Arb8.h>

#include <brlcad/C/arb8.h>

#include "BrlData.h"


using namespace BRLCAD;


BrlArb8 BrlNewArb8From4Points
(
    double point1X, double point1Y, double point1Z,
    double point2X, double point2Y, double point2Z,
    double point3X, double point3Y, double point3Z,
    double point4X, double point4Y, double point4Z
) {
    Vector3D point1(point1X, point1Y, point1Z);
    Vector3D point2(point2X, point2Y, point2Z);
    Vector3D point3(point3X, point3Y, point3Z);
    Vector3D point4(point4X, point4Y, point4Z);

    return new Arb8Data(new Arb8(point1, point2, point3, point4));
}


BrlArb8 BrlNewArb8From8Points
(
    double point1X, double point1Y, double point1Z,
    double point2X, double point2Y, double point2Z,
    double point3X, double point3Y, double point3Z,
    double point4X, double point4Y, double point4Z,
    double point5X, double point5Y, double point5Z,
    double point6X, double point6Y, double point6Z,
    double point7X, double point7Y, double point7Z,
    double point8X, double point8Y, double point8Z
) {
    Vector3D point1(point1X, point1Y, point1Z);
    Vector3D point2(point2X, point2Y, point2Z);
    Vector3D point3(point3X, point3Y, point3Z);
    Vector3D point4(point4X, point4Y, point4Z);
    Vector3D point5(point5X, point5Y, point5Z);
    Vector3D point6(point6X, point6Y, point6Z);
    Vector3D point7(point7X, point7Y, point7Z);
    Vector3D point8(point8X, point8Y, point8Z);

    return new Arb8Data(new Arb8(point1, point2, point3, point4, point5, point6, point7, point8));
}


BrlArb8 BrlNewArb8From2Points
(
    double point1X, double point1Y, double point1Z,
    double point2X, double point2Y, double point2Z
) {
    Vector3D point1(point1X, point1Y, point1Z);
    Vector3D point2(point2X, point2Y, point2Z);

    return new Arb8Data(new Arb8(point1, point2));
}
