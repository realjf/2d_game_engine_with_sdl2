#ifndef _HELPERS_H_
#define _HELPERS_H_

#include <cstdlib>
#include <iostream>
#include <ctime>

class Helpers {
public:
    static int RandI(int min, int max) {
        if (min < max) {
            return ((rand() % (max - min)) + min);
        }
        return 0;
    }
};

#endif /* _HELPERS_H_ */
