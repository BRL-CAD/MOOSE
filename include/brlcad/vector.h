/*                      V E C T O R . H
 * BRL-CAD
 *
 * Copyright (c) 2008-2020 United States Government as represented by
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
/** @file vector.h
 *
 *  BRL-CAD core C++ interface:
 *      vector data types
 */

#ifndef BRLCAD_VECTOR_INCLUDED
#define BRLCAD_VECTOR_INCLUDED


namespace BRLCAD {
    struct Vector2D {
        double coordinates[2];

        Vector2D(void) {
            coordinates[0] = 0.;
            coordinates[1] = 0.;
        }

        Vector2D(const double vector[2]) {
            coordinates[0] = vector[0];
            coordinates[1] = vector[1];
        }

        Vector2D(double x,
                 double y) {
            coordinates[0] = x;
            coordinates[1] = y;
        }
    };


    struct Mapping2D {
        Vector2D point;
        Vector2D delta;

        Mapping2D(const Vector2D& pt,
                  const Vector2D& dl) : point(pt), delta(dl) {}
    };


    struct Vector3D {
        double coordinates[3];

        Vector3D(void) {
            coordinates[0] = 0.;
            coordinates[1] = 0.;
            coordinates[2] = 0.;
        }

        Vector3D(const double vector[3]) {
            coordinates[0] = vector[0];
            coordinates[1] = vector[1];
            coordinates[2] = vector[2];
        }

        Vector3D(double x,
                 double y,
                 double z) {
            coordinates[0] = x;
            coordinates[1] = y;
            coordinates[2] = z;
        }
    };


    struct Ray3D {
        Vector3D origin;
        Vector3D direction;
    };


    struct Curvature3D {
        Vector3D minPrincipalDirection;
        double   minPrincipalCurvature;
        double   maxPrincipalCurvature;

        Curvature3D(const Vector3D& minDirection,
                    double          minCurvature,
                    double          maxCurvature) {
            minPrincipalDirection = minDirection;
            minPrincipalCurvature = minCurvature;
            maxPrincipalCurvature = maxCurvature;
        }

        Curvature3D(void) : minPrincipalDirection(),
                                    minPrincipalCurvature(0.),
                                    maxPrincipalCurvature(0.) {}
    };
}


#endif // BRLCAD_VECTOR_INCLUDED
