#include <iostream>
#include <fcdk/ABI.h>

class A
{};

int
main()
{
  std::cout << "A = '" << FCDK::demangleTypename(typeid(A).name()) << '\'' << std::endl;
  return 0;
}
