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

#include <brlcad/Database/Combination.h>

#include <brlcad/C/combination.h>

#include "casts.h"


using namespace BRLCAD;


static Combination::TreeNode::Operator ConvertOperator
(
    BrlTreeNodeOperator op
) {
    Combination::TreeNode::Operator ret = Combination::TreeNode::Operator::Null;

    switch (op) {
    case BrlOpNull:
        ret = Combination::TreeNode::Operator::Null;
        break;

    case BrlOpUnion:
        ret = Combination::TreeNode::Operator::Union;
        break;

    case BrlOpIntersection:
        ret = Combination::TreeNode::Operator::Intersection;
        break;

    case BrlOpSubtraction:
        ret = Combination::TreeNode::Operator::Subtraction;
        break;

    case BrlOpExclusiveOr:
        ret = Combination::TreeNode::Operator::ExclusiveOr;
        break;

    case BrlOpNot:
        ret = Combination::TreeNode::Operator::Not;
        break;

    case BrlOpLeaf:
        ret = Combination::TreeNode::Operator::Leaf;
        break;

    default:
        assert(0);
    }

    return ret;
}


static BrlTreeNodeOperator ConvertOperatorBack
(
    Combination::TreeNode::Operator op
) {
    BrlTreeNodeOperator ret = BrlOpNull;

    switch (op) {
    case Combination::TreeNode::Operator::Null:
        ret = BrlOpNull;
        break;

    case Combination::TreeNode::Operator::Union:
        ret = BrlOpUnion;
        break;

    case Combination::TreeNode::Operator::Intersection:
        ret = BrlOpIntersection;
        break;

    case Combination::TreeNode::Operator::Subtraction:
        ret = BrlOpSubtraction;
        break;

    case Combination::TreeNode::Operator::ExclusiveOr:
        ret = BrlOpExclusiveOr;
        break;

    case Combination::TreeNode::Operator::Not:
        ret = BrlOpNot;
        break;

    case Combination::TreeNode::Operator::Leaf:
        ret = BrlOpLeaf;
        break;

    default:
        assert(0);
    }

    return ret;
}


BrlCombination BrlNewCombination
(
    void
) {
    return new CombinationData(new Combination());
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


enum BrlCombinationFastgenType BrlCombinationFastgenRegion
(
    BrlCombination combination
) {
    enum BrlCombinationFastgenType ret = BrlCombinationFastgenTypeNon;

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
                assert(0);
            }
        }
    }

    return ret;
}


void BrlCombinationSetFastgenRegion
(
    BrlCombination combination,
    enum BrlCombinationFastgenType value
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
                assert(0);
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


BrlTreeNode BrlCombinationTree
(
    BrlCombination combination
) {
    BrlTreeNode ret = nullptr;

    if (combination != nullptr) {
        Combination* comb = CastCombination(combination);

        assert(comb != nullptr);

        if (comb != nullptr) {
            Combination::TreeNode it = comb->Tree();
            ret = new TreeNodeData(it);
        }
    }

    return ret;
}


void BrlTreeNodeSetMatrix
(
    BrlTreeNode  node,
    const double matrix[16]
) {
    if (node != nullptr) {
        Combination::TreeNode* nodeIntern = CastTreeNode(node);

        assert(nodeIntern != nullptr);

        if (nodeIntern != nullptr)
            nodeIntern->SetMatrix(matrix);
    }
}


BrlTreeNode BrlTreeNodeLeftOperand
(
    BrlTreeNode node
) {
    BrlTreeNode ret = nullptr;

    if (node != nullptr) {
        Combination::TreeNode* nodeIntern = CastTreeNode(node);

        assert(nodeIntern != nullptr);

        if (nodeIntern != nullptr) {
            Combination::TreeNode it = nodeIntern->LeftOperand();
            ret = new TreeNodeData(it);
        }
    }

    return ret;
}


BrlTreeNode BrlTreeNodeRightOperand
(
    BrlTreeNode node
) {
    BrlTreeNode ret = nullptr;

    if (node != nullptr) {
        Combination::TreeNode* nodeIntern = CastTreeNode(node);

        assert(nodeIntern != nullptr);

        if (nodeIntern != nullptr) {
            Combination::TreeNode it = nodeIntern->RightOperand();
            ret = new TreeNodeData(it);
        }
    }

    return ret;
}


BrlTreeNode BrlTreeNodeOperand
(
    BrlTreeNode node
) {
    BrlTreeNode ret = nullptr;

    if (node != nullptr) {
        Combination::TreeNode* nodeIntern = CastTreeNode(node);

        assert(nodeIntern != nullptr);

        if (nodeIntern != nullptr) {
            Combination::TreeNode it = nodeIntern->Operand();
            ret = new TreeNodeData(it);
        }
    }

    return ret;
}


BrlTreeNode BrlTreeNodeApply
(
    BrlTreeNode         node,
    BrlTreeNodeOperator op
) {
    BrlTreeNode ret = nullptr;

    if (node != nullptr) {
        Combination::TreeNode* nodeIntern = CastTreeNode(node);

        assert(nodeIntern != nullptr);

        if (nodeIntern != nullptr)
            ret = new TreeNodeData(nodeIntern->Apply(ConvertOperator(op)));
    }

    return ret;
}


BrlTreeNode BrlTreeNodeApplyWithOther
(
    BrlTreeNode         node,
    BrlTreeNodeOperator op,
    BrlTreeNode         other
) {
    BrlTreeNode ret = nullptr;

    if ((node != nullptr) && (other != nullptr)) {
        Combination::TreeNode* nodeIntern = CastTreeNode(node);
        Combination::TreeNode* otherIntern = CastTreeNode(other);

        assert(nodeIntern != nullptr);
        assert(otherIntern != nullptr);

        if ((nodeIntern != nullptr) && (otherIntern != nullptr))
            ret = new TreeNodeData(nodeIntern->Apply(ConvertOperator(op), *otherIntern));
    }

    return ret;
}


BrlTreeNode BrlTreeNodeApplyWithLeaf
(
    BrlTreeNode         node,
    BrlTreeNodeOperator op,
    const char*         leafName
) {
    BrlTreeNode ret = nullptr;

    if ((node != nullptr) && (leafName != nullptr)) {
        Combination::TreeNode* nodeIntern = CastTreeNode(node);

        assert(nodeIntern != nullptr);

        if (nodeIntern != nullptr)
            ret = new TreeNodeData(nodeIntern->Apply(ConvertOperator(op), leafName));
    }

    return ret;
}


BrlTreeNode BrlTreeNodeApplyOtherWith
(
    BrlTreeNode         other,
    BrlTreeNodeOperator op,
    BrlTreeNode         node
) {
    BrlTreeNode ret = nullptr;

    if ((other != nullptr) && (node != nullptr)) {
        Combination::TreeNode* nodeIntern = CastTreeNode(node);
        Combination::TreeNode* otherIntern = CastTreeNode(other);

        assert(nodeIntern != nullptr);
        assert(otherIntern != nullptr);

        if ((nodeIntern != nullptr) && (otherIntern != nullptr))
            ret = new TreeNodeData(nodeIntern->Apply(*otherIntern, ConvertOperator(op)));
    }

    return ret;
}


BrlTreeNode BrlTreeNodeApplyLeafWith
(
    const char*         leafName,
    BrlTreeNodeOperator op,
    BrlTreeNode         node
) {
    BrlTreeNode ret = nullptr;

    if ((leafName != nullptr) && (node != nullptr)) {
        Combination::TreeNode* nodeIntern = CastTreeNode(node);

        assert(nodeIntern != nullptr);

        if (nodeIntern != nullptr)
            ret = new TreeNodeData(nodeIntern->Apply(leafName, ConvertOperator(op)));
    }

    return ret;
}


const char *BrlCombinationClassName
(
    void
) {
  return Combination::ClassName();
}
