#include <Framework/Clock.h>
#include <Geometry2d/Line.h>
#include <Geometry2d/Point2d.h>
#include <Geometry2d/Triangle.h>
#include <Render2d/RenderableGeometry.h>
#include <RenderScene/Renderable.h>
#include <RenderScene/Renderable2d.h>
#include <RenderScene/RenderableBlueprint.h>
#include <RenderScene/TracedGeometryBatchModifier2d.h>

#include "TestApp.h"

#include <gtest/gtest.h>

//======================================================================================================================
#define TEST_SUITE_NAME RenderablesIn2dTest
#define TEST_CASE(name) TEST(TEST_SUITE_NAME, name)

//----------------------------------------------------------------------------------------------------------------------
#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)
#define MAKE_WND_TITLE(caseDesc) (STRINGIFY(TEST_SUITE_NAME) + String(" - ") + caseDesc)

//======================================================================================================================
using namespace geometry_2d;
using namespace render_scene;

//======================================================================================================================
namespace {
    class HouseBlueprint final : public render_scene::RenderableBlueprint {
    public:
        Renderable makeRenderable(TracedGeometryBatchModifier2d&) override;
    };

}

//======================================================================================================================
TEST_CASE(DrawStaticHouse)
{
    framework::InitializedApp<TestApp> app(MAKE_WND_TITLE("draw static house"));

    HouseBlueprint houseBlueprint;
    app->getRenderScene().addRenderable(houseBlueprint);

    EXPECT_NO_THROW(app->run());
}

//======================================================================================================================
TEST_CASE(DrawHouseMovingAlongScreenBorder)
{
    framework::InitializedApp<TestApp> app(MAKE_WND_TITLE("the house moving along the screen border"));
    const auto& appClock = app->getAppClock();

    HouseBlueprint houseBlueprint;
    auto& houseRenderable = app->getRenderScene().addRenderable(houseBlueprint);

    app->onIterate([&] {

    });

    EXPECT_NO_THROW(app->run());
}

//======================================================================================================================
Renderable HouseBlueprint::makeRenderable(TracedGeometryBatchModifier2d& batch2d)
{
    batch2d.add(render_2d::RenderableGeometry<Triangle>{
        .primitive = Triangle{
            .pt1 = {.x = -0.1, .y = 0.1},
            .pt2 = {.x = -0.1, .y = -0.1},
            .pt3 = {.x = 0.1, .y = -0.1},
        },
        .contentTraits = ContentTraits<Triangle>{
            .faceContent = content::Color{128, 0, 0},
        },
    });
    batch2d.add(render_2d::RenderableGeometry<Triangle>{
        .primitive = Triangle{
            .pt1 = {.x = -0.1, .y = 0.1},
            .pt2 = {.x = 0.1, .y = -0.1},
            .pt3 = {.x = 0.1, .y = 0.1},
        },
        .contentTraits = ContentTraits<Triangle>{
            .faceContent = content::Color{0, 128, 0},
        },
    });
    batch2d.add(render_2d::RenderableGeometry<Line>{
        .primitive = Line{
            .startPt = {.x = -0.1, .y = 0.1},
            .finalPt = {.x = 0.0, .y = 0.2},
        },
        .contentTraits = ContentTraits<Line>{
            .lineColor = content::Color{0, 0, 128},
        },
    });
    batch2d.add(render_2d::RenderableGeometry<Line>{
        .primitive = Line{
            .startPt = {.x = 0.0, .y = 0.2},
            .finalPt = {.x = 0.1, .y = 0.1},
        },
        .contentTraits = ContentTraits<Line>{
            .lineColor = content::Color{0, 0, 128},
        },
    });

    return Renderable(Renderable2d{batch2d.build()});
}
