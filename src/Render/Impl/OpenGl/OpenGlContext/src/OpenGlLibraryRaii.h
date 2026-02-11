#pragma once

//======================================================================================================================
namespace opengl_context {
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
