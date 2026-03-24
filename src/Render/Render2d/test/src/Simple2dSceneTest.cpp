#include <Geometry2d/Line.h>
#include <Geometry2d/Point2d.h>
#include <Geometry2d/Triangle.h>
#include <GuiAppTemplate/GuiAppWithRenderer.hpp>
#include <OpenGlContext/OpenGlPreconfigOptions.h>
#include <Render2d/GeometryBatch.h>
#include <Render2d/Renderer.h>
#include <Renderer/Renderer.h>
#include <SdlFramework/SdlFramework.h>
#include <SdlRenderContext/SdlRenderPreconfigOptions.h>
#include <Winsys/WindowMgr.h>

#include <gtest/gtest.h>

//======================================================================================================================
#define TEST_SUITE_NAME Simple2dSceneTest
#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)

//======================================================================================================================
namespace {
    template <class RendererPreconfigOptions>
    class PointLineTriangleApp final : public gui_app_template::GuiAppWithRenderer<RendererPreconfigOptions> {
        using Super = gui_app_template::GuiAppWithRenderer<RendererPreconfigOptions>;

    public:
        explicit PointLineTriangleApp(const String& caseDescription)
            : Super(winsys::WindowOptions{
                  .wndTitle = STRINGIFY(TEST_SUITE_NAME) + String(" - ") + caseDescription,
              })
        {
        }

    private:
        void _initAppWithRenderer() override
        {
            auto& renderer2d = this->getRenderer().get2dRenderer();
            _sceneGeometryBatch = renderer2d.createGeometryBatch();
            {
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

                _sceneGeometryBatch->add(point);
                _sceneGeometryBatch->add(line);
                _sceneGeometryBatch->add(triangle);
            }
        }

        void _render() override
        {
            this->getRenderer().clear(content::Color::black);

            auto& renderer2d = this->getRenderer().get2dRenderer();
            renderer2d.renderGeometryBatch(*_sceneGeometryBatch);

            this->getRenderer().finalizeRender();
        }

        uptr<framework::Framework> _createFramework() override
        {
            return makeUPtr<sdl_framework::SdlFramework>();
        }

    private:
        uptr<render_2d::GeometryBatch> _sceneGeometryBatch;
    };
}

//======================================================================================================================
#define TEST_CASE(name) TEST(TEST_SUITE_NAME, name)

//======================================================================================================================
TEST_CASE(DrawSimpleGeometryIn2d)
{
    {
        PointLineTriangleApp<sdl_render_context::SdlRenderPreconfigOptions> app(
            "Check that simple 2D geometry renders correctly on SDL renderer");
        EXPECT_NO_THROW(app.run());
    }

    {
        PointLineTriangleApp<opengl_context::OpenGlPreconfigOptions> app(
            "Check that simple 2D geometry renders correctly on OpenGL renderer");
        EXPECT_NO_THROW(app.run());
    }
}
