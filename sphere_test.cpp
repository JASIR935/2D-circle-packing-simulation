#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <array>
#include <cmath>
#include <iostream>

#include "sphere.hpp"


namespace cie
{

    TEST_CASE("Sphere2D Translation")
    {
        Sphere2D sphere(1.0, { 0.0, 0.0 });
        std::array<double, 2> translationVector = { 2.0, 3.0 };

        sphere.translate(translationVector);

        double tolerance = 1e-14;
        REQUIRE(sphere.getCenter()[0] == Approx(2.0).epsilon(tolerance));
        REQUIRE(sphere.getCenter()[1] == Approx(3.0).epsilon(tolerance));
    }

    TEST_CASE("Sphere2d Overlap Factor")
    {
        Sphere2D sphere1(1.0, { 0.0, 0.0 });
        Sphere2D sphere2(1.0, { 1.5, 0.0 }); // partial overlap
        Sphere2D sphere3(1.0, { 3.0, 0.0 }); // no overlap
        Sphere2D sphere4(1.0, { 0.0, 0.0 }); // full overlap

        double tolerance = 1e-6;

        REQUIRE(sphere1.overlapFactor(sphere2) == Approx(0.25).epsilon(tolerance));
        REQUIRE(sphere1.overlapFactor(sphere3) == Approx(0.0).epsilon(tolerance));
        REQUIRE(sphere1.overlapFactor(sphere4) == Approx(1.0).epsilon(tolerance));
    }

    TEST_CASE("Sphere2d isInside")
    {
        std::array<double, 2> sideLengths = { 2.0, 1.0 };

        Sphere2D sphere1(1.0, { 1.0, 0.5 }); // inside
        Sphere2D sphere2(1.0, { 0.0, 0.5 }); // outside left
        Sphere2D sphere3(1.0, { 2.0, 0.5 }); // outside right
        Sphere2D sphere4(1.0, { 1.0, 0.0 }); // outside bottom
        Sphere2D sphere5(1.0, { 1.0, 1.0 }); // outside top
    }

    TEST_CASE("Sphere2d solveOverlap")
    {
        Sphere2D sphere1(1.0, { 0.0, 0.0 });
        Sphere2D sphere2(1.0, { 1.0, 0.0 });
        Sphere2D sphere3(1.0, { -1.0, 0.5 });

        double tolerance = 1e-6;

        sphere1.solveOverlap(sphere2);
        REQUIRE(sphere1.getCenter()[0] == Approx(-1.0).epsilon(tolerance));
        REQUIRE(sphere1.getCenter()[1] == Approx(0.0).epsilon(tolerance));

        sphere1.solveOverlap(sphere3);
        REQUIRE(sphere1.getCenter()[0] == Approx(-1.0).epsilon(tolerance));
        REQUIRE(sphere1.getCenter()[1] == Approx(-1.5).epsilon(tolerance));
    }


    TEST_CASE("Sphere2d moveInside with rectangle")
    {
        std::array<double, 2> sideLengths = { 2.0, 1.0 }; // non-square rectangle
        double tolerance = 1e-6;

        cie::Sphere2D sphere(0.5, { 0.0, 0.0 }); // outside left-bottom
        sphere.moveInside(sideLengths);

        REQUIRE(sphere.getCenter()[0] == Approx(0.5).epsilon(tolerance));
        REQUIRE(sphere.getCenter()[1] == Approx(0.5).epsilon(tolerance));

        sphere.setCenter({ 4.0, 0.5 }); // outside right
        sphere.moveInside(sideLengths);

        REQUIRE(sphere.getCenter()[0] == Approx(1.5).epsilon(tolerance));
        REQUIRE(sphere.getCenter()[1] == Approx(0.5).epsilon(tolerance));

        sphere.setCenter({ 1.0, 0.5 }); // inside
        sphere.moveInside(sideLengths);
        REQUIRE(sphere.getCenter()[0] == Approx(1.0).epsilon(tolerance));
        REQUIRE(sphere.getCenter()[1] == Approx(0.5).epsilon(tolerance));
    }


} // namespace cie