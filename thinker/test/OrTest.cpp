#include "../../thirdParty/googletest/include/gtest/gtest.h"
#include "../include/Perceptron.h"


#include <iostream>
using namespace std;

class OrTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }
  virtual void TearDown() {
  }
};

TEST_F(OrTest, ComputeOutput_TwoLogicInputs_Expected)
 {
    vector<vector<double>> datas{{-1,-1},{-1,1},{1,-1},{1,1}};
    vector<double> expected = {-1,1,1,1};

    double learningRate = 0.01;
    int loopLearn = 50;
    Perceptron p = Perceptron(2);
    p.Train(datas,expected,learningRate,loopLearn);

    EXPECT_EQ(p.Evaluate(datas[0]),-1);
    EXPECT_EQ(p.Evaluate(datas[1]),1);
    EXPECT_EQ(p.Evaluate(datas[2]),1);
    EXPECT_EQ(p.Evaluate(datas[3]),1);
}
