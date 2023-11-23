#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include <string>
#include <vector>

#include "Cuboid.hh"

class Configuration
{
  public:
    std::vector<std::string> _Libs;
    std::vector<Cuboid> _mobileObjs;
};

#endif
