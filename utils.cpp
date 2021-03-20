 
#include <iostream>
#include <string>
#include <vector>

using namespace std;
// To make the system more flexible I prefer not to make a subclass for every person and room type

// Instead making subclasses for Person I use a class PersonType
// which contains a list of properties for a type of a person

class PersonType{
public:
    string typeString;
    vector<string> properties;
};


class Person{
public:
    // unique ID
    string uid;
    string type;
    string name;
    // Which access levels does this user have?
    vector<string> baseAccessTypes;
    // Which room numbers were opened especially for this user?
    vector<int> customAccess;
    // Properties appropriate for this particular user
    vector<string> properties;
};

class AccessLevel{
public:
    // Just the name of the access level (red, green, ... )
    string levelName;
    // room types allowed for access
    vector<string>access;
};

// Instead of making a subclass for every room type I prefer to just store 
// it as a string since room of any type has the same properties

class Room{
public:
    string type; // Room type (Cabinet, Classroom, ...)
    int id; // Room number or any other ID
    
    
};


class ConScope{
public:
    string name;
    vector<string> subscopes;
    vector<string> commands;
};
