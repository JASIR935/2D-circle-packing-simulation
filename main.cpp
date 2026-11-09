#include "sphere.hpp"

#include <array>
#include <vector>
#include <random>
#include <fstream>
#include <iostream>
#include <cmath>

using cie::Sphere2D;

int main()
{

    // Domain + target porosity


    const std::array<double, 2> sideLengths = { 100.0, 200.0 };   // Lx = 100, Ly = 200
    const double R = 5.0;                                         // circle radius


    const double epsilon = 0.2;
    const double solidFraction = 1.0 - epsilon;


    const double areaDomain = sideLengths[0] * sideLengths[1];


    const double areaCircle = (22.0 / 7.0) * std::pow(R, 2);


    const double coveredArea = (solidFraction * areaDomain) / areaCircle;
    const std::size_t numCircles = static_cast<std::size_t>(coveredArea);

    std::cout << "Number of circles = " << numCircles << "\n";
    std::cout << "Domain area = " << areaDomain << "\n";
    std::cout << "Circle area = " << areaCircle << "\n";


    // Store circles in a vector

    std::vector<Sphere2D> circle;
    circle.reserve(numCircles);


    //  Random initial placement


    std::mt19937 rng(42);


    std::uniform_real_distribution<double> distX(R, sideLengths[0] - R);
    std::uniform_real_distribution<double> distY(R, sideLengths[1] - R);

    for (std::size_t i = 0; i < numCircles; ++i)
    {

        double x = distX(rng);
        double y = distY(rng);

        std::array<double, 2> center = { x, y };


        circle.emplace_back(R, center);
    }


    //  Resolve overlaps iteratively (relaxation)

    const int    maxIterations = 40000;

    const double overlapTol = 1e-3;

    int iter = 0;

    for (; iter < maxIterations; ++iter)
    {
        bool anyOverlap = false;




        for (std::size_t i = 0; i < numCircles; ++i)
        {
            for (std::size_t j = i + 1; j < numCircles; ++j)
            {

                double f = circle[i].overlapFactor(circle[j]);

                if (f > overlapTol)
                {
                    anyOverlap = true;

                    // Current centers of circles i and j
                    auto ci = circle[i].getCenter();
                    auto cj = circle[j].getCenter();

                    double dx = cj[0] - ci[0];
                    double dy = cj[1] - ci[1];
                    double dist = std::sqrt(dx * dx + dy * dy);

                    if (dist < 1e-12)
                        continue;

                    double nx = dx / dist;
                    double ny = dy / dist;


                    double rSum = circle[i].getRadius() + circle[j].getRadius();
                    double overlapLength = f * rSum;

                    double shift = 0.5 * overlapLength;


                    circle[i].translate({ -nx * shift, -ny * shift });

                    circle[j].translate({ nx * shift,  ny * shift });


                    circle[i].moveInside(sideLengths);
                    circle[j].moveInside(sideLengths);
                }
            }
        }


        // Ensure all circles are inside domain

        bool allInside = true;
        for (std::size_t i = 0; i < numCircles; ++i)
        {
            if (!circle[i].isInside(sideLengths))
            {
                allInside = false;
                circle[i].moveInside(sideLengths);
            }
        }


        if (!anyOverlap && allInside)
            break;
    }

    std::cout << "Finished in " << iter << " iterations.\n";
    if (iter >= maxIterations)
        std::cout << "WARNING: maxIterations reached; configuration may still have small overlaps.\n";


    //  Export packing to CSV for plotting


    std::ofstream file("packing.csv");
    if (!file)
    {
        std::cerr << "ERROR: Could not open packing.csv for writing!\n";
        return 1;
    }

    file << "R,x,y\n";

    for (const auto& c : circle)
    {
        file << c.getRadius() << ","
            << c.getCenter()[0] << ","
            << c.getCenter()[1] << "\n";
    }

    file.close();
    std::cout << "Packing written to packing.csv\n";

    return 0;
}
