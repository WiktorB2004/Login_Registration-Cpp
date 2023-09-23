add_library(database_library)
target_sources(database_library PRIVATE database.cpp PUBLIC ${HEADER_LIST})
target_include_directories(database_library PUBLIC "${PROJECT_SOURCE_DIR}/include")