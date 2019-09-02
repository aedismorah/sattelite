#ifndef SFMLCANVAS_H
#define SFMLCANVAS_H

#include "system.h"
#include "qsfmlwidget.h"
#include <iostream>
#include <QElapsedTimer>
#include <QMainWindow>
#include <qcustomplot.h>

class SFMLCanvas : public QSFMLWidget
{
public:
    explicit SFMLCanvas(QWidget* Parent = nullptr);
    void onInit() override;
    void onUpdate() override;
    void setQCustomPlot(QCustomPlot* plotRT__, QCustomPlot* plotPHIT__){plotRT = plotRT__; plotPHIT = plotPHIT__;}
    void init(double r, double phi, double v, double w, double e, bool method);
    void clear();
    simulation::System system;
    bool startSim = false, collision = false, send = false;
    QElapsedTimer tmr;
    double timeBound = 1e-3, rBound = 6e6, phiBound = 1e-6, x_moon_coord_0 = 235, y_moon_coord_0 = 250, x_moon_coord, y_moon_coord, moon_w;
    sf::Texture earth_texture, moon_texture;
    sf::Sprite earth_sprite, moon_sprite;
    sf::CircleShape moon_trace_sprite;
private:
    QCustomPlot *plotRT, *plotPHIT;
    QVector<double> R, PHI, T, moon_trace_x, moon_trace_y;
};

#endif // SFMLCANVAS_H
