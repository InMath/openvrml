// -*- Mode: C++; indent-tabs-mode: nil; c-basic-offset: 4; fill-column: 78 -*-
//
// OpenVRML
//
// Copyright 2009  Braden McDaniel
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation; either version 3 of the License, or (at
// your option) any later version.
//
// This library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, see <http://www.gnu.org/licenses/>.
//

# include "error.h"
# include <boost/multi_index/detail/scope_guard.hpp>
# include <boost/ref.hpp>

using namespace boost::multi_index::detail;  // for scope_guard


# ifdef _WIN32
void openvrml::local::throw_runtime_error_from_win32_system_error(LONG result)
    OPENVRML_THROW1(std::runtime_error)
{
    using boost::ref;

    static const LPCVOID source;
    LPTSTR buf = 0;
    scope_guard buf_guard = make_guard(LocalFree, ref(buf));
    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM
                  | FORMAT_MESSAGE_ALLOCATE_BUFFER,
                  source,
                  result,
                  LANG_USER_DEFAULT,
                  reinterpret_cast< LPTSTR >(&buf),
                  0,
                  0);

    throw std::runtime_error(buf);
}
# endif