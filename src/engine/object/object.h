#ifndef _OBJECT_H_
#define _OBJECT_H_

class Object {
public:
    virtual void Draw() = 0;
    virtual void Update(float dt) = 0;
    virtual void Clean() = 0;
};

#endif /* _OBJECT_H_ */