#include "monster_generated.h"
#include <fstream>
#include <iostream>
using namespace MyGame::Sample;

int main()
{
    // Create a `FlatBufferBuilder`, which will be used to create our
    // monsters' FlatBuffers.
    flatbuffers::FlatBufferBuilder builder(1024);

    // Create a `vector` representing the inventory of the Orc. Each number
    // could correspond to an item that can be claimed after he is slain.
    unsigned char treasure[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto inventory = builder.CreateVector(treasure, 10);

    auto weapon_one_name = builder.CreateString("Sword");
    short weapon_one_damage = 3;
    auto weapon_two_name = builder.CreateString("Axe");
    short weapon_two_damage = 5;
    // Use the `CreateWeapon` shortcut to create Weapons with all the fields set.
    auto sword = CreateWeapon(builder, weapon_one_name, weapon_one_damage);
    auto axe = CreateWeapon(builder, weapon_two_name, weapon_two_damage);
    // Place the weapons into a `std::vector`, then convert that into a FlatBuffer `vector`.
    std::vector<flatbuffers::Offset<Weapon>> weapons_vector;
    weapons_vector.push_back(sword);
    weapons_vector.push_back(axe);
    auto weapons = builder.CreateVector(weapons_vector);

    Vec3 points[] = {Vec3(1.0f, 2.0f, 3.0f), Vec3(4.0f, 5.0f, 6.0f)};
    auto path = builder.CreateVectorOfStructs(points, 2);

    // Serialize a name for our monster, called "Orc".
    auto name = builder.CreateString("Orc");
    // Create the position struct
    auto position = Vec3(1.0f, 2.0f, 3.0f);
    // Set his hit points to 300 and his mana to 150.
    int hp = 300;
    int mana = 150;

    // Finally, create the monster using the `CreateMonster` helper function
    // to set all fields.
    // auto orc = CreateMonster(builder, &position, mana, hp, name, inventory,
    // Color_Red, weapons, Equipment_Weapon, axe.Union(),
    // path);
    // You can use this code instead of `CreateMonster()`, to create our orc
    // manually.
    MonsterBuilder monster_builder(builder);
    monster_builder.add_pos(&position);
    monster_builder.add_hp(hp);
    monster_builder.add_name(name);
    monster_builder.add_inventory(inventory);
    monster_builder.add_color(Color_Red);
    monster_builder.add_weapons(weapons);
    monster_builder.add_equipped_type(Equipment_Weapon);
    monster_builder.add_equipped(axe.Union());
    auto orc = monster_builder.Finish();

    builder.Finish(orc);

    // This must be called after `Finish()`.
    uint8_t *buf = builder.GetBufferPointer();
    int size = builder.GetSize(); // Returns the size of the buffer that
    // `GetBufferPointer()` points to.
    std::ofstream output("monster.mnn", std::ofstream::binary);
    output.write((const char *)buf, size);




    return 0;
}
