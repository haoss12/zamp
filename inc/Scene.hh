#ifndef SCENE_HH
#define SCENE_HH

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "AbstractScene.hh"
#include "Configuration.hh"

class Scene : public AbstractScene
{
  private:
    std::map<std::string, std::shared_ptr<Cuboid>> _mapOfObjects;

  public:
    Scene(const Configuration &_config)
    {
        for (auto &obj : _config._mobileObjs)
        {
            _mapOfObjects[obj.GetName()] = std::make_shared<Cuboid>(obj);
        }

        for (auto &obj : _mapOfObjects)
        {
            std::cout << "scena " << obj.second->GetName() << " " << obj.second->GetScale() << std::endl;
        }
    };

    AbstractMobileObj *FindMobileObj(const char *sName) override{};

    void AddMobileObj(AbstractMobileObj *pMobObj) override{};
};

#endif