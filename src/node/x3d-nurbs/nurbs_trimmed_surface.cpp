// -*- mode: c++; indent-tabs-mode: nil; c-basic-offset: 4; fill-column: 78 -*-
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

# include "nurbs_trimmed_surface.h"
# include <openvrml/node_impl_util.h>
# include <boost/array.hpp>

# ifdef HAVE_CONFIG_H
#   include <config.h>
# endif

using namespace openvrml;
using namespace openvrml::node_impl_util;
using namespace std;

namespace {

    class OPENVRML_LOCAL nurbs_trimmed_surface_node :
        public abstract_node<nurbs_trimmed_surface_node>,
        public geometry_node,
        public child_node {

        friend class openvrml_node_x3d_nurbs::nurbs_trimmed_surface_metatype;

        class add_trimming_contour_listener :
            public event_listener_base<self_t>,
            public mfnode_listener {
        public:
            explicit add_trimming_contour_listener(self_t & node);
            virtual ~add_trimming_contour_listener() OPENVRML_NOTHROW;

        private:
            virtual void do_process_event(const mfnode & fraction,
                                          double timestamp)
                OPENVRML_THROW1(std::bad_alloc);
        };

        class remove_trimming_contour_listener :
            public event_listener_base<self_t>,
            public mfnode_listener {
        public:
            explicit remove_trimming_contour_listener(self_t & node);
            virtual ~remove_trimming_contour_listener() OPENVRML_NOTHROW;

        private:
            virtual void do_process_event(const mfnode & fraction,
                                          double timestamp)
                OPENVRML_THROW1(std::bad_alloc);
        };

        add_trimming_contour_listener add_trimming_contour_listener_;
        remove_trimming_contour_listener remove_trimming_contour_listener_;
        exposedfield<sfnode> control_point_;
        exposedfield<sfnode> tex_coord_;
        exposedfield<mfnode> trimming_contour_;
        exposedfield<sfint32> u_tessellation_;
        exposedfield<sfint32> v_tessellation_;
        exposedfield<mfdouble> weight_;
        sfbool solid_;
        sfbool u_closed_;
        sfint32 u_dimension_;
        mfdouble u_knot_;
        sfint32 u_order_;
        sfbool v_closed_;
        sfint32 v_dimension_;
        mfdouble v_knot_;
        sfint32 v_order_;

    public:
        nurbs_trimmed_surface_node(
            const node_type & type,
            const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~nurbs_trimmed_surface_node() OPENVRML_NOTHROW;

    private:
        virtual bool do_modified() const
            OPENVRML_THROW1(boost::thread_resource_error);

        virtual void do_render_geometry(openvrml::viewer & viewer,
                                        rendering_context context);
    };


    /**
     * @class nurbs_trimmed_surface_node
     *
     * @brief Represents NurbsTrimmedSurface node instances.
     */

    /**
     * @var nurbs_trimmed_surface_node::nurbs_trimmed_surface_metatype
     *
     * @brief Class object for NurbsTrimmedSurface nodes.
     */

    /**
     * @var nurbs_trimmed_surface_node::add_trimming_contour_
     *
     * @brief add_trimming_contour eventIn
     */

    /**
     * @var nurbs_trimmed_surface_node::remove_trimming_contour_
     *
     * @brief remove_trimming_contour eventIn
     */

    /**
     * @var nurbs_trimmed_surface_node::control_point_
     *
     * @brief control_point exposedField
     */

    /**
     * @var nurbs_trimmed_surface_node::tex_coord_
     *
     * @brief tex_coord exposedField
     */

    /**
     * @var nurbs_trimmed_surface_node::trimming_contour_
     *
     * @brief trimming_contour exposedField
     */

    /**
     * @var nurbs_trimmed_surface_node::u_tessellation_
     *
     * @brief u_tessellation exposedField
     */

    /**
     * @var nurbs_trimmed_surface_node::v_tessellation_
     *
     * @brief v_tessellation exposedField
     */

    /**
     * @var nurbs_trimmed_surface_node::weight_
     *
     * @brief weight exposedField
     */

    /**
     * @var nurbs_trimmed_surface_node::solid_
     *
     * @brief solid field
     */

    /**
     * @var nurbs_trimmed_surface_node::u_closed_
     *
     * @brief u_closed field
     */

    /**
     * @var nurbs_trimmed_surface_node::u_dimension_
     *
     * @brief u_dimension field
     */

    /**
     * @var nurbs_trimmed_surface_node::u_knot_
     *
     * @brief u_knot field
     */

    /**
     * @var nurbs_trimmed_surface_node::u_order_
     *
     * @brief u_order field
     */

    /**
     * @var nurbs_trimmed_surface_node::v_closed_
     *
     * @brief v_closed field
     */

    /**
     * @var nurbs_trimmed_surface_node::v_dimension_
     *
     * @brief v_dimension field
     */

    /**
     * @var nurbs_trimmed_surface_node::v_knot_
     *
     * @brief v_knot field
     */

    /**
     * @var nurbs_trimmed_surface_node::v_order_
     *
     * @brief v_order field
     */

    nurbs_trimmed_surface_node::add_trimming_contour_listener::
    add_trimming_contour_listener(self_t & node):
        node_event_listener(node),
        event_listener_base<self_t>(node),
        mfnode_listener(node)
    {}

    nurbs_trimmed_surface_node::add_trimming_contour_listener::
    ~add_trimming_contour_listener() OPENVRML_NOTHROW
    {}

    void nurbs_trimmed_surface_node::add_trimming_contour_listener::
    do_process_event(const mfnode & /* fraction */, const double /* timestamp */)
        OPENVRML_THROW1(std::bad_alloc)
    {
        //TODO: add logic here
    }

    nurbs_trimmed_surface_node::remove_trimming_contour_listener::
    remove_trimming_contour_listener(self_t & node):
        node_event_listener(node),
        event_listener_base<self_t>(node),
        mfnode_listener(node)
    {}

    nurbs_trimmed_surface_node::remove_trimming_contour_listener::
    ~remove_trimming_contour_listener() OPENVRML_NOTHROW
    {}

    void nurbs_trimmed_surface_node::remove_trimming_contour_listener::
    do_process_event(const mfnode & /* fraction */, const double /* timestamp */)
        OPENVRML_THROW1(std::bad_alloc)
    {
        //TODO: add logic here
    }


    /**
     * @brief Insert this geometry into @p viewer's display list.
     *
     * @param viewer    a Viewer.
     * @param context   the rendering context.
     *
     * @todo Implement this!
     */
    void
    nurbs_trimmed_surface_node::
    do_render_geometry(openvrml::viewer & /* viewer */,
                       const rendering_context /* context */)
    {}

    /**
     * @brief Determine whether the node has been modified.
     *
     * @return @c true if the node or one of its children has been modified,
     *      @c false otherwise.
     */
    bool nurbs_trimmed_surface_node::do_modified() const
        OPENVRML_THROW1(boost::thread_resource_error)
    {
        if ((this->control_point_.value()
             && this->control_point_.value()->modified())
            || (this->tex_coord_.value()
                && this->tex_coord_.value()->modified()))
        {
            return true;
        }

        for (size_t i = 0; i < this->trimming_contour_.value().size(); ++i) {
            if (this->trimming_contour_.value()[i]->modified()) { return true; }
        }

        return false;
    }

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with this node.
     * @param scope     the scope to which the node belongs.
     */
    nurbs_trimmed_surface_node::
    nurbs_trimmed_surface_node(const node_type & type,
                               const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        abstract_node<self_t>(type, scope),
        geometry_node(type, scope),
        child_node(type, scope),
        add_trimming_contour_listener_(*this),
        remove_trimming_contour_listener_(*this),
        control_point_(*this),
        tex_coord_(*this),
        trimming_contour_(*this),
        u_tessellation_(*this),
        v_tessellation_(*this),
        weight_(*this),
        solid_(true),
        u_order_(3),
        v_order_(3)
    {}

    /**
     * @brief Destroy.
     */
    nurbs_trimmed_surface_node::~nurbs_trimmed_surface_node() OPENVRML_NOTHROW
    {}
}


/**
 * @brief @c node_metatype identifier.
 */
const char * const openvrml_node_x3d_nurbs::nurbs_trimmed_surface_metatype::id =
    "urn:X-openvrml:node:NurbsTrimmedSurface";

/**
 * @brief Construct.
 *
 * @param browser the @c browser associated with this
 *                @c nurbs_trimmed_surface_metatype.
 */
openvrml_node_x3d_nurbs::nurbs_trimmed_surface_metatype::
nurbs_trimmed_surface_metatype(openvrml::browser & browser):
    node_metatype(nurbs_trimmed_surface_metatype::id, browser)
{}

/**
 * @brief Destroy.
 */
openvrml_node_x3d_nurbs::nurbs_trimmed_surface_metatype::
~nurbs_trimmed_surface_metatype()
    OPENVRML_NOTHROW
{}

# define NURBS_TRIMMED_SURFACE_INTERFACE_SEQ \
    ((exposedfield, sfnode, "metadata", metadata)) \
    ((eventin,      mfnode, "addTrimmingContour", add_trimming_contour_listener_)) \
    ((eventin,      mfnode, "removeTrimmingContour", remove_trimming_contour_listener_)) \
    ((exposedfield, sfnode, "controlPoint",          control_point_)) \
    ((exposedfield, sfnode, "texCoord",              tex_coord_)) \
    ((exposedfield, mfnode, "trimmingContour",       trimming_contour_)) \
    ((exposedfield, sfint32, "uTessellation",         u_tessellation_)) \
    ((exposedfield, sfint32, "vTessellation",         v_tessellation_)) \
    ((exposedfield, mfdouble, "weight",               weight_)) \
    ((field,        sfbool,   "solid",                solid_)) \
    ((field,        sfbool,   "uClosed",              u_closed_)) \
    ((field,        sfint32,  "uDimension",           u_dimension_)) \
    ((field,        mfdouble, "uKnot",                u_knot_)) \
    ((field,        sfint32,  "uOrder",               u_order_)) \
    ((field,        sfbool,   "vClosed",              v_closed_)) \
    ((field,        sfint32,  "vDimension",           v_dimension_)) \
    ((field,        mfdouble, "vKnot",                v_knot_)) \
    ((field,        sfint32,  "vOrder",               v_order_))

OPENVRML_NODE_IMPL_UTIL_DEFINE_DO_CREATE_TYPE(
    openvrml_node_x3d_nurbs,
    nurbs_trimmed_surface_metatype,
    nurbs_trimmed_surface_node,
    NURBS_TRIMMED_SURFACE_INTERFACE_SEQ)
