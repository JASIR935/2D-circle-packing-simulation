#include "sphere.hpp"
#include <cmath>

namespace cie {

	Sphere2D::Sphere2D(double radius, const std::array<double, 2>& center)
	{
		radius_ = radius;
		center_ = center;
		volume_ = 3.14 * radius * radius;
	}
	double Sphere2D::getRadius() const {
		return radius_;
	}

	double Sphere2D::getVolume() const {
		return volume_;
	}

	const std::array<double, 2>& Sphere2D::getCenter() const {

		return center_;
	}

	Sphere2D& Sphere2D::translate(const std::array<double, 2>& vector) {
		center_[0] += vector[0];
		center_[1] += vector[1];
		return *this;
	}

	double Sphere2D::overlapFactor(const Sphere2D& other)
	{
		double dx = other.center_[0] - center_[0];
		double dy = other.center_[1] - center_[1];

		double distance = std::sqrt(dx * dx + dy * dy);
		double totalRadius = radius_ + other.radius_;

		if (distance >= totalRadius)
			return 0.0;

		return (totalRadius - distance) / totalRadius;

	}

	bool Sphere2D::isInside(const std::array<double, 2>& sideLengths)
	{
		return (center_[0] - radius_ >= 0.00) &&
			(center_[1] - radius_ >= 0.00) &&
			(center_[0] + radius_ <= sideLengths[0]) &&
			(center_[1] + radius_ <= sideLengths[1]);
	}

	Sphere2D& Sphere2D::solveOverlap(Sphere2D& other)
	{
		double dx = other.center_[0] - center_[0];
		double dy = other.center_[1] - center_[1];

		double dxy = std::sqrt(dx * dx + dy * dy);
		double rSum = radius_ + other.radius_;

		const double eps = 1e-4;
		if (dxy < eps)
		{
			// Arbitrarily push this circle a bit in +x direction
			center_[0] += rSum;
			return *this;
		}

		double overlap = rSum - dxy;

		if (overlap <= 0.0)
			return *this;  // no overlap

		// unit vector from i to j
		double ux = dx / dxy;
		double uy = dy / dxy;

		// move THIS sphere (i) away from j
		center_[0] -= overlap * ux;
		center_[1] -= overlap * uy;

		return *this;
	}


	Sphere2D& Sphere2D::moveInside(const std::array<double, 2>& sideLengths)
	{
		if (center_[0] - radius_ < 0.0)
			center_[0] = radius_;

		if (center_[1] - radius_ < 0.0)
			center_[1] = radius_;

		if (center_[0] + radius_ > sideLengths[0])
			center_[0] = sideLengths[0] - radius_;

		if (center_[1] + radius_ > sideLengths[1])
			center_[1] = sideLengths[1] - radius_;

		return *this;
	}

	void Sphere2D::setCenter(const std::array<double, 2>& center)
	{
		center_ = center;
	}

}