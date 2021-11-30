#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <fstream>

double integrate_trap(const std::vector<double>& F, double h)
{
    double sum = 0.0;
    sum = std::accumulate(F.begin(), F.end() - 1, std::move(sum));
    sum = std::accumulate(F.begin() + 1, F.end(), std::move(sum));
    return h * sum / 2.0;
}

double integrate_simp(const std::vector<double>& F, double h)
{
    double sum = 0.0;
    for(size_t i = 1; i + 1 < F.size(); ++i)
    {
        if(i % 2 == 1) sum += 4.0 * F[i];
        else sum += 2.0 * F[i];
    }
    sum += *F.begin();
    sum += *F.rbegin();
    return h * sum / 3.0;
}

double extrapol_rich(double I1, double I2, int p)
{
    return I1 + (I1 - I2) / (std::pow(2.0, p) - 1.0);
}

int main()
{
    double h = 0.125;
    std::vector<double> F{0, 0.021470, 0.293050, 0.494105,
                          0.541341, 0.516855, 0.468617,
                          0.416531, 0.367879};

    double I1 = integrate_trap(F, h);
    double h2 = 2.0 * h;
    std::vector<double> F2(F.size() / 2 + 1);
    for(size_t i = 0; i < F.size(); i += 2)
    {
        F2[i / 2] = F[i];
    }
    double I2 = integrate_trap(F2, h2);
    double Ir = extrapol_rich(I1, I2, 2);

    double Is = integrate_simp(F, h);

    std::ofstream fout;
    fout.open("out.txt");

    fout << "Trapezoid integrate: " << I1 << " " << I2 << std::endl;
    fout << "Trapezoid integrate with Richarson correction: " << Ir << std::endl;
    fout << "Simpson integrate: " << Is << std::endl;

    fout.close();
    return 0;
}
