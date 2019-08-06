file(GLOB TEXTURE_FILES "*.png")

cmrc_add_resource_library(
        textures
        NAMESPACE textures
        ${TEXTURE_FILES}
)
