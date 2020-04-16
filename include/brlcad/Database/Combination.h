/*                      C O M B I N A T I O N . H
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
/** @file Combination.h
 *
 *  BRL-CAD core C++ interface:
 *      combination (ID_COMBINATION) database object declaration
 */

#ifndef BRLCAD_COMBINATION_INCLUDED
#define BRLCAD_COMBINATION_INCLUDED

#include <brlcad/Database/Object.h>


struct rt_comb_internal;
union tree;


namespace BRLCAD {
    class BRLCAD_MOOSE_EXPORT Combination : public Object {
    public:
        Combination(void);
        Combination(const Combination& original);
        virtual ~Combination(void);

        const Combination&    operator=(const Combination& original);

        class TreeNode; // part 1/2 of a work-around a bug in i686-apple-darwin9-gcc-4.0.1 (GCC) 4.0.1 (Apple Inc. build 5465)

        class BRLCAD_MOOSE_EXPORT ConstTreeNode {
        public:
            enum Operator {
                Null,         ///< the empty tree of an empty combination, may signal an error too e.g. if an operand of a leaf was requested
                Union,        ///< a binary operation, the set theoretic union set of the two operands
                Intersection, ///< a binary operation, the set theoretic intersection set of the two operands
                Subtraction,  ///< a binary operation, the set theoretic complement or difference set of the two operands
                ExclusiveOr,  ///< a binary operation, the set theoretic symmetric difference set of the two operands
                Not,          ///< a unary operation, the complement with the whole space
                Leaf          ///< actually an operand
            };

            ConstTreeNode(void) : m_tree(0) {}
            ConstTreeNode(const ConstTreeNode& original) : m_tree(original.m_tree) {}
            virtual ~ConstTreeNode(void) {}

            const ConstTreeNode& operator=(const ConstTreeNode& original) {
                m_tree = original.m_tree;
                return *this;
            }

            Operator             Operation(void) const;
            ConstTreeNode        LeftOperand(void) const;  ///< the left operand of a binary operation
            ConstTreeNode        RightOperand(void) const; ///< the right operand of a binary operation
            ConstTreeNode        Operand(void) const;      ///< the operand of a unary operation
            const char*          Name(void) const;         ///< the name of the operand object in a leaf
            const double*        Matrix(void) const;       ///< the transformation matrix of the operand object in a leaf

                                 operator void*(void) {            ///< to test if the node is NULL
                return m_tree;
            }

        protected:
            tree* m_tree;

            ConstTreeNode(tree* original) : m_tree(original) {}

            friend class TreeNode; // part 2/2 of a work-around a bug in i686-apple-darwin9-gcc-4.0.1 (GCC) 4.0.1 (Apple Inc. build 5465)
            friend class Combination;
        };


        class BRLCAD_MOOSE_EXPORT TreeNode : public ConstTreeNode {
        public:
            TreeNode(void) : ConstTreeNode(), m_internalp(0), m_resp(0) {}
            TreeNode(const TreeNode& original) : ConstTreeNode(original),
                                                         m_internalp(original.m_internalp),
                                                         m_resp(original.m_resp) {}
            virtual ~TreeNode(void) {}

            const TreeNode& operator=(const TreeNode& original) {
                ConstTreeNode::operator=(original);

                m_internalp = original.m_internalp;
                m_resp      = original.m_resp;

                return *this;
            }

            TreeNode        LeftOperand(void);                 ///< the left operand of a binary operation
            TreeNode        RightOperand(void);                ///< the right operand of a binary operation
            TreeNode        Operand(void);                     ///< the operand of a unary operation
            void            SetName(const char* value) const;  ///< sets the name of the operand object in a leaf
            void            SetMatrix(double value[16]) const; ///< sets the transformation matrix of the operand object in a leaf

            /// applies an operator to this node
            /** - it creates a new node
                - the operator has to be unary, i.e. \a Not
                - \return the new created operation node
            */
            TreeNode        Apply(Operator op);

            /// creates a new node with "this op theOther"
            /** - the operator has to be binary
                - this node becomes a child of the new created one
                - \return the new created operation node
            */
            TreeNode        Apply(Operator             op,
                                  const ConstTreeNode& theOther);

            /// "this op leaf(\a leafName)"
            /** - creates two nodes
                  - a leaf node using \a leafName
                  - a operation node
                - the operator has to be binary
                - this node becomes a child of the new created operation node
                - \return the new created operation node
            */
            TreeNode        Apply(Operator    op,
                                  const char* leafName);

            /// creates a new node with "theOther op this"
            /** - the operator has to be binary
                - this node becomes a child of the new created one
                - \return the new created operation node
            */
            TreeNode        Apply(const ConstTreeNode& theOther,
                                  Operator             op);

            /// "this op leaf(\a leafName)"
            /** - creates two nodes
                  - a leaf node using \a leafName
                  - a operation node
                - the operator has to be binary
                - this node becomes a child of the new created operation node
                - \return the new created operation node
            */
            TreeNode        Apply(const char* leafName,
                                  Operator    op);

            /// deletes this node and rewinds all parint nodes until a valid state is reached
            /** E.g. if this node is an operand of a binary operation, this operation will be removed too
                and the other operand of this binary operation becomes the new child node of the former binary operations parent node.

                This node becomes invalid (operator \a Null) during this procedure.
            */
            void            Delete(void);

        private:
            rt_comb_internal* m_internalp;
            resource*         m_resp;

            TreeNode(tree*             original,
                     rt_comb_internal* internalp,
                     resource*         resp) : ConstTreeNode(original), m_internalp(internalp), m_resp(resp) {}

            friend class Combination;
        };


        ConstTreeNode         Tree(void) const;
        TreeNode              Tree(void);

        /// adds a leaf to the tree
        /** If the tree's root node is not \a Null \a Tree().Apply(Union, leafName) will be performed */
        void                  AddLeaf(const char* leafName);

        bool                  IsRegion(void) const;
        void                  SetIsRegion(bool value);

        enum FastgenType {
            Non,   ///< not a Fastgen region
            Plate,
            Volume
        };

        FastgenType           FastgenRegion(void) const;
        void                  SetFastgenRegion(FastgenType value);
        int                   RegionId(void) const;
        void                  SetRegionId(int value);
        int                   Aircode(void) const;
        void                  SetAircode(int value);
        int                   GiftMaterial(void) const;
        void                  SetGiftMaterial(int value);
        int                   LineOfSight(void) const;
        void                  SetLineOfSight(int value);
        bool                  HasColor(void) const;
        void                  SetHasColor(bool value);
        double                Red(void) const;
        void                  SetRed(double value);
        double                Green(void) const;
        void                  SetGreen(double value);
        double                Blue(void) const;
        void                  SetBlue(double value);
        const char*           Shader(void) const;
        void                  SetShader(const char* value);
        bool                  Inherit(void) const; ///< override lower nodes color and shader
        void                  SetInherit(bool value);
        const char*           Material(void) const;
        void                  SetMaterial(const char* value);
        double                Temperature(void) const;
        void                  SetTemperature(double value);

        // inherited from BRLCAD::Object
        virtual const Object& operator=(const Object& original);
        virtual Object*       Clone(void) const;
        static const char*    ClassName(void);
        virtual const char*   Type(void) const;
        virtual bool          IsValid(void) const;

    protected:
        Combination(resource*       resp,
                    directory*      pDir,
                    rt_db_internal* ip,
                    db_i*           dbip = 0);

        friend class ConstDatabase;

    private:
        // holds Objects's content if not connected to a database
        rt_comb_internal* m_internalp;

        const rt_comb_internal*   Internal(void) const;
        virtual rt_comb_internal* Internal(void);

        friend class Database;
    };
}


#endif // BRLCAD_COMBINATION_INCLUDED
