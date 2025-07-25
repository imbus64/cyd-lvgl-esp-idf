idf_component_register(SRCS "main.c" "task_lvgl.c" "lcd.c" "speedometer.c" "touch.c"
    INCLUDE_DIRS ".")

execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_REV
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

add_compile_definitions(BUILD_GIT_HASH=\"${GIT_REV}\")
