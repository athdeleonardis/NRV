#include "../../src/util/name_map.hpp"
#include <iostream>

using namespace NRV::Utilities;

class TestMap : public NameMap {
private:
    id_t pr_id_counter;
private:
    id_t prGenerateId() override {
        return pr_id_counter++;
    }
};

int main() {
    TestMap f_name_map = TestMap();

    std::cout << "Enter the number of strings to enter: ";
    int n;
    std::cin >> n;

    std::cout << "Enter " << n << " names:" << std::endl;
    NameMap::name_t names[n];
    for (int i = 0; i < n; i++) {
        std::cin >> names[i];
        f_name_map << names[i];
    }

    std::cout << "Id of names: " << std::endl;
    for (int i = 0; i < n; i++)
        std::cout << names[i] << ": " << f_name_map[names[i]] << std::endl;
}
