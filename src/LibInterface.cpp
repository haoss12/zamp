#include "LibInterface.hh"

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