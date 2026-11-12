#pragma once

//======================================================================================================================
namespace framework {
    //==================================================================================================================
    template <typename App>
    class InitializedApp final {
    public:
        template <typename... AppCtorArgs>
        InitializedApp(AppCtorArgs&&...);

        App& getApp();
        const App& getApp() const;

        App* operator->();
        const App* operator->() const;

        operator App&();
        operator const App&() const;

    private:
        App _app;
    };
}

