#include "name_map.hpp"

namespace NRV::Utilities {
    //
    // NameMap Public Methods
    //

    NameMap::NameMap() {
        pr_map = map_t();
    }

    NameMap::~NameMap() {

    }

    NameMap::id_t NameMap::operator<<(name_t name) {
        id_t id = prGenerateId();
        pr_map[name] = id;
        return id;
    }

    void NameMap::operator>>(name_t name) {
        pr_map.erase(name);
    }

    NameMap::id_t NameMap::operator[](name_t name) {
        return pr_map[name];
    }
}
