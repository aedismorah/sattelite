#include "system.h"
#include <QMessageBox>

namespace simulation
{
    System::System()
    {
        timer.start();
    }

    void System::addObject(Object& object)
    {
        object_v.push_back(object);
    }

    bool System::update(double dt, bool& collision)
    {
        if(timer.elapsed() >= dt)
        {
            dt /= 1000;
            for(auto it = object_v.begin(); it < object_v.end(); ++it)
                if(!it->update(dt)){collision = true;}
            timer.restart();
            return true;
        }
        return false;
    }
}
