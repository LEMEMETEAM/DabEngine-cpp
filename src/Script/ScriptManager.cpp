#include "Script/ScriptManager.hpp"

void checkError(lua_State* L)
{
    int ret = lua_pcall(L, 0, 0, 0);
    if(ret)
    {
        App::debugLog("%s\n", lua_tostring(L, -1));
    }
}

void ScriptManager::loadFromFile(std::string file)
{
    luaL_loadfile(m_L, file.c_str());
    checkError(m_L);
}

void ScriptManager::loadFromString(std::string source)
{
    luaL_loadstring(m_L, source.c_str());
    checkError(m_L);
}