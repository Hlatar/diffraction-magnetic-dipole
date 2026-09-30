#include <fstream>
#include <iostream>
#include "diffraction.hpp"

using namespace diffr;

int main() {
    Params     p;
    Generatrix gen(p);
    Green      gr(p);
    Source     src(p, gen);

    // --- металлический слой ---
    CollocationSolver solver_m(p, gen, gr, src, 32,
                               CollocationSolver::Mode::Metal);
    std::vector<cd> sol_m = solver_m.solve();
    std::cout << "metal: " << sol_m.size() << " unknowns\n";

    // --- слой графена ---
    CollocationSolver solver_g(p, gen, gr, src, 32,
                               CollocationSolver::Mode::Graphene);
    std::vector<cd> sol_g = solver_g.solve();
    std::cout << "graphene: " << sol_g.size() << " unknowns\n";

    // --- сохранение ---
    std::ofstream fout("solution.dat");
    // TODO: записать sol_m, sol_g

    return 0;
}