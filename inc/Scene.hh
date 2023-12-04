#ifndef SCENE_HH
#define SCENE_HH

#include <map>
#include <string>

#include "AbstractScene.hh"
#include "Configuration.hh"

class Scene : public AbstractScene
{
  private:
    std::map<std::string, AbstractMobileObj> _mapOfObjects;

  public:
    Scene(const Configuration &_config);
};

#endif