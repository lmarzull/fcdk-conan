#ifndef __FCDK_TESTS_ARGV_HELPER_H__
#define __FCDK_TESTS_ARGV_HELPER_H__


#include <initializer_list>
#include <vector>


namespace FCDK::Test
{


class ArgvHelper
{
public:
  ArgvHelper( std::initializer_list<const char*> argv_list )
  {
    for ( auto argv: argv_list )
      _argv.push_back( const_cast<char*>( argv ) );
  }


  char**  argv() 
  {
    return _argv.data();
  }


  std::size_t size() const { return _argv.size(); }


private:
  std::vector<char*>  _argv;
};


} // FCDK::Test


#endif  // #ifndef __FCDK_TESTS_ARGV_HELPER_H__
