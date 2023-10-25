#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <map>
#include <memory>
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

  std::string list[] = {"Move", "Set", "Rotate"};

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
  return _mSet[sCommandName];
}

int main()
{

  Set4LibInterfaces SetOfInterfaces;
  if (!SetOfInterfaces.Init())
  {
    return 1;
  }

  AbstractInterp4Command *pSetCmd = SetOfInterfaces.get_pLibInterface("Set")->CreateCmd();

  std::cout << std::endl;
  std::cout << pSetCmd->GetCmdName() << std::endl;
  std::cout << std::endl;
  pSetCmd->PrintSyntax();
  std::cout << std::endl;
  pSetCmd->PrintCmd();
  std::cout << std::endl;

  delete pSetCmd;

  LibInterface MoveCmdInterface;

  if (!MoveCmdInterface.Init("libInterp4Move.so"))
  {
    return 1;
  }

  AbstractInterp4Command *pMoveCmd = MoveCmdInterface.CreateCmd();

  std::cout << std::endl;
  std::cout << pMoveCmd->GetCmdName() << std::endl;
  std::cout << std::endl;
  pMoveCmd->PrintSyntax();
  std::cout << std::endl;
  pMoveCmd->PrintCmd();
  std::cout << std::endl;

  delete pMoveCmd;
}
