#include "logisticRegressionExample.hpp"

#include "../Utility.hpp"
#include "../Matplotlib.hpp"
#include "../LogisticRegression.hpp"
#include "../SoftmaxRegression.hpp"

int main(){

    auto X_training = readFromCSV( "../Data/X_train_logistic_regression.csv" );
    auto X_test = readFromCSV( "../Data/X_test_logistic_regression.csv" );
    auto y_training = readFromCSV( "../Data/y_train_logistic_regression.csv" );
    auto y_test = readFromCSV( "../Data/y_test_logistic_regression.csv" );

    matplotlib::figure();
    matplotlib::plot
    (
            X_training.col(0).data(), X_training.col(0).data()+X_training.col(0).rows(),
            X_training.col(1).data(), X_training.col(1).data()+X_training.col(1).rows(),
            ".g"
    );
    matplotlib::grid(true);
    matplotlib::show();
    matplotlib::close();

    LogisticRegression model;

    model.train( X_training, y_training, 0.009, 600 );

    auto [w, b] = model.getParameters();
    auto costs = model.getCosts();

    std::cout << "weights:\n";
    std::cout << w << '\n';

    std::cout << "bias:\n";
    std::cout << b << '\n';

    auto yPredictTraining = model.predict(X_training);
    auto yPredictTest = model.predict(X_test);

    std::cout << "Train accuracy: \n";
    std::cout << 100 - (yPredictTraining - y_training).array().abs().mean()*100.0 << "%\n";

    std::cout << "Test accuracy: \n";
    std::cout << 100 - (yPredictTest - y_test).array().abs().mean()*100.0 << "%\n";

    std::cout << model.computeError( X_test, y_test ) << '\n';
    std::cout << model.computeError( X_training, y_training ) << '\n';
    
    return 0;
}