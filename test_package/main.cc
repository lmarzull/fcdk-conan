#include <iostream>
#include <fcdk/CommandLineOptionFlag.h>

int
main()
{
  FCDK::CommandLineOptionFlag show_help('h', "help", "show this help message");
  std::cout << "Hello, world!" << std::endl;
}
