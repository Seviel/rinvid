load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "rinvid_core",
    srcs = [
        "animation.cpp",
        "circle_shape.cpp",
        "quad_shape.cpp",
        "rectangle_shape.cpp",
        "rinvid_gfx.cpp",
        "shape.cpp",
        "sprite.cpp",
        "texture.cpp",
        "transformable.cpp",
        "triangle_shape.cpp",
    ],
    hdrs = [
        "include/animation.h",
        "include/circle_shape.h",
        "include/drawable.h",
        "include/fixed_polygon_shape.h",
        "include/quad_shape.h",
        "include/rectangle_shape.h",
        "include/rinvid_gfx.h",
        "include/rinvid_gl.h",
        "include/shape.h",
        "include/sprite.h",
        "include/texture.h",
        "include/transformable.h",
        "include/triangle_shape.h",
    ],
    copts = ["-Werror -Wall -Wextra -pedantic"],
    linkopts = select({
        "@bazel_tools//src/conditions:windows": ["-lsfml-window -lsfml-system -lopengl32 -lwinmm -lgdi32"],
        "//conditions:default": ["-lsfml-window -lsfml-system -lGL"],
    }),
    visibility = ["//examples:__subpackages__"],
    deps = ["//util"],
)
