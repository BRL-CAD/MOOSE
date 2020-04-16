/*                      O B J E C T . H
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
/** @file Object.h
 *
 *  BRL-CAD core C++ interface:
 *      database object declaration
 */

#ifndef BRLCAD_OBJECT_INCLUDED
#define BRLCAD_OBJECT_INCLUDED

#include <cstddef>


struct resource;
struct directory;
struct rt_db_internal;
struct db_i;
struct bu_attribute_value_set;


namespace BRLCAD {
    class BRLCAD_MOOSE_EXPORT Object {
    public:
        virtual ~Object(void);

        // works if both Objects are of the same derived class
        virtual const Object& operator=(const Object& original) = 0;

        // a virtual constructor which creates the right derived class
        // and the corresponding destructor
        // which keeps the memory management in a healthy state
        virtual Object*       Clone(void) const = 0;
        void                  Destroy(void);

        // these two functions can be used to determine the type of the object
        static const char*    ClassName(void);
        virtual const char*   Type(void) const                           = 0;

        // Is this object functional?
        virtual bool          IsValid(void) const                        = 0;

        // for all objects
        const char*           Name(void) const;
        void                  SetName(const char* name);


        class BRLCAD_MOOSE_EXPORT AttributeIterator {
        public:
            AttributeIterator(void) : m_avs(0), m_searchKey(0), m_index(-1) {}
            AttributeIterator(const AttributeIterator& original) : m_avs(original.m_avs),
                                                                   m_searchKey(original.m_searchKey),
                                                                   m_index(original.m_index) {}
            ~AttributeIterator(void) {}

            const AttributeIterator& operator=(const AttributeIterator& original) {
                m_avs       = original.m_avs;
                m_searchKey = original.m_searchKey;
                m_index     = original.m_index;
                return *this;
            }

            const AttributeIterator& operator++(void);
            bool                     Good(void) const;
            const char*              Key(void) const;
            const char*              Value(void) const;

        private:
            const bu_attribute_value_set* m_avs;
            const char*                   m_searchKey;
            size_t                        m_index;

            AttributeIterator(const bu_attribute_value_set* avs,
                              const char*                   searchKey,
                              size_t                        index);

            friend class Object;
        };


        bool                  HasAttribute(const char* key) const;
        AttributeIterator     FirstAttribute(void) const;            ///> returns an iterator pointing on the first attribute
        const char*           Attribute(const char* key) const;      ///> returns the value of the first attribute with this key
        AttributeIterator     MultiAttribute(const char* key) const; ///> returns an iterator pointing on the first attribute with this key
        void                  SetAttribute(const char* key,
                                           const char* value);       ///> overwrites the attribute entry with this key or creates a new one if there is none
        void                  AddMultiAttribute(const char* key,
                                                const char* value);  ///> creates an attribute entry with this values even if there exitsts already one with this key
        void                  RemoveAttribute(const char* key);      ///> removes the first attribute with this key
        void                  ClearAttributes(void);                 ///> removes all attributes


    protected:
        resource*       m_resp;
        directory*      m_pDir;
        rt_db_internal* m_ip;
        db_i*           m_dbip;

        Object(void);
        Object(resource*       resp,
               directory*      pDir,
               rt_db_internal* ip,
               db_i*           dbip);
        Object(const Object& original);

        void Copy(const Object& original);
        bool Validate(void) const;

    private:
        // holds Objects's name if not connected to a database
        char*                   m_name;
        bu_attribute_value_set* m_avs;

        const bu_attribute_value_set* GetAvs(void) const;
        bu_attribute_value_set*       GetAvs(bool create);

        friend class Database;
    };
}


#endif // BRLCAD_OBJECT_INCLUDED
