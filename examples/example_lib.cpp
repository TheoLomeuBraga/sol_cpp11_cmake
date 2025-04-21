#include <sol.hpp>
#include <lauxlib.h>
#include <math.h>
#include <string.h>
#include <iostream>

struct GameAcount
{
public:
    std::string user_name;
    std::string pass_word;
    GameAcount() {}

    GameAcount(std::string user_name, std::string pass_word)
    {
        this->user_name = user_name;
        this->pass_word = pass_word;
        std::cout << user_name << "'s acount created\n";
    }

    void talk(){
        std::cout << "my name is " << user_name << "\n";
    }

    ~GameAcount() { std::cout << "acount deleted\n"; }
};

void nothing(lua_State *L){}

void add_lib(lua_State *L){
    sol::state lua(L,nothing);
    lua.open_libraries(sol::lib::base, sol::lib::math,sol::lib::utf8);

    
    sol::constructors<sol::types<>, sol::types<std::string,std::string>> game_acount_ctor;
    lua.new_userdata<GameAcount>("GameAcount",game_acount_ctor, "user_name", &GameAcount::user_name, "pass_word", &GameAcount::pass_word,"talk",&GameAcount::talk);
}

#if defined(_WIN32) || defined(_WIN64)
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __attribute__((visibility("default")))
#endif

extern "C" EXPORT int luaopen_libexamplelib(lua_State *L)
{
    add_lib(L);
    return 1;
}