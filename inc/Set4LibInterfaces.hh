#ifndef SET4LIBINTERFACES_HH
#define SET4LIBINTERFACES_HH

#include <exception>
#include <map>
#include <memory>

#include "LibInterface.hh"

class Set4LibInterfaces
{
  private:
    std::map<std::string, std::shared_ptr<LibInterface>> _mSet;

    std::string extractSubstring(const std::string &str, const std::string &prefix, const std::string &postfix);

  public:
    bool Init();
    bool AddLib(const std::string &sLibName);
    std::shared_ptr<LibInterface> get_pLibInterface(const char *sCommandName);
};


#endif // SET4LIBINTERFACES_HH