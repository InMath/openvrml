// -*- Mode: C++; indent-tabs-mode: nil; c-basic-offset: 4; fill-column: 78 -*-
//
// OpenVRML
//
// Copyright 1998  Chris Morley
// Copyright 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2009  Braden McDaniel
// Copyright 2002  S. K. Bose
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

# ifdef HAVE_CONFIG_H
#   include <config.h>
# endif

# include <boost/array.hpp>
# include <openvrml/node_impl_util.h>
# include <private.h>
# include "plane_sensor.h"

namespace {

    class OPENVRML_LOCAL plane_sensor_node :
        public openvrml::node_impl_util::abstract_node<plane_sensor_node>,
        public openvrml::pointing_device_sensor_node {

        friend class openvrml_node_vrml97::plane_sensor_metatype;

        exposedfield<openvrml::sfbool> auto_offset_;
        exposedfield<openvrml::sfbool> enabled_;
        exposedfield<openvrml::sfvec2f> max_position_;
        exposedfield<openvrml::sfvec2f> min_position_;
        exposedfield<openvrml::sfvec3f> offset_;
        exposedfield<openvrml::sfstring> description_;
        openvrml::sfbool is_active_;
        sfbool_emitter is_active_emitter_;
        openvrml::sfvec3f track_point_changed_;
        sfvec3f_emitter track_point_changed_emitter_;
        openvrml::sfvec3f translation_changed_;
        sfvec3f_emitter translation_changed_emitter_;
        openvrml::sfbool is_over_;
        sfbool_emitter is_over_emitter_;

        openvrml::sfvec3f activationPoint;

        openvrml::mat4f activationMatrix;
        openvrml::mat4f modelview;

    public:
        plane_sensor_node(const openvrml::node_type & type,
                          const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~plane_sensor_node() OPENVRML_NOTHROW;

    private:
        virtual void do_render_child(openvrml::viewer & viewer,
                                     openvrml::rendering_context context);
        virtual void do_activate(double timestamp, bool over, bool active,
                                 const double (&point)[3]);
    };

    /**
     * @class plane_sensor_node
     *
     * The PlaneSensor node maps pointing device motion into two-dimensional
     * translation in a plane parallel to the <var>z</var>&nbsp;=&nbsp;0 plane
     * of the local coordinate system. The PlaneSensor node uses the descendent
     * geometry of its parent node to determine whether it is liable to
     * generate events.
     */

    /**
     * @var class plane_sensor_node::plane_sensor_metatype
     *
     * @brief Class object for PlaneSensor instances.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<plane_sensor_node>::exposedfield<openvrml::sfbool> plane_sensor_node::auto_offset_
     *
     * @brief autoOffset exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<plane_sensor_node>::exposedfield<openvrml::sfbool> plane_sensor_node::enabled_
     *
     * @brief enabled exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<plane_sensor_node>::exposedfield<openvrml::sfvec2f> plane_sensor_node::max_position_
     *
     * @brief maxPosition exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<plane_sensor_node>::exposedfield<openvrml::sfvec2f> plane_sensor_node::min_position_
     *
     * @brief minPosition exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<plane_sensor_node>::exposedfield<openvrml::sfvec3f> plane_sensor_node::offset_
     *
     * @brief offset exposedField.
     */

    /**
     * @var openvrml::sfbool plane_sensor_node::is_active_
     *
     * @brief isActive eventOut value.
     */

    /**
     * @var openvrml::sfbool_emitter plane_sensor_node::is_active_emitter_
     *
     * @brief isActive eventOut emitter.
     */

    /**
     * @var openvrml::sfvec3f plane_sensor_node::track_point_changed_
     *
     * @brief trackPoint_changed eventOut value.
     */

    /**
     * @var openvrml::sfvec3f_emitter plane_sensor_node::track_point_changed_emitter_
     *
     * @brief trackPoint_changed eventOut emitter.
     */

    /**
     * @var openvrml::sfvec3f plane_sensor_node::translation_changed_
     *
     * @brief translation_changed eventOut value.
     */

    /**
     * @var openvrml::sfvec3f_emitter plane_sensor_node::translation_changed_emitter_
     *
     * @brief translation_changed eventOut emitter.
     */

    /**
     * @var openvrml::sfvec3f plane_sensor_node::activationPoint
     *
     * @brief The point at which the PlaneSensor was activated.
     */

    /**
     * @var openvrml::mat4f plane_sensor_node::activationMatrix
     *
     * @brief Activation matrix.
     */

    /**
     * @var openvrml::mat4f plane_sensor_node::modelview
     *
     * @brief The modelview matrix.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node.
     * @param scope     the scope to which the node belongs.
     */
    plane_sensor_node::
    plane_sensor_node(const openvrml::node_type & type,
                      const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        child_node(type, scope),
        openvrml::node_impl_util::abstract_node<plane_sensor_node>(type, scope),
        pointing_device_sensor_node(type, scope),
        auto_offset_(*this, true),
        enabled_(*this, true),
        max_position_(*this, openvrml::make_vec2f(-1.0, -1.0)),
        min_position_(*this, openvrml::make_vec2f(0.0, 0.0)),
        offset_(*this, openvrml::make_vec3f(0.0, 0.0, 0.0)),
        description_(*this),
        is_active_(false),
        is_active_emitter_(*this, this->is_active_),
        track_point_changed_emitter_(*this, this->track_point_changed_),
        translation_changed_emitter_(*this, this->translation_changed_),
        is_over_emitter_(*this, this->is_over_),
        activationMatrix(openvrml::make_mat4f()),
        modelview(openvrml::make_mat4f())
    {
        this->node::modified(true);
    }

    /**
     * @brief Destroy.
     */
    plane_sensor_node::~plane_sensor_node() OPENVRML_NOTHROW
    {}

    /**
     * @brief Render the node.
     *
     * Render a frame if there is one available.
     *
     * @param viewer    a viewer.
     * @param context   a rendering context.
     */
    void
    plane_sensor_node::
    do_render_child(openvrml::viewer &, const openvrml::rendering_context context)
    {
        //
        // Store the ModelView matrix which is calculated at the time of rendering
        // in render-context. This matrix will be in use at the time of activation.
        //
        this->modelview = context.matrix();
    }

    /**
     * @brief Activate the plane sensor.
     *
     * @todo The local coords are computed for one instance; do we need to
     *       convert @p p to local coords for each instance (USE) of the
     *       sensor?
     *
     * @param timestamp the current time.
     * @param over      whether the pointer is over affected geometry.
     * @param active    whether the pointer is active; e.g., the mouse button
     *                  is depressed.
     * @param p         the point on the affected geometry "under" the pointer.
     */
    void
    plane_sensor_node::do_activate(const double timestamp,
                                   bool,
                                   const bool active,
                                   const double (&p)[3])
    {
        if (this->enabled_.sfbool::value()) {
            using openvrml::vec3f;
            using openvrml::make_vec3f;
            if (active && !this->is_active_.value()) {
                // Become active
                this->is_active_.value(active);

                vec3f V = make_vec3f(static_cast<float>(p[0]),
                                     static_cast<float>(p[1]),
                                     static_cast<float>(p[2]));
                this->activationMatrix = this->modelview.inverse();
                V *= this->activationMatrix;
                this->activationPoint.value(V);
                node::emit_event(this->is_active_emitter_, timestamp);
            } else if (!active && this->is_active_.value()) {
                // Become inactive
                this->is_active_.value(active);
                node::emit_event(this->is_active_emitter_, timestamp);

                // auto offset
                if (this->auto_offset_.sfbool::value()) {
                    this->offset_.sfvec3f::value(
                        this->translation_changed_.value());
                    node::emit_event(this->offset_, timestamp);
                }
            } else if (active) {
                using openvrml::vec2f;

                // Tracking
                vec3f V = make_vec3f(static_cast<float>(p[0]),
                                     static_cast<float>(p[1]),
                                     static_cast<float>(p[2]));
                V *= this->activationMatrix;
                this->track_point_changed_.value(V);
                node::emit_event(this->track_point_changed_emitter_,
                                 timestamp);

                vec3f t = make_vec3f(V[0] - this->activationPoint.value().x()
                                     + this->offset_.sfvec3f::value().x(),
                                     V[1] - this->activationPoint.value().y()
                                     + this->offset_.sfvec3f::value().y(),
                                     0.0);

                const vec2f & min_pos = this->min_position_.sfvec2f::value();
                const vec2f & max_pos = this->max_position_.sfvec2f::value();

                if (min_pos.x() == max_pos.x()) {
                    t.x(min_pos.x());
                } else if (min_pos.x() < max_pos.x()) {
                    if (t.x() < min_pos.x()) {
                        t.x(min_pos.x());
                    } else if (t.x() > max_pos.x()) {
                        t.x(max_pos.x());
                    }
                }

                if (min_pos.y() == max_pos.y()) {
                    t.y(min_pos.y());
                } else if (min_pos.y() < max_pos.y()) {
                    if (t.y() < min_pos.y()) {
                        t.y(min_pos.y());
                    } else if (t.y() > max_pos.y()) {
                        t.y(max_pos.y());
                    }
                }

                this->translation_changed_.value(t);
                node::emit_event(this->translation_changed_emitter_,
                                 timestamp);
            }
        }
    }
}


/**
 * @brief @c node_metatype identifier.
 */
const char * const openvrml_node_vrml97::plane_sensor_metatype::id =
    "urn:X-openvrml:node:PlaneSensor";

/**
 * @brief Construct.
 *
 * @param browser the browser associated with this node class object.
 */
openvrml_node_vrml97::plane_sensor_metatype::
plane_sensor_metatype(openvrml::browser & browser):
    node_metatype(plane_sensor_metatype::id, browser)
{}

/**
 * @brief Destroy.
 */
openvrml_node_vrml97::plane_sensor_metatype::~plane_sensor_metatype()
    OPENVRML_NOTHROW
{}

# define PLANE_SENSOR_INTERFACE_SEQ \
    ((exposedfield, sfbool,   "autoOffset",          auto_offset_)) \
    ((exposedfield, sfbool,   "enabled",             enabled_)) \
    ((exposedfield, sfvec2f,  "maxPosition",         max_position_)) \
    ((exposedfield, sfvec2f,  "minPosition",         min_position_)) \
    ((exposedfield, sfvec3f,  "offset",              offset_)) \
    ((eventout,     sfbool,   "isActive",            is_active_emitter_)) \
    ((eventout,     sfvec3f,  "trackPoint_changed",  track_point_changed_emitter_)) \
    ((eventout,     sfvec3f,  "translation_changed", translation_changed_emitter_)) \
    ((exposedfield, sfnode,   "metadata",            metadata)) \
    ((exposedfield, sfstring, "description",         description_)) \
    ((eventout,     sfbool,   "isOver",              is_over_emitter_))

OPENVRML_NODE_IMPL_UTIL_DEFINE_DO_CREATE_TYPE(openvrml_node_vrml97,
                                              plane_sensor_metatype,
                                              plane_sensor_node,
                                              PLANE_SENSOR_INTERFACE_SEQ)
