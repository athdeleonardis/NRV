#ifndef NRV_GL_SESSION
#define NRV_GL_SESSION

namespace NRV::Graphics {
    class GLSession {
    private:
        void prApplyWindowHints();
    public:
        GLSession();
        ~GLSession();
    };
}

#endif
