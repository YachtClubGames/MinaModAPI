cmake_minimum_required(VERSION 3.15)

project(MinaModExamples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(MOD_EXAMPLES
    basic
    hp_bars
    render
    traverse_scene_graph
)

foreach(MOD IN LISTS MOD_EXAMPLES)
    # the game expects each mod as <mods>/<mod-folder>/mod.dll (mod.so on linux)
    set(MOD_DIR ${CMAKE_BINARY_DIR}/mods/${MOD})

    add_library(${MOD} MODULE examples/${MOD}.cpp)
    target_include_directories(${MOD} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    set_target_properties(${MOD} PROPERTIES
        OUTPUT_NAME mod
        PREFIX ""
        # $<1:...> keeps multi-config generators (visual studio) from appending Debug/Release
        LIBRARY_OUTPUT_DIRECTORY "$<1:${MOD_DIR}>"
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN ON
    )

    # 0 for min/maxGameVersion means no version constraint
    file(WRITE ${MOD_DIR}/mod.yc
"[YCD Version: 1]
MinaModDef
{
\tid: \"${MOD}\",
\tname: \"${MOD}\",
\tmodVersion: 1,
\tminGameVersion: 0,
\tmaxGameVersion: 0,
\tloadPriority: 0,
}
")
endforeach()

# run the game with -mod -mod-allow-code to load deployed mods
if(WIN32)
    set(MOD_DEPLOY_DIR "$ENV{APPDATA}/Yacht Club Games/Mina the Hollower/mods")
else()
    set(MOD_DEPLOY_DIR "$ENV{HOME}/.local/share/Yacht Club Games/Mina the Hollower/mods")
endif()
file(TO_CMAKE_PATH "${MOD_DEPLOY_DIR}" MOD_DEPLOY_DIR)

add_custom_target(deploy
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_BINARY_DIR}/mods" "${MOD_DEPLOY_DIR}"
    COMMENT "Deploying mods to ${MOD_DEPLOY_DIR}"
)
add_dependencies(deploy ${MOD_EXAMPLES})
