#ifndef SCENE_HH
#define SCENE_HH

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Configuration.hh"
#include "AbstractScene.hh"
#include "AccessControl.hh"

class Scene : public AbstractScene
{
  private:
    std::map<std::string, std::shared_ptr<Cuboid>> _mapOfObjects;

  public:
    explicit Scene(const Configuration &_config)
    {
        for (auto &obj : _config._mobileObjs)
        {
          _mapOfObjects[obj.GetName()] = std::make_shared<Cuboid>(obj);
        }

        for (auto &obj : _mapOfObjects)
        {
          obj.second->PrintState();
        }
    };

    std::shared_ptr<Cuboid> FindMobileObj(const std::string &sName) override
    {
      auto it = _mapOfObjects.find(sName);
      if (it == _mapOfObjects.end())
      {
        return std::shared_ptr<Cuboid>(nullptr);
      }
      return _mapOfObjects[sName];
    };

    void AddMobileObj(Cuboid *pMobObj) override
    {
      _mapOfObjects[pMobObj->GetName()] = std::make_shared<Cuboid>(*pMobObj);
    };

    std::map<std::string, std::shared_ptr<Cuboid>> GetWholeMap()
    {
      return _mapOfObjects;
    };
};

#endif