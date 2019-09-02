#include "object.h"

namespace simulation
{
    Object::Object(double r0, double phi0, double v0, double w0, double e, bool METHOD) //metod 0 - Euler, 1 - Runge-Kutte; step is whole time of 1 calculation
    { //f0 IN RADIANS AND w0 TOO
        X = vector(r0, phi0, v0, w0);
        method = METHOD;
        this->e = e;
        method ? dt = pow(e, 0.25) : dt = e;
        globalTime = 0;
        circle.setRadius(1);
        sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
    }

    vector Object::F(vector U) //here is no t because F doesn't depend on explicitly on time
	{
		vector res;
        res.r   =   U.v;
        res.phi  =   U.w;
        res.w   =   -2 * (U.v)*(U.w) / U.r;
        res.v   =   (U.r*U.w*U.w) - G * M / (U.r*U.r);
		return(res);
	}


    bool Object::update(double udpateTime) //returns 0 on succes and 1 on error; If you're interested what kind of an exception - look errno;
    {
        switch (method)
        {
            case Euler_case:
                return Euler(udpateTime);
            case Runge_Kutte_case:
                return Runge_Kutte(udpateTime);
        }
    }

    bool Object::Euler(double udpateTime)
	{
        if(X.r > Earth_radius)
		{
			if (dt == 0)
				throw std::invalid_argument("dt is zero");

			delta = F(X)*dt;
			
			if (fabs(delta.r) >= e)  //according to the paper
				dt /= 2;
            else
            {
                X = X + delta;
                globalTime += dt;
                if(globalTime > udpateTime)
                {
                    sprite.setPosition(X.r * cos(X.phi)/Earth_radius*scale + 235, X.r * sin(X.phi)/Earth_radius*scale + 250);
                    trace.push_back(sf::Vector2f(X.r * cos(X.phi)/Earth_radius*scale + 235, X.r * sin(X.phi)/Earth_radius*scale + 250));
                    sprite.setRotation(X.phi*180/M_PI);
                    k++;
                }
            }
            return true;
		}
        else
            return false;
	}

    bool Object::Runge_Kutte(double udpateTime)
	{
		if (pr(dt) == 0)
			throw std::invalid_argument("dt is zero");

        if(X.r > Earth_radius)
		{
            k1 = F(X);
            k2 = F(X + k1*dt*0.5);
            k3 = F(X + k2*dt*0.5);
            k4 = F(X + k3*dt);
            delta = (k1 + k2 * 2 + k3 * 2 + k4) * (dt / 6);

			if (fabs(delta.r) >= e) //according to the paper
			{
				dt /= 2;
				if (pr(dt) == 0)
					throw std::invalid_argument("dt is zero");
			}
            else
            {
                X = X + delta;
                globalTime += dt;
                if(globalTime > udpateTime * k)
                {
                    sprite.setPosition(X.r * cos(X.phi)/Earth_radius*scale + 235, X.r * sin(X.phi)/Earth_radius*scale + 250);
                    trace.push_back(sf::Vector2f(X.r * cos(X.phi)/Earth_radius*scale + 235, X.r * sin(X.phi)/Earth_radius*scale + 250));
                    sprite.setRotation(X.phi*180/M_PI);
                    k++;
                }
            }
		}
        else
            return false;
    }
}
