#ifndef SET4LIBINTERFACES_HH
#define SET4LIBINTERFACES_HH

#include <map>
#include <memory>
#include <exception>

#include "LibInterface.hh"

class Set4LibInterfaces
{
private:
  std::map<std::string, std::shared_ptr<LibInterface>> _mSet;

public:
  bool Init();
  std::shared_ptr<LibInterface> get_pLibInterface(const char *sCommandName);
};

bool Set4LibInterfaces::Init()
{
  // get all four plugins into the map

  std::string list[] = {"Move", "Set", "Rotate", "Pause"};

  for (auto &s : list)
  {
    _mSet[s] = std::make_shared<LibInterface>();
    std::string filename = "libInterp4" + s + ".so";
    if (!_mSet[s].get()->Init(filename.c_str()))
    {
      return false;
    }
  }
  return true;
}

std::shared_ptr<LibInterface> Set4LibInterfaces::get_pLibInterface(const char *sCommandName)
{
  if (_mSet.count(sCommandName) == 0) // this element is not in the map
  {
    throw std::logic_error("no matching element");
  }
  return _mSet[sCommandName];
}

#endif //SET4LIBINTERFACES_HH