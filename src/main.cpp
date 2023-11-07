#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <map>
#include <memory>
#include <exception>

#include "AbstractInterp4Command.hh"

class LibInterface
{
  void *_pLinHnd = nullptr;
  AbstractInterp4Command *(*_pCreateCmd)(void) = nullptr;

public:
  ~LibInterface()
  {
    if (_pLinHnd)
      dlclose(_pLinHnd);
  }

  bool Init(const char *sFileName);

  AbstractInterp4Command *CreateCmd() { return _pCreateCmd(); }
};

bool LibInterface::Init(const char *sFileName)
{
  if (sFileName == nullptr)
  {
    std::cerr << "!!! Nieprawidłowa nazwa: " << std::endl;
  }

  _pLinHnd = dlopen(sFileName, RTLD_LAZY);
  if (!_pLinHnd)
  {
    std::cerr << "!!! Brak biblioteki: " << sFileName << std::endl;
    return false;
  }

  void *pFun = dlsym(_pLinHnd, "CreateCmd");
  if (!pFun)
  {
    std::cerr << "!!! Nie znaleziono funkcji CreateCmd" << std::endl;
    return false;
  }
  _pCreateCmd = reinterpret_cast<AbstractInterp4Command *(*)(void)>(pFun);

  return true;
}

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

int main()
{

  Set4LibInterfaces SetOfInterfaces;
  if (!SetOfInterfaces.Init())
  {
    return 1;
  }

  // test if all of the components in set are working properly

  std::string list[] = {"Move", "Set", "Rotate", "Pause"};

  for (auto &s : list)
  {
    AbstractInterp4Command *pCmd = SetOfInterfaces.get_pLibInterface(s.c_str())->CreateCmd();

    std::cout << std::endl;
    std::cout << pCmd->GetCmdName() << std::endl;
    pCmd->PrintSyntax();
    pCmd->PrintCmd();
    std::cout << std::endl;

    delete pCmd;
  }

  for (auto &s : list)
  {
    AbstractInterp4Command *pCmd = SetOfInterfaces.get_pLibInterface(s.c_str())->CreateCmd();

    std::cout << std::endl;
    std::cout << pCmd->GetCmdName() << std::endl;
    pCmd->PrintSyntax();
    pCmd->PrintCmd();
    std::cout << std::endl;

    delete pCmd;
  }
}
