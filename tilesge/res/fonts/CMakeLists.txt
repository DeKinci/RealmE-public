file(GLOB FONTS_FILES "*.ttf")

cmrc_add_resource_library(
        fonts
        NAMESPACE fonts
        ${FONTS_FILES}
)