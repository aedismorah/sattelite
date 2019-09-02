#ifndef OBJECT_H
#define OBJECT_H

#include "vector.h"
#include <QVector>

#define pr(x) ((x) > -1E-5 && (x) < 1E-5) ? (int)0 : (int)1
#define Euler_case false
#define Runge_Kutte_case true

namespace simulation
{
	class Object
	{
	private:
        vector X, delta, k1, k2, k3, k4;
        bool method;
        double e, globalTime, dt;

		const double M = 5.97E24;
		const double G = 6.67E-11;
        const double Earth_radius = 6.3E6;

		vector F(vector U);
        bool Euler(double udpateTime);
        bool Runge_Kutte(double udpateTime);

	public:
        Object(double r0, double phi0, double v0, double w0, double e, bool metod);
        bool update(double udpateTime);
        double getR()       const{return X.r;           }
        double getPhi()     const{return X.phi;         }
        double getV()       const{return X.v;           }
        double getW()       const{return X.w;           }
        double getT()       const{return globalTime;    }

        void setR(double R)         {X.r = R;           }
        void setPhi(double PHI)     {X.phi = PHI;       }
        void setV(double V)         {X.v = V;           }
        void setW(double W)         {X.w = W;           }
        void setE(double E)         {e = E; method ? dt = pow(e, 0.25) : dt = e; globalTime = 0; trace.clear();}
        void setMethod(bool METHOD) {method = METHOD;}

        double R0 = 1e9, scale;
        int k = 0;

        sf::Texture texture;
        sf::Sprite sprite;

        QVector<sf::Vector2f> trace;
        sf::CircleShape circle;
	};
}

#endif // OBJECT_H
