// #include "GameManager.h"

// GameManager::GameManager()
// {
//     GameMap = new Map();
//     Hero = new MainHero();
//     NewRender = new RenderGame(GameMap);
// }

// GameManager::~GameManager()
// {
//     if (NewRender != nullptr)
//         delete NewRender;
//     if (Hero != nullptr)
//         delete Hero;
//     if (GameMap != nullptr)
//         delete GameMap;
// }

// void GameManager::GameLoop()
// {
//     bool IsGameActive = true;
//     int key;

//     while (IsGameActive) {
//         system("cls");

//         NewRender->Render();
//         std::cout << std::endl
//                   << "Prees '1' to move | Press '2' to see stats | Press '3' to quit the game"
//                   << std::endl;

//         if (!(std::cin >> key)) {
//             std::cin.clear();
//             std::cin.ignore(1000, '\n');
//             std::cout << "Invalid input. Please enter a number." << std::endl;
//             continue;
//         }

//         switch (key) {
//         case 1: {
//             char direction;
//             std::cout
//                 << std::endl
//                 << "Press 'W' to move up; 'S' to move down; 'A' to move left; 'D' to move right"
//                 << std::endl;
//             std::cin >> direction;
//             std::cout << "Programm is working";
//             NewEvent = new KeyPressEvent(direction, GameMap, Hero);
//             std::cout << "Programm is working";
//             NewEvent->HandleEvent();
//             std::cout << "Programm is working";
//             delete NewEvent;
//             std::cout << "Programm is working";
//             break;
//         }
//         case 2: {
//             system("cls");
//             std::cout << "Your HP: " << Hero->GetHP() << std::endl
//                       << "Your Level: " << Hero->GetLevel() << std::endl
//                       << "Your Mana: " << Hero->GetMana();
//             system("pause");
//             break;
//         }
//         case 3: {
//             IsGameActive = false;
//             break;
//         }
//         default: {
//             std::cout << std::endl << "Invalid command!" << std::endl;
//             system("pause");
//             break;
//         }
//         }
//     }
// }
