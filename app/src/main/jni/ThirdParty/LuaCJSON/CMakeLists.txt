add_library(LuaCJSON STATIC fpconv.c lua_cjson.c strbuf.c)
target_include_directories(LuaCJSON PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(LuaCJSON Lua)
