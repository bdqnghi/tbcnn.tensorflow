#include "Algorithms/NaiveBayes.h"
#include "Exceptions/MatrixSizeException.h"

#include <iostream>

#include "math.h"

using namespace Medusa;
using namespace arma;
using namespace std;

    int NaiveBayes::learn( mat data, umat classifiers ) {

        colvec classifier = conv_to<colvec>::from( classifiers.col( configuration->classifierColumn ) );

        if ( data.n_cols != configuration->sourceDimensions ) {
            MatrixSizeException exception( "NaiveBayes: Unexpected data dimension" );
            throw exception;
        }

        if ( data.n_rows != classifier.n_rows ) {
            MatrixSizeException exception( "NaiveBayes: The number of data entries and classifiers do not match." );
            throw exception;
        }

        for ( int iter = 0; iter < data.n_rows; iter++ ) {

            rowvec dataRow = data.row( iter );
            GaussianDist* dist = distributions[ classifier.row( iter ) ];

            if ( dist == NULL ) {
                dist = new GaussianDist( dataRow.n_cols );
            }

            dist->count++;
            dist->squaredSum = dist->squaredSum + pow( dataRow, 2 );
            dist->sum = dist->sum + dataRow;

            total->count++;
            total->squaredSum = total->squaredSum + pow( dataRow, 2 );
            total->sum = total->sum + dataRow;


        }
        return 1;

    }

    double NaiveBayes::getBayesNumerator( rowvec data, GaussianDist* dist ) {
        if (
             data.n_cols != ( dist->squaredSum ).n_cols ||
             data.n_cols != ( dist->sum ).n_cols ||
             data.n_cols != ( total->squaredSum ).n_cols ||
             data.n_cols != ( total->sum ).n_cols
             ) {

            MatrixSizeException exception( "NaiveBayes: data dimensions do not match stored distributions" );
            throw exception;
        }

        rowvec distMean = ( dist->sum ) / ( dist->count );
        rowvec distVar = pow( ( ( dist->squaredSum ) / dist->count ), 2 ) - pow( distMean, 2 );

        rowvec gaussianScale = ( 1 / sqrt( 2 * 3.1415 * distVar ) );
        rowvec gaussian = exp( ( -pow( ( data - distMean ), 2 ) ) / ( 2 * distVar ) );

        // The probability of each feature given this classification
        rowvec featureProbabilities = gaussianScale % gaussian;

        // Simplest way to multiply these probabilities is to take log, sum, and then exp.
        rowvec logProb = log( featureProbabilities );
        double logProbSum = accu( logProb );
        double multProb = exp( logProbSum );

        //Now need to scale by probability of that class.

        double probability = ( dist->count / total->count ) * multProb;

        return probability;
    }

    mat NaiveBayes::run( mat input ) {
        if ( input.n_cols != configuration->sourceDimensions ) {
            MatrixSizeException exception( "NaiveBayes: Unexpected data dimension" );
            throw exception;
        }

        map< unsigned int, GaussianDist*>::iterator distIter;

        mat resultSet;

        for ( int dataIter = 0; dataIter < input.n_rows; dataIter++ ) {
            unsigned int bestClass;
            double bestNumerator;

            rowvec data = input.row( dataIter );
            for ( distIter = distributions.begin( ); distIter != distributions.end( ); distIter++ ) {
                double numerator = getBayesNumerator( data, distIter->second );
                if ( numerator > bestNumerator ) {
                    bestClass = distIter->first;
                    bestNumerator = numerator;
                }
            }

            rowvec result = zeros( data.n_cols + 1 );
            result.cols( 1, result.n_cols ) = data;
            result.col( 0 ) = bestClass;
            resultSet.row( dataIter ) = result;
        }
        
        return resultSet;
    }

    NaiveBayes::NaiveBayes( NaiveBayesConfig config ) {
        configuration = new NaiveBayesConfig();
        *configuration = config;
        total = new GaussianDist( configuration->sourceDimensions );
    }

    NaiveBayes::~NaiveBayes( ) {
    }

    MatrixFormat NaiveBayes::getInputFormat( ) {
        MatrixFormat format;
        format.format = DOUBLE;
        format.size = configuration->sourceDimensions;
        return format;
    }

    MatrixFormat NaiveBayes::getOutputFormat( ) {
        MatrixFormat format;
        format.format = DOUBLE;
        format.size = configuration->sourceDimensions + 1;
        return format;
    }
