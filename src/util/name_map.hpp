#ifndef NRV_NAMEMAP
#define NRV_NAMEMAP

#include <cstdint>
#include <string>
#include <unordered_map>

namespace NRV::Utilities {
    class NameMap {
    public:
    typedef std::string name_t;
    typedef uint64_t id_t;

    private:
        id_t pr_id_counter;
        std::unordered_map<name_t,id_t> pr_name_to_id;
        std::unordered_map<id_t, name_t> pr_id_to_name;
    public:
        NameMap();
        ~NameMap();
        id_t operator<<(name_t);
        id_t operator[](name_t name);
        name_t operator[](id_t name);
    };
}

#endif
