/*
 * Copyright (C) 2017 RTAndroid Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package rtandroid.benchmark.benchmarks;

public class MatrixMultiplication implements Benchmark
{
    private static final String NAME = "Matrix-Multiplication";
    private static final int MATRIX_SIZE = 10;

    private final long mMatrix[][] = new long[MATRIX_SIZE][MATRIX_SIZE];

    @Override
    public void execute(int parameter)
    {
        for (int i = 0; i < MATRIX_SIZE; i++) { mMatrix[i][i] = System.currentTimeMillis(); }

        for (int i = 0; i < parameter; i++)
         for (int k = 0; k < MATRIX_SIZE; k++)
          for (int j = 0; j < MATRIX_SIZE; j++)
           for (int m = 0; m < MATRIX_SIZE; m++) { mMatrix[k][j] = mMatrix[k][m] * mMatrix[j][m]; }
    }

    @Override
    public String getName()
    {
        return NAME;
    }
}
