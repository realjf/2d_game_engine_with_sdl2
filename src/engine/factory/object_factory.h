#ifndef _OBJECT_FACTORY_H_
#define _OBJECT_FACTORY_H_

#include <map>
#include <string>
#include <memory>
#include <functional>
#include "object/game_object.h"

class ObjectFactory {
public:
    ObjectPtr CreateObject(std::string type, Transform *tf);
    void RegisterType(std::string className, std::function<GameObject *(Transform *tf)> type);
    static ObjectFactory *GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new ObjectFactory(); }

private:
    ObjectFactory() {}
    std::map<std::string, std::function<ObjectPtr(Transform *tf)>> m_TypeRegistry;
    static ObjectFactory *s_Instance;
};

template <class Type>
class Registrar {
public:
    Registrar(std::string className) {
        ObjectFactory::GetInstance()->RegisterType(className, [](Transform *tf) -> ObjectPtr { return new Type(tf); });
    }
};

#endif /* _OBJECT_FACTORY_H_ */
