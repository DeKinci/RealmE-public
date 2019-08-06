file(GLOB SHADER_FILES "*.glsl")

cmrc_add_resource_library(
        shaders
        NAMESPACE shaders
        ${SHADER_FILES}
)
