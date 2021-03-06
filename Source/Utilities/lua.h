/*
 * Filename      : lua.h
 * Author(s)     : Chris Thielen (chris@luethy.net)
 * Date Created  : Saturday, January 5, 2008
 * Last Modified : Friday, November 14, 2009
 * Purpose       : Provides abilities to load, store, and run Lua scripts
 * Notes         : To be used in conjunction with various other subsystems, A.I., GUI, etc.
 */

#ifndef __H_LUA__
#define __H_LUA__

#include "includes.h"

#ifdef __cplusplus
extern "C" {
#endif
#	include <lua.h>
#	include <lualib.h>
#	include <lauxlib.h>
#ifdef __cplusplus
}
#endif

#include "Sprites/spritemanager.h"

class Lua {
	public:
		static bool Load( string filename );
		static bool Run( string line );
		static bool Update();
		static vector<string> GetOutput();

		static void RegisterFunctions();
		static bool SetSpriteList(SpriteManager* the_sprites);
		static SpriteManager* GetSpriteList();

		static int console_echo(lua_State *L);
		static int pause(lua_State *L);
		static int unpause(lua_State *L);
		static int ispaused(lua_State *L);
		static int getPlayer(lua_State *L);
		static int shakeCamera(lua_State *L);
		static int getModelNames(lua_State *L);
		static int getSprites(lua_State *L, int type);
		static int getShips(lua_State *L);
		static int getPlanets(lua_State *L);
	private:
		static vector<string> buffer;

		static bool Init();
		static bool Close();

		// Internal variables
		static SpriteManager* my_sprites;
		static lua_State *L;
		static bool luaInitialized;
};

#endif // __H_LUA__
