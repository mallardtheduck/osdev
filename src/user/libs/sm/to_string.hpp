#ifndef _TO_STRING_HPP
#define _TO_STRING_HPP

#include <string>
#include <sstream>

template < typename T > std::string to_string( const T& n )
{
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}

#endif
