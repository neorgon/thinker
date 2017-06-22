#include "../../thirdParty/googletest/include/gtest/gtest.h"
#include "../include/OptionParser.h"

class UTest : public ::testing::Test
{
	public:
	
	protected:
	virtual void SetUp() {
		
	}
	virtual void TearDown() {
		
	}

};


TEST_F(UTest, AddInteger )
{
	int argc = 1;
	const char* args[] ={""};
	OptionParser op(argc, args);
	

	
	op.AddInteger("calorias",'c');
	
	EXPECT_EQ(op.definitions[0].GetName(),"calorias");
	EXPECT_EQ(op.definitions[0].GetAbbr(),"c");
	EXPECT_EQ(op.definitions[0].GetOptional(),0);
	EXPECT_EQ(op.definitions[0].GetType() , OptionType::Integer);
}



TEST_F(UTest, AddInteger2 )
{

	int argc = 1;
	const char* args[] ={""};
	OptionParser op(argc, args);

	op.AddInteger("proteinas",'p', true);

	EXPECT_EQ(op.definitions[0].GetName(),"proteinas");
	EXPECT_EQ(op.definitions[0].GetAbbr(),"p");
	EXPECT_EQ(op.definitions[0].GetOptional(),1);
	EXPECT_EQ(op.definitions[0].GetType() , OptionType::Integer);
}


TEST_F(UTest, AddReal )
{

	int argc = 1;
	const char* args[] ={""};
	OptionParser op(argc, args);

	op.AddReal("grasas_hidrogenadas", 'h');

	EXPECT_EQ(op.definitions[0].GetName(),"grasas_hidrogenadas");
	EXPECT_EQ(op.definitions[0].GetAbbr(),"h");
	EXPECT_EQ(op.definitions[0].GetOptional(),0);
	EXPECT_EQ(op.definitions[0].GetType() , OptionType::Real);
}

TEST_F(UTest, AddReal2 )
{

	int argc = 1;
	const char* args[] ={""};
	OptionParser op(argc, args);

	op.AddReal("grasas_hidrogenadas", 'h',true);

	EXPECT_EQ(op.definitions[0].GetName(),"grasas_hidrogenadas");
	EXPECT_EQ(op.definitions[0].GetAbbr(),"h");
	EXPECT_EQ(op.definitions[0].GetOptional(),1);
	EXPECT_EQ(op.definitions[0].GetType() , OptionType::Real);
}


TEST_F(UTest, AddBool )
{

	int argc = 1;
	const char* args[] ={""};	
	OptionParser op(argc, args);

	op.AddBoolean("bBool", 'b');

	EXPECT_EQ(op.definitions[0].GetName(),"bBool");
	EXPECT_EQ(op.definitions[0].GetAbbr(),"b");
	EXPECT_EQ(op.definitions[0].GetOptional(),1);    //////////REVISAR POR Q INICIALIZA EN TRUE (1)
	EXPECT_EQ(op.definitions[0].GetType() , OptionType::Boolean);
}

TEST_F(UTest, AddBool2 )
{

	int argc = 1;
	const char* args[] ={""};
	OptionParser op(argc, args);

	op.AddBoolean("bBool", 'b',true);

	EXPECT_EQ(op.definitions[0].GetName(),"bBool");
	EXPECT_EQ(op.definitions[0].GetAbbr(),"b");
	EXPECT_EQ(op.definitions[0].GetOptional(),1);
	EXPECT_EQ(op.definitions[0].GetType() , OptionType::Boolean);
}

TEST_F(UTest, Text )
{

	int argc = 1;
	const char* args[] ={""};
	OptionParser op(argc, args);

	op.AddText("nombre", 'n',false);

	EXPECT_EQ(op.definitions[0].GetName(),"nombre");
	EXPECT_EQ(op.definitions[0].GetAbbr(),"n");
	EXPECT_EQ(op.definitions[0].GetOptional(),0);
	EXPECT_EQ(op.definitions[0].GetType() , OptionType::Text);


	op.AddText("sobrenombre", 's',true);

	EXPECT_EQ(op.definitions[1].GetName(),"sobrenombre");
	EXPECT_EQ(op.definitions[1].GetAbbr(),"s");
	EXPECT_EQ(op.definitions[1].GetOptional(),1);
	EXPECT_EQ(op.definitions[1].GetType() , OptionType::Text);

}


TEST_F(UTest, AddAllOptions)
{
	int argc = 1;
	const char* args[] ={""};
	OptionParser op(argc, args);

	op.AddText("nombre", 'n',false);

	EXPECT_EQ(op.definitions[0].GetName(),"nombre");
	EXPECT_EQ(op.definitions[0].GetAbbr(),"n");
	EXPECT_EQ(op.definitions[0].GetOptional(),0);
	EXPECT_EQ(op.definitions[0].GetType() , OptionType::Text);
	
	op.AddInteger("calorias",'c');
	
	EXPECT_EQ(op.definitions[1].GetName(),"calorias");
	EXPECT_EQ(op.definitions[1].GetAbbr(),"c");
	EXPECT_EQ(op.definitions[1].GetOptional(),0);
	EXPECT_EQ(op.definitions[1].GetType() , OptionType::Integer);
	
	op.AddReal("grasas_hidrogenadas", 'h');

	EXPECT_EQ(op.definitions[2].GetName(),"grasas_hidrogenadas");
	EXPECT_EQ(op.definitions[2].GetAbbr(),"h");
	EXPECT_EQ(op.definitions[2].GetOptional(),0);
	EXPECT_EQ(op.definitions[2].GetType() , OptionType::Real);

	op.AddBoolean("bBool", 'b');

	EXPECT_EQ(op.definitions[3].GetName(),"bBool");
	EXPECT_EQ(op.definitions[3].GetAbbr(),"b");
	EXPECT_EQ(op.definitions[3].GetOptional(),1);         /////////////////MISMO ERROR DEL BOOLEANO
	EXPECT_EQ(op.definitions[3].GetType() , OptionType::Boolean);
	
}



TEST_F(UTest, DefinitionExeption)
{
	int argc = 1;
	const char* args[] ={""};
	OptionParser op(argc, args);

	op.AddText("nombre", 'n',false);

	EXPECT_EQ(op.definitions[0].GetName(),"nombre");
	EXPECT_EQ(op.definitions[0].GetAbbr(),"n");
	EXPECT_EQ(op.definitions[0].GetOptional(),0);
	EXPECT_EQ(op.definitions[0].GetType() , OptionType::Text);
	
	op.AddInteger("calorias",'c');
	
	EXPECT_EQ(op.definitions[1].GetName(),"calorias");
	EXPECT_EQ(op.definitions[1].GetAbbr(),"c");
	EXPECT_EQ(op.definitions[1].GetOptional(),0);
	EXPECT_EQ(op.definitions[1].GetType() , OptionType::Integer);
	
}


////////////////////////////////////////////////////////////////

TEST_F(UTest, OptionParser_Definition_ExceptedError)
 {
    //Arrange
    int argc = 5;
    const char* args[] = { "Scanner", "--calorias", "15", "-p", "100"};

    //Act
    OptionParser op(argc, args);
      
    EXPECT_THROW( op.AddInteger("-calorias", 'p') ,DefinitionException);
}

TEST_F(UTest, OptionParser_Wrong_Option_NameInput_Definition_ExceptedError)
 {
    //Arrange
    int argc = 5;
    const char* args[] = { "Scanner", "--calorias", "15", "-p", "100"};

    //Act
    OptionParser op(argc, args);

    try {

    op.AddInteger("-calorias", 'c');
    op.AddInteger("proteinas", 'p');
  

        op.Validate();
        FAIL() <<"Expected DefinitionException";
    }
    catch(DefinitionException const & err) {
        EXPECT_EQ(err.what(),string("Name declaration error"));
    }
    catch(...) {
        FAIL() <<"Expected DefinitionException";
    }

}


TEST_F(UTest, OptionParser_Definition_ExceptedError2)
 {
    //Arrange
    int argc = 5;
    const char* args[] = { "Scanner", "--calorias", "15", "-p", "100"};

    //Act
    OptionParser op(argc, args);

	EXPECT_THROW( op.AddInteger("--calorias", 'c') ,DefinitionException);

}

TEST_F(UTest, OptionParser_Wrong_Option_NameInput_Definition_ExceptedError2)
 {
    //Arrange
    int argc = 5;
    const char* args[] = { "Scanner", "--calorias", "15", "-p", "100"};

    //Act
    OptionParser op(argc, args);

    try {

    op.AddInteger("--calorias", 'c');
    op.AddInteger("proteinas", 'p');
   
        op.Validate();
        FAIL() <<"Expected DefinitionException";
    }
    catch(DefinitionException const & err) {
        EXPECT_EQ(err.what(),string("Name declaration error"));
    }
    catch(...) {
        FAIL() <<"Expected DefinitionException";
    }

}


TEST_F(UTest,OptionParser_AbbrInput_Definition_ExceptedError)
 {
    //Arrange
    int argc = 5;
    const char* args[] = { "Scanner", "--calorias", "15", "-p", "100"};

    //Act
    OptionParser op(argc, args);
 	
	EXPECT_THROW( op.AddInteger("prote", '4') ,DefinitionException);
}

TEST_F(UTest, OptionParser_Wrong_Option_AbbrInput_Definition_ExceptedError)
 {
    //Arrange
    int argc = 5;
    const char* args[] = { "Scanner", "--calorias", "15", "-p", "100"};

    //Act
    OptionParser op(argc, args);

    try {

    op.AddInteger("calorias", '6');
    op.AddInteger("proteinas", 'p');
    


        op.Validate();
        FAIL() <<"Expected DefinitionException";
    }
    catch(DefinitionException const & err) {
        EXPECT_EQ(err.what(),string("Abbreviation declaration error"));
    }
    catch(...) {
        FAIL() <<"Expected DefinitionException";
    }

}


TEST_F(UTest, OptionParser_Wrong_Option_Name_Definition_ExceptedErrorGeneral)
 {
    //Arrange
    int argc = 5;
    const char* args[] = { "Scanner", "--calorias", "15", "-p", "100"};

    //Act
    OptionParser op(argc, args);

 
    op.AddInteger("calorias", 'c');
    op.AddInteger("proteinas", 'p');
    EXPECT_THROW (op.AddInteger("proteinas", 'r'),DefinitionException);


}


TEST_F(UTest, OptionParser_Wrong_Option_Name_Definition_ExceptedError)
 {
    //Arrange
    int argc = 5;
    const char* args[] = { "Scanner", "--calorias", "15", "-p", "100"};

    //Act
    OptionParser op(argc, args);

    try {

    op.AddInteger("calorias", 'c');
    op.AddInteger("proteinas", 'p');
    op.AddInteger("proteinas", 'r');


       // op.Validate();
        FAIL() <<"Expected DefinitionException";
    }
    catch(DefinitionException const & err) {
        EXPECT_EQ(err.what(),string("Repeated definition"));
    }
    catch(...) {
        FAIL() <<"Expected DefinitionException";
    }

}


TEST_F(UTest, OptionParser_Wrong_Option_Abbr_Definition_ExceptedErrorGeneral)
 {
    //Arrange
    int argc = 5;
    const char* args[] = { "Scanner", "--calorias", "15", "-p", "100"};

    //Act
    OptionParser op(argc, args);
 	 op.AddInteger("proteinas", 'p');
	EXPECT_THROW( op.AddInteger("prote", 'p') ,DefinitionException);
}


TEST_F(UTest, OptionParser_Wrong_Option_Abbr_Definition_ExceptedError)
 {
    //Arrange
    int argc = 5;
    const char* args[] = { "Scanner", "--calorias", "15", "-p", "100"};

    //Act
    OptionParser op(argc, args);

    try {

    op.AddInteger("calorias", 'c');
    op.AddInteger("proteinas", 'p');
    op.AddInteger("prote", 'p');


        op.Validate();
        FAIL() <<"Expected DefinitionException";
    }
    catch(DefinitionException const & err) {
        EXPECT_EQ(err.what(),string("Repeated definition"));
    }
    catch(...) {
        FAIL() <<"Expected DefinitionException";
    }

}