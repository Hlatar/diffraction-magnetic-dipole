#pragma once

#include <complex>
#include <vector>
#include <cstddef>

namespace diffr {

using cd = std::complex<double>;

// ============================================================
// 1. ПАРАМЕТРЫ
// ============================================================
struct Params {
    double omega = 0.0;
    double mu0   = 0.0;
    double eps0  = 0.0;

    cd k0 = 0.0;
    cd k1 = 0.0;
    cd km = 0.0;
    cd k1_gr = 0.0;

    cd     sigma_g = 0.0;
    double z_s     = 0.0;

    double a     = 1.0;
    double b     = 1.0;
    double t_min = 0.0; // t - parameter
    double t_max = 0.0;
};

// ============================================================
// 2. ОБРАЗУЮЩАЯ
// ============================================================
class Generatrix {
public:
    explicit Generatrix(const Params& p);

    void   point(double t, double& rho, double& z) const; // передавать только t остальное высчитывать.
    double dl(double t) const;
    void   normal(double t, double& n_rho, double& n_z) const;

private:
    const Params& p_;
};

// ============================================================
// 3. ФУНКЦИЯ ГРИНА
// ============================================================
class Green {
public:
    Green(const Params& p, int n_phi = 64); // параметры сделать глобальными чтобы не передавать.

    cd G_value(double t, double tm, cd k) const;
    cd dG_drho(double t, double tm, cd k) const;
    cd dG_dz  (double t, double tm, cd k) const;
    cd dG_dn  (double t, double tm, cd k, const Generatrix& gen) const;

private:
    const Params& p_;
    int n_phi_;
    std::vector<double> phi_;  // лучше массивы
    std::vector<double> w_phi_;
};

// ============================================================
// 4. ИСТОЧНИК — ВЕРТИКАЛЬНЫЙ МАГНИТНЫЙ ДИПОЛЬ
// ============================================================
class Source {
public:
    Source(const Params& p, const Generatrix& gen);

    cd u0(double t) const;
    cd du0_dn(double t) const;

private:
    const Params&     p_;
    const Generatrix& gen_;
};

// ============================================================
// 5. КВАДРАТУРА ГАУССА-ЛЕЖАНДРА
// ============================================================
template <typename F>  // взять готовый из gsl , начать лучше с методом трапеции (оставить)
cd gauss_integral(F f, double tL, double tR, int n = 8) {
    static const double x[8] = {
        -0.9602898564975363, -0.7966664774136267,
        -0.5255324099163290, -0.1834346424956498,
         0.1834346424956498,  0.5255324099163290,
         0.7966664774136267,  0.9602898564975363
    };
    static const double w[8] = {
        0.1012285362903763, 0.2223810344533745,
        0.3137066458778873, 0.3626837833783620,
        0.3626837833783620, 0.3137066458778873,
        0.2223810344533745, 0.1012285362903763
    };
    cd sum = 0.0;
    for (int i = 0; i < n; ++i) {
        double t = 0.5*(tR - tL)*x[i] + 0.5*(tR + tL);
        sum += w[i] * f(t);
    }
    return 0.5 * (tR - tL) * sum;
}

// ============================================================
// 6. МЕТОД КОЛЛОКАЦИЙ
// ============================================================
class CollocationSolver {
public:
    enum class Mode { Metal, Graphene };

    CollocationSolver(const Params& p,
                      const Generatrix& gen,
                      const Green& gr,
                      const Source& src,
                      int N = 32,
                      Mode mode = Mode::Metal);

    std::vector<cd> solve() const;

    const std::vector<double>& collocation_points() const { return t_coll_; }
    int                        unknowns_per_point() const {
        return mode_ == Mode::Metal ? 2 : 4;
    }

private:
    void block(double tm, double tL, double tR,
               std::vector<cd>& A) const;

    void assemble(std::vector<cd>& M, int& size) const;
    void rhs(std::vector<cd>& b) const;

    const Params&     p_;
    const Generatrix& gen_;
    const Green&      gr_;
    const Source&     src_;
    int               N_;
    Mode              mode_;

    std::vector<double> t_edges_;
    std::vector<double> t_coll_;
};

// ============================================================
// 7. ПОСТОБРАБОТКА
// ============================================================
cd field_at_point(double rho, double z,
                  const std::vector<cd>& sol,
                  const Params& p,
                  const Generatrix& gen,
                  const Green& gr,
                  const Source& src);

} // namespace diffr