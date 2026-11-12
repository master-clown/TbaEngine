#pragma once

#include <Framework/InitializedApp.h>

#include <utility>

//======================================================================================================================
namespace framework {
    //==================================================================================================================
    template <typename App>
    template <typename... AppCtorArgs>
    InitializedApp<App>::InitializedApp(AppCtorArgs&&... args)
        : _app(std::forward<AppCtorArgs>(args)...)
    {
        _app.init();
    }

    //==================================================================================================================
    template <typename App>
    App& InitializedApp<App>::getApp()
    {
        return _app;
    }

    //==================================================================================================================
    template <typename App>
    const App& InitializedApp<App>::getApp() const
    {
        return _app;
    }

    //==================================================================================================================
    template <typename App>
    App* InitializedApp<App>::operator->()
    {
        return &getApp();
    }

    //==================================================================================================================
    template <typename App>
    const App* InitializedApp<App>::operator->() const
    {
        return &getApp();
    }

    //==================================================================================================================
    template <typename App>
    InitializedApp<App>::operator App&()
    {
        return getApp();
    }

    //==================================================================================================================
    template <typename App>
    InitializedApp<App>::operator const App&() const
    {
        return getApp();
    }
}
