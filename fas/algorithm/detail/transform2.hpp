//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_DETAIL_TRANSFORM2_HPP
#define FAS_ALGORITHM_DETAIL_TRANSFORM2_HPP

#include <fas/mp/apply.hpp>
#include <fas/static_check/verifying.hpp>
#include <fas/type_list/check_two_lists.hpp>
#include <fas/type_list/metalist.hpp>
#include <fas/typemanip/empty_type.hpp>

namespace fas{ namespace detail{

template< typename L1, typename L2, typename F>
struct transform2_impl;

template<typename MT1, typename MT2, typename L1, typename L2, typename F>
struct transform2_impl2;

#ifdef FASLIB_TYPE_LIST_CHECK

template<typename L1, typename L2, typename F>
struct transform2_verifying;

template<typename L1, typename L2, typename F>
struct transform2_helper
  : verifying< transform2_verifying<L1, L2, F>, check_two_lists<L1, L2> >::type
{
};

template<typename L1, typename L2, typename F>
struct transform2_verifying
  : transform2_impl< L1, L2,  F>
{
};

#else

template<typename L1, typename L2, typename F>
struct transform2_helper
  : transform2_impl<L1, L2,  F>
{
};

#endif

template< typename L1, typename L2, typename F>
struct transform2_impl
  : transform2_impl2<typename L1::metatype, typename L2::metatype, L1, L2,  F>
{
};


#ifndef DISABLE_TYPE_LIST_SPEC

////////////////////// 
//// type_list
////////////////////// 

template< typename F>
struct transform2_impl<empty_list, empty_list, F>
{
  typedef empty_list type;
};


template< typename L, typename R, typename F>
struct transform2_impl< type_list<L, R>, empty_list, F >
{
  typedef type_list<
    typename apply<F, L, empty_type>::type,
    typename transform2_impl<  R, empty_list, F>::type
  > type;
};


template< typename L, typename R, typename F>
struct transform2_impl< empty_list, type_list<L, R>,  F >
{
  typedef type_list<
    typename apply<F, empty_type, L>::type,
    typename transform2_impl< empty_list, R, F>::type
  > type;
};


template< typename L1, typename R1, typename L2, typename R2, typename F>
struct transform2_impl< type_list<L1, R1>, type_list<L2, R2>,  F >
{
  typedef type_list<
    typename apply<F, L1, L2>::type,
    typename transform2_impl< R1, R2, F>::type
  > type;
};

////////////////////// 
//// tl
////////////////////// 

/*
template< typename F>
struct transform2_impl<el, el, F>
{
  typedef el type;
};


template< typename L, typename R, typename F>
struct transform2_impl< tl<L, R>, el, F >
{
  typedef tl<
    typename apply<F, L, empty_type>::type,
    typename transform2_impl<  R, el, F>::type
  > type;
};


template< typename L, typename R, typename F>
struct transform2_impl< el, tl<L, R>,  F >
{
  typedef tl<
    typename apply<F, empty_type, L>::type,
    typename transform2_impl< el, R, F>::type
  > type;
};


template< typename L1, typename R1, typename L2, typename R2, typename F>
struct transform2_impl< tl<L1, R1>, tl<L2, R2>,  F >
{
  typedef type_list<
    typename apply<F, L1, L2>::type,
    typename transform2_impl< R1, R2, F>::type
  > type;
};
*/
#endif // DISABLE_TYPE_LIST_SPEC


template<typename L1, typename L2, typename F>
struct transform2_impl2<metalist::type_list, metalist::type_list, L1, L2, F>
{
  typedef typename L1::left_type head1;
  typedef typename L1::right_type tail1;
  
  typedef typename L2::left_type head2;
  typedef typename L2::right_type tail2;
  
  typedef typename L1::template rebind<
        typename apply<F, head1, head2>::type,
        typename transform2_impl<tail1, tail2, F>::type
      >::type type;
};

template<typename L1, typename L2, typename F>
struct transform2_impl2<metalist::type_list, metalist::empty_list, L1, L2, F>
{
  typedef typename L1::left_type head1;
  typedef typename L1::right_type tail1;
  
  typedef typename L1::template rebind<
        typename apply<F, head1, empty_type>::type,
        typename transform2_impl<tail1, L2, F>::type
      >::type type;
};

template<typename L1, typename L2, typename F>
struct transform2_impl2< metalist::empty_list, metalist::type_list, L1, L2, F>
{
  typedef typename L2::left_type head2;
  typedef typename L2::right_type tail2;
  
  typedef typename L2::template rebind<
        typename apply< F, empty_type, head2>::type,
        typename transform2_impl< L1, tail2, F>::type
      >::type type;
};


template<typename L1, typename L2,  typename F>
struct transform2_impl2<metalist::empty_list, metalist::empty_list, L1, L2, F>
{
  typedef L1 type;
};

/// //////////////////////////////////
/// //////////////////////////////////
/// //////////////////////////////////
/// //////////////////////////////////

template< typename L1, typename L2, template<typename,typename> class F>
struct transform2_impl_t;

template<typename MT1, typename MT2, typename L1, typename L2, template<typename,typename> class F>
struct transform2_impl2_t;

#ifdef FASLIB_TYPE_LIST_CHECK

template<typename L1, typename L2, template<typename,typename> class F>
struct transform2_verifying_t;

template<typename L1, typename L2, template<typename,typename> class F>
struct transform2_helper_t
  : verifying< transform2_verifying_t<L1, L2, F>, check_two_lists<L1, L2> >::type
{
};

template<typename L1, typename L2, template<typename,typename> class F>
struct transform2_verifying_t
  : transform2_impl_t< L1, L2,  F>
{
};

#else

template<typename L1, typename L2, template<typename,typename> class F>
struct transform2_helper_t
  : transform2_impl_t<L1, L2,  F>
{
};

#endif

template< typename L1, typename L2, template<typename,typename> class F>
struct transform2_impl_t
  : transform2_impl2_t<typename L1::metatype, typename L2::metatype, L1, L2,  F>
{
};


#ifndef DISABLE_TYPE_LIST_SPEC


template< template<typename,typename> class F>
struct transform2_impl_t<empty_list, empty_list, F>
{
  typedef empty_list type;
};


template< typename L, typename R, template<typename,typename> class F>
struct transform2_impl_t< type_list<L, R>, empty_list, F >
{
  typedef type_list<
    typename F< L, empty_type>::type,
    typename transform2_impl_t<  R, empty_list, F>::type
  > type;
};


template< typename L, typename R, template<typename,typename> class F>
struct transform2_impl_t< empty_list, type_list<L, R>,  F >
{
  typedef type_list<
    typename F<empty_type, L>::type,
    typename transform2_impl_t< empty_list, R, F>::type
  > type;
};


template< typename L1, typename R1, typename L2, typename R2, template<typename,typename> class F>
struct transform2_impl_t< type_list<L1, R1>, type_list<L2, R2>,  F >
{
  typedef type_list<
    typename F< L1, L2>::type,
    typename transform2_impl_t< R1, R2, F>::type
  > type;
};

#endif // DISABLE_TYPE_LIST_SPEC


template<typename L1, typename L2, template<typename,typename> class F>
struct transform2_impl2_t<metalist::type_list, metalist::type_list, L1, L2, F>
{
  typedef typename L1::left_type head1;
  typedef typename L1::right_type tail1;
  
  typedef typename L2::left_type head2;
  typedef typename L2::right_type tail2;
  
  typedef typename L1::template rebind<
        typename F< head1, head2>::type,
        typename transform2_impl_t<tail1, tail2, F>::type
      >::type type;
};

template<typename L1, typename L2, template<typename,typename> class F>
struct transform2_impl2_t<metalist::type_list, metalist::empty_list, L1, L2, F>
{
  typedef typename L1::left_type head1;
  typedef typename L1::right_type tail1;
  
  typedef typename L1::template rebind<
        typename F<head1, empty_type>::type,
        typename transform2_impl_t<tail1, L2, F>::type
      >::type type;
};

template<typename L1, typename L2, template<typename,typename> class F>
struct transform2_impl2_t< metalist::empty_list, metalist::type_list, L1, L2, F>
{
  typedef typename L2::left_type head2;
  typedef typename L2::right_type tail2;
  
  typedef typename L2::template rebind<
        typename F< empty_type, head2>::type,
        typename transform2_impl_t< L1, tail2, F>::type
      >::type type;
};


template<typename L1, typename L2,  template<typename,typename> class F>
struct transform2_impl2_t<metalist::empty_list, metalist::empty_list, L1, L2, F>
{
  typedef L1 type;
};

}}


#endif