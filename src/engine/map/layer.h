#ifndef _LAYER_H_
#define _LAYER_H_

class Layer {
public:
    virtual void Render() = 0;
    virtual void Update() = 0;
};

#endif /* _LAYER_H_ */
