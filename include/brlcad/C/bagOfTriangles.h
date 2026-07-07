/*                          B A G O F T R I A N G L E S . H
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
/** @file bagOfTriangles.h
 *
 * BRL-CAD core simplified C interface:
 * declares handles and functions for BagOfTriangles object and face handling
 */

#ifndef BRLCAD_C_BAG_OF_TRIANGLES_INCLUDED
#define BRLCAD_C_BAG_OF_TRIANGLES_INCLUDED

#include <brlcad/C/object.h>
#include <brlcad/C/vector.h>
#include <brlcad/C/globals.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef BrlObject BrlBagOfTriangles;
typedef BrlHandle BrlBagOfTrianglesFace;


BRLCAD_MOOSE_EXPORT BrlBagOfTriangles              BrlNewBagOfTriangles(void);


enum BrlBagOfTrianglesBotMode {
    BrlBotModeSurface,
    BrlBotModeSolid,
    BrlBotModePlate,
    BrlBotModeEqualLineOfSightPlate
};


BRLCAD_MOOSE_EXPORT int                             BrlBagOfTrianglesMode(BrlBagOfTriangles bot);
BRLCAD_MOOSE_EXPORT void                            BrlBagOfTrianglesSetMode(BrlBagOfTriangles bot,
                                                                             int               mode);


enum BrlBagOfTrianglesBotOrientation {
    BrlBotOrientationUnoriented,
    BrlBotOrientationClockWise,
    BrlBotOrientationCounterClockWise
};


BRLCAD_MOOSE_EXPORT int                             BrlBagOfTrianglesOrientation(BrlBagOfTriangles bot);
BRLCAD_MOOSE_EXPORT void                            BrlBagOfTrianglesSetOrientation(BrlBagOfTriangles bot,
                                                                                    int               orientation);


BRLCAD_MOOSE_EXPORT int                            BrlBagOfTrianglesFacesHaveNormals(BrlBagOfTriangles bot);
BRLCAD_MOOSE_EXPORT void                           BrlBagOfTrianglesSetFacesHaveNormals(BrlBagOfTriangles bot,
                                                                                        int               facesHaveNormals);

BRLCAD_MOOSE_EXPORT int                            BrlBagOfTrianglesUseFaceNormals(BrlBagOfTriangles bot);
BRLCAD_MOOSE_EXPORT void                           BrlBagOfTrianglesSetUseFaceNormals(BrlBagOfTriangles bot,
                                                                                      int               useFaceNormals);

BRLCAD_MOOSE_EXPORT int                            BrlBagOfTrianglesUseFloats(BrlBagOfTriangles bot);
BRLCAD_MOOSE_EXPORT void                           BrlBagOfTrianglesSetUseFloats(BrlBagOfTriangles bot,
                                                                                 int               useFloats);

BRLCAD_MOOSE_EXPORT int                            BrlBagOfTrianglesNumberOfFaces(BrlBagOfTriangles bot);

BRLCAD_MOOSE_EXPORT BrlBagOfTrianglesFace          BrlBagOfTrianglesGetFace(BrlBagOfTriangles bot,
                                                                            int               index);
BRLCAD_MOOSE_EXPORT BrlBagOfTrianglesFace          BrlBagOfTrianglesAddFace(BrlBagOfTriangles bot,
                                                                            double            point1X,
                                                                            double            point1Y,
                                                                            double            point1Z,
                                                                            double            point2X,
                                                                            double            point2Y,
                                                                            double            point2Z,
                                                                            double            point3X,
                                                                            double            point3Y,
                                                                            double            point3Z);
BRLCAD_MOOSE_EXPORT void                           BrlBagOfTrianglesDeleteFace(BrlBagOfTriangles bot,
                                                                               int               index);

BRLCAD_MOOSE_EXPORT const char*                    BrlBagOfTrianglesClassName(void);

BRLCAD_MOOSE_EXPORT void                           BrlBagOfTrianglesFacePoint(BrlBagOfTrianglesFace face, 
                                                                              int                   index, 
                                                                              double*               outX,
                                                                              double*               outY,
                                                                              double*               outZ);
BRLCAD_MOOSE_EXPORT void                           BrlBagOfTrianglesFaceSetPoint(BrlBagOfTrianglesFace face,
                                                                                 int                   index,
                                                                                 double                pointX,
                                                                                 double                pointY,
                                                                                 double                pointZ);
BRLCAD_MOOSE_EXPORT void                           BrlBagOfTrianglesFaceSetPoints(BrlBagOfTrianglesFace face,
                                                                                  double                point1X,
                                                                                  double                point1Y,
                                                                                  double                point1Z,
                                                                                  double                point2X,
                                                                                  double                point2Y,
                                                                                  double                point2Z,
                                                                                  double                point3X,
                                                                                  double                point3Y,
                                                                                  double                point3Z);

BRLCAD_MOOSE_EXPORT double                         BrlBagOfTrianglesFaceThickness(BrlBagOfTrianglesFace face);
BRLCAD_MOOSE_EXPORT void                           BrlBagOfTrianglesFaceSetThickness(BrlBagOfTrianglesFace face,
                                                                                     double                value);

BRLCAD_MOOSE_EXPORT int                            BrlBagOfTrianglesFaceApendThickness(BrlBagOfTrianglesFace face);
BRLCAD_MOOSE_EXPORT void                           BrlBagOfTrianglesFaceSetApendThickness(BrlBagOfTrianglesFace face,
                                                                                          int                   apendThickness);

BRLCAD_MOOSE_EXPORT void                           BrlBagOfTrianglesFaceNormal(BrlBagOfTrianglesFace face,
                                                                               int                   index,
                                                                               double*               outNormalX,
                                                                               double*               outNormalY,
                                                                               double*               outNormalZ);
BRLCAD_MOOSE_EXPORT void                           BrlBagOfTrianglesFaceSetNormal(BrlBagOfTrianglesFace face,
                                                                                  int                   index,
                                                                                  double                normalX,
                                                                                  double                normalY,
                                                                                  double                normalZ);
BRLCAD_MOOSE_EXPORT void                           BrlBagOfTrianglesFaceSetNormals(BrlBagOfTrianglesFace face,
                                                                                   double                normal1X,
                                                                                   double                normal1Y,
                                                                                   double                normal1Z,
                                                                                   double                normal2X,
                                                                                   double                normal2Y,
                                                                                   double                normal2Z,
                                                                                   double                normal3X,
                                                                                   double                normal3Y,
                                                                                   double                normal3Z);

BRLCAD_MOOSE_EXPORT void                           BrlBagOfTrianglesFaceDelete(BrlBagOfTrianglesFace face);


#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_BAG_OF_TRIANGLES_INCLUDED
