#pragma once

//======================================================================================================================
namespace texture {
    class TextureSampler;
    class TexturingObjectsCreator;
}

//======================================================================================================================
namespace texture {
    class TexturingMgr {
    public:
        virtual ~TexturingMgr();

        virtual TexturingObjectsCreator& getTexturingObjectsCreator() = 0;

        void setCurrentTextureSampler(TextureSampler&);
        void setCurrentTextureSamplerToNone();

    protected:
        using TextureSamplerOrNull = TextureSampler*;
        virtual void _setCurrentTextureSampler(TextureSamplerOrNull) = 0;
    };
}
