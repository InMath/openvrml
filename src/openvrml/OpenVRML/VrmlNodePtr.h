//
// OpenVRML
//
// Copyright (C) 2000  Braden McDaniel
// 
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// 
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
// 

# ifndef OPENVRML_NODEPTR_H
#   define OPENVRML_NODEPTR_H

#   include <assert.h>
#   include "common.h"

class VrmlNode;

#   ifdef OPENVRML_HAVE_SGI_HASH_MAP
#     include <hash_map>
template <>
    struct hash<VrmlNode *> {
        size_t operator()(VrmlNode * ptr) const {
            return reinterpret_cast<size_t>(ptr);
        }
    };

typedef hash_map<VrmlNode *, size_t> CountMap;
#   else
#     include <map>
typedef std::map<VrmlNode *, size_t> CountMap;
#   endif

class OPENVRML_SCOPE VrmlNodePtr {

    friend class VrmlNodeScript;

    CountMap::value_type * countPtr; // MSVC6 doesn't like std::map<>::pointer

public:
    explicit VrmlNodePtr(VrmlNode * node = 0);
    VrmlNodePtr(const VrmlNodePtr & nodePtr);
    ~VrmlNodePtr();

    operator bool() const;

    VrmlNodePtr & operator=(const VrmlNodePtr & nodePtr);

    bool operator==(const VrmlNodePtr & nodePtr) const;

    VrmlNode & operator*() const;
    VrmlNode * operator->() const;
    VrmlNode * get() const;

    void reset(VrmlNode * node = 0);
    void swap(VrmlNodePtr & nodePtr) throw ();

private:
    void dispose() throw ();
    void share(CountMap::value_type * countPtr) throw ();
};


inline VrmlNodePtr::~VrmlNodePtr() { this->dispose(); }

inline VrmlNodePtr::operator bool() const { return this->countPtr; }

inline VrmlNodePtr & VrmlNodePtr::operator=(const VrmlNodePtr & nodePtr) {
    this->share(nodePtr.countPtr);
    return *this;
}

inline VrmlNode & VrmlNodePtr::operator*() const {
    assert(this->countPtr);
    assert(this->countPtr->first);
    return *this->countPtr->first;
}

inline VrmlNode * VrmlNodePtr::operator->() const {
    assert(this->countPtr);
    assert(this->countPtr->first);
    return this->countPtr->first;
}

inline VrmlNode * VrmlNodePtr::get() const {
    return this->countPtr ? this->countPtr->first : 0;
}

inline void VrmlNodePtr::swap(VrmlNodePtr & nodePtr) throw () {
    std::swap(this->countPtr, nodePtr.countPtr);
}

inline bool VrmlNodePtr::operator==(const VrmlNodePtr & nodePtr) const {
    return (this->countPtr == nodePtr.countPtr);
}

# endif
