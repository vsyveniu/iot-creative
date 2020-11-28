idf_component_register(SRCS "main.c"
                       INCLUDE_DIRS "include"
                        REQUIRES defines
                      )
spiffs_create_partition_image(spiffs ../html FLASH_IN_PROJECT)                      