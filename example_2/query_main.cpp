#include <iostream>
#include <fstream>
// #include <cstdlib>
#include "relational_db.h"

const bool MULTI_ARGS = false;

using namespace std;



/** test0() checks to ensure that uniqueness is functioning
 * 
 * test.dl has 60 facts for the deck scheme, but only 23 of them are unique
 * This checks to see that there are exactly 23 entries in resulting relation
 * fails is there are any more or any less
 */
bool test0(RelationalDB* db) {
    // get the deck relation and check for exactly 23 entries
    Relation* r = db->getRelation("deck");
    bool b = r->size() == 23;

    delete r;
    cout << "-|test 0: ignore duplicate facts on construction" << endl;
    if (b) {
        cout << " `-Passed test 0!" << endl;
    } else {
        cout << " `-Failed test 0!" << endl;
    }
    cout << endl;
    return b;
}

/** test1() checks basic functionality on a rename
 * 
 * check the rename on this empty scheme we defined
 * T should change to Toughness
 */
bool test1(RelationalDB* db ) {
    Relation* r = db->getRelation("SamePWRandTGH")->rename(2,"Toughness");
    bool b = r->str() ==
    // this should be the exact form of the output
    " SamePWRandTGH =                            A                            P                    Toughness\n"
    "                ---------------------------------------------------------------------------------------\n"
    "0 entries in SamePWRandTGH\n";

    delete r;
    cout << "-|test 1: simple rename on relation SamePWDandTGH" << endl;
    if (b) {
        cout << " `-Passed test 1!" << endl;
    } else {
        cout << " `-Failed test 1!" << endl;
    }
    cout << endl;
    return b;
}

/** test2() checks the projection operator on the card table
 * 
 * check that the card table returns only the projected column with **unique entries**
 * projecting card.EXP
 */
bool test2(RelationalDB* db) {
    // project the EXP column from
    // cout << db->getRelation("card")->project({4})->str();
    Relation * r = db->getRelation("card")->project({4});
    bool b = r->str() ==
    " card =                          EXP\n"
    "       -----------------------------\n"
    "                               'M15'\n"
    "                         'gatecrash'\n"
    "                 'return to ravnica'\n"
    "3 entries in card\n";

    delete r;
    cout << "-|test 2: simple project on relation card" << endl;
    if (b) {
        cout << " `-Passed test 2!" << endl;
    } else {
        cout << " `-Failed test 2!" << endl;
    }
    cout << endl;
    return b;
}

/** test3() 'data collapse'
 * select one value from a colum, then project that column. Should return only one value
 *    (the value we selected for)
 * 
 * mostly testing for uniqueness after operations
 * Throw in a rename just for fun
 */
bool test3(RelationalDB* db) {
    vector<function<bool(vector<string>)>> checks;
    string value = "'3'";
    int idx1 = 1;
    checks.push_back( [value, idx1] (vector<string> vec) -> bool {
            try {
                return value == vec.at(idx1);
            } catch (...) {
                return false;
            }
        }
    );

    Relation* r = db->getRelation("stat")->select(checks)->project({1})->rename(0, "A");
    bool b = r->str() ==
    " stat =                            A\n"
    "       -----------------------------\n"
    "                                 '3'\n"
    "1 entries in stat\n";

    delete r;
    cout << "-|test 3: data collapse (select project) on relation stat" << endl;
    if (b) {
        cout << " `-Passed test 3!" << endl;
    } else {
        cout << " `-Failed test 3!" << endl;
    }
    cout << endl;
    return b;
}


/** test4() simple selection on relation deck
 * 
 * check that only the unique entry of enchantment creature is returned
 *    when it is selected.
 * SELECT * FROM deck WHERE 3 = 'enchantment creature';
 */
bool test4(RelationalDB* db) {
    vector<function<bool(vector<string>)>> checks;
    string value = "'enchantment creature'";
    size_t index = 2;
    checks.push_back( [value, index] (vector<string> vec) -> bool {
            try {
                return value == vec.at(index);
            } catch (...) {
                return false;
            }
        }
    );

    Relation* r = db->getRelation("deck")->select(checks);
    bool b = r->str() == 
    // expected output: only archetype of aggression
    " deck =                         NAME                          CMC                         TYPE                          PWR                          TGH\n"
    "       -------------------------------------------------------------------------------------------------------------------------------------------------\n"
    "           'archetype of aggression'                          '3'       'enchantment creature'                          '3'                          '2'\n"
    "1 entries in deck\n";

    delete r;
    cout << "-|test 4: simple select on relation deck" << endl;
    if (b) {
        cout << " `-Passed test 4!" << endl;
    } else {
        cout << " `-Failed test 4!" << endl;
    }
    cout << endl;

    return b;
}

/** test5() pair equality selection on relation deck
 * 
 * check that we can use pairwise selection, by selecting all entries that 
 */
bool test5(RelationalDB* db) {
    vector<function<bool(vector<string>)>> checks;
    size_t idx1 = 3;
    size_t idx2 = 4;
    checks.push_back( [idx1, idx2] (vector<string> vec) -> bool {
            try {
                return vec.at(idx1) == vec.at(idx2);
            } catch (...) {
                return false;
            }
        }
    );

    Relation* r = db->getRelation("deck")->select(checks);
    bool b = r->str() ==
    " deck =                         NAME                          CMC                         TYPE                          PWR                          TGH\n"
    "       -------------------------------------------------------------------------------------------------------------------------------------------------\n"
    "                  'bonded horncrest'                          '4'                   'creature'                          '5'                          '5'\n"
    "             'burning sun''s avatar'                          '6'                   'creature'                          '6'                          '6'\n"
    "                   'goring ceratops'                          '7'                   'creature'                          '3'                          '3'\n"
    "                'huatli''s snubhorn'                          '2'                   'creature'                          '2'                          '2'\n"
    "                'huatli''s spurring'                          '1'                    'instant'                           ''                           ''\n"
    "           'huatli, dinosaur knight'                          '6'               'planeswalker'                           ''                           ''\n"
    "                  'lightning strike'                          '2'                    'instant'                           ''                           ''\n"
    "                          'mountain'                          '0'                 'basic land'                           ''                           ''\n"
    "                            'plains'                          '0'                 'basic land'                           ''                           ''\n"
    "          'priest of the waking sun'                          '1'                   'creature'                          '1'                          '1'\n"
    "                   'pterodon knight'                          '4'                   'creature'                          '3'                          '3'\n"
    "                     'rallying roar'                          '3'                    'instant'                           ''                           ''\n"
    "                   'slash of talons'                          '1'                    'instant'                           ''                           ''\n"
    "                      'stone quarry'                          '0'                       'land'                           ''                           ''\n"
    "                 'sun-blessed mount'                          '5'                   'creature'                          '4'                          '4'\n"
    "               'tilonalli''s knight'                          '2'                   'creature'                          '2'                          '2'\n"
    "16 entries in deck\n"
    ;

    delete r;
    cout << "-|test 5: pairwise select on relation deck" << endl;
    if (b) {
        cout << " `-Passed test 5!" << endl;
    } else {
        cout << " `-Failed test 5!" << endl;
    }
    cout << endl;
    return b;
}

/** test6() checks that projects returns the columns in
 *   the opposite order that they appear in the relation
 *   if the arguments are given in a different order than
 *   they appear in the relation
 */
bool test6(RelationalDB* db) {
    // cout << db->getRelation("stat")->project({1,0}).str();
    Relation* r = db->getRelation("stat")->project({1,0});
    bool b = r->str() ==
    " stat =                            B                            A\n"
    "       ----------------------------------------------------------\n"
    "                                 '1'                          '1'\n"
    "                                 '2'                          '1'\n"
    "               '2432902008176640000'                          '0'\n"
    "                                 '3'                          '1'\n"
    "                                 '3'                          '2'\n"
    "                                 '3'                          '3'\n"
    "6 entries in stat\n";

    delete r;
    cout << "-|test 6: projection reversal" << endl;
    if (b) {
        cout << " `-Passed test 6!" << endl;
    } else {
        cout << " `-Failed test 6!" << endl;
    }
    cout << endl;
    return b;
}

/** test7() the most simple query
 * 
 * stat(X,'3')?
 */
bool test7(RelationalDB* db) {
    vector<function<bool(vector<string>)>> checks;
    string value = "'3'";
    size_t idx1 = 1;
    checks.push_back( [value, idx1] (vector<string> vec) -> bool {
            try {
                return value == vec.at(idx1);
            } catch (...) {
                return false;
            }
        }
    );

    Relation* r = db->getRelation("stat")->select(checks)->project({0})->rename(0, "Z");
    bool b = r->str() ==
    " stat =                            Z\n"
    "       -----------------------------\n"
    "                                 '1'\n"
    "                                 '2'\n"
    "                                 '3'\n"
    "3 entries in stat\n";

    delete r;
    cout << "-|test 7: stat(Z,'3')? (hardcoded equivalent)" << endl;
    if (b) {
        cout << " `-Passed test 7!" << endl;
    } else {
        cout << " `-Failed test 7!" << endl;
    }
    cout << endl;
    return b;
}

/** test8() simple identicality check
 * 
 * pairwise selection, projection of one column, rename the col
 * stat(X,X)?
 */
bool test8(RelationalDB* db) {
    vector<function<bool(vector<string>)>> checks;
    size_t idx1 = 0;
    size_t idx2 = 1;
    checks.push_back( [idx1, idx2] (vector<string> vec) -> bool {
            try {
                return vec.at(idx1) == vec.at(idx2);
            } catch (...) {
                return false;
            }
        }
    );

    Relation* r = db->getRelation("stat")->select(checks)->project({0})->rename(0, "X");
    bool b = r->str() ==
    " stat =                            X\n"
    "       -----------------------------\n"
    "                                 '1'\n"
    "                                 '3'\n"
    "2 entries in stat\n";

    delete r;
    cout << "-|test 8: stat(X,X)? (hardcoded equivalent)" << endl;
    if (b) {
        cout << " `-Passed test 8!" << endl;
    } else {
        cout << " `-Failed test 8!" << endl;
    }
    cout << endl;
    return b;
}

/** test9() composite selection
 * 
 * selects only the creatures whose power and toughness are the same. Similar to the query
 * deck(A,B,'creature',X,X)?
 * 
 * tests pairwise and single selection at the same time.
 */
bool test9(RelationalDB* db) {
    vector<function<bool(vector<string>)>> checks;
    size_t idx1 = 3;
    size_t idx2 = 4;
    checks.push_back( [idx1, idx2] (vector<string> vec) -> bool {
            try {
                return vec.at(idx1) == vec.at(idx2);
            } catch (...) {
                return false;
            }
        }
    );
    string value = "'creature'";
    idx1 = 2;
    checks.push_back( [value, idx1] (vector<string> vec) -> bool {
            try {
                return "'creature'" == vec.at(idx1);
            } catch (...) {
                cout << "domain exception";
                return false;
            }
        }
    );

    Relation* r = db->getRelation("deck")->select(checks)->project({0,1,3,4});
    bool b = r->str() ==
    " deck =                         NAME                          CMC                          PWR                          TGH\n"
    "       --------------------------------------------------------------------------------------------------------------------\n"
    "                  'bonded horncrest'                          '4'                          '5'                          '5'\n"
    "             'burning sun''s avatar'                          '6'                          '6'                          '6'\n"
    "                   'goring ceratops'                          '7'                          '3'                          '3'\n"
    "                'huatli''s snubhorn'                          '2'                          '2'                          '2'\n"
    "          'priest of the waking sun'                          '1'                          '1'                          '1'\n"
    "                   'pterodon knight'                          '4'                          '3'                          '3'\n"
    "                 'sun-blessed mount'                          '5'                          '4'                          '4'\n"
    "               'tilonalli''s knight'                          '2'                          '2'                          '2'\n"
    "8 entries in deck\n";

    delete r;
    cout << "-|test 9: deck(NAME,CMC,'creature',PWR,PWR)? (composite pairwise and simple select)" << endl;
    if (b) {
        cout << " `-Passed test 9!" << endl;
    } else {
        cout << " `-Failed test 9!" << endl;
    }
    cout << endl;
    return b;
}

/** test10() composing a pairwise, direct selects, project, and rename to X
 * 
 * card(NAME,X,X,'6','return to ravnica')?
 */
bool test10(RelationalDB* db) {
    vector<function<bool(vector<string>)>> checks;
    string value = "'return to ravnica'";
    size_t idx1 = 4;
    checks.push_back([value, idx1] (vector<string> vec) -> bool {
            try {
                return value == vec.at(idx1);
            } catch (...) {
                return false;
            }
        }
    );
    value = "'6'";
    idx1 = 3;
    checks.push_back([value, idx1] (vector<string> vec) -> bool {
            try {
                return value == vec.at(idx1);
            } catch (...) {
                return false;
            }
        }
    );
    idx1 = 1;
    size_t idx2 = 2;
    checks.push_back( [idx1, idx2] (vector<string> vec) -> bool {
            try {
                return vec.at(idx1) == vec.at(idx2);
            } catch (...) {
                return false;
            }
        }
    );


    // cout << db->getRelation("card")->select(checks).project({0,1}).rename(1,"X").str();
    Relation* r = db->getRelation("card")->select(checks)->project({0,1})->rename(1,"X");
    bool b = r->str() ==
    " card =                         NAME                            X\n"
    "       ----------------------------------------------------------\n"
    "                        'niv-mizzet'                          '5'\n"
    "1 entries in card\n";

    delete r;
    cout << "-|test 10: card(NAME,X,X,'6','return to ravnica')? (hardcoded equivalent)" << endl;
    if (b) {
        cout << " `-Passed test 10!" << endl;
    } else {
        cout << " `-Failed test 10!" << endl;
    }
    cout << endl;
    return b;
}

bool runTests(RelationalDB* db) {
    bool pass = true;
    pass = pass && test1(db);
    pass = pass && test2(db);
    pass = pass && test3(db);
    pass = pass && test4(db);
    pass = pass && test5(db);
    pass = pass && test6(db);
    cout << "Commence query mimicing:" << endl << endl;
    pass = pass && test7(db);
    pass = pass && test8(db);
    pass = pass && test9(db);
    pass = pass && test10(db);

    return pass;
}

int parseArgs(int argc, char * argv[]) {

    for (int i = 1; i < argc; i++) {
        ifstream infile;
        infile.open(argv[i]);
        if (!infile.is_open()) {
            cout << "Failed to open `" << argv[i]
                 << "'" << endl;
            continue;
        }
        RelationalDB * db = new RelationalDB(infile);
        // do stuff here
        delete db;
    }
    return 0;
}

int parseOne(int argc, char * argv[]) {

    if (argc != 2) {
        return 0;
    }

    ifstream infile;
    infile.open(argv[1]);
    if (!infile.is_open()) {
        cout << "Failed to open `" << argv[1]
             << "'" << endl;
    }
    RelationalDB * db = new RelationalDB(infile);
    // db->display(cout);
    if (runTests(db)) {
        cout << "Passed all tests!" << endl;
    } else {
        cout << "Testing Failed!" << endl;
    }
    delete db;
    return 0;
}

int main (int argc, char * argv[]) {
    
    // instantiate a lexical analyzer and analyze the given file
    if (MULTI_ARGS) {
        return parseArgs(argc, argv);
    }
    return parseOne(argc, argv);

    // take the analysis and parse it as datalog. 
    
    return 0;
}