// -*- Mode: C++; indent-tabs-mode: nil; c-basic-offset: 4; -*-
//
// Copyright 2005  Braden McDaniel
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

# include <fstream>
# include <sstream>
# include <boost/thread.hpp>
# include <boost/test/unit_test.hpp>
# include "test_browser.h"

using namespace std;
using namespace openvrml;

void create_vrml_from_stream()
{
    test_browser b(vrml97_profile_id);

    const char vrmlstring[] = "Group {}";
    stringstream vrmlstream(vrmlstring);

    vector<boost::intrusive_ptr<node> > nodes =
        b.create_vrml_from_stream(vrmlstream);

    BOOST_REQUIRE(nodes.size() == 1);
    BOOST_REQUIRE(nodes[0] != boost::intrusive_ptr<node>(0));
    BOOST_CHECK_EQUAL(nodes[0]->type().id(), "Group");
}

void create_vrml_from_url()
{
    class children_listener : public openvrml::mfnode_listener {
        bool received_event_;
        boost::mutex & mutex_;
        boost::condition & condition_;

    public:
        children_listener(boost::mutex & mutex, boost::condition & condition):
            received_event_(false),
            mutex_(mutex),
            condition_(condition)
        {}

        bool received_event() const
        {
            return this->received_event_;
        }

    private:
        virtual void do_process_event(const openvrml::mfnode &, double)
            throw (std::bad_alloc)
        {
            boost::mutex::scoped_lock lock(this->mutex_);
            this->received_event_ = true;
            this->condition_.notify_all();
        }
    };

    {
	ofstream file("test.wrl");
        file << "#VRML V2.0 utf8" << endl
	     << "Shape {}" << endl;
    }
    test_browser b(vrml97_profile_id);
    const char vrmlstring[] = "Group {}";
    stringstream vrmlstream(vrmlstring);
    vector<boost::intrusive_ptr<node> > nodes =
        b.create_vrml_from_stream(vrmlstream);

    boost::mutex mutex;
    boost::condition listener_received_event;

    children_listener listener(mutex, listener_received_event);
    mfnode_emitter & emitter =
        nodes[0]->event_emitter<mfnode>("children_changed");
    emitter.add(listener);

    vector<string> url(1, "test.wrl");
    b.create_vrml_from_url(url, nodes[0], "set_children");
    {
        boost::mutex::scoped_lock lock(mutex);
        while (!listener.received_event()) {
            listener_received_event.wait(lock);
        }
    }

    grouping_node * group = node_cast<grouping_node *>(nodes[0].get());
    BOOST_REQUIRE(group);
    const vector<boost::intrusive_ptr<node> > & children = group->children();
    BOOST_REQUIRE(children.size() == 1);
    BOOST_CHECK_EQUAL(children[0]->type().id(), "Shape");

    int remove_result = remove("test.wrl");
    BOOST_CHECK(remove_result == 0);
}

boost::unit_test::test_suite * init_unit_test_suite(int, char * [])
{
    using boost::unit_test::test_suite;
    test_suite * const suite = BOOST_TEST_SUITE("browser");
    suite->add(BOOST_TEST_CASE(&create_vrml_from_stream));
    suite->add(BOOST_TEST_CASE(&create_vrml_from_url));
    return suite;
}