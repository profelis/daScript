SET(DAS_METAL_DETECTED TRUE)

# C++ binding is Apple-only (system Metal.framework, zero third-party code).
# The metal/ daslang files (MSL emitter — Phase 1+) register unconditionally on
# all platforms; only this Obj-C++ shim is gated.
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
