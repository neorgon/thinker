#include "../../thirdParty/googletest/include/gtest/gtest.h"
#include "../include/Perceptron.h"


#include <iostream>
using namespace std;

class XYTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }
  virtual void TearDown() {
  }
};

TEST_F(XYTest, ComputeOutput_XplusYFunction_BinaryClasification)
 {
    vector<vector<double>> datas{{1,1},{-1,-1}};
    vector<double> expected = {1,-1};

    double learningRate = 0.01;
    int loopLearn = 50;
    Perceptron p = Perceptron(2);
    p.Train(datas,expected,learningRate,loopLearn);

    vector<double> d1 {3,-2};
    vector<double> d2 {-2,3};
    vector<double> d3 {-2,-2};
    EXPECT_EQ(p.Evaluate(d1),1);
    EXPECT_EQ(p.Evaluate(d2),1);
    EXPECT_EQ(p.Evaluate(d3),-1);
}
