#pragma once

#include <Common/Integers.h>
#include <Common/Stl/Optional.h>

#include <functional>

//======================================================================================================================
namespace opengl_render_2d {
    class VboRaii final {
    public:
        using BufferSizeInBytes = long;
        using IsMappable = bool;
        VboRaii(BufferSizeInBytes, IsMappable = false);

        struct MapOnCreation { };
        VboRaii(BufferSizeInBytes, MapOnCreation);

        //--------------------------------------------------------------------------------------------------------------
        VboRaii(VboRaii&&);
        VboRaii& operator=(VboRaii&&);

        //--------------------------------------------------------------------------------------------------------------
        VboRaii(const VboRaii&) = delete;
        VboRaii& operator=(const VboRaii&) = delete;

        //--------------------------------------------------------------------------------------------------------------
        ~VboRaii();

        //--------------------------------------------------------------------------------------------------------------
        void createVboMapping();

        //--------------------------------------------------------------------------------------------------------------
        BufferSizeInBytes getVboSizeInBytes() const;

        using BufferRawId = uint32;
        BufferRawId getVboId() const;

        Optional<void*> getVboMappingPtr() const;

    private:
        void _release();

        //--------------------------------------------------------------------------------------------------------------
        static void _staticAssertsOnTypedefs() noexcept;

    private:
        BufferSizeInBytes _currentSizeInBytes = 0;
        BufferRawId _bufferId = 0;
        Optional<void*> _bufferMappingPtr;
    };
}
