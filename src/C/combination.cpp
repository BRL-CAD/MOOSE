/*                  C O M B I N A T I O N . C P P
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
/** @file combination.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      Implements handles and functions for Combination object and CSG tree handling
 */

#include <cassert>

#include "bu/log.h"

#include <brlcad/Database/Combination.h>

#include <brlcad/C/combination.h>

#include "casts.h"


using namespace BRLCAD;


static Combination::TreeNode::Operator ConvertOperator
(
    BrlCombinationTreeNodeOperator op
) {
    Combination::TreeNode::Operator ret = Combination::TreeNode::Operator::Null;

    switch (op) {
    case BrlCombinationTreeNodeOperatorNull:
        ret = Combination::TreeNode::Operator::Null;
        break;

    case BrlCombinationTreeNodeOperatorUnion:
        ret = Combination::TreeNode::Operator::Union;
        break;

    case BrlCombinationTreeNodeOperatorIntersection:
        ret = Combination::TreeNode::Operator::Intersection;
        break;

    case BrlCombinationTreeNodeOperatorSubtraction:
        ret = Combination::TreeNode::Operator::Subtraction;
        break;

    case BrlCombinationTreeNodeOperatorExclusiveOr:
        ret = Combination::TreeNode::Operator::ExclusiveOr;
        break;

    case BrlCombinationTreeNodeOperatorNot:
        ret = Combination::TreeNode::Operator::Not;
        break;

    case BrlCombinationTreeNodeOperatorLeaf:
        ret = Combination::TreeNode::Operator::Leaf;
        break;

    default:
        bu_log("BrlCombinationTreeNode~: invalid BrlCombinationTreeNodeOperator");
    }

    return ret;
}


static BrlCombinationTreeNodeOperator ConvertOperatorBack
(
    Combination::TreeNode::Operator op
) {
    BrlCombinationTreeNodeOperator ret = BrlCombinationTreeNodeOperatorNull;

    switch (op) {
    case Combination::TreeNode::Operator::Null:
        ret = BrlCombinationTreeNodeOperatorNull;
        break;

    case Combination::TreeNode::Operator::Union:
        ret = BrlCombinationTreeNodeOperatorUnion;
        break;

    case Combination::TreeNode::Operator::Intersection:
        ret = BrlCombinationTreeNodeOperatorIntersection;
        break;

    case Combination::TreeNode::Operator::Subtraction:
        ret = BrlCombinationTreeNodeOperatorSubtraction;
        break;

    case Combination::TreeNode::Operator::ExclusiveOr:
        ret = BrlCombinationTreeNodeOperatorExclusiveOr;
        break;

    case Combination::TreeNode::Operator::Not:
        ret = BrlCombinationTreeNodeOperatorNot;
        break;

    case Combination::TreeNode::Operator::Leaf:
        ret = BrlCombinationTreeNodeOperatorLeaf;
        break;

    default:
        bu_log("BrlCombinationTreeNode~: invalid BRLCAD::Combination::TreeNode::Operator");
    }

    return ret;
}


BrlCombination BrlNewCombination(void) {
    return new CombinationData(new Combination());
}


BrlCombinationTreeNodeOperator BrlCombinationTreeNodeOperation
(
    BrlCombinationTreeNode node
) {
    BrlCombinationTreeNodeOperator ret = BrlCombinationTreeNodeOperatorNull;

    if (node != nullptr) {
        Combination::TreeNode* nodeIntern = CastCombinationTreeNode(node);

        assert(nodeIntern != nullptr);

        if (nodeIntern != nullptr)
            ret = ConvertOperatorBack(nodeIntern->Operation());
    }

    return ret;
}


BrlCombinationTreeNode BrlCombinationTreeNodeLeftOperand
(
    BrlCombinationTreeNode node
) {
    BrlCombinationTreeNode ret = nullptr;

    if (node != nullptr) {
        Combination::TreeNode* nodeIntern = CastCombinationTreeNode(node);

        assert(nodeIntern != nullptr);

        if (nodeIntern != nullptr)
            ret = new CombinationTreeNodeData(nodeIntern->LeftOperand());
    }

    return ret;
}


BrlCombinationTreeNode BrlCombinationTreeNodeRightOperand
(
    BrlCombinationTreeNode node
) {
    BrlCombinationTreeNode ret = nullptr;

    if (node != nullptr) {
        Combination::TreeNode* nodeIntern = CastCombinationTreeNode(node);

        assert(nodeIntern != nullptr);

        if (nodeIntern != nullptr)
            ret = new CombinationTreeNodeData(nodeIntern->RightOperand());
    }

    return ret;
}


BrlCombinationTreeNode BrlCombinationTreeNodeOperand
(
    BrlCombinationTreeNode node
) {
    BrlCombinationTreeNode ret = nullptr;

    if (node != nullptr) {
        Combination::TreeNode* nodeIntern = CastCombinationTreeNode(node);

        assert(nodeIntern != nullptr);

        if (nodeIntern != nullptr)
            ret = new CombinationTreeNodeData(nodeIntern->Operand());
    }

    return ret;
}


const char* BrlCombinationTreeNodeName
(
    BrlCombinationTreeNode node
) {
    const char* ret = nullptr;

    if (node != nullptr) {
        Combination::TreeNode* nodeIntern = CastCombinationTreeNode(node);

        assert(nodeIntern != nullptr);

        if (nodeIntern != nullptr)
            ret = nodeIntern->Name();
    }

    return ret;
}


void BrlCombinationTreeNodeSetName
(
    BrlCombinationTreeNode node,
    const char*            name
) {
    if (node != nullptr) {
        Combination::TreeNode* nodeIntern = CastCombinationTreeNode(node);

        assert(nodeIntern != nullptr);

        if (nodeIntern != nullptr)
            nodeIntern->SetName(name);
    }
}


const double* BrlCombinationTreeNodeMatrix
(
    BrlCombinationTreeNode node
) {
    const double* ret = nullptr;

    if (node != nullptr) {
        Combination::TreeNode* nodeIntern = CastCombinationTreeNode(node);

        assert(nodeIntern != nullptr);

        if (nodeIntern != nullptr)
            ret = nodeIntern->Matrix();
    }

    return ret;
}


void BrlCombinationTreeNodeSetMatrix
(
    BrlCombinationTreeNode node,
    const double           matrix[16]
) {
    if (node != nullptr) {
        Combination::TreeNode* nodeIntern = CastCombinationTreeNode(node);

        assert(nodeIntern != nullptr);

        if (nodeIntern != nullptr)
            nodeIntern->SetMatrix(matrix);
    }
}


BrlCombinationTreeNode BrlCombinationTreeNodeApplyUnary
(
    BrlCombinationTreeNode         node,
    BrlCombinationTreeNodeOperator op
) {
    BrlCombinationTreeNode ret = nullptr;

    if (node != nullptr) {
        Combination::TreeNode* nodeIntern = CastCombinationTreeNode(node);

        assert(nodeIntern != nullptr);

        if (nodeIntern != nullptr)
            ret = new CombinationTreeNodeData(nodeIntern->Apply(ConvertOperator(op)));
    }

    return ret;
}


BrlCombinationTreeNode BrlCombinationTreeNodeApplyNodeRight
(
    BrlCombinationTreeNode         node,
    BrlCombinationTreeNodeOperator op,
    BrlCombinationTreeNode         other
) {
    BrlCombinationTreeNode ret = nullptr;

    if ((node != nullptr) && (other != nullptr)) {
        Combination::TreeNode* nodeIntern  = CastCombinationTreeNode(node);
        Combination::TreeNode* otherIntern = CastCombinationTreeNode(other);

        assert(nodeIntern != nullptr);
        assert(otherIntern != nullptr);

        if ((nodeIntern != nullptr) && (otherIntern != nullptr))
            ret = new CombinationTreeNodeData(nodeIntern->Apply(ConvertOperator(op), *otherIntern));
    }

    return ret;
}


BrlCombinationTreeNode BrlCombinationTreeNodeApplyLeafRight
(
    BrlCombinationTreeNode         node,
    BrlCombinationTreeNodeOperator op,
    const char*                    leafName
) {
    BrlCombinationTreeNode ret = nullptr;

    if ((node != nullptr) && (leafName != nullptr)) {
        Combination::TreeNode* nodeIntern = CastCombinationTreeNode(node);

        assert(nodeIntern != nullptr);

        if (nodeIntern != nullptr)
            ret = new CombinationTreeNodeData(nodeIntern->Apply(ConvertOperator(op), leafName));
    }

    return ret;
}


BrlCombinationTreeNode BrlCombinationTreeNodeApplyNodeLeft
(
    BrlCombinationTreeNode         node,
    BrlCombinationTreeNode         other,
    BrlCombinationTreeNodeOperator op
) {
    BrlCombinationTreeNode ret = nullptr;

    if ((other != nullptr) && (node != nullptr)) {
        Combination::TreeNode* nodeIntern  = CastCombinationTreeNode(node);
        Combination::TreeNode* otherIntern = CastCombinationTreeNode(other);

        assert(nodeIntern != nullptr);
        assert(otherIntern != nullptr);

        if ((nodeIntern != nullptr) && (otherIntern != nullptr))
            ret = new CombinationTreeNodeData(nodeIntern->Apply(*otherIntern, ConvertOperator(op)));
    }

    return ret;
}


BrlCombinationTreeNode BrlCombinationTreeNodeApplyLeafLeft
(
    BrlCombinationTreeNode         node,
    const char*                    leafName,
    BrlCombinationTreeNodeOperator op
) {
    BrlCombinationTreeNode ret = nullptr;

    if ((leafName != nullptr) && (node != nullptr)) {
        Combination::TreeNode* nodeIntern = CastCombinationTreeNode(node);

        assert(nodeIntern != nullptr);

        if (nodeIntern != nullptr)
            ret = new CombinationTreeNodeData(nodeIntern->Apply(leafName, ConvertOperator(op)));
    }

    return ret;
}


void BrlCombinationTreeNodeDelete
(
    BrlCombinationTreeNode node
) {
    if (node != nullptr) {
        Combination::TreeNode* nodeIntern = CastCombinationTreeNode(node);

        assert(nodeIntern != nullptr);

        if (nodeIntern != nullptr)
            nodeIntern->Delete();
    }
}


BrlCombinationTreeNode BrlCombinationTree
(
    BrlCombination combination
) {
    BrlCombinationTreeNode ret = nullptr;

    if (combination != nullptr) {
        Combination* comb = CastCombination(combination);

        assert(comb != nullptr);

        if (comb != nullptr)
            ret = new CombinationTreeNodeData(comb->Tree());
    }

    return ret;
}


void BrlCombinationAddLeaf
(
    BrlCombination combination,
    const char*    leafName
) {
    if (combination != nullptr) {
        Combination* comb = CastCombination(combination);

        assert(comb != nullptr);

        if (comb != nullptr)
            comb->AddLeaf(leafName);
    }
}


int BrlCombinationIsRegion
(
    BrlCombination combination
) {
    int ret = 0;

    if (combination != nullptr) {
        Combination* comb = CastCombination(combination);

        assert(comb != nullptr);

        if (comb != nullptr)
            ret = comb->IsRegion() ? 1 : 0;
    }

    return ret;
}


void BrlCombinationSetIsRegion
(
    BrlCombination combination,
    int            value
) {
    if (combination != nullptr) {
        Combination* comb = CastCombination(combination);

        assert(comb != nullptr);

        if (comb != nullptr)
            comb->SetIsRegion(value != 0);
    }
}


BrlCombinationFastgenType BrlCombinationFastgenRegion
(
    BrlCombination combination
) {
    BrlCombinationFastgenType ret = BrlCombinationFastgenTypeNon;

    if (combination != nullptr) {
        Combination* comb = CastCombination(combination);

        assert(comb != nullptr);

        if (comb != nullptr) {
            switch (comb->FastgenRegion()) {
            case Combination::FastgenType::Non:
                ret = BrlCombinationFastgenTypeNon;
                break;

            case Combination::FastgenType::Plate:
                ret = BrlCombinationFastgenTypePlate;
                break;

            case Combination::FastgenType::Volume:
                ret = BrlCombinationFastgenTypeVolume;
                break;

            default:
                bu_log("BrlCombinationFastgenRegion: invalid BRLCAD::Combination::FastgenType");
            }
        }
    }

    return ret;
}


void BrlCombinationSetFastgenRegion
(
    BrlCombination            combination,
    BrlCombinationFastgenType value
) {
    if (combination != nullptr) {
        Combination* comb = CastCombination(combination);

        assert(comb != nullptr);

        if (comb != nullptr) {
            switch (value) {
            case BrlCombinationFastgenTypeNon:
                comb->SetFastgenRegion(Combination::FastgenType::Non);
                break;

            case BrlCombinationFastgenTypePlate:
                comb->SetFastgenRegion(Combination::FastgenType::Plate);
                break;

            case BrlCombinationFastgenTypeVolume:
                comb->SetFastgenRegion(Combination::FastgenType::Volume);
                break;

            default:
                bu_log("BrlCombinationSetFastgenRegion: invalid BrlCombinationFastgenType");
            }
        }
    }
}


int BrlCombinationRegionId
(
    BrlCombination combination
) {
    int ret = 0;

    if (combination != nullptr) {
        Combination* comb = CastCombination(combination);

        assert(comb != nullptr);

        if (comb != nullptr)
            ret = comb->RegionId();
    }

    return ret;
}


void BrlCombinationSetRegionId
(
    BrlCombination combination,
    int            value
) {
    if (combination != nullptr) {
        Combination* comb = CastCombination(combination);

        assert(comb != nullptr);

        if (comb != nullptr)
            comb->SetRegionId(value);
    }
}


int BrlCombinationAircode
(
    BrlCombination combination
) {
    int ret = 0;

    if (combination != nullptr) {
        Combination* comb = CastCombination(combination);

        assert(comb != nullptr);

        if (comb != nullptr)
            ret = comb->Aircode();
    }

    return ret;
}


void BrlCombinationSetAircode
(
    BrlCombination combination,
    int            value
) {
    if (combination != nullptr) {
        Combination* comb = CastCombination(combination);

        assert(comb != nullptr);

        if (comb != nullptr)
            comb->SetAircode(value);
    }
}


int BrlCombinationGiftMaterial
(
    BrlCombination combination
) {
    int ret = 0;

    if (combination != nullptr) {
        Combination* comb = CastCombination(combination);

        assert(comb != nullptr);

        if (comb != nullptr)
            ret = comb->GiftMaterial();
    }

    return ret;
}


void BrlCombinationSetGiftMaterial
(
    BrlCombination combination,
    int            value
) {
    if (combination != nullptr) {
        Combination* comb = CastCombination(combination);

        assert(comb != nullptr);

        if (comb != nullptr)
            comb->SetGiftMaterial(value);
    }
}


int BrlCombinationLineOfSight
(
    BrlCombination combination
) {
    int ret = 0;

    if (combination != nullptr) {
        Combination* comb = CastCombination(combination);

        assert(comb != nullptr);

        if (comb != nullptr)
            ret = comb->LineOfSight();
    }

    return ret;
}


void BrlCombinationSetLineOfSight
(
    BrlCombination combination,
    int            value
) {
    if (combination != nullptr) {
        Combination* comb = CastCombination(combination);

        assert(comb != nullptr);

        if (comb != nullptr)
            comb->SetLineOfSight(value);
    }
}


int BrlCombinationHasColor
(
    BrlCombination combination
) {
    int ret = 0;

    if (combination != nullptr) {
        Combination* comb = CastCombination(combination);

        assert(comb != nullptr);

        if (comb != nullptr)
            ret = comb->HasColor() ? 1 : 0;
    }

    return ret;
}


void BrlCombinationSetHasColor
(
    BrlCombination combination,
    int            value
) {
    if (combination != nullptr) {
        Combination* comb = CastCombination(combination);

        assert(comb != nullptr);

        if (comb != nullptr)
            comb->SetHasColor(value != 0);
    }
}


double BrlCombinationRed
(
    BrlCombination combination
) {
    double ret = 0.;

    if (combination != nullptr) {
        Combination* comb = CastCombination(combination);

        assert(comb != nullptr);

        if (comb != nullptr)
            ret = comb->Red();
    }

    return ret;
}


void BrlCombinationSetRed
(
    BrlCombination combination,
    double         value
) {
    if (combination != nullptr) {
        Combination* comb = CastCombination(combination);

        assert(comb != nullptr);

        if (comb != nullptr)
            comb->SetRed(value);
    }
}


double BrlCombinationGreen
(
    BrlCombination combination
) {
    double ret = 0.;

    if (combination != nullptr) {
        Combination* comb = CastCombination(combination);

        assert(comb != nullptr);

        if (comb != nullptr)
            ret = comb->Green();
    }

    return ret;
}


void BrlCombinationSetGreen
(
    BrlCombination combination,
    double         value
) {
    if (combination != nullptr) {
        Combination* comb = CastCombination(combination);

        assert(comb != nullptr);

        if (comb != nullptr)
            comb->SetGreen(value);
    }
}


double BrlCombinationBlue
(
    BrlCombination combination
) {
    double ret = 0.;

    if (combination != nullptr) {
        Combination* comb = CastCombination(combination);

        assert(comb != nullptr);

        if (comb != nullptr)
            ret = comb->Blue();
    }

    return ret;
}


void BrlCombinationSetBlue
(
    BrlCombination combination,
    double         value
) {
    if (combination != nullptr) {
        Combination* comb = CastCombination(combination);

        assert(comb != nullptr);

        if (comb != nullptr)
            comb->SetBlue(value);
    }
}


const char* BrlCombinationShader
(
    BrlCombination combination
) {
    const char* ret = nullptr;

    if (combination != nullptr) {
        Combination* comb = CastCombination(combination);

        assert(comb != nullptr);

        if (comb != nullptr)
            ret = comb->Shader();
    }

    return ret;
}


void BrlCombinationSetShader
(
    BrlCombination combination,
    const char*    value
) {
    if (combination != nullptr) {
        Combination* comb = CastCombination(combination);

        assert(comb != nullptr);

        if (comb != nullptr)
            comb->SetShader(value);
    }
}


int BrlCombinationInherit
(
    BrlCombination combination
) {
    int ret = 0;

    if (combination != nullptr) {
        Combination* comb = CastCombination(combination);

        assert(comb != nullptr);

        if (comb != nullptr)
            ret = comb->Inherit() ? 1 : 0;
    }

    return ret;
}


void BrlCombinationSetInherit
(
    BrlCombination combination,
    int            value
) {
    if (combination != nullptr) {
        Combination* comb = CastCombination(combination);

        assert(comb != nullptr);

        if (comb != nullptr)
            comb->SetInherit(value != 0);
    }
}


const char* BrlCombinationMaterial
(
    BrlCombination combination
) {
    const char* ret = nullptr;

    if (combination != nullptr) {
        Combination* comb = CastCombination(combination);

        assert(comb != nullptr);

        if (comb != nullptr)
            ret = comb->Material();
    }

    return ret;
}


void BrlCombinationSetMaterial
(
    BrlCombination combination,
    const char*    value
) {
    if (combination != nullptr) {
        Combination* comb = CastCombination(combination);

        assert(comb != nullptr);

        if (comb != nullptr)
            comb->SetMaterial(value);
    }
}


double BrlCombinationTemperature
(
    BrlCombination combination
) {
    double ret = 0.;

    if (combination != nullptr) {
        Combination* comb = CastCombination(combination);

        assert(comb != nullptr);

        if (comb != nullptr)
            ret = comb->Temperature();
    }

    return ret;
}


void BrlCombinationSetTemperature
(
    BrlCombination combination,
    double         value
) {
    if (combination != nullptr) {
        Combination* comb = CastCombination(combination);

        assert(comb != nullptr);

        if (comb != nullptr)
            comb->SetTemperature(value);
    }
}


const char *BrlCombinationClassName(void) {
  return Combination::ClassName();
}
