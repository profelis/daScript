IF(NOT DAS_GLTF_INCLUDED)
    SET(DAS_GLTF_INCLUDED TRUE)
    MESSAGE(STATUS "dasGLTF module included.")

    ADD_MODULE_DAS(gltf gltf gltf_types)
    ADD_MODULE_DAS(gltf gltf gltf_accessor)
    ADD_MODULE_DAS(gltf gltf gltf_parse)
    ADD_MODULE_DAS(gltf gltf gltf_scene)
    ADD_MODULE_DAS(gltf gltf gltf_boost)

    install(DIRECTORY ${PROJECT_SOURCE_DIR}/modules/dasGLTF/gltf
        DESTINATION ${DAS_INSTALL_MODULESDIR}/dasGLTF
        FILES_MATCHING
        PATTERN "*.das"
    )
    install(FILES ${PROJECT_SOURCE_DIR}/modules/dasGLTF/.das_module
        DESTINATION ${DAS_INSTALL_MODULESDIR}/dasGLTF
    )

ENDIF()
