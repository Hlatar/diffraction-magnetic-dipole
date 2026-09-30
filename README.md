# Method of One-Dimensional Integral Equations for the Diffraction of an Electromagnetic Field of a Magnetic Dipole by an Axisymmetric Particle

**Author:** Zhailashev Batyrkhan Bolatuly  
**Supervisor:** N.I. Berezina, PhD in Physics and Mathematics, Senior Researcher  
**Moscow, 2026**

## Overview

This coursework is devoted to the numerical solution of the diffraction problem for the electromagnetic field of a vertical magnetic dipole scattered by an axisymmetric particle. Two models of the particle are considered:

- a particle covered with a thin metallic layer;
- a particle covered with a graphene layer.

The problem is reduced to systems of one-dimensional integral equations along the generatrix of the particle and solved numerically by the collocation method.

## Status

Work in progress. The class skeleton is in place; the method implementations are being filled in.

## Project Structure

- `diffraction.hpp` — class declarations and global parameters.
- `diffraction.cpp` — method implementations (in progress).
- `main.cpp` — entry point.
- `Makefile` — build configuration.

## Build

```bash
make
```

Run:

```bash
make run
```

Clean build artifacts:

```bash
make clean
```

## Roadmap

- [ ] Implement `Generatrix::point`, `Generatrix::dl`, `Generatrix::normal`.
- [ ] Implement the Green's function `Green::G_value` and its derivatives.
- [ ] Implement the dipole source `Source::u0`, `Source::du0_dn`.
- [ ] Assemble the matrix and right-hand side in `CollocationSolver`.
- [ ] Solve the resulting SLAE and validate on a test problem.

## References

1. Dmitriev V.I., Zakharov E.V. *Method of Integral Equations in Computational Electrodynamics*. — Moscow: MAKS Press, 2008, 316 p.
2. Zakharov E.V. *A method for computing axisymmetric electromagnetic fields in inhomogeneous media*. — In: Electromagnetic logging of inhomogeneous media. — Moscow University Press, 1976, pp. 4–12.
3. Zakharov E.V. *A method for solving boundary value problems of electrodynamics for inhomogeneous media with axial symmetry*. — Computational Methods and Programming, vol. 28. — Moscow University Press, 1978, pp. 232–238.