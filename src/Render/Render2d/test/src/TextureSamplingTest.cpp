#include <Common/Stl/Array.h>
#include <Geometry2d/Line.h>
#include <Geometry2d/Point2d.h>
#include <Geometry2d/Triangle.h>
#include <OpenGlContext/OpenGlPreconfigOptions.h>
#include <SdlRenderContext/SdlRenderPreconfigOptions.h>
#include <Texture/Texture.h>
#include <Texture/TextureData.h>
#include <Texture/TextureSampler.h>
#include <Texture/TextureSamplingParameters.h>
#include <Texture/TexturingMgr.h>
#include <Texture/TexturingObjectsCreator.h>
#include <TextureLoader/TextureLoader.h>
#include <TextureStorage/TextureStorage.h>

#include "GeometryBatchRenderingApp.h"

#include <gtest/gtest.h>

#include <filesystem>
#include <functional>

//======================================================================================================================
#define TEST_SUITE_NAME TextureSamplingTest
#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)
#define MAKE_WND_TITLE(caseDesc) (STRINGIFY(TEST_SUITE_NAME) + String(" - ") + caseDesc)

//======================================================================================================================
namespace {
    //==================================================================================================================
    void testAllRenderers(const String& testDescription, const InitSceneGeometryBatch&);

    //==================================================================================================================
    // TODO: Remove when rectangle primitive is supported
    struct Box final {
        geometry_2d::Point2d leftUpperCorner;
        geometry_2d::ScreenCoordinate width;
        geometry_2d::ScreenCoordinate height;
    };

    void addTexturedBox(render_2d::GeometryBatchModifier&, texture_storage::TextureId, const Box&);
}

//======================================================================================================================
#define TEST_CASE(name) TEST(TEST_SUITE_NAME, name)

//======================================================================================================================
TEST_CASE(DrawRectangleTexturedAsContainer)
{
    static const auto textureFile = std::filesystem::canonical("./resources/container.png");

    const auto initSceneGeometryBatch = [](render::Renderer& renderer,
                                           render_2d::GeometryBatchModifier& modifier) {
        auto& texturingMgr = renderer.getTexturingMgr();
        auto& texturingObjectsCreator = texturingMgr.getTexturingObjectsCreator();

        const auto textureData = texture_loader::TextureLoader{}.loadFromFile(textureFile);
        const auto texId = renderer.getTextureStorage().add(
            texturingObjectsCreator.createTexture(textureData));

        addTexturedBox(modifier, texId, Box{
                                            .leftUpperCorner = geometry_2d::Point2d{.x = -0.5, .y = 0.5},
                                            .width = 1.0,
                                            .height = 1.0,
                                        });
    };

    testAllRenderers("A rectangle textured as a container",
                     initSceneGeometryBatch);
}

//======================================================================================================================
namespace {
    [[nodiscard]]
    uptr<texture::TextureSampler> initBatchForFilteringTest(render::Renderer& renderer,
                                                            render_2d::GeometryBatchModifier& modifier,
                                                            texture::TextureSamplingParameters samplingParams)
    {
        using geometry_2d::ScreenCoordinate;

        auto& texturingMgr = renderer.getTexturingMgr();
        auto& texturingObjectsCreator = texturingMgr.getTexturingObjectsCreator();
        auto sampler = texturingObjectsCreator.createSampler(std::move(samplingParams));
        texturingMgr.setCurrentTextureSampler(*sampler);

        const auto texId = [&] {
            static const auto textureFile = std::filesystem::canonical("./resources/container.png");

            const auto textureData = texture_loader::TextureLoader{}.loadFromFile(textureFile);
            return renderer.getTextureStorage().add(texturingObjectsCreator.createTexture(textureData));
        }();

        static constexpr ScreenCoordinate screenSizeInNdc = 2.0;
        static constexpr size_t numOfBoxes = 3;
        static constexpr ScreenCoordinate horSpacePerBox = screenSizeInNdc / numOfBoxes;
        static constexpr ScreenCoordinate boxMargin = 0.05;
        static constexpr ScreenCoordinate boxWidth = horSpacePerBox - 2 * boxMargin;
        static constexpr ScreenCoordinate boxHeight = screenSizeInNdc - 2 * boxMargin;

        ScreenCoordinate nextBoxLeftUpperCornerX = -1.0;
        for (size_t iBox = 0; iBox < numOfBoxes; ++iBox, nextBoxLeftUpperCornerX += horSpacePerBox)
            addTexturedBox(modifier, texId, Box{
                                                .leftUpperCorner = geometry_2d::Point2d{
                                                    .x = nextBoxLeftUpperCornerX + boxMargin,
                                                    .y = 1.0 - boxMargin,
                                                },
                                                .width = boxWidth,
                                                .height = boxHeight,
                                            });

        return sampler;
    }
}

//----------------------------------------------------------------------------------------------------------------------
TEST_CASE(MultipleBoxes_NearestNeighborPixelFiltering)
{
    using SamplerParams = texture::TextureSamplingParameters;
    using PixelFiltering = SamplerParams::Filtering;

    uptr<texture::TextureSampler> sampler;

    const auto initSceneGeometryBatch = [&sampler](render::Renderer& renderer,
                                                   render_2d::GeometryBatchModifier& modifier) mutable {
        sampler = initBatchForFilteringTest(renderer, modifier, texture::TextureSamplingParameters{
                                                                    .minifyMipmapFiltering = PixelFiltering::Nearest,
                                                                });
    };

    testAllRenderers("Multiple container boxes with Nearest neighbor pixel filtering",
                     initSceneGeometryBatch);
}

//----------------------------------------------------------------------------------------------------------------------
TEST_CASE(MultipleBoxes_LinearNeighborPixelFiltering)
{
    using SamplerParams = texture::TextureSamplingParameters;
    using PixelFiltering = SamplerParams::Filtering;

    uptr<texture::TextureSampler> sampler;

    const auto initSceneGeometryBatch = [&sampler](render::Renderer& renderer,
                                                   render_2d::GeometryBatchModifier& modifier) mutable {
        sampler = initBatchForFilteringTest(renderer, modifier, texture::TextureSamplingParameters{
                                                                    .minifyMipmapFiltering = PixelFiltering::Linear,
                                                                });
    };

    testAllRenderers("Multiple container boxes with Linear neighbor pixel filtering",
                     initSceneGeometryBatch);
}

//======================================================================================================================
namespace {
    //==================================================================================================================
    void testAllRenderers(const String& testDescription, const InitSceneGeometryBatch& initSceneGeometryBatch)
    {
        // TODO: uncomment when SDL supports texturing
        // {
        //     GeometryBatchRenderingApp<sdl_render_context::SdlRenderPreconfigOptions> app(
        //         MAKE_WND_TITLE("SDL renderer. " + testDescription),
        //         initSceneGeometryBatch);
        //     EXPECT_NO_THROW(app.run());
        // }

        {
            GeometryBatchRenderingApp<opengl_context::OpenGlPreconfigOptions> app(
                MAKE_WND_TITLE("OpenGL renderer. " + testDescription),
                initSceneGeometryBatch,
                UseTexturing{true});
            EXPECT_NO_THROW(app.run());
        }
    }

    //==================================================================================================================
    void addTexturedBox(render_2d::GeometryBatchModifier& modifier,
                        const texture_storage::TextureId texId,
                        const Box& box)
    {
        const auto triangle1 = render_2d::RenderableGeometry<geometry_2d::Triangle>{
            .primitive = geometry_2d::Triangle{
                .pt1 = {.x = box.leftUpperCorner.x, .y = box.leftUpperCorner.y},
                .pt2 = {.x = box.leftUpperCorner.x, .y = box.leftUpperCorner.y - box.height},
                .pt3 = {.x = box.leftUpperCorner.x + box.width, .y = box.leftUpperCorner.y - box.height},
            },
            .contentTraits = geometry_2d::ContentTraits<geometry_2d::Triangle>{
                .faceContent = texId,
                .textureCoords = {
                    geometry_2d::TextureCoords{.u = 0.0, .v = 1.0},
                    geometry_2d::TextureCoords{.u = 0.0, .v = 0.0},
                    geometry_2d::TextureCoords{.u = 1.0, .v = 0.0},
                },
            },
        };

        const auto triangle2 = render_2d::RenderableGeometry<geometry_2d::Triangle>{
            .primitive = geometry_2d::Triangle{
                .pt1 = {.x = box.leftUpperCorner.x, .y = box.leftUpperCorner.y},
                .pt2 = {.x = box.leftUpperCorner.x + box.width, .y = box.leftUpperCorner.y - box.height},
                .pt3 = {.x = box.leftUpperCorner.x + box.width, .y = box.leftUpperCorner.y},
            },
            .contentTraits = geometry_2d::ContentTraits<geometry_2d::Triangle>{
                .faceContent = texId,
                .textureCoords = {
                    geometry_2d::TextureCoords{.u = 0.0, .v = 1.0},
                    geometry_2d::TextureCoords{.u = 1.0, .v = 0.0},
                    geometry_2d::TextureCoords{.u = 1.0, .v = 1.0},
                },
            },
        };

        modifier.append(triangle1);
        modifier.append(triangle2);
    }
}
