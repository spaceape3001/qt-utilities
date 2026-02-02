################################################################################
##
##  YOUR QUILL
##
################################################################################

project(graphtools)

add_library(${PROJECT_NAME} SHARED
)

target_link_libraries(${PROJECT_NAME}
    yq_graphQt
)
LinkTest(${PROJECT_NAME})
