idf_component_register(
    SRCS "CrcFastReverse.c" "crc16.c"         # list the source files of this component
    INCLUDE_DIRS "./include"        # optional, add here public include directories
    REQUIRES driver         # optional, list the public requirements (component names)
)
