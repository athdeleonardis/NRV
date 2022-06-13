#ifndef NRV_NAMEMAP
#define NRV_NAMEMAP

#include <cstdint>
#include <string>
#include <unordered_map>

namespace NRV::Utilities {
    class NameMap {
    public:
    typedef std::string name_t;
    typedef uint32_t id_t;
    typedef std::unordered_map<name_t,id_t> map_t;

    private:
        map_t pr_map;
    private:
        virtual id_t prGenerateId() = 0;
    public:
        NameMap();
        ~NameMap();
        id_t operator<<(name_t);
        void operator>>(name_t);
        id_t operator[](name_t name);
    };

    class BindableNameMap : public NameMap {
    public:
        virtual void bind(id_t id) = 0;
    };
}

#endif
