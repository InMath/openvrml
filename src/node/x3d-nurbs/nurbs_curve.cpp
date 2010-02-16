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

# include "nurbs_curve.h"
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
     * @brief Represents NurbsCurve node instances.
     */
    class OPENVRML_LOCAL nurbs_curve_node :
        public abstract_node<nurbs_curve_node>,
        public geometry_node,
        public child_node {

        friend class openvrml_node_x3d_nurbs::nurbs_curve_metatype;

        exposedfield<sfnode> control_point_;
        exposedfield<sfint32> tessellation_;
        exposedfield<mfdouble> weight_;
        sfbool closed_;
        mfdouble knot_;
        sfint32 order_;

    public:
        nurbs_curve_node(const node_type & type,
                         const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~nurbs_curve_node() OPENVRML_NOTHROW;

    private:
        virtual bool do_modified() const
            OPENVRML_THROW1(boost::thread_resource_error);

        virtual void do_render_geometry(openvrml::viewer & viewer,
                                        rendering_context context);
    };


    /**
     * @var nurbs_curve_node::nurbs_curve_metatype
     *
     * @brief Class object for NurbsCurve nodes.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<nurbs_curve_node>::exposedfield<openvrml::sfnode> nurbs_curve_node::control_point_
     *
     * @brief control_point exposedField
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<nurbs_curve_node>::exposedfield<openvrml::sfint32> nurbs_curve_node::tessellation_
     *
     * @brief tessellation exposedField
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<nurbs_curve_node>::exposedfield<openvrml::mfdouble> nurbs_curve_node::weight_
     *
     * @brief weight exposedField
     */

    /**
     * @var openvrml::sfbool nurbs_curve_node::closed_
     *
     * @brief closed field
     */

    /**
     * @var openvrml::mfdouble nurbs_curve_node::knot_
     *
     * @brief knot field
     */

    /**
     * @var openvrml::sfint32 nurbs_curve_node::order_
     *
     * @brief order field
     */


    /**
     * @brief Insert this geometry into @p viewer's display list.
     *
     * @param viewer    a Viewer.
     * @param context   the rendering context.
     *
     * @todo Implement this!
     */
    void
    nurbs_curve_node::
    do_render_geometry(openvrml::viewer & /* viewer */,
                       const rendering_context /* context */)
    {}

    /**
     * @brief Determine whether the node has been modified.
     *
     * @return @c true if the node or one of its children has been modified,
     *      @c false otherwise.
     */
    bool nurbs_curve_node::do_modified() const
        OPENVRML_THROW1(boost::thread_resource_error)
    {
        return this->control_point_.value()
            && this->control_point_.value()->modified();
    }

    /**
     * @brief Construct.
     *
     * @param type  the @c node_type associated with this node.
     * @param scope the @c scope to which the node belongs.
     */
    nurbs_curve_node::
    nurbs_curve_node(const node_type & type,
                     const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        abstract_node<self_t>(type, scope),
        geometry_node(type, scope),
        child_node(type, scope),
        control_point_(*this),
        tessellation_(*this),
        weight_(*this),
        order_(3)
    {}

    /**
     * @brief Destroy.
     */
    nurbs_curve_node::~nurbs_curve_node() OPENVRML_NOTHROW
    {}
}


/**
 * @brief @c node_metatype identifier.
 */
const char * const openvrml_node_x3d_nurbs::nurbs_curve_metatype::id =
    "urn:X-openvrml:node:NurbsCurve";

/**
 * @brief Construct.
 *
 * @param browser the @c browser associated with this @c nurbs_curve_metatype.
 */
openvrml_node_x3d_nurbs::nurbs_curve_metatype::
nurbs_curve_metatype(openvrml::browser & browser):
    node_metatype(nurbs_curve_metatype::id, browser)
{}

/**
 * @brief Destroy.
 */
openvrml_node_x3d_nurbs::nurbs_curve_metatype::~nurbs_curve_metatype()
    OPENVRML_NOTHROW
{}

/**
 * @brief Create a @c node_type.
 *
 * @param id            the name for the new @c node_type.
 * @param interfaces    the interfaces for the new @c node_type.
 *
 * @return a @c node_type capable of creating NurbsCurve nodes.
 *
 * @exception unsupported_interface if @p interfaces includes an interface
 *                                  not supported by @c nurbs_curve_metatype.
 * @exception std::bad_alloc        if memory allocation fails.
 */
const boost::shared_ptr<openvrml::node_type>
openvrml_node_x3d_nurbs::nurbs_curve_metatype::
do_create_type(const std::string & id,
               const node_interface_set & interfaces) const
    OPENVRML_THROW2(unsupported_interface, std::bad_alloc)
{
    typedef boost::array<node_interface, 7> supported_interfaces_t;
    static const supported_interfaces_t supported_interfaces = {
        node_interface(node_interface::exposedfield_id,
                       field_value::sfnode_id,
                       "metadata"),
        node_interface(node_interface::exposedfield_id,
                       field_value::sfnode_id,
                       "controlPoint"),
        node_interface(node_interface::exposedfield_id,
                       field_value::sfint32_id,
                       "tessellation"),
        node_interface(node_interface::exposedfield_id,
                       field_value::mfdouble_id,
                       "weight"),
        node_interface(node_interface::field_id,
                       field_value::sfbool_id,
                       "closed"),
        node_interface(node_interface::field_id,
                       field_value::mfdouble_id,
                       "knot"),
        node_interface(node_interface::field_id,
                       field_value::sfint32_id,
                       "order")
    };
    typedef node_type_impl<nurbs_curve_node> node_type_t;

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
                &nurbs_curve_node::metadata);
        } else if (*interface_ == *++supported_interface) {
            the_node_type.add_exposedfield(
                supported_interface->field_type,
                supported_interface->id,
                &nurbs_curve_node::control_point_);
        } else if (*interface_ == *++supported_interface) {
            the_node_type.add_exposedfield(
                supported_interface->field_type,
                supported_interface->id,
                &nurbs_curve_node::tessellation_);
        } else if (*interface_ == *++supported_interface) {
            the_node_type.add_exposedfield(
                supported_interface->field_type,
                supported_interface->id,
                &nurbs_curve_node::weight_);
        } else if (*interface_ == *++supported_interface) {
            the_node_type.add_field(
                supported_interface->field_type,
                supported_interface->id,
                &nurbs_curve_node::closed_);
        } else if (*interface_ == *++supported_interface) {
            the_node_type.add_field(
                supported_interface->field_type,
                supported_interface->id,
                &nurbs_curve_node::knot_);
        } else if (*interface_ == *++supported_interface) {
            the_node_type.add_field(
                supported_interface->field_type,
                supported_interface->id,
                &nurbs_curve_node::order_);
        } else {
            throw unsupported_interface(*interface_);
        }
    }
    return type;
}
