#pragma once

//======================================================================================================================
namespace opengl_renderer {
    class OpenGlLibraryRaii final {
    public:
        struct LibraryInitOptions final {
            using OpenGlFunctionsLoader = void* (*)(const char* functionName);

            OpenGlFunctionsLoader openGlFunctionsLoader;
        };

        explicit OpenGlLibraryRaii(const LibraryInitOptions&);
        ~OpenGlLibraryRaii();
    };
}
