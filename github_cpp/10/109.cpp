



#include "stdafx.h"

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>


}

#include <vector>
#undef min

#include <algorithm>
#define _J(j) ( (j+1)%2 )
#define _I(i) ( (i+1)   )
int lua_Distance(lua_State * L)
{
    size_t sz1, sz2;
    const char * str1 = luaL_checklstring(L, 1, &sz1);
    const char * str2 = luaL_checklstring(L, 2, &sz2);
    if (sz1 > sz2) {
        std::swap(sz1, sz2);
        std::swap(str1, str2);
    }
    std::vector<size_t> EditBuffer[2];
    EditBuffer[0].resize(sz1 + 1,0);
    EditBuffer[1].resize(sz1 + 1,0);
    for (size_t i = 0; i <= sz1; i++) {
        EditBuffer[0][i] = i;
    }
    for (size_t j = 0; j < sz2;j++) {
        for (auto it = EditBuffer[_J(j)].begin(); it != EditBuffer[_J(j)].end();  it++) {
            *it = 0;
        }
        EditBuffer[_J(j)][0] = j +1;
        for (size_t i = 0; i < sz1;i++) {
            if (str2[j] == str1[i]) {
                EditBuffer[_J(j)][_I(i)] = EditBuffer[_J(j - 1)][_I(i - 1)];
            }
            else {
                EditBuffer[_J(j)][_I(i)] = std::min(EditBuffer[_J(j)][_I(i - 1)] + 1,
                                           std::min(EditBuffer[_J(j - 1)][_I(i)] + 1,
                                                    EditBuffer[_J(j - 1)][_I(i - 1)] + 1));
            }
        }
    }
    lua_pushinteger(L, EditBuffer[_J(sz2 - 1)][_I(sz1 - 1)]);
    return 1;
}


extern "C" int __declspec(dllexport) luaopen_EditDistance(lua_State* L)
{
    static const struct luaL_Reg methods[] =
    {
        { "Distance", lua_Distance },
        { NULL, NULL }
    };
    luaL_register(L, "EditDistance", methods);


    return 1;
}
