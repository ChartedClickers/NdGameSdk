include(CMakePackageConfigHelpers)

function(_ndg_sdk_install)
    get_property(_sdk_targets GLOBAL PROPERTY NDGAMESDK_SDK_TARGETS)
    if (NOT _sdk_targets)
        return()
    endif()

    # Build/install interface include dirs for main SDK targets
    foreach(_t IN LISTS _sdk_targets)
        if (TARGET ${_t})
            set_property(TARGET ${_t} PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
                $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/shared>
                $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/NdGameSdk>
                $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/dependencies/external/glm>
                $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/dependencies/external/glm/glm>
                $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/_deps/safetyhook-src/include>
                $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/vcpkg_installed/${VCPKG_TARGET_TRIPLET}/include>
                $<INSTALL_INTERFACE:include>
                $<INSTALL_INTERFACE:include/NdGameSdk>
                $<INSTALL_INTERFACE:include/NdGameSdk/shared>
                $<INSTALL_INTERFACE:include/thirdparty>
                $<INSTALL_INTERFACE:include/thirdparty/glm>
                $<INSTALL_INTERFACE:include/safetyhook>
            )
            set_property(TARGET ${_t} PROPERTY INTERFACE_LINK_LIBRARIES "nlohmann_json::nlohmann_json;fmt::fmt-header-only;safetyhook;Zydis")
        endif()
    endforeach()

    # Headers
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/src/NdGameSdk/ DESTINATION include/NdGameSdk FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/shared/ DESTINATION include/NdGameSdk/shared FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")

    # Third-party headers needed by consumers
    if (EXISTS "${CMAKE_BINARY_DIR}/_deps/safetyhook-src/include")
        install(DIRECTORY ${CMAKE_BINARY_DIR}/_deps/safetyhook-src/include/ DESTINATION include/safetyhook)
    endif()
    if (EXISTS "${CMAKE_BINARY_DIR}/_deps/zydis-src/include")
        install(DIRECTORY ${CMAKE_BINARY_DIR}/_deps/zydis-src/include/ DESTINATION include/thirdparty/zydis)
    endif()
    if (EXISTS "${CMAKE_BINARY_DIR}/_deps/zydis-src/dependencies/zycore/include")
        install(DIRECTORY ${CMAKE_BINARY_DIR}/_deps/zydis-src/dependencies/zycore/include/ DESTINATION include/thirdparty/zycore)
    endif()
    if (EXISTS "${CMAKE_SOURCE_DIR}/dependencies/external/glm")
        install(DIRECTORY ${CMAKE_SOURCE_DIR}/dependencies/external/glm/ DESTINATION include/thirdparty/glm)
    endif()
    if (EXISTS "${CMAKE_BINARY_DIR}/vcpkg_installed/${VCPKG_TARGET_TRIPLET}/include")
        install(DIRECTORY ${CMAKE_BINARY_DIR}/vcpkg_installed/${VCPKG_TARGET_TRIPLET}/include/ DESTINATION include/thirdparty)
    endif()

    # Per-target install to keep per-ndgame layout
    foreach(_t IN LISTS _sdk_targets)
        if (TARGET ${_t})
            string(REGEX REPLACE "SDK$" "" _game "${_t}")
            install(TARGETS ${_t}
                EXPORT NdGameSdkTargets
                RUNTIME DESTINATION bin/${_game}/$<CONFIG>
                LIBRARY DESTINATION bin/${_game}/$<CONFIG>
                ARCHIVE DESTINATION lib/${_game}/$<CONFIG>
            )
        endif()
    endforeach()

    # Third-party static libs used by public headers
    if (TARGET safetyhook)
        set_property(TARGET safetyhook PROPERTY INTERFACE_INCLUDE_DIRECTORIES
            $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/_deps/safetyhook-src/include>
            $<INSTALL_INTERFACE:include/safetyhook>
        )
        install(TARGETS safetyhook
            EXPORT NdGameSdkTargets
            RUNTIME DESTINATION bin/thirdparty/$<CONFIG>
            LIBRARY DESTINATION bin/thirdparty/$<CONFIG>
            ARCHIVE DESTINATION lib/thirdparty/$<CONFIG>
        )
    endif()
    if (TARGET Zydis)
        set_property(TARGET Zydis PROPERTY INTERFACE_INCLUDE_DIRECTORIES        
            $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/_deps/zydis-src/include>      
            $<INSTALL_INTERFACE:include/thirdparty/zydis>
        )
        install(TARGETS Zydis
            EXPORT NdGameSdkTargets
            RUNTIME DESTINATION bin/thirdparty/$<CONFIG>
            LIBRARY DESTINATION bin/thirdparty/$<CONFIG>
            ARCHIVE DESTINATION lib/thirdparty/$<CONFIG>
        )
    endif()
    install(FILES
        ${CMAKE_BINARY_DIR}/_deps/zydis-build/zycore/Debug/Zycore.lib
        DESTINATION lib/thirdparty/Debug
        CONFIGURATIONS Debug
    )
    install(FILES
        ${CMAKE_BINARY_DIR}/_deps/zydis-build/zycore/RelWithDebInfo/Zycore.lib
        DESTINATION lib/thirdparty/RelWithDebInfo
        CONFIGURATIONS RelWithDebInfo
    )

    install(EXPORT NdGameSdkTargets
        NAMESPACE FDG::
        FILE NdGameSdkTargets.cmake
        DESTINATION cmake/NdGameSdk
    )

    configure_package_config_file(
        ${CMAKE_SOURCE_DIR}/cmake/NdGameSdkConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/NdGameSdkConfig.cmake
        INSTALL_DESTINATION cmake/NdGameSdk
    )

    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/NdGameSdkConfig.cmake
        DESTINATION cmake/NdGameSdk
    )
endfunction()

# Defer until targets exist
cmake_language(DEFER CALL _ndg_sdk_install)
