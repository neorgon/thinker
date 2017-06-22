//g++ -isystem ../../thirdParty/googletest/include -g -pthread -lpthread ../src/*.cpp ../exceptions/*.cpp ATest.cpp ../../thirdParty/googletest/make/gtest_main.a -o ATest.exe -std=c++11 -std=gnu++11 

#include "../../thirdParty/googletest/include/gtest/gtest.h"
#include "../include/OptionParser.h"

class ATest : public ::testing::Test
{
	protected:
	virtual void SetUp() {

	}
	virtual void TearDown() {

	}

};

//////////////////////////////ACCEPTED INTEGER ////////////////////////////////////////////////////
TEST_F(ATest, OptionParser_Integer_ACEPTE)
 {
    //Arrange
    int argc = 5;
    const char* args[] = { "Scanner", "--calorias", "15", "-p", "100"};

    //Act
    OptionParser op(argc, args);

    op.AddInteger("calorias", 'c');
    op.AddInteger("proteinas", 'p');

    EXPECT_TRUE(op.Validate());

}
TEST_F(ATest, OptionParser_Integer_ACEPTE2)
 {
    //Arrange
    int argc = 5;
    const char* args[] = { "Scanner", "--calorias", "-15", "-p", "-100"};

    //Act
    OptionParser op(argc, args);

    op.AddInteger("calorias", 'c');
    op.AddInteger("proteinas", 'p');

    EXPECT_TRUE(op.Validate());

}
///////////////////////////////ERROR INTEGER/////////////////////////////////////////////////////

TEST_F(ATest, OptionParser_GivenWrongArgsInInteger_ExpectedErrorGeneral)
{
    int argc = 5;
    const char* args[] = { "Scanner", "--calorias", "False", "-p", "18"};

    //Act
    OptionParser op(argc, args);

    op.AddInteger("calorias", 'c');
    op.AddInteger("proteinas", 'p');
      
    EXPECT_THROW( op.Validate() ,SemanticException);
}

TEST_F(ATest, OptionParser_GivenWrongArgsInInteger_ExpectedError)
 {
    //Arrange
    int argc = 5;
    const char* args[] = { "Scanner", "--calorias", "False", "-p", "18"};

    //Act
    OptionParser op(argc, args);

    op.AddInteger("calorias", 'c');
    op.AddInteger("proteinas", 'p');

    //Assert
    try {
        op.Validate();
        FAIL() <<"Expected SemanticException";
    }
    catch(SemanticException const & err) {
        EXPECT_EQ(err.what(),string("Error Integer Number Type"));
    }
    catch(...) {
        FAIL() <<"Expected SemanticException";
    }
}


TEST_F(ATest, OptionParser_GivenWrongArgsInInteger_ExpectedError2)
 {
    //Arrange
    int argc = 5;
    const char* args[] = { "Scanner", "--calorias", "12.4", "-p", "100"};

    //Act
    OptionParser op(argc, args);

    op.AddInteger("calorias", 'c');
    op.AddInteger("proteinas", 'p');

    //Assert
    try {
        op.Validate();
        FAIL() <<"Expected SemanticException";
    }
    catch(SemanticException const & err) {
        EXPECT_EQ(err.what(),string("Error Integer Number Type"));
    }
    catch(...) {
        FAIL() <<"Expected SemanticException";
    }
}

TEST_F(ATest, OptionParser_GivenWrongArgsInInteger_ExpectedError3)
 {
    //Arrange
    int argc = 4;
    const char* args[] = { "Scanner", "--calorias", "-p", "100"};

    //Act
    OptionParser op(argc, args);

    op.AddInteger("calorias", 'c');
    op.AddInteger("proteinas", 'p');

    //Assert
    try {
        op.Validate();
        FAIL() <<"Expected SemanticException";
    }
    catch(SemanticException const & err) {
        EXPECT_EQ(err.what(),string("Error Integer Number Type"));
    }
    catch(...) {
        FAIL() <<"Expected SemanticException";
    }
}

//////////////////////////////ACCEPTED BOOLEAN////////////////////////////////////////////////////
TEST_F(ATest, OptionParser_Boolean_ACEPTE)
 {
    //Arrange
    int argc = 6;
    const char* args[] = { "Scanner", "--calorias", "true", "-p", "false","-g"};

    //Act
    OptionParser op(argc, args);

    op.AddBoolean("calorias", 'c');
    op.AddBoolean("proteinas", 'p');
    op.AddBoolean("grasas", 'g');

    EXPECT_TRUE(op.Validate());

}
///////////////////////////////ERROR BOOLEAN/////////////////////////////////////////////////////

TEST_F(ATest, OptionParser_GivenWrongArgsInValuesBoolean_ExpectedError)
 {
    //Arrange
    int argc = 7;
    const char* args[] = { "Scanner", "--calorias", "250", "-p", "100","-f","verdadero"};

    //Act
    OptionParser op(argc, args);

    op.AddInteger("calorias", 'c');
    op.AddInteger("proteinas", 'p');
    op.AddBoolean("fBool", 'f');

    //Act
    //Assert
    try {
        op.Validate();
        FAIL() <<"Expected SemanticException";
    }
    catch(SemanticException const & err) {
        EXPECT_EQ(err.what(),string("Error Boolean Type"));
    }
    catch(...) {
        FAIL() <<"Expected SemanticException";
    }
}

TEST_F(ATest, OptionParser_GivenWrongArgsInValuesBoolean_ExpectedError2)
 {
    //Arrange
    int argc = 7;
    const char* args[] = { "Scanner", "--calorias", "250", "-p", "100","-f","10"};

    //Act
    OptionParser op(argc, args);

    op.AddInteger("calorias", 'c');
    op.AddInteger("proteinas", 'p');
    op.AddBoolean("fBool", 'f');

    //Act
    //Assert
    try {
        op.Validate();
        FAIL() <<"Expected SemanticException";
    }
    catch(SemanticException const & err) {
        EXPECT_EQ(err.what(),string("Error Boolean Type"));
    }
    catch(...) {
        FAIL() <<"Expected SemanticException";
    }
}

//////////////////////////////ACCEPTED REAL////////////////////////////////////////////////////

TEST_F(ATest, OptionParser_REAL_ACEPTE)
 {
    //Arrange
    int argc = 7;
    const char* args[] = { "Scanner", "--calorias", "50", "-p", "18.5","-g","0.8"};

    //Act
    OptionParser op(argc, args);

    op.AddReal("calorias", 'c');
    op.AddReal("proteinas", 'p');
    op.AddReal("grasas", 'g');

    EXPECT_TRUE(op.Validate());

}
///////////////////////////////ERROR REAL/////////////////////////////////////////////////////

TEST_F(ATest, OptionParser_GivenWrongArgsInValuesReal_ExpectedError)
 {
    //Arrange
    int argc = 7;
    const char* args[] = { "Scanner", "--calorias", "250", "--grasas_saturadas", "false","-f","verdadero"};

    //Act
    OptionParser op(argc, args);

    op.AddInteger("calorias", 'c');
    op.AddReal("grasas_saturadas", 'g');
    op.AddBoolean("fBool", 'f');

    //Act
    //Assert
    try {
        op.Validate();
        FAIL() <<"Expected SemanticException";
    }
    catch(SemanticException const &err) {
        EXPECT_EQ(err.what(), string("Error Real Number Type"));
    }
    catch(...) {
        FAIL() <<"Expected SemanticException";
    }
}

TEST_F(ATest, OptionParser_GivenWrongArgsInValuesReal_ExpectedError2)
 {
    //Arrange
    int argc = 6;
    const char* args[] = { "Scanner", "--calorias", "250", "--grasas_saturadas","-f","true"};

    //Act
    OptionParser op(argc, args);

    op.AddInteger("calorias", 'c');
    op.AddReal("grasas_saturadas", 'g');
    op.AddBoolean("fBool", 'f');

    //Act
    //Assert
    try {
        op.Validate();
        FAIL() <<"Expected SemanticException";
    }
    catch(SemanticException const &err) {
        EXPECT_EQ(err.what(), string("Error Real Number Type"));
    }
    catch(...) {
        FAIL() <<"Expected SemanticException";
    }
}

//////////////////////////////////////////////////////////////////////////////////////

TEST_F(ATest, OptionParser_GivenWrongArgsInNames_ExpectedErrorGeneral)
 {
    //Arrange
    int argc = 5;
    const char* args[] = { "Scanner", "--calorias", "250", "p", "100"};

    //Act
    //Assert
   
    EXPECT_THROW(OptionParser op(argc, args) , SyntaxException);
}

TEST_F(ATest, OptionParser_GivenWrongArgsInNames_ExpectedError)
 {
    //Arrange
    int argc = 5;
    const char* args[] = { "Scanner", "--calorias", "250", "p", "100"};

    //Act
    //Assert

    try {
        OptionParser op(argc, args);
        FAIL() <<"Expected SyntaxException";
    }
    catch(SyntaxException const & err) {
        EXPECT_EQ(err.what(),string("Wrong format Option."));
    }
    catch(...) {
        FAIL() <<"Expected SyntaxException";
    }

}


TEST_F(ATest, OptionParser_GivenWrongMandatoryCommand_ExpectedErrorGeneral1)
 {
    //Arrange
    int argc = 5;
    const char* args[] = { "Scanner", "--calorias", "250", "-g", "10.0"};

    //Act
    //Assert
    OptionParser op(argc, args);
    op.AddInteger("calorias", 'c',true);
    op.AddReal("grasas_saturadas", 'g',true);
    op.AddBoolean("fBool", 'f',true);
    EXPECT_THROW(op.Validate(); , SyntaxException);
}

TEST_F(ATest, OptionParser_GivenWrongMandatoryCommand_ExpectedError1)
 {
    //Arrange
    int argc = 5;
    const char* args[] = { "Scanner", "--calorias", "250", "-g", "10.0"};

    //Act
    //Assert
    OptionParser op(argc, args);
    op.AddInteger("calorias", 'c',true);
    op.AddReal("grasas_saturadas", 'g',true);
    op.AddBoolean("fBool", 'f',true);


    try {
        op.Validate();
        FAIL() <<"Expected SyntaxException";
    }
    catch(SyntaxException const & err) {
        EXPECT_EQ(err.what(),string("Mandatory command not found"));
    }
    catch(...) {
        FAIL() <<"Expected SyntaxException";
    }

}

TEST_F(ATest, OptionParser_GivenWrongMandatoryCommand_ExpectedError2)
 {
    //Arrange
    int argc = 3;
    const char* args[] = { "Scanner", "--calorias", "250"};

    //Act
    //Assert
    OptionParser op(argc, args);
    op.AddInteger("calorias", 'c',true);
    op.AddReal("grasas_saturadas", 'g',true);
    op.AddBoolean("fBool", 'f',true);


    try {
        op.Validate();
        FAIL() <<"Expected SyntaxException";
    }
    catch(SyntaxException const & err) {
        EXPECT_EQ(err.what(),string("Mandatory command not found"));
    }
    catch(...) {
        FAIL() <<"Expected SyntaxException";
    }

}

TEST_F(ATest, OptionParser_GivenWrongMandatoryCommand_ExpectedError3)
 {
    //Arrange
    int argc = 3;
    const char* args[] = { "Scanner","--calorias", "250" };

    //Act
    //Assert
    OptionParser op(argc, args);
    op.AddInteger("calorias", 'c',true);
    op.AddReal("grasas_saturadas", 'g',false);
    op.AddBoolean("fBool", 'f',true);


    try {
        op.Validate();
        FAIL() <<"Expected SyntaxException";
    }
    catch(SyntaxException const & err) {
        EXPECT_EQ(err.what(),string("Mandatory command not found"));
    }
    catch(...) {
        FAIL() <<"Expected SyntaxException";
    }

}


TEST_F(ATest, OptionParser_Input_ACEPTE)
 {
    try {
    //Arrange
    int argc = 5;
    const char* args[] = { "Scanner", "-calorias", "15", "--p", "100"};

    //Act
    OptionParser op(argc, args);

    op.AddInteger("calorias", 'c');
    op.AddInteger("proteinas", 'p');

    
        op.Validate();
        FAIL() <<"Expected SyntaxException";
    }
    catch(SyntaxException const & err) {
        //cerr<<err.what();
        EXPECT_EQ(err.what(),string("Wrong format Option."));
    }
    catch(...) {
        FAIL() <<"Expected SyntaxException";
    }

}


//////////////////////////

TEST_F(ATest, OptionParser_Wrong_INPUT_ACEPTE_ExpectedError)
 {
    //Arrange
    try
    {
        int argc = 9;
    const char* args[] = { "Scanner", "--calorias", "50", "-p", "18.5","-g","0.8","-c","12"};

    //Act
    OptionParser op(argc, args);

    op.AddReal("calorias", 'c');
    op.AddReal("proteinas", 'p');
    op.AddReal("grasas", 'g');  
    op.Validate();
    FAIL() <<"Expected SyntaxException";
    }
    catch(SyntaxException const & err) {
        EXPECT_EQ(err.what(),string("Duplicated Parameter"));
    }
    catch(...) {
        FAIL() <<"Expected SyntaxException";
    }
}
