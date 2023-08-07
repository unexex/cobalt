
#define l2Dlib_c
#define LUA_LIB



#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#include "lj_obj.h"
#include "lj_err.h"
#include "lj_buf.h"
#include "lj_strscan.h"
#include "lj_strfmt.h"
#if LJ_HASFFI
#include "lj_ctype.h"
#include "lj_cdata.h"
#include "lj_cconv.h"
#include "lj_carith.h"
#endif
#include "lj_ff.h"
#include "lj_lib.h"


#include "classes.h"


static int vec2_index(lua_State *L) {
  Vec2* vec2 = (Vec2*)lua_touserdata(L, 1);
  const char* key = luaL_checkstring(L, 2);
  if (strcmp(key, "X") == 0) {
    lua_pushnumber(L, vec2->x);
    return 1;
  } else if (strcmp(key, "Y") == 0) {
    lua_pushnumber(L, vec2->y);
    return 1;
  }
  return 0;
}

static int push_vec2(lua_State *L, float x, float y) {
  Vec2* vec2 = (Vec2*)lua_newuserdata(L, sizeof(Vec2));
  vec2->x = x;
  vec2->y = y;
  if (luaL_newmetatable(L, "vec2")) {
    lua_pushcfunction(L, vec2_index);
    lua_setfield(L, -2, "__index");
  }
  lua_setmetatable(L, -2);
  return 1;
}


LJLIB_CF(vec2_add) {
  Vec2* a = (Vec2*)lua_touserdata(L, 1);
  Vec2* b = (Vec2*)lua_touserdata(L, 2);
  push_vec2(L, a->x + b->x, a->y + b->y);
  return 1;
}
LJLIB_CF(vec2_sub) {
  Vec2* a = (Vec2*)lua_touserdata(L, 1);
  Vec2* b = (Vec2*)lua_touserdata(L, 2);
  push_vec2(L, a->x - b->x, a->y - b->y);
  return 1;
}
LJLIB_CF(vec2_mul) {
  Vec2* a = (Vec2*)lua_touserdata(L, 1);
  Vec2* b = (Vec2*)lua_touserdata(L, 2);
  push_vec2(L, a->x * b->x, a->y * b->y);
  return 1;
}
LJLIB_CF(vec2_div) {
  Vec2* a = (Vec2*)lua_touserdata(L, 1);
  Vec2* b = (Vec2*)lua_touserdata(L, 2);
  push_vec2(L, a->x / b->x, a->y / b->y);
  return 1;
}
LJLIB_CF(vec2_new) {
  float x = luaL_checknumber(L, 1);
  float y = luaL_checknumber(L, 2);
  push_vec2(L, x, y);
  return 1;
}
LJLIB_CF(vec2_fromOffsetScale) {
  float x = luaL_checknumber(L, 1);
  float y = luaL_checknumber(L, 2);
  float ox = luaL_checknumber(L, 3);
  float oy = luaL_checknumber(L, 4);

  int screenx, screeny;

  screenx = luaL_checknumber(L, 5);
  screeny = luaL_checknumber(L, 6);

  x = x * screenx;
  y = y * screeny;
  x += ox;
  y += oy;
  x = (x / screenx) * 2 - 1;
  y = (y / screeny) * 2 - 1;

  push_vec2(L, x, y);
  return 1;
}

static const luaL_Reg vec2lib[] = {
    {"new", vec2_new},
    {"add", vec2_add},
    {"sub", vec2_sub},
    {"mul", vec2_mul},
    {"div", vec2_div},
    {"fromScreen", vec2_fromOffsetScale},
    {NULL, NULL}
};



LUAMOD_API int luaopen_2D (lua_State *L) {
  luaL_newlib(L, vec2lib);

  push_vec2(L, 0, 0);
  lua_setfield(L, -2, "zero");
  push_vec2(L, 1, 1);
  lua_setfield(L, -2, "one");
  return 1;
}