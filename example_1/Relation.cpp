#include "Relation.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

Relation::Relation() {};

Relation::~Relation() {};

void Relation::addTuple(Tuple newTuple)
{
	tuples.insert(newTuple);
}

Relation Relation::makeNewRelation(std::vector<Token> list)
{
	//name = "Test";
	//header.push_back("Meeting");
	//header.push_back("Parting");
	//Tuple tup1;
	//Tuple tup2;
	//tup1.push_back("Hi");
	//tup1.push_back("Bye");
	//tup2.push_back("Aloha");
	//tup2.push_back("Aloha");
	//addTuple(tup1);
	//addTuple(tup2);
	name = list.at(0).getValue();
	for (size_t i = 1; i < list.size(); i++)
	{
		header.push_back(list.at(i).getValue());
	}
	Relation newRelation = Relation(name, header, tuples);
	return newRelation;
}

Relation Relation::makeTestRelation()
{
	//name = "Test";
	//header.push_back("Meeting");
	//header.push_back("Parting");
	//header.push_back("Thanking");
	//Tuple tup1;
	//Tuple tup2;
	//Tuple tup3;
	//Tuple tup4;
	//tup1.push_back("Hi");
	//tup1.push_back("Bye");
	//tup1.push_back("ThankYou");
	//tup2.push_back("Aloha");
	//tup2.push_back("Aloha");
	//tup2.push_back("Mahalo");
	//tup3.push_back("Hey");
	//tup3.push_back("SeeYa");
	//tup3.push_back("Thanks");
	//tup4.push_back("Hi");
	//tup4.push_back("Goodbye");
	//tup4.push_back("Thanks");
	//addTuple(tup1);
	//addTuple(tup2);
	//addTuple(tup3);
	//addTuple(tup4);

	Relation newRelation = Relation(name, header, tuples);
	return newRelation;
}
