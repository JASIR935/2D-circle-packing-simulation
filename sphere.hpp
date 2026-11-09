
#ifndef SPHERE2D_HPP
#define SPHERE2D_HPP

#include <array>

namespace cie {

class Sphere2D {
private:
    std::array<double, 2> center_;
    double radius_;
    double volume_;

public:
    // Constructor
    Sphere2D(double radius, const std::array<double, 2>& center);

    // Move the sphere by adding a vector to its center
    Sphere2D& translate(const std::array<double, 2>& vector);

    // Checking the overlapping (read-only function)
    double overlapFactor(const Sphere2D& other);

    // Check if the sphere is inside a box
    bool isInside(const std::array<double, 2>& sideLengths);

    // Try to resolve overlap between two spheres
    Sphere2D& solveOverlap(Sphere2D& other);

    // Move the sphere so it is inside the box
    Sphere2D& moveInside(const std::array<double, 2>& sideLengths);

    // Set a new center
    void setCenter(const std::array<double, 2>& center);

    // Getters
    const std::array<double, 2>& getCenter() const;
    double getRadius() const;
    double getVolume() const;
};

} // namespace cie

#endif // SPHERE2D_HPP

