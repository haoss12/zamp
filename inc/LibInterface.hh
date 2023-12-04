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

#endif // LIBINTERFACE_HH