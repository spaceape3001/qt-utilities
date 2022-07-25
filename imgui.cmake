if(NOT TARGET imgui)
    find_package(GLFW3 REQUIRED)
    set(VULKAN_DIR $ENV{VULKAN_SDK})
    find_package(Vulkan REQUIRED)

    find_package(Freetype REQUIRED)
    set(imgui_dir ${CMAKE_CURRENT_LIST_DIR}/imgui)
    add_library(imgui SHARED
        ${imgui_dir}/imgui.cpp
        ${imgui_dir}/imgui.h
        ${imgui_dir}/imgui_demo.cpp
        ${imgui_dir}/imgui_draw.cpp
        ${imgui_dir}/imgui_tables.cpp
        ${imgui_dir}/imgui_widgets.cpp
        ${imgui_dir}/backends/imgui_impl_vulkan.cpp
        ${imgui_dir}/backends/imgui_impl_glfw.cpp
        ${imgui_dir}/misc/cpp/imgui_stdlib.cpp
        ${imgui_dir}/misc/freetype/imgui_freetype.cpp
    )
    target_include_directories(imgui 
        PUBLIC 
            ${imgui_dir}
        PRIVATE 
            ${FREETYPE_INCLUDE_DIRS}
    )
    target_compile_definitions(imgui 
        PUBLIC 
            IMGUI_USE_WCHAR32=1 
            IMGUI_ENABLE_FREETYPE=1
        PRIVATE
            GLFW_INCLUDE_VULKAN=1
    )
    target_compile_options(imgui PRIVATE 
        -w
    )
    target_link_libraries(imgui 
        PUBLIC 
            ${Vulkan_LIBRARIES} 
            ${GLFW3_LIBRARY}
            ${FREETYPE_LIBRARIES}
    )
    LinkTest(imgui)
endif()

