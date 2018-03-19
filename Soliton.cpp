//
// Created by User on 3/19/2018.
//

#include "Soliton.h"

#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>

using namespace std;

const double PI = 3.14159;

Soliton::Soliton(int particleCount, double time) {

    this->particleCount = particleCount;
    this->targetTime = time;

    cout << "Generating" << endl;
    GenerateParticles();

    ToString();

    cout << "Iterating" << endl;
    MakeIterations();

}

void Soliton::GenerateParticles() {

    Particle zeroParticle(0, A, 0);
    particles.push_back(zeroParticle);
    particles.push_back(zeroParticle);
    particles.push_back(zeroParticle);

    for (int i = 3; i < particleCount + 1; i++)
    {
        double coordinate, deviation;

        coordinate = dx * (i - 2);

        deviation = A * cos(2 * PI * (i - 2) / (particleCount - 1));

        Particle ithParticle(coordinate, deviation, 0);

        particles.push_back(ithParticle);
    }
    particles.push_back(zeroParticle);
    particles[particleCount + 1].SetCoordinate(dx * (particleCount - 1));

    particles.push_back(zeroParticle);
    particles.push_back(zeroParticle);

    particles[0].SetDeviation(particles[particleCount].GetDeviation());

    particles[1].SetDeviation(particles[particleCount + 1].GetDeviation());

    particles[particleCount + 2].SetDeviation(particles[2].GetDeviation());

    particles[particleCount + 3].SetDeviation(particles[3].GetDeviation());

    for (int i = 0; i < particleCount + 5; i++) {

        particlesT.push_back(zeroParticle);

    }

}


void Soliton::MakeIterations()
{
    double timeCuts[10][100];
    int cut = 0;
    int percent = 0;

    while (currentTime < targetTime)
    {

        int tempPerc = int(10 * currentTime / targetTime);

        if (percent != tempPerc) {

            percent = tempPerc;
            cout << "Processed " << percent << "0 %   " << "\r" << std::flush;

            for (int i = 2; i < particleCount + 2; i++) {

                timeCuts[cut][i] = particles[i].GetDeviation();

            }

            cut += 1;
        }

        currentTime += dt;

        for (int i = 2; i < particleCount + 2; i++)
        {
            particlesT[i].SetDeviation(f(i));
        }

        for (int i = 2; i < particleCount + 2; i++)
        {
            particles[i].SetDeviation(particlesT[i].GetDeviation());
        }

        particles[0].SetDeviation(particles[particleCount].GetDeviation());

        particles[1].SetDeviation(particles[particleCount + 1].GetDeviation());

        particles[particleCount + 2].SetDeviation(particles[2].GetDeviation());

        particles[particleCount + 3].SetDeviation(particles[3].GetDeviation());

    }

    std::ofstream file;
    file.open("solitondata.txt");

    for (int j = 2; j < particleCount + 2; j++) {

        file << particles[j].GetCoordinate() << " " << flush;

        for (int i = 0; i < cut; i++) {

            file << timeCuts[i][j] << " " << flush;

        }

        file << particles[j].GetDeviation() << endl;

    }

    file.close();

}


void Soliton::ToString()
{
    ofstream initial;
    initial.open("init.txt");

    cout << "logging..." << endl;

    for (int i = 2; i <= particleCount + 1; i++)
    {
        initial << particles[i].GetCoordinate() << " " << particles[i].GetDeviation() << endl;
    }

    initial.close();
}


double Soliton::f(int i) {
    double i0 = particles[i - 2].GetDeviation();
    double i1 = particles[i - 1].GetDeviation();
    double i2 = particles[i].GetDeviation();
    double i3 = particles[i + 1].GetDeviation();
    double i4 = particles[i + 2].GetDeviation();


    double temp0 = (i4 - i0) / (2 * pow(dx, 3));
    double temp1 = (i3 - i1) / (pow(dx, 3));
    double temp2 = delta * delta * (temp0 - temp1);
    double temp3 = 3 * i2 * (i3 - i1) / dx;
    double temp4 = dt * (temp3 + temp2);
    return i2 - temp4;
}


Soliton::Particle::Particle(double coordinate, double deviation, double speed) {
    SetCoordinate(coordinate);
    SetDeviation(deviation);
    SetSpeed(speed);
}

Soliton::Particle::~Particle() { }

void Soliton::Particle::SetCoordinate(double coordinate) { this->coordinate = coordinate; }

void Soliton::Particle::SetDeviation(double deviation)   { this->deviation = deviation;}

void Soliton::Particle::SetSpeed(double speed)           { this->speed = speed; }

double Soliton::Particle::GetCoordinate()                { return this->coordinate; }

double Soliton::Particle::GetDeviation()                 { return this->deviation; }

double Soliton::Particle::GetSpeed()                     { return this->speed; }