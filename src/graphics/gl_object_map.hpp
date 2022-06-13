#ifndef NRV_GL_OBJECT_MAP
#define NRV_GL_OBJECT_MAP

#include "../util/name_map.hpp"

#include <iostream>
#include <unordered_map>
#include <cstdint>

namespace NRV::Graphics {
    class VertexArrayMap : public Utilities::BindableNameMap {
    private:
        id_t prGenerateId() override;
    public:
        void bind(id_t id) override;
    };

    class VertexBufferMap : public Utilities::BindableNameMap {
    private:
        id_t prGenerateId() override;
    public:
        void bind(id_t id) override;
    };

    class ShaderMap : public Utilities::NameMap {
    public:
        enum Type {
            vertex,
            tess_control,
            tess_eval,
            geometry,
            fragment,
            compute
        };
        typedef const char * path_t;
        typedef char * code_t;
    private:
        Type pr_type;
    private:
        ShaderMap();
        id_t prGenerateId() override;
        code_t prReadFile(path_t file);
        void prCompile(id_t id, code_t code);
    public:
        ShaderMap(Type type);
        void operator>>(name_t name);
        void load(id_t id, path_t file);
    };

    class ProgramMap : public Utilities::BindableNameMap {
    private:
        id_t prGenerateId() override;
    public:
        void bind(id_t id) override;
        void attach(id_t program, id_t shader);
        void detach(id_t program, id_t shader);
        void finalize(id_t id);
    };
}

#endif
