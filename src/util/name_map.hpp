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
    typedef void (*deleter_t)(id_t);
    private:
        map_t pr_map;
    private:
        deleter_t pr_deleter;
    private:
        NameMap();
        void prDeleteAll();
        virtual id_t prGenerateId() = 0;
    public:
        NameMap(deleter_t deletor);
        ~NameMap();
        id_t operator<<(name_t);
        void operator>>(name_t);
        id_t operator[](name_t name);
        map_t& getMap();
    };

    class BindableNameMap : public NameMap {
    private:
        BindableNameMap();
    public:
        BindableNameMap(deleter_t deleter);
        virtual void bind(id_t id) = 0;
    };
}

#endif
