#include <fstream>
#include <iostream>
#include "diffraction.hpp"

using namespace diffr;

int main() {
    // --- настройка параметров (синглтон) ---
    auto& p = Params::get();
    // p.omega = ...;
    // p.mu0   = ...;
    // p.eps0  = ...;
    // p.k0    = ...;
    // p.k1    = ...;
    // p.km    = ...;
    // p.k1_gr = ...;
    // p.sigma_g = ...;
    // p.z_s   = ...;
    // p.t_min = ...;
    // p.t_max = ...;

    Generatrix gen;
    Green      gr(64);
    Source     src;

    // --- металлический слой ---
    CollocationSolver solver_m(gen, gr, src, 32,
                               CollocationSolver::Mode::Metal);
    std::vector<cd> sol_m = solver_m.solve();
    std::cout << "metal: " << sol_m.size() << " unknowns\n";

    // --- слой графена ---
    CollocationSolver solver_g(gen, gr, src, 32,
                               CollocationSolver::Mode::Graphene);
    std::vector<cd> sol_g = solver_g.solve();
    std::cout << "graphene: " << sol_g.size() << " unknowns\n";

    // --- сохранение ---
    std::ofstream fout("solution.dat");
    // TODO: записать sol_m, sol_g

    return 0;
}