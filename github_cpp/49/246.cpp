// linear-regression.cpp : Defines the entry point for the console application.
//

// https://habr.com/company/ods/blog/322076/

#include <iostream>
#include <vector>
#include <numeric>
#include <limits.h>
#include <float.h>
#include <math.h>


namespace {

void generatePolyMembers(
    const std::vector<double>& input,
    int power, int idx, double product, std::vector<double>& result)
{
    if (power == 0)
    {
        if (idx != -1)
            result.push_back(product);
        return;
    }

    if (idx == -1)
    {
        generatePolyMembers(input, power - 1, idx, product, result);
        ++idx;
    }

    for (; idx < input.size(); ++idx)
    {
        generatePolyMembers(input, power - 1, idx, product * input[idx], result);
    }
}

std::vector<double> generatePolyMembers(const std::vector<double>& input, int power)
{
    std::vector<double> result;
    generatePolyMembers(input, power, -1, 1., result);
    return result;
}

int sign(double v)
{
    return (v > 0) ? 1 : ((v < 0) ? -1 : 0);
}

} // namespace

int main()
{
    enum { MAX_POLY_POWER = 3 };

    int numFeatures, numRows;
    std::cin >> numFeatures >> numRows;

    std::vector<std::vector<double>> data;
    std::vector<double> prices;
    for (int i = 0; i < numRows; ++i)
    {
        std::vector<double> row;
        for (int j = 0; j < numFeatures; ++j)
        {
            double v;
            std::cin >> v;
            row.push_back(v);
        }
        data.push_back(generatePolyMembers(row, MAX_POLY_POWER));

        double v;
        std::cin >> v;
        prices.push_back(v);
    }

    const auto num_params = data[0].size();

    std::vector<double> avg(num_params, 0.);
    std::vector<double> dev(num_params, 0.);

    for (const auto& l : data)
    {
        for (int i = 0; i < num_params; ++i)
        {
            avg[i] += l[i];
            dev[i] += l[i] * l[i];
        }
    }

    for (int i = 0; i < num_params; ++i)
    {
        avg[i] /= numRows;
        dev[i] = sqrt(dev[i] / numRows - avg[i] * avg[i]);
    }

    for (auto& l : data)
    {
        for (int i = 0; i < num_params; ++i)
        {
            l[i] = (l[i] - avg[i]) / dev[i];
        }
    }

    for (auto& l : data)
    {
        l.insert(l.begin(), 1.);
    }

    std::vector<double> w(num_params + 1, -1.);

    enum { N_ITER = 100000 };
    
    //const double lambda = 1.;
    const double lambda = .5;
    const double lr = 0.1;

    double prev_sq_dist = DBL_MAX;

    for (int i = 0; i < N_ITER; ++i)
    {
        double sq_dist = 0.;

        std::vector<double> delta_l(num_params + 1, 0.);
        for (int i = 0; i < numRows; ++i)
        {
            const auto& l = data[i];
            const auto delta = std::inner_product(l.begin(), l.end(), w.begin(), 0.) - prices[i];
            sq_dist += delta * delta;
            for (int j = 0; j < delta_l.size(); ++j)
                delta_l[j] += l[j] * delta;
        }

        if (sq_dist >= prev_sq_dist)
            break;
        prev_sq_dist = sq_dist;

        for (int i = 0; i < delta_l.size(); ++i)
        {
            const auto delta = delta_l[i] / numRows + lambda * sign(w[i]);
            w[i] -= lr * delta;
        }
    }

    int num_tests;
    std::cin >> num_tests;

    for (int i = 0; i < num_tests; ++i)
    {
        std::vector<double> row;
        for (int j = 0; j < numFeatures; ++j)
        {
            double v;
            std::cin >> v;
            row.push_back(v);
        }

        auto l = generatePolyMembers(row, MAX_POLY_POWER);
        for (int i = 0; i < num_params; ++i)
        {
            l[i] = (l[i] - avg[i]) / dev[i];
        }
        l.insert(l.begin(), 1.);

        const auto result = std::inner_product(l.begin(), l.end(), w.begin(), 0.);
        std::cout << result << '\n';
    }

    return 0;
}
