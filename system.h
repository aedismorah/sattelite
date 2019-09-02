#ifndef SYSTEM_H
#define SYSTEM_H

#include "object.h"

namespace simulation
{
    class System
    {
    public:
        System();
        void addObject(Object& object);
        bool update(double dt, bool& collision);
        std::vector<Object> object_v;
    private:
        QElapsedTimer timer;
    };
}

#endif // SYSTEM_H
