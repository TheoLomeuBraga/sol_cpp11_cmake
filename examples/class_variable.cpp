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
    ~GameAcount() {std::cout << "acount deleted\n";}
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

void print_hello_world(){
    std::cout << "hello world\n";
}



int main() {
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::math,sol::lib::utf8);

    sol::constructors<sol::types<>, sol::types<std::string,std::string>> game_acount_ctor;
    lua.new_userdata<GameAcount>("GameAcount",game_acount_ctor, "user_name", &GameAcount::user_name, "pass_word", &GameAcount::pass_word);

    sol::constructors<sol::types<>, sol::types<GameAcount,int,int>> player_ctor;
    lua.new_userdata<Player>("Player",player_ctor,"acount",&Player::acount,"position_y",&Player::position_x,"position_y",&Player::position_y,"talk",&Player::talk,"make_math",&Player::make_math);

    lua.set_function("print_hello_world",print_hello_world);
    





    
    lua.script(

        "print_hello_world()\n"
        "acount = GameAcount.new(\"alan\",\"123\")\n"
        "player = Player.new(acount,64,128)\n"
        "player:talk()\n"

        "math_value = player:make_math(2,2)\n"
        "print(\"2 + 2 is: \", math_value)\n"

        "player = nil\n"

    );
    lua.collectgarbage();

    lua.script(

        "function say()\n"
        "   print(\"some thing\")\n"
        "end\n"

    );
    lua.get<sol::function>("say")();

    lua["random_number"] = 16;
    lua.script(
        "print(\"lua\",random_number)"
    );
    std::cout << "c++ " << lua.get<int>("random_number") << "\n";






    int *pointable_number = new int(39);
    lua["pointable_number"] = *pointable_number;
    std::cout << "pointable_number " << lua.get<int>("pointable_number") << "\n";


    lua.script(
        "pointable_number = pointable_number + 10\n"
        "print(\"pointable_number\",pointable_number)\n"
    );

    std::cout << "pointable_number on lua " << lua.get<int>("pointable_number") << "    "  << "pointable_number on c++ " << *pointable_number << "\n";

    delete pointable_number;


    lua.script(
        "text = \"ã§êúì\"\n"
        "print(text)\n"
    );

    std::cout << lua.get<std::string>("text") << "\n";


}
