#ifndef LIBINTERFACE_HH
#define LIBINTERFACE_HH

#include <dlfcn.h>

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

    AbstractInterp4Command *CreateCmd()
    {
        return _pCreateCmd();
    }
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

#endif // LIBINTERFACE_HH