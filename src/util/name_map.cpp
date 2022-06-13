#include "name_map.hpp"

namespace NRV::Utilities {
    //
    // NameMap Public Methods
    //

    NameMap::NameMap(deleter_t deletor) {
        pr_deleter = deletor;
        pr_map = map_t();
    }

    NameMap::~NameMap() {
        prDeleteAll();
    }

    void NameMap::prDeleteAll() {
        if (pr_deleter != NULL) {
            for (auto& it : pr_map) {
                pr_deleter(it.second);
            }   
        }
        
    }

    NameMap::id_t NameMap::operator<<(name_t name) {
        id_t id = prGenerateId();
        pr_map[name] = id;
        return id;
    }

    void NameMap::operator>>(name_t name) {
        if (pr_deleter != NULL)
            pr_deleter((*this)[name]);
        pr_map.erase(name);
    }

    NameMap::id_t NameMap::operator[](name_t name) {
        return pr_map[name];
    }

    NameMap::map_t& NameMap::getMap() {
        return pr_map;
    }

    BindableNameMap::BindableNameMap(deleter_t deleter) : NameMap(deleter) {}
}
