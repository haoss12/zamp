#include "Set4LibInterfaces.hh"

std::string Set4LibInterfaces::extractSubstring(const std::string &str, const std::string &prefix,
                                                const std::string &postfix)
{
    size_t startPos = str.find(prefix);
    if (startPos == std::string::npos)
    {
        return ""; // Start delimiter not found
    }

    startPos += prefix.length(); // Move startPos to the character next to the start delimiter

    size_t endPos = str.find(postfix, startPos);
    if (endPos == std::string::npos)
    {
        return ""; // End delimiter not found
    }

    return str.substr(startPos, endPos - startPos);
}

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

bool Set4LibInterfaces::AddLib(const std::string &sLibName)
{
    static std::string prefix = "libInterp4";
    static std::string postfix = ".so";
    std::string name = extractSubstring(sLibName, prefix, postfix);
    _mSet[name] = std::make_shared<LibInterface>();
    if (!_mSet[name].get()->Init(sLibName.c_str()))
    {
        return false;
    }

    return true;
}

std::shared_ptr<LibInterface> Set4LibInterfaces::get_pLibInterface(const char *sCommandName)
{
    if (_mSet.count(sCommandName) == 0) // this element is not in the map
    {
        throw std::logic_error("Brak pasujacej wtyczki!");
    }
    return _mSet[sCommandName];
}