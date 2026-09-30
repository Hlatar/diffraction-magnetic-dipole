#include "diffraction.hpp"
#include <cmath>
#include <stdexcept>

namespace diffr {

// ============================================================
// Generatrix
// ============================================================
Generatrix::Generatrix(const Params& p) : p_(p) {}

void Generatrix::point(double t, double& rho, double& z) const {
    // TODO
}

double Generatrix::dl(double t) const {
    // TODO
    return 0.0;
}

void Generatrix::normal(double t, double& n_rho, double& n_z) const {
    // TODO
}

// ============================================================
// Green
// ============================================================
Green::Green(const Params& p, int n_phi)
    : p_(p), n_phi_(n_phi), phi_(n_phi), w_phi_(n_phi)
{
    // TODO: заполнить phi_, w_phi_
}

cd Green::G_value(double t, double tm, cd k) const {
    // TODO
    return 0.0;
}

cd Green::dG_drho(double t, double tm, cd k) const {
    // TODO
    return 0.0;
}

cd Green::dG_dz(double t, double tm, cd k) const {
    // TODO
    return 0.0;
}

cd Green::dG_dn(double t, double tm, cd k, const Generatrix& gen) const {
    // TODO
    return 0.0;
}

// ============================================================
// Source
// ============================================================
Source::Source(const Params& p, const Generatrix& gen)
    : p_(p), gen_(gen) {}

cd Source::u0(double t) const {
    // TODO
    return 0.0;
}

cd Source::du0_dn(double t) const {
    // TODO
    return 0.0;
}

// ============================================================
// CollocationSolver
// ============================================================
CollocationSolver::CollocationSolver(const Params& p,
                                     const Generatrix& gen,
                                     const Green& gr,
                                     const Source& src,
                                     int N, Mode mode)
    : p_(p), gen_(gen), gr_(gr), src_(src), N_(N), mode_(mode)
{
    // TODO: заполнить t_edges_, t_coll_
}

void CollocationSolver::block(double tm, double tL, double tR,
                              std::vector<cd>& A) const
{
    // TODO
}

void CollocationSolver::assemble(std::vector<cd>& M, int& size) const {
    // TODO
}

void CollocationSolver::rhs(std::vector<cd>& b) const {
    // TODO
}

std::vector<cd> CollocationSolver::solve() const {
    // TODO
    return {};
}

// ============================================================
// Постобработка
// ============================================================
cd field_at_point(double rho, double z,
                  const std::vector<cd>& sol,
                  const Params& p,
                  const Generatrix& gen,
                  const Green& gr,
                  const Source& src)
{
    // TODO
    return 0.0;
}

} // namespace diffr