#include <gtest/gtest.h>
#include "levenshtein.hpp"

TEST(LevenshteinDistance, FirstStringIsEmpty) {
    EXPECT_EQ(5, levenshteinDistance("", "world"));
}

TEST(LevenshteinDistance, SecondStringIsEmpty) {
    EXPECT_EQ(5, levenshteinDistance("hello", ""));
}

TEST(LevenshteinDistance, EqualStrings) {
    EXPECT_EQ(0, levenshteinDistance("bamboozled", "bamboozled"));
}

TEST(LevenshteinDistance, DeleteCharactersFromFirstStringUntilEqual) {
    EXPECT_EQ(4, levenshteinDistance("bamboozled", "bamboo"));
    EXPECT_EQ(3, levenshteinDistance("bamboozle", "bamboo"));
    EXPECT_EQ(2, levenshteinDistance("bamboozl", "bamboo"));
    EXPECT_EQ(1, levenshteinDistance("bambooz", "bamboo"));
    EXPECT_EQ(0, levenshteinDistance("bamboo", "bamboo"));
}

TEST(LevenshteinDistance, DeleteCharactersFromSecondStringUntilEqual) {
    EXPECT_EQ(4, levenshteinDistance("bamboo", "bamboozled"));
    EXPECT_EQ(3, levenshteinDistance("bamboo", "bamboozle"));
    EXPECT_EQ(2, levenshteinDistance("bamboo", "bamboozl"));
    EXPECT_EQ(1, levenshteinDistance("bamboo", "bambooz"));
    EXPECT_EQ(0, levenshteinDistance("bamboo", "bamboo"));
}

TEST(LevenshteinDistance, SubstituteCharactersUntilEqual) {
    EXPECT_EQ(3, levenshteinDistance("foo", "bar"));
    EXPECT_EQ(2, levenshteinDistance("foo", "bao"));
    EXPECT_EQ(1, levenshteinDistance("foo", "boo"));
    EXPECT_EQ(0, levenshteinDistance("foo", "foo"));
}

TEST(LevenshteinDistance, CombinedSubstitutionAndDeletionUntilEqual) {
    EXPECT_EQ(3, levenshteinDistance("sitting", "kitten"));
    EXPECT_EQ(2, levenshteinDistance("kitting", "kitten")); // s -> k
    EXPECT_EQ(1, levenshteinDistance("kitteng", "kitten")); // i -> e
    EXPECT_EQ(0, levenshteinDistance("kitten", "kitten")); // delete g

    EXPECT_EQ(3, levenshteinDistance("Sunday", "Saturday"));
    EXPECT_EQ(2, levenshteinDistance("Sunday", "Sturday")); // delete a
    EXPECT_EQ(1, levenshteinDistance("Sunday", "Surday")); // delete t
    EXPECT_EQ(0, levenshteinDistance("Sunday", "Sunday")); // r -> n
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
