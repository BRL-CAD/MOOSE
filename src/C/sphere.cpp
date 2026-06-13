/*                      S P H E R E . C P P
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
/** @file sphere.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      Implements a handle and functions for Sphere solid handling
 */

#include <cassert>

#include <brlcad/Database/Sphere.h>

#include <brlcad/C/sphere.h>

#include "casts.h"


using namespace BRLCAD;


BrlSphere BrlNewSphere
(
    void
) {
    return new SphereData(new Sphere());
}


BrlSphere BrlNewSphereAsSphere
(
    double centerX, double centerY, double centerZ,
    double radius
) {
    Vector3D center(centerX, centerY, centerZ);

    return new SphereData(new Sphere(center, radius));
}


BrlVector3D BrlSphereCenter
(
    BrlSphere sphere
) {
    BrlVector3D ret = nullptr;

    if (sphere != nullptr) {
        Sphere* sphr = CastSphere(sphere);

        assert(sphr != nullptr);

        if (sphr != nullptr)
            ret = new Vector3DData(sphr->Center());
    }
    return ret;
}


void BrlSphereSetCenter
(
    BrlSphere sphere, 
    double    centerX, double centerY, double centerZ
) {
    if (sphere != nullptr) {
        Sphere* sphr = CastSphere(sphere);

        assert(sphr != nullptr);

        if (sphr != nullptr) {
            Vector3D center(centerX, centerY, centerZ);

            sphr->SetCenter(center);
        }
    }
}


double BrlSphereRadius
(
    BrlSphere sphere
) {
    double ret = 0.;

    if (sphere != nullptr) {
        Sphere* sphr = CastSphere(sphere);

        assert(sphr != nullptr);

        if (sphr != nullptr)
            ret = sphr->Radius();
    }

    return ret;
}


void BrlSphereSetRadius
(
    BrlSphere sphere,
    double    radius
) {
    if (sphere != nullptr) {
        Sphere* sphr = CastSphere(sphere);

        assert(sphr != nullptr);

        if (sphr != nullptr)
            sphr->SetRadius(radius);
    }
}


void BrlSphereSet
(
    BrlSphere sphere,
    double    centerX, double centerY, double centerZ,
    double    radius
) {
    if (sphere != nullptr) {
        Sphere* sphr = CastSphere(sphere);

        assert(sphr != nullptr);

        if (sphr != nullptr) {
            Vector3D center(centerX, centerY, centerZ);

            sphr->Set(center, radius);
        }
    }
}
