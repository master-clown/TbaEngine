#include <Geometry2d/Line.h>
#include <Geometry2d/Point2d.h>
#include <Geometry2d/Triangle.h>
#include <OpenGlContext/OpenGlPreconfigOptions.h>
#include <SdlRenderContext/SdlRenderPreconfigOptions.h>

#include "GeometryBatchRenderingApp.h"

#include <gtest/gtest.h>

#include <functional>

//======================================================================================================================
#define TEST_SUITE_NAME Simple2dSceneTest
#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)
#define MAKE_WND_TITLE(caseDesc) (STRINGIFY(TEST_SUITE_NAME) + String(" - ") + caseDesc)

//======================================================================================================================
namespace {
    //==================================================================================================================
    void testAllRenderers(const String& testDescription, const InitSceneGeometryBatch& initSceneGeometryBatch)
    {
        {
            GeometryBatchRenderingApp<sdl_render_context::SdlRenderPreconfigOptions> app(
                MAKE_WND_TITLE("SDL renderer. " + testDescription),
                initSceneGeometryBatch);
            EXPECT_NO_THROW(app.run());
        }

        {
            GeometryBatchRenderingApp<opengl_context::OpenGlPreconfigOptions> app(
                MAKE_WND_TITLE("OpenGL renderer. " + testDescription),
                initSceneGeometryBatch);
            EXPECT_NO_THROW(app.run());
        }
    }
}

//======================================================================================================================
#define TEST_CASE(name) TEST(TEST_SUITE_NAME, name)

//======================================================================================================================
TEST_CASE(DrawSimpleGeometryIn2d)
{
    const auto initSceneGeometryBatch = [](render_2d::GeometryBatchModifier& modifier) {
        const auto point = render_2d::RenderableGeometry<geometry_2d::Point2d>{
            .primitive = geometry_2d::Point2d{.x = -0.9, .y = 0.9},
            .contentTraits = geometry_2d::ContentTraits<geometry_2d::Point2d>{
                .color = content::Color{.b = 255},
            },
        };

        const auto line = render_2d::RenderableGeometry<geometry_2d::Line>{
            .primitive = geometry_2d::Line{.startPt = {.x = 0.0, .y = 0.8},
                                           .finalPt = {.x = -0.5, .y = -0.4}},
            .contentTraits = geometry_2d::ContentTraits<geometry_2d::Line>{
                .lineColor = {.r = 100},
            },
        };

        const auto triangle = render_2d::RenderableGeometry<geometry_2d::Triangle>{
            .primitive = geometry_2d::Triangle{
                .pt1 = {.x = 0.5, .y = -0.2},
                .pt2 = {.x = 0.8, .y = -0.6},
                .pt3 = {.x = 0.3, .y = -0.5},
            },
            .contentTraits = geometry_2d::ContentTraits<geometry_2d::Triangle>{
                .faceContent = content::Color{.g = 255},
            },
        };

        modifier.append(point);
        modifier.append(line);
        modifier.append(triangle);
    };

    testAllRenderers("Check that simple 2D geometry renders correctly", initSceneGeometryBatch);
}

//======================================================================================================================
TEST_CASE(DrawSameTriangle100000Times)
{
    static constexpr auto trianglesCount = 100'000;

    const auto initSceneGeometryBatch = [](render_2d::GeometryBatchModifier& modifier) {
        const auto triangle = render_2d::RenderableGeometry<geometry_2d::Triangle>{
            .primitive = geometry_2d::Triangle{
                .pt1 = {.x = 0.5, .y = -0.2},
                .pt2 = {.x = 0.8, .y = -0.6},
                .pt3 = {.x = 0.3, .y = -0.5},
            },
            .contentTraits = geometry_2d::ContentTraits<geometry_2d::Triangle>{
                .faceContent = content::Color{.g = 255},
            },
        };

        for (int i = 0; i < trianglesCount; ++i)
            modifier.append(triangle);
    };

    testAllRenderers(strFormat("Draw of {} same triangles", trianglesCount),
                     initSceneGeometryBatch);
}
