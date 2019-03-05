#include "Database.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

Database::Database() {};

Database::~Database() {};

void Database::makeRelation()
{
	//relation.makeNewRelation();
	//testRelation.makeTestRelation();
	/*test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
	test8();
	test9();
	test10();*/
}

////Test 1 checks the rename function to make sure I can rename a header as desired
//void Database::test1()
//{
//	Relation newRelation = relation;
//	std::string expectedOutput = "Test\nGreet   Parting \nAloha   Aloha   \nHi      Bye     \n";
//	newRelation.rename(0, "Greet");
//	if (newRelation.toString() == expectedOutput)
//	{
//		std::cout << "Test1 is a success!" << std::endl;
//	}
//	else
//	{
//		std::cout << "Test1 failed!" << std::endl;
//	}
//}
//
////Test 2 checks the project function to make sure I can project the desired columns from the table
//void Database::test2()
//{
//	Relation newRelation = relation;
//	std::vector<int> inputVec;
//	inputVec.push_back(0);
//	inputVec.push_back(1);
//	std::string expectedOutput = "Test\nMeeting Parting \nAloha   Aloha   \nHi      Bye     \n";
//	newRelation = newRelation.project(inputVec);
//	if (newRelation.toString() == expectedOutput)
//	{
//		std::cout << "Test2 is a success!" << std::endl;
//	}
//	else
//	{
//		std::cout << "Test2 failed!" << std::endl;
//	}
//}
//
////Test 3 checks for the proper functionality of the first select. The one that is called for a constant.
//void Database::test3()
//{
//	Relation newRelation = relation;
//	std::string expectedOutput = "Test\nMeeting Parting \nHi      Bye     \n";
//	newRelation = newRelation.selectOne(0, "Hi");
//	if (newRelation.toString() == expectedOutput)
//	{
//		std::cout << "Test3 is a success!" << std::endl;
//	}
//	else
//	{
//		std::cout << "Test3 failed!" << std::endl;
//	}
//}
//
////Test 4 checks for the proper functionality of the second select. The one that is called for two matching variables.
//void Database::test4()
//{
//	Relation newRelation = relation;
//	std::string expectedOutput = "Test\nMeeting Parting \nAloha   Aloha   \n";
//	newRelation = newRelation.selectTwo(0, 1);
//	if (newRelation.toString() == expectedOutput)
//	{
//		std::cout << "Test4 is a success!" << std::endl;
//	}
//	else
//	{
//		std::cout << "Test4 failed!" << std::endl;
//	}
//}
//
////Test 5 checks for a combination of select1 and project functions.
//void Database::test5()
//{
//	Relation newRelation = relation;
//	std::string expectedOutput = "Test\nMeeting \nHi      \n";
//	std::vector<int> inputVec;
//	inputVec.push_back(0);
//	newRelation = newRelation.selectOne(1, "Bye");
//	newRelation = newRelation.project(inputVec);
//	if (newRelation.toString() == expectedOutput)
//	{
//		std::cout << "Test5 is a success!" << std::endl;
//	}
//	else
//	{
//		std::cout << "Test5 failed!" << std::endl;
//	}
//}
//
////Test 6 checks functionality of a combination of the rename and select2 functions.
//void Database::test6()
//{
//	Relation newRelation = relation;
//	std::string expectedOutput = "Test\nMeeting Leaving \nAloha   Aloha   \n";
//	newRelation = newRelation.rename(1, "Leaving");
//	newRelation = newRelation.selectTwo(0, 1);
//	if (newRelation.toString() == expectedOutput)
//	{
//		std::cout << "Test6 is a success!" << std::endl;
//	}
//	else
//	{
//		std::cout << "Test6 failed!" << std::endl;
//	}
//}
//
////Test 7 tests the Query Test('Hi',X,Y) for using the select1 function
//void Database::test7()
//{
//	Relation newRelation = testRelation;
//	std::vector<int> inputVec;
//	inputVec.push_back(1);
//	inputVec.push_back(2);
//	std::string expectedOutput = "Test\nX       Y       \nBye     ThankYou\nGoodbye Thanks  \n";
//	newRelation = newRelation.selectOne(0, "Hi");
//	newRelation = newRelation.project(inputVec);
//	newRelation = newRelation.rename(0, "X");
//	newRelation = newRelation.rename(1, "Y");
//	if (newRelation.toString() == expectedOutput)
//	{
//		std::cout << "Test7 is a success!" << std::endl;
//	}
//	else
//	{
//		std::cout << "Test7 failed!" << std::endl;
//	}
//}
//
////Test 8 tests the query Test(X,X,X) for using select2 more than once. My current output will be nothing, because
////	I have no tuple that has the same value for all three entries.
//void Database::test8()
//{
//	Relation newRelation = testRelation;
//	std::vector<int> inputVec;
//	std::string expectedOutput = "Test\n\n";
//	newRelation = newRelation.selectTwo(0, 1);
//	newRelation = newRelation.selectTwo(1, 2);
//	newRelation = newRelation.project(inputVec);
//	if (newRelation.toString() == expectedOutput)
//	{
//		std::cout << "Test8 is a success!" << std::endl;
//	}
//	else
//	{
//		std::cout << "Test8 failed!" << std::endl;
//	}
//}
//
////Test 9 tests the query Test(X,'Goodbye','Thanks').
//void Database::test9()
//{
//	Relation newRelation = testRelation;
//	std::vector<int> inputVec;
//	inputVec.push_back(0);
//	std::string expectedOutput = "Test\nX       \nHi      \n";
//	newRelation = newRelation.selectOne(1, "Goodbye");
//	newRelation = newRelation.selectOne(2, "Thanks");
//	newRelation = newRelation.project(inputVec);
//	newRelation = newRelation.rename(0, "X");
//	if (newRelation.toString() == expectedOutput)
//	{
//		std::cout << "Test9 is a success!" << std::endl;
//	}
//	else
//	{
//		std::cout << "Test9 failed!" << std::endl;
//	}
//}
//
////Test 10 tests the Query Test(X,X,'Mahalo') to test the use of both selects being used to evaluate a query.
//void Database::test10()
//{
//	Relation newRelation = testRelation;
//	std::vector<int> inputVec;
//	inputVec.push_back(1);
//	std::string expectedOutput = "Test\nX       \nAloha   \n";
//	newRelation = newRelation.selectTwo(0, 1);
//	newRelation = newRelation.selectOne(2, "Mahalo");
//	newRelation = newRelation.project(inputVec);
//	newRelation = newRelation.rename(0, "X");
//	if (newRelation.toString() == expectedOutput)
//	{
//		std::cout << "Test10 is a success!" << std::endl;
//	}
//	else
//	{
//		std::cout << "Test10 failed!" << std::endl;
//	}
//}

void Database::toString()
{
	//relation.toString();
}