
#ifndef SCRIPTMANAGER_H_
#define SCRIPTMANAGER_H_

#include <lua/lua.hpp>
#include "Core/App.hpp"
#include <string>

class ScriptManager
{
    public:
        static ScriptManager& getManager()
        {
            static ScriptManager s;
            return s;
        }

        void loadFromFile(std::string file);
        void loadFromString(std::string source);

    private:
        lua_State* m_L;

        ScriptManager()
        {
            lua_State* L = luaL_newstate();
            if(!L)
            {
                App::debugLog("Lua state failed to load\n");
                //add bool
                throw;
            }
            luaL_openlibs(L);
            m_L = L;
        }
        ScriptManager(ScriptManager const&);              // Don't Implement
        void operator=(ScriptManager const&); // Don't implement
};

#endif