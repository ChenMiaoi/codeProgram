#include <iostream>
#include <string>
#include <set>
#include <list>
#include <iterator>
#include <algorithm>

class Person {
public:
    std::string last;
    std::string first;

    Person(const std::string& last_name, const std::string& first_name)
        : last(last_name), first(first_name) {}
    std::string first_name() const { return first; }
    std::string last_name() const { return last; }
};

class PersonSortCriterion {
public:
    bool operator() (const Person& p1, const Person& p2) const {
        // ! 如果last_name小的则为小
        // ! 如果last_name相等，则first_name小的则为小
        return p1.last_name() < p2.last_name() ||
            (p1.last_name() == p2.last_name() && p1.first_name() < p2.first_name());
    }
};

void foo() {
    std::set<Person, PersonSortCriterion> coll;
    coll.insert({"rih", "dsja"});
    coll.insert({"dsak", "dsja"});
    coll.insert({"rih", "cnasui"});
    coll.insert({"wqnri", "dwiah"});

    std::insert_iterator<std::set<Person, PersonSortCriterion>> iter (coll, coll.end());
    *iter++ = {"sdasd", "dasda"};

    for (const auto& i : coll)
        std::cout << i.last_name() << " " << i.first_name() << "\n";
}

class IntSequence {
private:
    int var;
public:
    IntSequence (int ininialValue): var(ininialValue) {}
    int operator() () { return ++var; }
};

void foo1() {
    std::list<int> coll;
    std::generate_n(std::back_inserter(coll), 9, IntSequence(1));
    for (const auto& i : coll)
        std::cout << i << " ";
    std::cout << "\n";

    std::generate(std::next(coll.begin()), std::prev(coll.end()), IntSequence(42));
    for (const auto& i : coll)
        std::cout << i << " ";
    std::cout << "\n";
}

void foo2() {
    std::list<int> coll;
    IntSequence seq(1);

    std::generate_n<std::back_insert_iterator<std::list<int>>, int, IntSequence&>(
            std::back_inserter(coll), 4, seq
    );
    for (const auto& i : coll)
        std::cout << i << " ";
    std::cout << "\n";

    std::generate_n(std::back_inserter(coll), 4, IntSequence(42));
    for (const auto& i : coll)
        std::cout << i << " ";
    std::cout << "\n";

    // ! 可以看见，当seq以reference的形式传入后，seq本身发生了改变
    std::generate_n(std::back_inserter(coll), 4, seq);
    for (const auto& i : coll)
        std::cout << i << " ";
    std::cout << "\n";

    std::generate_n(std::back_inserter(coll), 4, seq);
    for (const auto& i : coll)
        std::cout << i << " ";
    std::cout << "\n";
}

int main() {
    foo();
    foo1();
    foo2();
    return 0;
}
