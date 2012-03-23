//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_IMPLEMENTATION_TYPE_LIST_ORGANIZE_HPP
#define FAS_IMPLEMENTATION_TYPE_LIST_ORGANIZE_HPP

#include "detail/organize.hpp"

namespace fas{


template<typename L>
struct organize
{
  typedef typename detail::organize_helper<L>::type type;
};


}

#endif