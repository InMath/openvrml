// -*- Mode: C++; indent-tabs-mode: nil; c-basic-offset: 4; -*-
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

# include "field_value_ptr.h"
# include "field.h"

namespace OpenVRML {

/**
 * @class field_value_ptr
 *
 * @ingroup fieldvalues
 *
 * @brief A reference-counting smart pointer for
 *        @link field_value field_values@endlink.
 *
 * field_value_ptr is patterned after the <a
 * href="http://boost.org/libs/smart_ptr/shared_ptr.htm">Boost shared_ptr</a>,
 * and it works basically the same way. A field_value_ptr should be constructed
 * or reset with a field_value created with @c new (or 0).
 *
 * @see http://boost.org/libs/smart_ptr/shared_ptr.htm
 */

/**
 * @var field_value * field_value_ptr::value
 *
 * @brief A pointer to a field_value.
 */

/**
 * @var size_t * field_value_ptr::count
 *
 * @brief A pointer to the reference count.
 */

/**
 * @brief Construct.
 *
 * @param value a pointer to a field_value constructed with @c new.
 *
 * @exception std::bad_alloc    if memory allocation fails.
 */
field_value_ptr::field_value_ptr(field_value * const value)
    throw (std::bad_alloc):
    value(value)
{
    try {
        this->count = new size_t(1); // prevent leak if new throws
    } catch (std::bad_alloc & ex) {
        delete value;
        throw;
    }
}

/**
 * @brief Construct a copy.
 *
 * @param ptr the field_value_ptr to copy.
 */
field_value_ptr::field_value_ptr(const field_value_ptr & ptr) throw ():
    value(ptr.value)
{
    ++*(this->count = ptr.count); // never throws
}

/**
 * @fn field_value_ptr::~field_value_ptr() throw ()
 *
 * @brief Destroy.
 *
 * Decrement the reference count.  If the reference count drops to zero, the
 * field_value will be destroyed.
 */

/**
 * @fn field_value_ptr::operator bool() const throw ()
 *
 * @brief Automatically convert to bool.
 */

/**
 * @brief Assignment operator.
 *
 * @param ptr
 *
 * @return a reference to the field_value_ptr.
 */
field_value_ptr & field_value_ptr::operator=(const field_value_ptr & ptr)
    throw ()
{
    if (this->count != ptr.count) {
        ++*ptr.count;
        this->dispose();
        this->value = ptr.value;
        this->count = ptr.count;
    }
    return *this;
}

/**
 * @fn field_value & field_value_ptr::operator*() const throw ()
 *
 * @brief Dereference.
 *
 * @return a reference to the field_value.
 */

/**
 * @fn field_value * field_value_ptr::operator->() const throw ()
 *
 * @brief Delegate to the field_value.
 *
 * @return a pointer to the field_value.
 */

/**
 * @fn field_value * field_value_ptr::get() const throw ()
 *
 * @brief Get the field_value pointer.
 *
 * @return a pointer to the field_value.
 */

/**
 * @brief Reset the field_value_ptr to a new field_value.
 *
 * @param value a pointer to a field_value constructed with @c new.
 *
 * @exception std::bad_alloc    if memory allocation fails.
 */
void field_value_ptr::reset(field_value * const value) throw (std::bad_alloc)
{
    if (this->value == value) { return; }
    if (--*this->count == 0) {
        delete this->value;
    } else {
        try {
            this->count = new size_t;
        } catch (std::bad_alloc & ex) {
            ++*this->count;
            delete value;
            throw;
        }
    }
    *this->count = 1;
    this->value = value;
}

/**
 * @brief Decrement the reference count; destroy the field_value if the count
 *        drops to zero.
 */
void field_value_ptr::dispose() throw ()
{
    if (--*this->count == 0) {
        delete this->value;
        delete this->count;
    }
}

/**
 * @fn bool operator==(const field_value_ptr & lhs, const field_value_ptr & rhs) throw ()
 *
 * @brief Compare for equality.
 *
 * @return @c true if @p lhs and @p rhs point to the same field_value; @c false
 *         otherwise.
 */

/**
 * @fn bool operator!=(const field_value_ptr & lhs, const field_value_ptr & rhs) throw ()
 *
 * @relates field_value_ptr
 *
 * @brief Compare for inequality.
 *
 * @return @c true if @p lhs and @p rhs point to different field_values;
 *         @c false otherwise.
 */

} // namespace OpenVRML