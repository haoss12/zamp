#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "AbstractInterp4Command.hh"

int main()
{
  void *pLibHnd_Move = dlopen("libInterp4Move.so", RTLD_LAZY);
  AbstractInterp4Command *(*pCreateCmd_Move)(void);
  void *pFun;

  if (!pLibHnd_Move)
  {
    std::cerr << "!!! Brak biblioteki: Interp4Move.so" << std::endl;
    return 1;
  }

  pFun = dlsym(pLibHnd_Move, "CreateCmd");
  if (!pFun)
  {
    std::cerr << "!!! Nie znaleziono funkcji CreateCmd" << std::endl;
    return 1;
  }
  pCreateCmd_Move = reinterpret_cast<AbstractInterp4Command *(*)(void)>(pFun);

  AbstractInterp4Command *pCmd = pCreateCmd_Move();

  std::cout << std::endl;
  std::cout << pCmd->GetCmdName() << std::endl;
  std::cout << std::endl;
  pCmd->PrintSyntax();
  std::cout << std::endl;
  pCmd->PrintCmd();
  std::cout << std::endl;

  delete pCmd;

  dlclose(pLibHnd_Move);
}
