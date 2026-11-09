# 2D Circle Packing Simulation – C++

This project was developed as part of the *Computation in Engineering 1* coursework at the Technical University of Munich (TUM).

The objective was to generate a random packing of circles inside a rectangular domain with a target porosity of 0.2.

I implemented a `Sphere2D` class in C++ with different functions for calculating circle properties, checking overlaps, moving circle centres, resolving overlaps and ensuring that all circles remain within the domain boundaries.

The main program generates random initial circle positions and uses an iterative algorithm to detect and resolve overlaps by adjusting the centres of the circles. The final circle positions and radii are exported to a CSV file, which can also be visualised using a Python script.
