// -*- Mode: C++; indent-tabs-mode: nil; c-basic-offset: 4; fill-column: 78 -*-
//
// OpenVRML
//
// Copyright 2006, 2007, 2008, 2009  Braden McDaniel
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

# include "coordinate_interpolator2d.h"
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
     * @brief Represents CoordinateInterpolator2D node instances.
     */
    class OPENVRML_LOCAL coordinate_interpolator2d_node :
        public abstract_node<coordinate_interpolator2d_node>,
        public child_node {

        friend
        class openvrml_node_x3d_interpolation::coordinate_interpolator2d_metatype;

        class set_fraction_listener : public event_listener_base<self_t>,
                                      public sffloat_listener {
            public:
                explicit set_fraction_listener(self_t & node);
                virtual ~set_fraction_listener() OPENVRML_NOTHROW;

            private:
                virtual void do_process_event(const sffloat & fraction,
                                              double timestamp)
                    OPENVRML_THROW1(std::bad_alloc);
        };

        set_fraction_listener set_fraction_listener_;
        exposedfield<mffloat> key_;
        exposedfield<mfvec2f> key_value_;
        mfvec2f value_changed_;
        mfvec2f_emitter value_changed_emitter_;

    public:
        coordinate_interpolator2d_node(const node_type & type,
                           const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~coordinate_interpolator2d_node() OPENVRML_NOTHROW;
    };


    /**
     * @var coordinate_interpolator2d_node::coordinate_interpolator2d_metatype
     *
     * @brief Class object for CoordinateInterpolator2D nodes.
     */

    /**
     * @var coordinate_interpolator2d_node::set_fraction_listener coordinate_interpolator2d_node::set_fraction_listener_
     *
     * @brief set_fraction eventIn listener.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<coordinate_interpolator2d_node>::exposedfield<mffloat> coordinate_interpolator2d_node::key_
     *
     * @brief key exposedField
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<coordinate_interpolator2d_node>::exposedfield<mfvec2f> coordinate_interpolator2d_node::key_value_
     *
     * @brief key_value exposedField
     */

    /**
     * @var openvrml::mfvec2f coordinate_interpolator2d_node::value_changed_
     *
     * @brief value_changed eventOut
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<coordinate_interpolator2d_node>::mfvec2f_emitter coordinate_interpolator2d_node::value_changed_emitter_
     *
     * @brief value_changed eventOut emitter.
     */

    coordinate_interpolator2d_node::set_fraction_listener::
    set_fraction_listener(self_t & node):
        node_event_listener(node),
        event_listener_base<self_t>(node),
        sffloat_listener(node)
    {}

    coordinate_interpolator2d_node::set_fraction_listener::
    ~set_fraction_listener() OPENVRML_NOTHROW
    {}

    void coordinate_interpolator2d_node::set_fraction_listener::
    do_process_event(const sffloat & /* fraction */, const double /* timestamp */)
        OPENVRML_THROW1(std::bad_alloc)
    {
        //TODO: add logic here
    }


    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with this node.
     * @param scope     the scope to which the node belongs.
     */
    coordinate_interpolator2d_node::
    coordinate_interpolator2d_node(
        const node_type & type,
        const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        abstract_node<self_t>(type, scope),
        child_node(type, scope),
        set_fraction_listener_(*this),
        key_(*this),
        key_value_(*this),
        value_changed_emitter_(*this, this->value_changed_)
    {}

    /**
     * @brief Destroy.
     */
    coordinate_interpolator2d_node::~coordinate_interpolator2d_node()
        OPENVRML_NOTHROW
    {}
}


/**
 * @brief @c node_metatype identifier.
 */
const char * const
openvrml_node_x3d_interpolation::coordinate_interpolator2d_metatype::id =
    "urn:X-openvrml:node:CoordinateInterpolator2D";

/**
 * @brief Construct.
 *
 * @param browser the @c browser associated with this
 *                @c coordinate_interpolator2d_metatype.
 */
openvrml_node_x3d_interpolation::coordinate_interpolator2d_metatype::
coordinate_interpolator2d_metatype(openvrml::browser & browser):
    node_metatype(coordinate_interpolator2d_metatype::id, browser)
{}

/**
 * @brief Destroy.
 */
openvrml_node_x3d_interpolation::coordinate_interpolator2d_metatype::
~coordinate_interpolator2d_metatype()
    OPENVRML_NOTHROW
{}

# define COORDINATE_INTERPOLATOR2D_INTERFACE_SEQ                       \
    ((exposedfield, sfnode,  "metadata",      metadata))               \
    ((eventin,      sffloat, "set_fraction",  set_fraction_listener_)) \
    ((exposedfield, mffloat, "key",           key_))                   \
    ((exposedfield, mfvec2f, "keyValue",      key_value_))             \
    ((eventout,     mfvec2f, "value_changed", value_changed_emitter_))

OPENVRML_NODE_IMPL_UTIL_DEFINE_DO_CREATE_TYPE(
    openvrml_node_x3d_interpolation,
    coordinate_interpolator2d_metatype,
    coordinate_interpolator2d_node,
    COORDINATE_INTERPOLATOR2D_INTERFACE_SEQ)
