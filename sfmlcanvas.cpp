#include "sfmlcanvas.h"
#include <cmath>

SFMLCanvas::SFMLCanvas(QWidget* Parent) : QSFMLWidget(Parent)
{
}

void SFMLCanvas::init(double r, double fi, double v, double w, double e, bool method)
{
    moon_w = 13.0/60.0/24.0/60.0/60.0;
    simulation::Object object(r, fi, v, w, e, method);
    system.addObject(object);
    system.object_v.back().texture.loadFromFile("img.png");
    system.object_v.back().sprite.setTexture(system.object_v.back().texture);
    system.object_v.back().sprite.setPosition(sf::Vector2f(0, 0));

    earth_texture.loadFromFile  ("earth.png");
    earth_sprite.setTexture     (earth_texture);
    earth_sprite.setOrigin      (earth_texture.getSize().x/2, earth_texture.getSize().y/2);
    earth_sprite.setPosition    (235, 250);

    moon_texture.loadFromFile   ("moon.png");
    moon_sprite.setTexture      (moon_texture);
    earth_sprite.setOrigin      (moon_texture.getSize().x/2, moon_texture.getSize().y/2);

    moon_trace_sprite.setRadius(1);
}

void SFMLCanvas::onInit()
{
}

void SFMLCanvas::onUpdate()
{
    if(startSim && !collision)
    {
        //f(tmr.elapsed() > 25000){QMessageBox::question(this, "results", "по-моему достойно, жду комментариев)", QMessageBox::Ok); exit(0);}
        if(system.update(0.2, collision))
        {
            if(collision && !send)
            {
                QMessageBox::question(this, "Спутник столкнулся с Землей", "Повысьте точность вычислений или измените начальные данные", QMessageBox::Ok);
                send = true;
                system.object_v.back().setR(1e9);
            }

            sf::RenderWindow::clear();

            sf::RenderWindow::draw(system.object_v.back().sprite);

            for(auto tr : system.object_v.back().trace)
            {
                system.object_v.back().circle.setPosition(tr);
                sf::RenderWindow::draw(system.object_v.back().circle);
            }

            // обработка движения луны плюс следа от движения луны
            //
            x_moon_coord = x_moon_coord_0 + 362.6E6 * cos(moon_w * system.object_v.back().getT())/6.3E6 * system.object_v.back().scale;
            y_moon_coord = y_moon_coord_0 + 405.4E6 * sin(moon_w * system.object_v.back().getT())/6.3E6 * system.object_v.back().scale;

            moon_trace_x.push_back(x_moon_coord);
            moon_trace_y.push_back(y_moon_coord);

            moon_sprite.setPosition    (x_moon_coord, y_moon_coord);
            sf::RenderWindow::draw(moon_sprite);
            //std::cout << x_moon_coord << ";;" << y_moon_coord << std::endl;

            for(int i = 0; i < moon_trace_x.size(); ++i)
            {
                moon_trace_sprite.setPosition(moon_trace_x[i], moon_trace_y[i]);
                sf::RenderWindow::draw(moon_trace_sprite);
            }

            //
            //
            sf::RenderWindow::draw(earth_sprite);
            PHI.push_back(system.object_v.back().getPhi());
            R.push_back(system.object_v.back().getR());
            T.push_back(system.object_v.back().getT());

            double minR = *std::min_element(R.constBegin(), R.constEnd());
            double maxR = *std::max_element(R.constBegin(), R.constEnd());

            double minPHI = *std::min_element(PHI.constBegin(), PHI.constEnd());
            double maxPHI = *std::max_element(PHI.constBegin(), PHI.constEnd());

            plotRT->graph(0)->setData(T, R);
            plotRT->xAxis->setRange(0, T.back());
            plotRT->yAxis->setRange(minR, maxR);
            plotRT->replot();

            plotPHIT->graph(0)->setData(T, PHI);
            plotPHIT->xAxis->setRange(0, T.back());
            plotPHIT->yAxis->setRange(minPHI, maxPHI);
            plotPHIT->replot();

            sf::RenderWindow::display();
        }
    }
    else
    {
        sf::RenderWindow::clear();
        sf::RenderWindow::display();
    }
}

void SFMLCanvas::clear()
{
    T.clear();
    R.clear();
    PHI.clear();
    moon_trace_x.clear();
    moon_trace_y.clear();
}
