#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include <string>
#include <vector>

#include "Cuboid.hh"
#include "Set4LibInterfaces.hh"

class Configuration
{
  public:
    std::vector<std::string> _Libs;
    std::vector<Cuboid> _mobileObjs;
    Set4LibInterfaces _SetOfLibs;
};

#endif
