#include <sol.hpp>
#include <iostream>
#include <cassert>
#include <cmath>
#include <string>

struct GameAcount {
public:
    std::string user_name;
    std::string pass_word;
    GameAcount() {}

    GameAcount(std::string user_name,std::string pass_word) {
        this->user_name = user_name;
        this->pass_word = pass_word;
        std::cout << user_name << "'s acount created\n";
    }
};

class Player{
public:
    Player() {}
    
    GameAcount acount;
    int position_x = 0;
    int position_y = 0;

    Player(GameAcount acount,int position_x,int position_y) {
        this->acount = acount;
        this->position_x = position_x;
        this->position_y = position_y;

        std::cout << "player " << acount.user_name << " created " << "in " << position_x << " " << position_y << " i'm in ( " << position_x << " , " << position_y << " )" << "\n";

    }

    void talk(){
        std::cout << "hello my name is " << acount.user_name << "\n";
    }

    int make_math( int a , int b ){
        return a + b - 1;
    }

};

int main() {
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::math);

    sol::constructors<sol::types<>, sol::types<std::string,std::string>> game_acount_ctor;
    lua.new_userdata<GameAcount>("GameAcount",game_acount_ctor, "user_name", &GameAcount::user_name, "pass_word", &GameAcount::pass_word);

    sol::constructors<sol::types<>, sol::types<GameAcount,int,int>> player_ctor;
    lua.new_userdata<Player>("Player",player_ctor,"acount",&Player::acount,"position_y",&Player::position_x,"position_y",&Player::position_y,"talk",&Player::talk,"make_math",&Player::make_math);


    
    
    lua.script(
        "acount = GameAcount.new(\"alan\",\"123\")\n"
        "player = Player.new(acount,64,128)\n"
        "player:talk()\n"
        "math_value = player:make_math(2,2)\n"
        "print(\"2 + 2 is: \", math_value)\n"
    
    );
}
