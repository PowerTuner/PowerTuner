cmake_minimum_required(VERSION 3.19)
project(PowerTuner VERSION 1.0 DESCRIPTION "Official PowerTuner multiplatform client" LANGUAGES CXX)

include(CheckIPOSupported)

set(PROJECT_AUTHOR "kylon")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()
configure_file(resources/cmake/version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/version.h)

qt_add_resources(QT_RESOURCE
    resources/resources.qrc
)

set(SDL_TESTS OFF)
set(SDL_TEST_LIBRARY OFF)
set(SDL_EXAMPLES OFF)
set(SDL_DISABLE_INSTALL ON)
set(SDL_DISABLE_INSTALL_DOCS ON)
set(SDL_INSTALL_TESTS OFF)
set(SDL_STATIC ON)
set(SDL_SHARED OFF)
set(SDL_SHARED_DEFAULT OFF)
set(SDL_SHARED_AVAILABLE OFF)
set(SDL_AUDIO OFF)
set(SDL_VIDEO OFF)
set(SDL_GPU OFF)
set(SDL_RENDER OFF)
set(SDL_CAMERA OFF)
set(SDL_HAPTIC OFF)
set(SDL_POWER OFF)
set(SDL_JOYSTICK ON)
set(SDL_VIRTUAL_JOYSTICK OFF)
set(SDL_SENSOR OFF)
set(SDL_DIALOG OFF)
set(SDL_UNIX_CONSOLE_BUILD ON)
add_subdirectory(src/extern/SDL EXCLUDE_FROM_ALL)
set_property(TARGET SDL3-static PROPERTY POSITION_INDEPENDENT_CODE ON)

qt_add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${QT_RESOURCE}
    mainwindow.ui

    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h

    src/styles/StyleType.h
    src/styles/Style.h
    src/styles/VoidPurpleStyle.h

    src/include/ButtonKey.h
    src/include/GamepadButton.h
    src/include/keyMap.h
    src/include/GamepadButtonMap.h
    src/include/GamepadMapping.h
    src/include/Daemon.h

    src/classes/Settings.cpp
    src/classes/Settings.h
    src/classes/InputHandler.cpp
    src/classes/InputHandler.h
    src/classes/GamepadWorker.cpp
    src/classes/GamepadWorker.h

    src/widgets/components/PInputItem.h
    src/widgets/components/Switch/SwitchButton.cpp
    src/widgets/components/Switch/SwitchButton.h
    src/widgets/components/Slider/Slider.cpp
    src/widgets/components/Slider/Slider.h
    src/widgets/components/Select/Select.cpp
    src/widgets/components/Select/Select.h
    src/widgets/components/Button/Button.cpp
    src/widgets/components/Button/Button.h
    src/widgets/components/TextEdit/TextEdit.cpp
    src/widgets/components/TextEdit/TextEdit.h
    src/widgets/components/SpinBox/SpinBox.cpp
    src/widgets/components/SpinBox/SpinBox.h
    src/widgets/components/LineEdit/LineEdit.cpp
    src/widgets/components/LineEdit/LineEdit.h
    src/widgets/components/NavButton/NavButton.cpp
    src/widgets/components/NavButton/NavButton.h
    src/widgets/components/NavButton/NavButtonSinRotate.cpp
    src/widgets/components/NavButton/NavButtonSinRotate.h
    src/widgets/components/Scrollarea/Scrollbar.cpp
    src/widgets/components/Scrollarea/Scrollbar.h
    src/widgets/components/Scrollarea/ScrollArea.cpp
    src/widgets/components/Scrollarea/ScrollArea.h

    src/widgets/complex/Navbar/Navbar.cpp
    src/widgets/complex/Navbar/Navbar.h
    src/widgets/complex/Statusbar/Statusbar.cpp
    src/widgets/complex/Statusbar/Statusbar.h

    src/widgets/pages/Label/Label.cpp
    src/widgets/pages/Label/Label.h
    src/widgets/pages/Title/Title.cpp
    src/widgets/pages/Title/Title.h

    src/layouts/FlowLayout.cpp
    src/layouts/FlowLayout.h

    src/pages/PageUtils.cpp
    src/pages/PageUtils.h
    src/pages/PPage.cpp
    src/pages/PPage.h
    src/pages/home/Home.cpp
    src/pages/home/Home.h
    src/pages/logs/Logs.cpp
    src/pages/logs/Logs.h
    src/pages/clientSettings/ClientSettings.cpp
    src/pages/clientSettings/ClientSettings.h
    src/pages/daemons/Daemons.cpp
    src/pages/daemons/Daemons.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt::Core Qt::Widgets SDL3::SDL3)

check_ipo_supported(RESULT has_ipo OUTPUT ipo_error)
if (has_ipo)
    message(STATUS "${PROJECT_NAME}: IPO/LTO enabled")
    set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif ()

install(TARGETS ${PROJECT_NAME}
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET ${PROJECT_NAME}
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
