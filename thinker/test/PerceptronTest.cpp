#include "../../thirdParty/googletest/include/gtest/gtest.h"

//#include "../include/TransitionByStep.h"
#include "../include/TransitionSigmoid.h"
#include "../include/TransitionHiperbolicTangent.h"
#include "../include/TransitionSoftMax.h"
#include "../include/Perceptron.h"
#include <cmath>
#include <random>
#include <iostream>


double round_places(double value, int to)
{
    double places = pow(10.0, to);
    return round(value * places) / places;
}

class PerceptronTest : public ::testing::Test
{
 protected:
  virtual void SetUp() {
  }
  virtual void TearDown() {
  }
};
default_random_engine generator1;
uniform_real_distribution<double> distribution1{-1,1};

TEST_F(PerceptronTest, PerceptronTest_withBysetp)
{
    Perceptron* p = new Perceptron(2);
    vector<double> inputs = {0.1,0.1};

    EXPECT_EQ(p->Evaluate(inputs),1)<< "Se esperaba 1 de respuesta";
}
/*TEST_F(PerceptronTest, PerceptronTest_withSoftMax)
{
    Transition* t = new TransitionSoftMax();
    Perceptron* p = new Perceptron(2,0.1,t);
    vector<double> inputs = {0.1,0.1};

    EXPECT_EQ(p->ComputeOutput(inputs),1)<< "Se esperaba 1 de respuesta";
}*/
TEST_F(PerceptronTest, PerceptronTest_withSigmoid)
{
    Transition* transition = new TransitionSigmoid();
    int numberInputs = 2;
    Perceptron* perceptron = new Perceptron(numberInputs,transition,distribution1,generator1);
    vector<double> inputs = {0.1,0.1};
    EXPECT_EQ(round_places(perceptron->Evaluate(inputs),4),0.3443)<< "Se esperaba 0.3443 de respuesta";
}
TEST_F(PerceptronTest, PerceptronTest_withTangentHiperbolic)
{
    Transition* transition = new TransitionHiperbolicTangent();
    int numberInputs = 2;
    Perceptron* perceptron = new Perceptron(numberInputs,transition,distribution1,generator1);
    vector<double> inputs = {0.1,0.1};
    EXPECT_EQ(round_places(perceptron->Evaluate(inputs),4),0.1602)<< "Se esperaba 0.1602 de respuesta";
}