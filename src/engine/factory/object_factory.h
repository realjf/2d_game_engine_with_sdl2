#ifndef _OBJECT_FACTORY_H_
#define _OBJECT_FACTORY_H_

#include <map>
#include <string>
#include <memory>
#include <functional>
#include "object/game_object.h"

using ObjectPtr = std::unique_ptr<GameObject>;
using ObjectList = std::vector<ObjectPtr>;
enum ObjectCategory {
    SCENE_OBJECTS = 0,
    GAME_OBJECTS = 1
};

class ObjectFactory {
public:
    GameObject *CreateObject(std::string type, Properties *props);
    void RegisterType(std::string className, std::function<GameObject *(Properties *props)> type);
    static ObjectFactory *GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new ObjectFactory(); }

private:
    ObjectFactory() {}
    std::map<std::string, std::function<GameObject *(Properties *props)>> m_TypeRegistry;
    static ObjectFactory *s_Instance;
};

template <class Type>
class Registrar {
public:
    Registrar(std::string className) {
        ObjectFactory::GetInstance()->RegisterType(className, [](Properties *props) -> GameObject * { return new Type(props); });
    }
};

#endif /* _OBJECT_FACTORY_H_ */
