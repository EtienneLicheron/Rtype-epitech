// /*
// ** EPITECH PROJECT, 2022
// ** RType
// ** File description:
// ** Bestiaire
// */

// #ifndef __BESTIAIRE_HPP__
// #define __BESTIAIRE_HPP__
// #include <string>
// #include <exception>
// #include <map>
// #include <vector>
// #include <fstream>
// #include <iostream>
// #include <string>
// #include <regex>

// #include "ECS/Attribute.hpp"
// #include "ECS/Entity.hpp"
// #include "ECS/Coordinator.hpp"

// namespace RType
// {
//     namespace Shared
//     {
//         class Bestiaire
//         {
//         public:
//             Bestiaire();
//             ~Bestiaire();
//             std::vector<RType::Shared::ECS::Entity> get_wave_mob(std::string wave);
//             RType::Shared::ECS::Entity create_mob(int type);
//             std::string get_wave_string(int wave);

//         private:
//             std::map<int, std::string> _bestiaire;
//             void load_bestiaire_map(void);
//             void registerAttribute();
//             Shared::ECS::Coordinator _coordinator;
//         };
//     }
// }

// #endif /* !__BESTIAIRE_HPP__ */
