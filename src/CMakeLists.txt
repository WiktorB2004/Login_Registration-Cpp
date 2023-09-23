add_library(database_library)
target_sources(database_library PRIVATE database.cpp PUBLIC ${HEADER_LIST})