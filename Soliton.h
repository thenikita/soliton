//
// Created by User on 3/19/2018.
//

#include <vector>

#ifndef SOLITON_SOLITON_H
#define SOLITON_SOLITON_H


class Soliton {

public:
    Soliton(int particleCount, double time);

private:
    double A = 0.05;
    double delta = 0.01;
    int particleCount;

    double dt = 0.000001;
    double dx = 0.01;

    double targetTime;
    double currentTime = 0;

    class Particle
    {
    public:
        Particle(double coordinate, double deviation, double speed);
        ~Particle();

        void SetCoordinate(double coordinate);
        void SetDeviation(double deviation);
        void SetSpeed(double speed);

        double GetCoordinate();
        double GetDeviation();
        double GetSpeed();

    private:
        double coordinate;
        double deviation;
        double speed;
    };

    std::vector<Particle> particles;
    std::vector<Particle> particlesT;

private:
    void GenerateParticles();
    void ToString();
    void MakeIterations();
    double f(int i);
};


#endif //SOLITON_SOLITON_H
