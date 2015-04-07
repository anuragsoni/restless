#include <string>
#include <iostream>
#include <restless.hpp>
using namespace std;
class Person
{
    string m_name;
    int m_age;

public:
    Person &name(string const &name) {this->m_name = name; return *this;}
    Person &age(int const age) {this->m_age = age; return *this;}

    friend ostream & operator << (ostream &os, Person const &);
};


ostream & operator << (ostream &os, Person const &person)
{
    return os << "Hello, my name is " << person.m_name << " and I am " << person.m_age << " years old.";
}


int main(void)
{
    Person person;
    cout << person.name("Peter").age(21) << endl;

    auto res = asoni::Handle()
        .get("http://example.com")
        .exec();

    std::cout << res.code << " " << res.body << '\n';

}