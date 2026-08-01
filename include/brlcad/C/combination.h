/*                  C O M B I N A T I O N . H
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
/** @file combination.h
 *
 *  BRL-CAD core simplified C interface:
 *      declares handles and functions for Combination object and CSG tree handling
 */


#ifndef BRLCAD_C_COMBINATION_INCLUDED
#define BRLCAD_C_COMBINATION_INCLUDED

#include <brlcad/C/object.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef BrlObject BrlCombination;


BRLCAD_MOOSE_EXPORT BrlCombination                BrlNewCombination(void);


typedef BrlHandle BrlCombinationTreeNode;

enum BrlCombinationTreeNodeOperator {
    BrlCombinationTreeNodeOperatorNull,
    BrlCombinationTreeNodeOperatorUnion,
    BrlCombinationTreeNodeOperatorIntersection,
    BrlCombinationTreeNodeOperatorSubtraction,
    BrlCombinationTreeNodeOperatorExclusiveOr,
    BrlCombinationTreeNodeOperatorNot,
    BrlCombinationTreeNodeOperatorLeaf
};

BRLCAD_MOOSE_EXPORT BrlCombinationTreeNodeOperator BrlCombinationTreeNodeOperation(BrlCombinationTreeNode node);
BRLCAD_MOOSE_EXPORT BrlCombinationTreeNode         BrlCombinationTreeNodeLeftOperand(BrlCombinationTreeNode node);
BRLCAD_MOOSE_EXPORT BrlCombinationTreeNode         BrlCombinationTreeNodeRightOperand(BrlCombinationTreeNode node);
BRLCAD_MOOSE_EXPORT BrlCombinationTreeNode         BrlCombinationTreeNodeOperand(BrlCombinationTreeNode node);
BRLCAD_MOOSE_EXPORT const char*                    BrlCombinationTreeNodeName(BrlCombinationTreeNode node);
BRLCAD_MOOSE_EXPORT void                           BrlCombinationTreeNodeSetName(BrlCombinationTreeNode node,
                                                                                 const char*            name);
BRLCAD_MOOSE_EXPORT const double*                  BrlCombinationTreeNodeMatrix(BrlCombinationTreeNode node);
BRLCAD_MOOSE_EXPORT void                           BrlCombinationTreeNodeSetMatrix(BrlCombinationTreeNode node,
                                                                                   const double           matrix[16]);

BRLCAD_MOOSE_EXPORT BrlCombinationTreeNode         BrlCombinationTreeNodeApplyUnary(BrlCombinationTreeNode         node,
                                                                                    BrlCombinationTreeNodeOperator op);
BRLCAD_MOOSE_EXPORT BrlCombinationTreeNode         BrlCombinationTreeNodeApplyNodeRight(BrlCombinationTreeNode         node,
                                                                                        BrlCombinationTreeNodeOperator op,
                                                                                        BrlCombinationTreeNode         other);
BRLCAD_MOOSE_EXPORT BrlCombinationTreeNode         BrlCombinationTreeNodeApplyLeafRight(BrlCombinationTreeNode         node,
                                                                                        BrlCombinationTreeNodeOperator op,
                                                                                        const char*                    leafName);
BRLCAD_MOOSE_EXPORT BrlCombinationTreeNode         BrlCombinationTreeNodeApplyNodeLeft(BrlCombinationTreeNode         node,
                                                                                       BrlCombinationTreeNode         other,
                                                                                       BrlCombinationTreeNodeOperator op);
BRLCAD_MOOSE_EXPORT BrlCombinationTreeNode         BrlCombinationTreeNodeApplyLeafLeft(BrlCombinationTreeNode         node,
                                                                                       const char*                    leafName,
                                                                                       BrlCombinationTreeNodeOperator op);

BRLCAD_MOOSE_EXPORT void                           BrlCombinationTreeNodeDelete(BrlCombinationTreeNode node);


BRLCAD_MOOSE_EXPORT BrlCombinationTreeNode         BrlCombinationTree(BrlCombination combination);

BRLCAD_MOOSE_EXPORT void                           BrlCombinationAddLeaf(BrlCombination combination,
                                                                         const char*    leafName);

BRLCAD_MOOSE_EXPORT int                            BrlCombinationIsRegion(BrlCombination combination);
BRLCAD_MOOSE_EXPORT void                           BrlCombinationSetIsRegion(BrlCombination combination,
                                                                             int            value);

enum BrlCombinationFastgenType {
    BrlCombinationFastgenTypeNon,
    BrlCombinationFastgenTypePlate,
    BrlCombinationFastgenTypeVolume
};

BRLCAD_MOOSE_EXPORT BrlCombinationFastgenType      BrlCombinationFastgenRegion(BrlCombination combination);
BRLCAD_MOOSE_EXPORT void                           BrlCombinationSetFastgenRegion(BrlCombination            combination,
                                                                                  BrlCombinationFastgenType value);

BRLCAD_MOOSE_EXPORT int                            BrlCombinationRegionId(BrlCombination combination);
BRLCAD_MOOSE_EXPORT void                           BrlCombinationSetRegionId(BrlCombination combination,
                                                                             int            value);

BRLCAD_MOOSE_EXPORT int                            BrlCombinationAircode(BrlCombination combination);
BRLCAD_MOOSE_EXPORT void                           BrlCombinationSetAircode(BrlCombination combination,
                                                                            int            value);

BRLCAD_MOOSE_EXPORT int                            BrlCombinationGiftMaterial(BrlCombination combination);
BRLCAD_MOOSE_EXPORT void                           BrlCombinationSetGiftMaterial(BrlCombination combination,
                                                                                 int            value);

BRLCAD_MOOSE_EXPORT int                            BrlCombinationLineOfSight(BrlCombination combination);
BRLCAD_MOOSE_EXPORT void                           BrlCombinationSetLineOfSight(BrlCombination combination,
                                                                                int            value);

BRLCAD_MOOSE_EXPORT int                            BrlCombinationHasColor(BrlCombination combination);
BRLCAD_MOOSE_EXPORT void                           BrlCombinationSetHasColor(BrlCombination combination,
                                                                             int            value);

BRLCAD_MOOSE_EXPORT double                         BrlCombinationRed(BrlCombination combination);
BRLCAD_MOOSE_EXPORT void                           BrlCombinationSetRed(BrlCombination combination,
                                                                        double         value);

BRLCAD_MOOSE_EXPORT double                         BrlCombinationGreen(BrlCombination combination);
BRLCAD_MOOSE_EXPORT void                           BrlCombinationSetGreen(BrlCombination combination,
                                                                          double         value);

BRLCAD_MOOSE_EXPORT double                         BrlCombinationBlue(BrlCombination combination);
BRLCAD_MOOSE_EXPORT void                           BrlCombinationSetBlue(BrlCombination combination,
                                                                         double         value);

BRLCAD_MOOSE_EXPORT const char*                    BrlCombinationShader(BrlCombination combination);
BRLCAD_MOOSE_EXPORT void                           BrlCombinationSetShader(BrlCombination combination,
                                                                           const char*    value);

BRLCAD_MOOSE_EXPORT int                            BrlCombinationInherit(BrlCombination combination);
BRLCAD_MOOSE_EXPORT void                           BrlCombinationSetInherit(BrlCombination combination,
                                                                            int            value);

BRLCAD_MOOSE_EXPORT const char*                    BrlCombinationMaterial(BrlCombination combination);
BRLCAD_MOOSE_EXPORT void                           BrlCombinationSetMaterial(BrlCombination combination,
                                                                             const char*    value);

BRLCAD_MOOSE_EXPORT double                         BrlCombinationTemperature(BrlCombination combination);
BRLCAD_MOOSE_EXPORT void                           BrlCombinationSetTemperature(BrlCombination combination,
                                                                                double         value);

BRLCAD_MOOSE_EXPORT const char*                    BrlCombinationClassName(void);


#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_COMBINATION_INCLUDED
