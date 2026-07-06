/* B A G O F T R I A N G L E S . H
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


enum BrlBotMode {
    BrlBotModeSurface = 1,
    BrlBotModeSolid,
    BrlBotModePlate,
    BrlBotModeEqualLineOfSightPlate
};

BRLCAD_MOOSE_EXPORT BrlBotMode                     BrlBagOfTrianglesMode(BrlBagOfTriangles bot);
BRLCAD_MOOSE_EXPORT void                           BrlBagOfTrianglesSetMode(BrlBagOfTriangles bot,
                                                                            enum BrlBotMode   mode);


enum BrlBotOrientation {
    BrlBotOrientationUnoriented = 1,
    BrlBotOrientationClockWise,
    BrlBotOrientationCounterClockWise
};

BRLCAD_MOOSE_EXPORT BrlBotOrientation              BrlBagOfTrianglesOrientation(BrlBagOfTriangles bot);
BRLCAD_MOOSE_EXPORT void                           BrlBagOfTrianglesSetOrientation(BrlBagOfTriangles bot,
                                                                                   enum BrlBotOrientation orientation);


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
                                                                            const double*     pt1,
                                                                            const double*     pt2,
                                                                            const double*     pt3);
BRLCAD_MOOSE_EXPORT void                           BrlBagOfTrianglesDeleteFace(BrlBagOfTriangles bot,
                                                                               int               index);

BRLCAD_MOOSE_EXPORT const char*                    BrlBagOfTrianglesClassName(void);

BRLCAD_MOOSE_EXPORT void                           BrlBagOfTrianglesFacePoint(BrlBagOfTrianglesFace face, 
                                                                              int                   index, 
                                                                              double*               out_pt);
BRLCAD_MOOSE_EXPORT void                           BrlBagOfTrianglesFaceSetPoint(BrlBagOfTrianglesFace face,
                                                                                 int                   index,
                                                                                 const double*           point);
BRLCAD_MOOSE_EXPORT void                           BrlBagOfTrianglesFaceSetPoints(BrlBagOfTrianglesFace face,
                                                                                  const double*         pt1,
                                                                                  const double*         pt2,
                                                                                  const double*         pt3);

BRLCAD_MOOSE_EXPORT double                         BrlBagOfTrianglesFaceThickness(BrlBagOfTrianglesFace face);
BRLCAD_MOOSE_EXPORT void                           BrlBagOfTrianglesFaceSetThickness(BrlBagOfTrianglesFace face,
                                                                                     double                value);

BRLCAD_MOOSE_EXPORT int                            BrlBagOfTrianglesFaceApendThickness(BrlBagOfTrianglesFace face);
BRLCAD_MOOSE_EXPORT void                           BrlBagOfTrianglesFaceSetApendThickness(BrlBagOfTrianglesFace face,
                                                                                          int                   apendThickness);

BRLCAD_MOOSE_EXPORT void                           BrlBagOfTrianglesFaceNormal(BrlBagOfTrianglesFace face,
                                                                               int                index,
                                                                               double*            out_normal);
BRLCAD_MOOSE_EXPORT void                           BrlBagOfTrianglesFaceSetNormal(BrlBagOfTrianglesFace face,
                                                                                  int                   index,
                                                                                  const double*         normal);
BRLCAD_MOOSE_EXPORT void                           BrlBagOfTrianglesFaceSetNormals(BrlBagOfTrianglesFace face,
                                                                                   const double*         normal1,
                                                                                   const double*         normal2,
                                                                                   const double*         normal3);

BRLCAD_MOOSE_EXPORT void                           BrlBagOfTrianglesFaceDelete(BrlBagOfTrianglesFace face);


#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_BAG_OF_TRIANGLES_INCLUDED
