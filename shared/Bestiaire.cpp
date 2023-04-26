// /*
// ** EPITECH PROJECT, 2022
// ** RType
// ** File description:
// ** Bestiaire
// */

// #include "Bestiaire.hpp"

// RType::Shared::Bestiaire::Bestiaire()
// {
//     load_bestiaire_map();
// }

// // create Bestiaries from files and can send to client by string
// void RType::Shared::Bestiaire::load_bestiaire_map(void)
// {
//     int key;
//     std::string line;
//     std::ifstream file_stream;
//     std::smatch cmd;
//     file_stream.open("shared/Bestiaire.txt");
//     if (!file_stream.is_open())
//         std::cout << "Error: file not found" << std::endl;
//     while (file_stream.good()) {
//         std::getline(file_stream, line);
//         if (line[0] == '#')
//             continue;
//         line = std::regex_replace(line, std::regex("\\s{2,}"), " ");
//         std::regex_search(line, cmd, std::regex("^[0-9]+"));
//         key = std::stoi(cmd[0]);
//         line = line.substr(line.find(" ")+1, line.length());
//         _bestiaire[key] = line;
//     }
//     file_stream.close();
// }

// void RType::Shared::Bestiaire::registerAttribute()
// {
//     _coordinator.registerAttribute<RType::Shared::ECS::Speed>();
//     _coordinator.registerAttribute<RType::Shared::ECS::Health>();
//     _coordinator.registerAttribute<RType::Shared::ECS::Attack>();
// }

// RType::Shared::ECS::Entity RType::Shared::Bestiaire::create_mob(int type)
// {
//     std::string tmp = _bestiaire[type];
//     std::cout << "TYPE :" << type << " TMP :" << tmp << std::endl;
//     size_t pos;
//     std::vector<std::string>args;
//     while ((pos = tmp.find(" ")) != std::string::npos) {
//         args.push_back(tmp.substr(0, pos));
//         tmp.erase(0, pos + 1);
//     }
//     args.push_back(tmp);
//     _coordinator.init();
//     this->registerAttribute();
//     RType::Shared::ECS::Entity entity = _coordinator.createEntity("Enemy type " + std::to_string(type));
//     _coordinator.addAttribute<RType::Shared::ECS::Health>(entity, {std::stoi(args[0].c_str())});
//     // _coordinator.addAttribute<RType::Shared::ECS::Attack>(entity, {std::stoi(args[1].c_str()), RType::Shared::ECS::Speed{std::stof(args[2].c_str())}});
//     _coordinator.addAttribute<RType::Shared::ECS::Speed>(entity, {std::stof(args[3].c_str())});
//     return entity;
// }

// std::vector<RType::Shared::ECS::Entity> RType::Shared::Bestiaire::get_wave_mob(std::string wave)
// {
//     std::vector<RType::Shared::ECS::Entity> mobs;
//     size_t pos = 0;
//     int type = 0;
//     int token;
//     wave = std::regex_replace(wave, std::regex("ty_"), "");
//     while ((pos = wave.find(" ")) != std::string::npos) {
//         token = std::stoi(wave.substr(0, pos));
//         if (type == 0) {
//             type = token;
//         } else {
//             for (int i = 0; i < token; i++)
//                 mobs.push_back(this->create_mob(type));
//             type = 0;
//         }
//         wave.erase(0, pos + 1);
//     }
//     for (int i = 0; i < std::stoi(wave); i++)
//         mobs.push_back(this->create_mob(type));
//     return mobs;
// }

// std::string RType::Shared::Bestiaire::get_wave_string(int wave)
// {
//     int i = 0;
//     std::string line;
//     std::ifstream file_stream;
//     file_stream.open("shared/Scripte.txt");
//     if (!file_stream.is_open())
//         std::cout << "Error: file not found" << std::endl;
//     while (file_stream.good()) {
//         std::getline(file_stream, line);
//         line = std::regex_replace(line, std::regex("\\s{2,}"), " ");
//         if (i == wave)
//             break;
//         i++;
//     }
//     file_stream.close();
//     return line;
// }

// RType::Shared::Bestiaire::~Bestiaire()
// {
// }
