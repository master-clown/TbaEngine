#include <GuiAppTemplate/GuiAppTemplate.h>

#include <Geometry2d/Line.h>
#include <Geometry2d/Point2d.h>
#include <Geometry2d/Triangle.h>
#include <Render2d/GeometryBatch.h>
#include <Render2d/Renderer.h>
#include <Renderer/Renderer.h>
#include <SdlFramework/SdlFramework.h>
#include <SdlRenderContext/SdlRenderPreconfigOptions.h>
#include <Winsys/WindowMgr.h>

#include <gtest/gtest.h>

//======================================================================================================================
#define TEST_SUITE_NAME SdlRendererCreationTest
#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)

//======================================================================================================================
class BaseSdlRenderTestApp : public gui_app_template::GuiAppTemplate {
    using Super = gui_app_template::GuiAppTemplate;

public:
    explicit BaseSdlRenderTestApp(const String& caseDescription)
        : Super(winsys::WindowOptions{
              .wndTitle = STRINGIFY(TEST_SUITE_NAME) + String(" - ") + caseDescription,
          })
    {
    }

protected:
    uptr<winsys::Window> _createWindow(const winsys::WindowOptions& windowOptions) override
    {
        return getFramework().getWindowMgr().createWindow({
            .winOptions = windowOptions,
            .rendererPreconfigOptions = makeUPtr<sdl_render_context::SdlRenderPreconfigOptions>(),
        });
    }

    uptr<framework::Framework> _createFramework() override
    {
        return makeUPtr<sdl_framework::SdlFramework>();
    }
};

//======================================================================================================================
#define TEST_CASE(name) TEST(TEST_SUITE_NAME, name)

//======================================================================================================================
TEST_CASE(CreateEmptyScreen)
{
    BaseSdlRenderTestApp app("Just run and finish without any exceptions");
    EXPECT_NO_THROW(app.run());
}

//======================================================================================================================
TEST_CASE(DrawSimpleGeometryIn2d)
{
    class SimpleGeometryIn2dApp : public BaseSdlRenderTestApp {
        using Super = BaseSdlRenderTestApp;

    public:
        explicit SimpleGeometryIn2dApp(const String& caseDescription)
            : Super(caseDescription)
        {
        }

    private:
        void _init() override
        {
            Super::_init();

            _renderer = getFramework().createRenderer(_getWindow().createRendererContext());

            const auto& winOptions = _getWindow().getWindowOptions();
            _renderer->get2dRenderer().setBaseRenderResolution(winOptions.wndWidth, winOptions.wndHeight);

            auto& renderer2d = _renderer->get2dRenderer();
            _testGeometryBatch = renderer2d.createGeometryBatch();
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

                _testGeometryBatch->add(point);
                _testGeometryBatch->add(line);
                _testGeometryBatch->add(triangle);
            }
        }

        void _render() override
        {
            _renderer->clear(content::Color::black);

            auto& renderer2d = _renderer->get2dRenderer();
            renderer2d.renderGeometryBatch(*_testGeometryBatch);

            _renderer->finalizeRender();
        }

    private:
        uptr<render::Renderer> _renderer;
        uptr<render_2d::GeometryBatch> _testGeometryBatch;
    };

    SimpleGeometryIn2dApp app("Check that simple 2D geometry renders correctly");
    EXPECT_NO_THROW(app.run());
}
