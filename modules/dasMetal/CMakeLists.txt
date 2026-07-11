SET(DAS_METAL_DETECTED TRUE)

# The metal/ daslang files (MSL emitter + [metal_kernel] + boost) are pure das and register on
# ALL platforms — the emitter/text tests (tests/msl) run everywhere. Only the Obj-C++ shim over
# Metal.framework is Apple-gated below.
IF (NOT DAS_METAL_DAS_INCLUDED)
    SET(DAS_METAL_DAS_INCLUDED TRUE)

    ADD_MODULE_DAS(metal metal msl_types)
    ADD_MODULE_DAS(metal metal msl_emit)
    ADD_MODULE_DAS(metal metal msl_shader)
    ADD_MODULE_DAS(metal metal das_metal_boost)

    install(DIRECTORY ${PROJECT_SOURCE_DIR}/modules/dasMetal/metal
        DESTINATION ${DAS_INSTALL_MODULESDIR}/dasMetal
        FILES_MATCHING
        PATTERN "*.das"
        PATTERN "_*" EXCLUDE
    )
ENDIF()

# C++ binding is Apple-only (system Metal.framework, zero third-party code).
IF ((NOT DAS_METAL_INCLUDED) AND ((NOT ${DAS_METAL_DISABLED}) OR (NOT DEFINED DAS_METAL_DISABLED)) AND APPLE)
    SET(DAS_METAL_INCLUDED TRUE)
    MESSAGE(STATUS "dasMetal module included.")

    SET(DAS_METAL_DIR ${PROJECT_SOURCE_DIR}/modules/dasMetal)

    SET(DAS_METAL_MODULE_SRC
        ${DAS_METAL_DIR}/src/dasMetal.h
        ${DAS_METAL_DIR}/src/dasMetal.mm
    )
    SET_SOURCE_FILES_PROPERTIES(${DAS_METAL_DIR}/src/dasMetal.mm PROPERTIES COMPILE_OPTIONS "-fobjc-arc")

    ADD_MODULE_CPP(DasMetal)
    ADD_MODULE_LIB(libDasModuleMetal dasModuleMetal ${DAS_METAL_MODULE_SRC})
    MACRO(SETUP_METAL_LIB lib)
        TARGET_LINK_LIBRARIES(${lib} PUBLIC
            "-framework Metal"
            "-framework Foundation"
        )
        SETUP_CPP11(${lib})
    ENDMACRO()
    SETUP_METAL_LIB(libDasModuleMetal)
    SETUP_METAL_LIB(dasModuleMetal)
ENDIF()
