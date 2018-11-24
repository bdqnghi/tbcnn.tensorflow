#include "LogisticRegression.hpp"

#include "Utility.hpp"

class LogisticRegression::impl{

    Eigen::VectorXd weights{};
    std::vector<double> costs{};
    Eigen::MatrixXd::Index nFeatures = 0;
    Eigen::MatrixXd::Index nTrainings = 0;
    double bias = 0;

    Eigen::MatrixXd computeSigmoid
    (
            Eigen::MatrixXd const& a
    )
    {
        return 1.0/( (-1.0*a.array()).exp() + 1 );
    }

    void initializeParameters ( bool nonZeroRandom );

public:

    impl() = default;

    void train
    (
            Eigen::MatrixXd const& X,
            Eigen::MatrixXd const& y,
            double learningRate,
            Eigen::MatrixXd::Index nIterations
    );

    Eigen::VectorXd predict
    (
            Eigen::MatrixXd const& X
    );
    
    double computeError
    (
            Eigen::MatrixXd const& XObservation,
            Eigen::MatrixXd const& yTarget
    );
    
    std::tuple<Eigen::MatrixXd, double>
    getParameters() const
    {
        return { weights, bias };
    }

    std::vector<double> const&
    getCosts() const
    {
        return costs;
    }
};

void LogisticRegression::impl::initializeParameters
( bool nonZeroRandom )
{
    if(!nonZeroRandom)
    {
        weights = Eigen::VectorXd::Zero(nFeatures);
        bias = 0.0;
    }
    else
    {
        auto limit = 1.0/std::sqrt(nFeatures);
        weights = generateUniform(nFeatures, 1, -limit, limit);
        bias = generateUniform(1, 1, -limit, limit)(0, 0);
    }
}

void LogisticRegression::impl::train
(         
        Eigen::MatrixXd const& X,
        Eigen::MatrixXd const& y,
        double learningRate,
        Eigen::MatrixXd::Index nIterations
)
{
    nFeatures = X.cols();
    nTrainings = X.rows();
    ASSERT( nTrainings == y.rows() );
    initializeParameters(false);

    costs = std::vector<double>(nIterations);
    for (Eigen::MatrixXd::Index i = 0; i < nIterations; ++i)
    {
        auto yPredict = computeSigmoid( (X*weights).array() + bias );
        auto error = yPredict - y;
        costs[i] = -1*
                   (
                           y.array()*yPredict.array().log()
                           +
                           (1.0-y.array())*(1.0-yPredict.array()).log()
                   ).mean();
        weights -= learningRate * (1.0/nTrainings)*X.transpose()*error;
        bias -= learningRate * (1.0/nTrainings)*error.sum();
    }
}

Eigen::VectorXd LogisticRegression::impl::predict
(         
        Eigen::MatrixXd const& X
)
{
    return computeSigmoid
            (
                    (X*weights).array() + bias
            ).unaryExpr
            (
                    [](auto value)
                    {
                        return value > 0.5 ? 1.0 : 0.0;
                    }
            );
}

double LogisticRegression::impl::computeError
(         
        Eigen::MatrixXd const& XObservation,
        Eigen::MatrixXd const& yTarget
)
{
    auto yPredict = computeSigmoid( (XObservation*weights).array() + bias );
    return -1*
           (
                   yTarget.array()*yPredict.array().log()
                   +
                   (1.0-yTarget.array())*(1.0-yPredict.array()).log()
           ).mean();
}

void LogisticRegression::train
(
        Eigen::MatrixXd const& X,
        Eigen::MatrixXd const& y,
        double learningRate,
        Eigen::MatrixXd::Index nIterations
)
{
    pimpl->train(X, y, learningRate, nIterations);
}

Eigen::VectorXd LogisticRegression::predict
(
        Eigen::MatrixXd const& X
)
{
    return pimpl->predict(X);
}

double LogisticRegression::computeError
(
        Eigen::MatrixXd const& XObservation,
        Eigen::MatrixXd const& yTarget
)
{
    return pimpl->computeError( XObservation, yTarget );
}

std::tuple<Eigen::MatrixXd, double>
LogisticRegression::getParameters() const
{
    return pimpl->getParameters();
}

std::vector<double> const&
LogisticRegression::getCosts() const
{
    return pimpl->getCosts();
}

LogisticRegression::LogisticRegression()
                   :pimpl{std::make_unique<impl>()}{
}

LogisticRegression::~LogisticRegression() = default;

LogisticRegression& LogisticRegression::operator=( LogisticRegression&& ) = default;