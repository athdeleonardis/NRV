#include "name_map.hpp"

namespace NRV::Utilities {
    NameMap::NameMap() {
        pr_id_counter = 1;
        pr_name_to_id = std::unordered_map<name_t,id_t>();
        pr_id_to_name = std::unordered_map<id_t,name_t>();
    }

    NameMap::~NameMap() {

    }

    NameMap::id_t NameMap::operator<<(name_t name) {
        pr_name_to_id[name] = pr_id_counter;
        pr_id_to_name[pr_id_counter] = name;
        id_t id = pr_id_counter;
        pr_id_counter++;
        return id;
    }

    NameMap::id_t NameMap::operator[](name_t name) {
        return pr_name_to_id[name];
    }

    NameMap::name_t NameMap::operator[](id_t id) {
        return pr_id_to_name[id];
    }
}
