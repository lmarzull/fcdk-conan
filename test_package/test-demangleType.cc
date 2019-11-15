#include <gtest/gtest.h>

#include <fcdk/ABI.h>


namespace TESTING_NS
{

class AClass
{};

}


TEST( demangleTypename, test_class_name )
{
  TESTING_NS::AClass a;
  ASSERT_EQ( FCDK::demangleTypename(typeid(a).name()), "TESTING_NS::AClass" );
}
