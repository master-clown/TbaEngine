#pragma once

//======================================================================================================================
namespace opengl_render {
    class OpenGlLibraryRaii final {
    public:
        struct LibraryInitOptions final {
            using LoadOpenGlFunction = void* (*)(const char* functionName);

            LoadOpenGlFunction loadOpenGlFunction;
        };

        explicit OpenGlLibraryRaii(const LibraryInitOptions&);
        ~OpenGlLibraryRaii();
    };
}
