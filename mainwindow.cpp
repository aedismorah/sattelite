#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->plotRT->addGraph();
    ui->plotRT->xAxis->setLabel("T, с");
    ui->plotRT->yAxis->setLabel("R, м");
    ui->plotPHIT->addGraph();
    ui->plotPHIT->xAxis->setLabel("T, с");
    ui->plotPHIT->yAxis->setLabel("Phi, рад");
    ui->sfml->setQCustomPlot(ui->plotRT, ui->plotPHIT);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_clicked()
{
    double r0, phi0, v0, w0, e;
    bool method;
    r0       =      ui->height->text().toDouble();
    phi0     =      ui->angle->text().toDouble();
    v0       =      ui->velocity->text().toDouble();
    w0       =      ui->angle_velocity->text().toDouble();
    e        =      ui->error->text().toDouble();
    method   =      bool(ui->method->currentIndex());

    if(!ui->sfml->startSim)
    {
        ui->sfml->init(r0, phi0, v0, w0, e, method);
        ui->sfml->startSim = true;
        ui->sfml->tmr.start();
    }
    else
    {
        ui->sfml->system.object_v.back().setR(r0);
        ui->sfml->system.object_v.back().setPhi(phi0);
        ui->sfml->system.object_v.back().setV(v0);
        ui->sfml->system.object_v.back().setW(w0);
        ui->sfml->system.object_v.back().setMethod(method);
        ui->sfml->system.object_v.back().setE(e);
        ui->sfml->clear();
    }

    ui->sfml->system.object_v.back().R0 = r0;
    double scale = ui->sfml->system.object_v.back().scale = ui->scale->text().toDouble();
    ui->sfml->send = false;
    ui->sfml->collision = false;
    ui->sfml->earth_sprite.setScale(scale/380.0*2, scale/380.0*2);
    //ui->sfml->moon_sprite.setScale(15/380.0*2, 15/380.0*2);
    ui->sfml->moon_sprite.setScale(scale/380.0*2*0.273, scale/380.0*2*0.273);
}
