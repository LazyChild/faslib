#ifndef FAS_RANGE_DETAIL_RANGE_HELPER_STREAM_HPP
#define FAS_RANGE_DETAIL_RANGE_HELPER_STREAM_HPP

#include <fas/range/typerange_flag.hpp>
#include <fas/range/output_range.hpp>
#include <fas/typemanip/is_const.hpp>
#include <iterator>
#include <ostream>
#include <istream>

namespace fas{

template< typename C>
struct range_helper<C, typerange_flag::stream >
{
  enum { flag = typerange_flag::stream };

  typedef output_range< std::ostreambuf_iterator<char>, char > orange;
  typedef input_range< std::istreambuf_iterator<char>, char > range;
  
  static inline orange make_orange(C& cnt, bool)
  {
    return orange( std::ostreambuf_iterator<char>(cnt) );
  };

  static inline range make_range(C& cnt)
  {
    return range( std::istreambuf_iterator<char>(cnt), std::istreambuf_iterator<char>() );
  };

};

};

#endif