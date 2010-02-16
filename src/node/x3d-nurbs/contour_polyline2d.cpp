// -*- mode: c++; indent-tabs-mode: nil; c-basic-offset: 4; fill-column: 78 -*-
//
// OpenVRML
//
// Copyright 2006, 2007, 2008  Braden McDaniel
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation; either version 3 of the License, or (at your
// option) any later version.
//
// This library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, see <http://www.gnu.org/licenses/>.
//

# include "contour_polyline2d.h"
# include <openvrml/node_impl_util.h>
# include <boost/array.hpp>

# ifdef HAVE_CONFIG_H
#   include <config.h>
# endif

using namespace openvrml;
using namespace openvrml::node_impl_util;
using namespace std;

namespace {

    /**
     * @brief Represents ContourPolyline2D node instances.
     */
    class OPENVRML_LOCAL contour_polyline2d_node :
        public abstract_node<contour_polyline2d_node> {

        friend class openvrml_node_x3d_nurbs::contour_polyline2d_metatype;

        exposedfield<mfvec2f> point_;

    public:
        contour_polyline2d_node(
            const node_type & type,
            const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~contour_polyline2d_node() OPENVRML_NOTHROW;
    };


    /**
     * @var contour_polyline2d_node::contour_polyline2d_metatype
     *
     * @brief Class object for ContourPolyline2D nodes.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<contour_polyline2d_node>::exposedfield<openvrml::mfvec2f> contour_polyline2d_node::point_
     *
     * @brief point exposedField
     */


    /**
     * @brief Construct.
     *
     * @param type  the @c node_type associated with this node.
     * @param scope the @c scope to which the node belongs.
     */
    contour_polyline2d_node::
    contour_polyline2d_node(const node_type & type,
                            const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        abstract_node<self_t>(type, scope),
        point_(*this)
    {}

    /**
     * @brief Destroy.
     */
    contour_polyline2d_node::~contour_polyline2d_node() OPENVRML_NOTHROW
    {}
}


/**
 * @brief @c node_metatype identifier.
 */
const char * const openvrml_node_x3d_nurbs::contour_polyline2d_metatype::id =
    "urn:X-openvrml:node:ContourPolyline2D";

/**
 * @brief Construct.
 *
 * @param browser the @c browser associated with this
 *                @c contour_polyline2d_metatype.
 */
openvrml_node_x3d_nurbs::contour_polyline2d_metatype::
contour_polyline2d_metatype(openvrml::browser & browser):
    node_metatype(contour_polyline2d_metatype::id, browser)
{}

/**
 * @brief Destroy.
 */
openvrml_node_x3d_nurbs::contour_polyline2d_metatype::
~contour_polyline2d_metatype()
    OPENVRML_NOTHROW
{}

/**
 * @brief Create a @c node_type.
 *
 * @param id            the name for the new @c node_type.
 * @param interfaces    the interfaces for the new @c node_type.
 *
 * @return a @c node_type capable of creating ContourPolyline2D nodes.
 *
 * @exception unsupported_interface if @p interfaces includes an interface
 *                                  not supported by
 *                                  @c contour_polyline2d_metatype.
 * @exception std::bad_alloc        if memory allocation fails.
 */
const boost::shared_ptr<openvrml::node_type>
openvrml_node_x3d_nurbs::contour_polyline2d_metatype::
do_create_type(const std::string & id,
               const node_interface_set & interfaces) const
    OPENVRML_THROW2(unsupported_interface, std::bad_alloc)
{
    typedef boost::array<node_interface, 3> supported_interfaces_t;
    static const supported_interfaces_t supported_interfaces = {
        node_interface(node_interface::exposedfield_id,
                       field_value::sfnode_id,
                       "metadata"),
        //this is wrong in the spec, so we must support both aliases
        node_interface(node_interface::exposedfield_id,
                       field_value::mfvec2f_id,
                       "point"),
        node_interface(node_interface::exposedfield_id,
                       field_value::mfvec2f_id,
                       "controlPoint")
    };
    typedef node_type_impl<contour_polyline2d_node> node_type_t;

    const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
    node_type_t & the_node_type = static_cast<node_type_t &>(*type);

    for (node_interface_set::const_iterator interface_(interfaces.begin());
         interface_ != interfaces.end();
         ++interface_) {
        supported_interfaces_t::const_iterator supported_interface =
            supported_interfaces.begin() - 1;
        if (*interface_ == *++supported_interface) {
            the_node_type.add_exposedfield(
                supported_interface->field_type,
                supported_interface->id,
                &contour_polyline2d_node::metadata);
        } else if (*interface_ == *++supported_interface ||
                   *interface_ == *++supported_interface) {
            the_node_type.add_exposedfield(
                supported_interface->field_type,
                supported_interface->id,
                &contour_polyline2d_node::point_);
        } else {
            throw unsupported_interface(*interface_);
        }
    }
    return type;
}
