//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_IMPLEMENTATION_DETAIL_TYPE_COUNT_HPP
#define FAS_IMPLEMENTATION_DETAIL_TYPE_COUNT_HPP

#include <fas/static_check/verifying.hpp>
#include <fas/type_list/check_list.hpp>
#include <fas/type_list/metalist.hpp>

namespace fas{ namespace detail{

template<typename T, typename L>
struct type_count_impl1;

template<typename MT, typename T, typename L>
struct type_count_impl2;

template<typename T1, typename T2>
struct type_count_some_type;

#ifdef FASLIB_TYPE_LIST_CHECK

template<typename T, typename L>
struct type_count_verifying;

template<typename T,typename L>
struct type_count_helper
  : verifying< type_count_verifying<T, L>, check_list<L> >::type
{
};

template<typename T, typename L>
struct type_count_verifying
  : type_count_impl1<T, L>
{
};

#else

template<typename T, typename L>
struct type_count_helper
  : type_count_impl1< T, L>
{
};

#endif

template<typename T, typename L>
struct type_count_impl1
  : type_count_impl2<typename L::metatype, T, L>
{
  
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<typename T, typename L, typename R>
struct type_count_impl1<T, type_list<L, R> >
{
  enum 
  {
    value = type_count_some_type<T, L>::value 
        + type_count_impl1<T, R>::value 
  };
};

/*
template<typename T, typename L, typename R>
struct type_count_impl1<T, tl<L, R> >
{
  enum 
  {
    value = type_count_some_type<T, L>::value 
        + type_count_impl1<T, R>::value 
  };
};
*/

template<typename T>
struct type_count_impl1<T, empty_list>
{
  enum { value = 0 };
};

/*
template<typename T>
struct type_count_impl1<T, el>
{
  enum { value = 0 };
};
*/

#endif // DISABLE_TYPE_LIST_SPEC

template<typename T, typename L>
struct type_count_impl2<metalist::type_list, T, L>
{
  typedef typename L::left_type head;
  typedef typename L::right_type tail;
  enum 
  {
    value = type_count_some_type<T, head>::value 
        + type_count_impl1<T, tail>::value 
  };
};

template<typename T, typename L>
struct type_count_impl2<metalist::empty_list, T, L>
{
  enum { value = 0 };
};

template<typename T1, typename T2>
struct type_count_some_type
{
  enum { value = 0 };
};

template<typename T>
struct type_count_some_type<T, T>
{
  enum { value = 1 };
};

}}


#endif