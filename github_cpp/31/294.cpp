
extern "C" {
#include "../pla.h"
}

#include <gtest/gtest.h>
#include <iostream>


class Linear_Algebra_Mat_Mul_Mat_ : public testing::Test {
    void SetUp() {

    }
    void TearDown() {

    }
public:
    const float tolerance = 0.00000001f;
    mat2x2 mat2_zero {{0,0},{0,0}};
    mat3x3 mat3_zero {{0,0,0},{0,0,0},{0,0,0}};
    mat4x4 mat4_zero {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    mat5x5 mat5_zero {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
    mat6x6 mat6_zero {{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0}};
    mat2x2 mat2A     {{0,1},{2,3}};
    mat3x3 mat3A     {{0,1,2},{3,4,5},{6,7,8}};
    mat4x4 mat4A     {{0,1,2,3},{4,5,6,7},{8,9,10,11},{12,13,14,15}};
    mat5x5 mat5A     {{0,1,2,3,4},{5,6,7,8,9},{10,11,12,13,14},{15,16,17,18,19},{20,21,22,23,24}};
    mat6x6 mat6A     {{0,1,2,3,4,5},{6,7,8,9,10,11},{12,13,14,15,16,17},{18,19,20,21,22,23},{24,25,26,27,28,29},{30,31,32,33,34,35}};
    mat2x2 mat2B     {{0,1},{2,3}};
    mat3x3 mat3B     {{0,1,2},{3,4,5},{6,7,8}};
    mat4x4 mat4B     {{0,1,2,3},{4,5,6,7},{8,9,10,11},{12,13,14,15}};
    mat5x5 mat5B     {{0,1,2,3,4},{5,6,7,8,9},{10,11,12,13,14},{15,16,17,18,19},{20,21,22,23,24}};
    mat6x6 mat6B     {{0,1,2,3,4,5},{6,7,8,9,10,11},{12,13,14,15,16,17},{18,19,20,21,22,23},{24,25,26,27,28,29},{30,31,32,33,34,35}};
};

TEST_F(Linear_Algebra_Mat_Mul_Mat_, Three_And_Four_Square_Mat_New_Mat_Cross_Mat_Test) {
    mat2x2 mat2_expected {{2,3},{6,11}};
    mat3x3 mat3_expected {{15,18,21},{42,54,66},{69,90,111}};
    mat4x4 mat4_expected {{56,62,68,74},{152,174,196,218},{248,286,324,362},{344,398,452,506}};
    mat5x5 mat5_expected {{150,160,170,180,190},{400,435,470,505,540},{650,710,770,830,890},{900,985,1070,1155,1240},{1150,1260,1370,1480,1590}};
    mat6x6 mat6_expected {{330,345,360,375,390,405},{870,921,972,1023,1074,1125},{1410,1497,1584,1671,1758,1845},{1950,2073,2196,2319,2442,2565},{2490,2649,2808,2967,3126,3285},{3030,3225,3420,3615,3810,4005}};

    mat2x2 mat2_result; mat2x2_copy(mat2_result, mat2_zero);
    mat3x3 mat3_result; mat3x3_copy(mat3_result, mat3_zero);
    mat4x4 mat4_result; mat4x4_copy(mat4_result, mat4_zero);
    mat5x5 mat5_result; mat5x5_copy(mat5_result, mat5_zero);
    mat6x6 mat6_result; mat6x6_copy(mat6_result, mat6_zero);

    mat2x2_mul_n(mat2_result, mat2A, mat2B);
    mat3x3_mul_n(mat3_result, mat3A, mat3B);
    mat4x4_mul_n(mat4_result, mat4A, mat4B);
    mat5x5_mul_n(mat5_result, mat5A, mat5B);
    mat6x6_mul_n(mat6_result, mat6A, mat6B);

    for (std::size_t size=2; size<7; ++size) {
        for (std::size_t row = 0; row<size; ++row) {
            for (std::size_t col = 0; col<size; ++col) {
                if (size == 2) EXPECT_NEAR(mat2_expected[row][col], mat2_result[row][col], tolerance) << "Matrix: "<< size << " Row: " << row << " Col: " << col;
                if (size == 3) EXPECT_NEAR(mat3_expected[row][col], mat3_result[row][col], tolerance) << "Matrix: "<< size << " Row: " << row << " Col: " << col;
                if (size == 4) EXPECT_NEAR(mat4_expected[row][col], mat4_result[row][col], tolerance) << "Matrix: "<< size << " Row: " << row << " Col: " << col;
                if (size == 5) EXPECT_NEAR(mat5_expected[row][col], mat5_result[row][col], tolerance) << "Matrix: "<< size << " Row: " << row << " Col: " << col;
                if (size == 6) EXPECT_NEAR(mat6_expected[row][col], mat6_result[row][col], tolerance) << "Matrix: "<< size << " Row: " << row << " Col: " << col;
            }
        }
    }
}

TEST_F(Linear_Algebra_Mat_Mul_Mat_, Three_And_Four_Square_Mat_Inline_Mat_Cross_Mat_Test) {
    mat2x2 mat2_expected {{2,3},{6,11}};
    mat3x3 mat3_expected {{15,18,21},{42,54,66},{69,90,111}};
    mat4x4 mat4_expected {{56,62,68,74},{152,174,196,218},{248,286,324,362},{344,398,452,506}};
    mat5x5 mat5_expected {{150,160,170,180,190},{400,435,470,505,540},{650,710,770,830,890},{900,985,1070,1155,1240},{1150,1260,1370,1480,1590}};
    mat6x6 mat6_expected {{330,345,360,375,390,405},{870,921,972,1023,1074,1125},{1410,1497,1584,1671,1758,1845},{1950,2073,2196,2319,2442,2565},{2490,2649,2808,2967,3126,3285},{3030,3225,3420,3615,3810,4005}};

    mat2x2_mul(mat2A, mat2B);
    mat3x3_mul(mat3A, mat3B);
    mat4x4_mul(mat4A, mat4B);
    mat5x5_mul(mat5A, mat5B);
    mat6x6_mul(mat6A, mat6B);

    for (std::size_t size = 2; size<7; ++size) {
        for (std::size_t row = 0; row < size; ++row) {
            for (std::size_t col = 0; col < size; ++col) {
                if (size == 2) EXPECT_NEAR(mat2_expected[row][col], mat2A[row][col], tolerance) << "Matrix: " << size << " Row: " << row << " Col: " << col;
                if (size == 3) EXPECT_NEAR(mat3_expected[row][col], mat3A[row][col], tolerance) << "Matrix: " << size << " Row: " << row << " Col: " << col;
                if (size == 4) EXPECT_NEAR(mat4_expected[row][col], mat4A[row][col], tolerance) << "Matrix: " << size << " Row: " << row << " Col: " << col;
                if (size == 5) EXPECT_NEAR(mat5_expected[row][col], mat5A[row][col], tolerance) << "Matrix: " << size << " Row: " << row << " Col: " << col;
                if (size == 6) EXPECT_NEAR(mat6_expected[row][col], mat6A[row][col], tolerance) << "Matrix: " << size << " Row: " << row << " Col: " << col;
            }
        }
    }
}

TEST_F(Linear_Algebra_Mat_Mul_Mat_, Three_And_Four_Square_Mat_New_And_Return_Mat_Cross_Mat_Test) {
    mat2x2 mat2_expected {{2,3},{6,11}};
    mat3x3 mat3_expected {{15,18,21},{42,54,66},{69,90,111}};
    mat4x4 mat4_expected {{56,62,68,74},{152,174,196,218},{248,286,324,362},{344,398,452,506}};
    mat5x5 mat5_expected {{150,160,170,180,190},{400,435,470,505,540},{650,710,770,830,890},{900,985,1070,1155,1240},{1150,1260,1370,1480,1590}};
    mat6x6 mat6_expected {{330,345,360,375,390,405},{870,921,972,1023,1074,1125},{1410,1497,1584,1671,1758,1845},{1950,2073,2196,2319,2442,2565},{2490,2649,2808,2967,3126,3285},{3030,3225,3420,3615,3810,4005}};

    vec2 * mat2_result = mat2x2_mul_nr(mat2_zero, mat2A, mat2B);
    vec3 * mat3_result = mat3x3_mul_nr(mat3_zero, mat3A, mat3B);
    vec4 * mat4_result = mat4x4_mul_nr(mat4_zero, mat4A, mat4B);
    vec5 * mat5_result = mat5x5_mul_nr(mat5_zero, mat5A, mat5B);
    vec6 * mat6_result = mat6x6_mul_nr(mat6_zero, mat6A, mat6B);

    for (std::size_t size=2; size<7; ++size) {
        for (std::size_t row = 0; row<size; ++row) {
            for (std::size_t col = 0; col<size; ++col) {
                if (size == 2) EXPECT_NEAR(mat2_expected[row][col], mat2_result[row][col], tolerance) << "Matrix: "<< size << " Row: " << row << " Col: " << col;
                if (size == 3) EXPECT_NEAR(mat3_expected[row][col], mat3_result[row][col], tolerance) << "Matrix: "<< size << " Row: " << row << " Col: " << col;
                if (size == 4) EXPECT_NEAR(mat4_expected[row][col], mat4_result[row][col], tolerance) << "Matrix: "<< size << " Row: " << row << " Col: " << col;
                if (size == 5) EXPECT_NEAR(mat5_expected[row][col], mat5_result[row][col], tolerance) << "Matrix: "<< size << " Row: " << row << " Col: " << col;
                if (size == 6) EXPECT_NEAR(mat6_expected[row][col], mat6_result[row][col], tolerance) << "Matrix: "<< size << " Row: " << row << " Col: " << col;
            }
        }
    }
}

TEST_F(Linear_Algebra_Mat_Mul_Mat_, Three_And_Four_Square_Mat_Return_Mat_Cross_Mat_Test) {
    mat2x2 mat2_expected {{2,3},{6,11}};
    mat3x3 mat3_expected {{15,18,21},{42,54,66},{69,90,111}};
    mat4x4 mat4_expected {{56,62,68,74},{152,174,196,218},{248,286,324,362},{344,398,452,506}};
    mat5x5 mat5_expected {{150,160,170,180,190},{400,435,470,505,540},{650,710,770,830,890},{900,985,1070,1155,1240},{1150,1260,1370,1480,1590}};
    mat6x6 mat6_expected {{330,345,360,375,390,405},{870,921,972,1023,1074,1125},{1410,1497,1584,1671,1758,1845},{1950,2073,2196,2319,2442,2565},{2490,2649,2808,2967,3126,3285},{3030,3225,3420,3615,3810,4005}};

    vec2 * mat2_result = mat2x2_mul_r(mat2A, mat2B);
    vec3 * mat3_result = mat3x3_mul_r(mat3A, mat3B);
    vec4 * mat4_result = mat4x4_mul_r(mat4A, mat4B);
    vec5 * mat5_result = mat5x5_mul_r(mat5A, mat5B);
    vec6 * mat6_result = mat6x6_mul_r(mat6A, mat6B);

    for (std::size_t size=2; size<7; ++size) {
        for (std::size_t row = 0; row<size; ++row) {
            for (std::size_t col = 0; col<size; ++col) {
                if (size == 2) EXPECT_NEAR(mat2_expected[row][col], mat2_result[row][col], tolerance) << "Matrix: "<< size << " Row: " << row << " Col: " << col;
                if (size == 3) EXPECT_NEAR(mat3_expected[row][col], mat3_result[row][col], tolerance) << "Matrix: "<< size << " Row: " << row << " Col: " << col;
                if (size == 4) EXPECT_NEAR(mat4_expected[row][col], mat4_result[row][col], tolerance) << "Matrix: "<< size << " Row: " << row << " Col: " << col;
                if (size == 5) EXPECT_NEAR(mat5_expected[row][col], mat5_result[row][col], tolerance) << "Matrix: "<< size << " Row: " << row << " Col: " << col;
                if (size == 6) EXPECT_NEAR(mat6_expected[row][col], mat6_result[row][col], tolerance) << "Matrix: "<< size << " Row: " << row << " Col: " << col;
            }
        }
    }
}

