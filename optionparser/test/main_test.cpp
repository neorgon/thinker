#include "../../thirdParty/googletest/include/gtest/gtest.h"
#include "../include/OptionParser.h"
#include "ATest.cpp"
#include "UTest.cpp"
#include "ITest.cpp"

int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}