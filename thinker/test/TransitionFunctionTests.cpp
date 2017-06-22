#include "../../thirdParty/googletest/include/gtest/gtest.h"
//#include "../include/Transition.h"
#include "../include/TransitionByStep.h"
#include "../include/TransitionSigmoid.h"
#include "../include/TransitionHiperbolicTangent.h"
#include "../include/TransitionSoftMax.h"
#include <cmath>
#include <iostream>


double round_nplaces(double value, int to)
{
    double places = pow(10.0, to);
    return round(value * places) / places;
}

TEST(TransitionFunctionTests, TransitionByStep_GivingNumbers_Expected)
 {
    Transition* transitionByStep = new TransitionByStep();
    vector<double> vectorAux = {-0.1,-0.5};
  
    EXPECT_EQ(transitionByStep->TransitionFunction(0),1)<< "Se esperaba 1 de respuesta";
    EXPECT_EQ(transitionByStep->TransitionFunction(0.5),1)<< "Se esperaba 1 de respuesta";
    EXPECT_EQ(transitionByStep->TransitionFunction(-0.3),-1)<< "Se esperaba -1 de respuesta";
    EXPECT_EQ(transitionByStep->TransitionFunction(-1),-1)<< "Se esperaba -1 de respuesta";
    EXPECT_EQ(transitionByStep->TransitionFunction(-1,vectorAux),0)<< "Se esperaba 0 de respuesta";
}
TEST(TransitionFunctionTests, TransitionSigmoid_GivingNumbers_Expected)
{
    //Arrange
    Transition* transitionSigmoid = new TransitionSigmoid();
    vector<double> vectorAux = {-0.1,-0.5};
    //Act
    auto eq1 = transitionSigmoid->TransitionFunction(-100);
    auto eq2 = transitionSigmoid->TransitionFunction(-46);
    auto eq3 = transitionSigmoid->TransitionFunction(-9);
    auto eq4 = transitionSigmoid->TransitionFunction(0);
    auto eq5 = transitionSigmoid->TransitionFunction(9);
    auto eq6 = transitionSigmoid->TransitionFunction(46);
    auto eq7 = transitionSigmoid->TransitionFunction(100);
    auto eq8 = transitionSigmoid->TransitionFunction(-1,vectorAux);

    //Assert
    EXPECT_EQ(round_nplaces(eq1,4),0)<< "Se esperaba 0 de respuesta";
    EXPECT_EQ(round_nplaces(eq2,4),0)<< "Se esperaba 0 de respuesta";
    EXPECT_EQ(round_nplaces(eq3,4),0.0001)<< "Se esperaba 0.001 de respuesta";
    EXPECT_EQ(round_nplaces(eq4,4),0.5)<< "Se esperaba 0.5 de respuesta";
    EXPECT_EQ(round_nplaces(eq5,4),0.9999)<< "Se esperaba 0.9999 de respuesta";
    EXPECT_EQ(round_nplaces(eq6,4),1)<< "Se esperaba 1 de respuesta";
    EXPECT_EQ(round_nplaces(eq7,4),1)<< "Se esperaba 1 de respuesta";
    EXPECT_EQ(eq8,0)<< "Se esperaba 0 de respuesta";
}

TEST(TransitionFunctionTests, TransitionHiperbolicTangent_GivingNumbers_Expected)
 {
    //Arrange
    Transition* transitionHiperbolicTangent = new TransitionHiperbolicTangent();
    vector<double> vectorAux = {-0.1,-0.5};
    //Act
    auto eq1 = transitionHiperbolicTangent->TransitionFunction(-200);
    auto eq2 = transitionHiperbolicTangent->TransitionFunction(-100);
    auto eq3 = transitionHiperbolicTangent->TransitionFunction(-9);
    auto eq4 = transitionHiperbolicTangent->TransitionFunction(0);
    auto eq5 = transitionHiperbolicTangent->TransitionFunction(1);
    auto eq6 = transitionHiperbolicTangent->TransitionFunction(50);
    auto eq7 = transitionHiperbolicTangent->TransitionFunction(100);
    auto eq8 = transitionHiperbolicTangent->TransitionFunction(-1,vectorAux);
    //cout<<eq3<<"eq3\n";
    //Assert
    EXPECT_EQ(eq1,-1)<< "Se esperaba -1 de respuesta";
    EXPECT_EQ(eq2,-1)<< "Se esperaba -1 de respuesta";
    EXPECT_EQ(round_nplaces(eq3,4),-1)<< "Se esperaba -1 de respuesta";
    EXPECT_EQ(eq4,0)<< "Se esperaba 0 de respuesta";
    EXPECT_EQ(round_nplaces(eq5,4),0.7616)<< "Se esperaba 0.7616 de respuesta";
    EXPECT_EQ(eq6,1)<< "Se esperaba 1 de respuesta";
    EXPECT_EQ(eq7,1)<< "Se esperaba 1 de respuesta";
    EXPECT_EQ(eq8,0)<< "Se esperaba 0 de respuesta";
}
TEST(TransitionFunctionTests, TransitionSoftMax_GivingNumbers_Expected)
 {
    Transition* transitionSoftMax = new TransitionSoftMax();
    vector<double> inputs = {1, 4, 2};
    auto eq1 = transitionSoftMax->TransitionFunction(0,inputs);
    auto eq2 = transitionSoftMax->TransitionFunction(1,inputs);
    auto eq3 = transitionSoftMax->TransitionFunction(2,inputs);
    auto eq4 = transitionSoftMax->TransitionFunction(0);
    EXPECT_EQ(round_nplaces(eq1,4),0.0420)<< "Se esperaba 0.0420 de respuesta";
    EXPECT_EQ(round_nplaces(eq2,4),0.8438)<< "Se esperaba 0.08438 de respuesta";
    EXPECT_EQ(round_nplaces(eq3,4),0.1142)<< "Se esperaba 0.1142 de respuesta";
    EXPECT_EQ((eq1 + eq2 +eq3),1)<< "Se esperaba 1 de respuesta";
    EXPECT_EQ(eq4,0)<< "Se esperaba 0 de respuesta";
}
TEST(TransitionByStep, calculate_derived)
 {
    Transition* transitionByStep = new TransitionByStep();
  
    EXPECT_EQ(transitionByStep->Derived(1),0)<< "Se esperaba 0 de respuesta";
    EXPECT_EQ(transitionByStep->Derived(100),0)<< "Se esperaba 0 de respuesta";
    EXPECT_EQ(transitionByStep->Derived(-151),0)<< "Se esperaba 0 de respuesta";
}
TEST(TransitionHiperbolicTangent, calculate_derived)
{
    Transition* transitionHT = new TransitionHiperbolicTangent();
  
    EXPECT_EQ(transitionHT->Derived(1),0)<< "Se esperaba 0 de respuesta";
    EXPECT_EQ(transitionHT->Derived(100),-9999)<< "Se esperaba 0 de respuesta";
    EXPECT_EQ(transitionHT->Derived(-151),-22800)<< "Se esperaba 0 de respuesta";
}
TEST(TransitionSigmoid, calculate_derived)
{
    Transition* transitionS = new TransitionSigmoid();
  
    EXPECT_EQ(transitionS->Derived(1),0)<< "Se esperaba 0 de respuesta";
    EXPECT_EQ(transitionS->Derived(100),-9999)<< "Se esperaba 0 de respuesta";
    EXPECT_EQ(transitionS->Derived(-151),-22800)<< "Se esperaba 0 de respuesta";
}
TEST(TransitionSoftMax, calculate_derived)
{
    Transition* transitionSoft = new TransitionSoftMax();
  
    EXPECT_EQ(transitionSoft->Derived(1),0)<< "Se esperaba 0 de respuesta";
    EXPECT_EQ(transitionSoft->Derived(100),-9900)<< "Se esperaba 0 de respuesta";
    EXPECT_EQ(transitionSoft->Derived(-151),-22952)<< "Se esperaba 0 de respuesta";
}