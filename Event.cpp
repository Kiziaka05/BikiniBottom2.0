// #include "Event.h"

// Event::Event()
// {
//     GameMap = nullptr;
//     Hero = nullptr;
// }

// Event::Event(Map *GameMap1, MainHero *Hero1)
// {
//     GameMap = GameMap1;
//     Hero = Hero1;
// }

// Event::~Event() {}

// void Event::HandleEvent() {}

// KeyPressEvent::KeyPressEvent(char key1, Map *GameMap1, MainHero *Hero1)
// {
//     Event(GameMap1, Hero1);
//     key = key1;
// }

// KeyPressEvent::~KeyPressEvent() {}

// void KeyPressEvent::HandleEvent()
// {
//     //std::pair<int, int> loc = Hero->GetLocation();

//     if (key == 'w' || key == 'W') {
//         if (loc.first == 0) {
//             std::cout << std::endl << "\n\x1B[31mUnable to move up!\033[0m" << std::endl;
//             return;
//         }
//         //Hero->SetLocation(loc.first - 1, loc.second);
//     } else if (key == 's' || key == 'S') {
//         if (loc.first == GameMap->GetSize() - 1) {
//             std::cout << std::endl << "\n\x1B[31mUnable to move down!\033[0m" << std::endl;
//             return;
//         }
//         //Hero->SetLocation(loc.first + 1, loc.second);
//     } else if (key == 'a' || key == 'A') {
//         if (loc.second == 0) {
//             std::cout << std::endl << "\n\x1B[31mUnable to move left!\033[0m" << std::endl;
//             return;
//         }
//         //Hero->SetLocation(loc.first, loc.second - 1);
//     } else if (key == 'd' || key == 'D') {
//         if (loc.second == GameMap->GetSize() - 1) {
//             std::cout << std::endl << "\n\x1B[31mUnable to move right!\033[0m" << std::endl;
//             return;
//         }
//         //Hero->SetLocation(loc.first, loc.second + 1);
//     } else {
//         std::cout << std::endl << "\n\x1B[31mUnknown command!\033[0m" << std::endl;
//     }
// }

// EncounterWithNPCEvent::EncounterWithNPCEvent() {}

// EncounterWithNPCEvent::EncounterWithNPCEvent(Map *GameMap1, MainHero *Hero1)
// {
//     Event(GameMap1, Hero1);
//     //CurrCell = GameMap->GetCell(Hero->GetLocation().first, Hero->GetLocation().second);
//     CurrUnit = CurrCell->GetUnit();
// }

// EncounterWithNPCEvent::~EncounterWithNPCEvent() {}

// void EncounterWithNPCEvent::HandleEvent()
// {
//     if (CurrCell != nullptr && CurrCell->IsCellHaveSomething()) {
//         if (CurrUnit->IsEnemy) {
//             EncounterWithEnemy NewEvent(GameMap, Hero);
//             NewEvent.HandleEvent();
//         } else if (!CurrUnit->IsEnemy && !CurrUnit->IsStruct && CurrUnit->IsNPC) {
//             EncounterWithFriendly NewEvent(GameMap, Hero);
//             NewEvent.HandleEvent();
//         } else if (CurrUnit->IsStruct) {
//             EncounterWithStruct NewEvent(GameMap, Hero);
//             NewEvent.HandleEvent();
//         }
//     } else {
//         std::cout << std::endl << "\n\x1B[31mThere is no NPC on this cell!\033[0m" << std::endl;
//     }
// }

// EncounterWithEnemy::EncounterWithEnemy(Map *GameMap1, MainHero *Hero1)
// {
//     EncounterWithNPCEvent(GameMap, Hero);
// }

// EncounterWithEnemy::~EncounterWithEnemy() {}

// void EncounterWithEnemy::HandleEvent()
// {
//     double HeroHp = Hero->GetHP();
//     double EnemyHp = CurrUnit->GetHP();

//     //battle logic will be added soon

//     if (EnemyHp <= 0) {
//         std::cout << std::endl << "Enemy is defeated!" << std::endl;
//         CurrCell->RemoveUnit();
//     }
//     if (HeroHp <= 0) {
//         std::cout << std::endl << "Hero is defeated!" << std::endl;
//     }
// }

// EncounterWithFriendly::EncounterWithFriendly(Map *GameMap1, MainHero *Hero1)
// {
//     EncounterWithNPCEvent(GameMap, Hero);
// }

// EncounterWithFriendly::~EncounterWithFriendly() {}

// void EncounterWithFriendly::HandleEvent()
// {
//     //some interaction will be added soon
// }

// EncounterWithStruct::EncounterWithStruct(Map *GameMap1, MainHero *Hero1)
// {
//     EncounterWithNPCEvent(GameMap, Hero);
// }

// EncounterWithStruct::~EncounterWithStruct() {}

// void EncounterWithStruct::HandleEvent()
// {
//     if (CurrUnit->IsBreakable) {
//         char key;
//         std::cout << std::endl << "Do you want to try to break it?[y/n]" << std::endl;
//         if (key == 'y') {
//             //breaking logic will be added soon
//             if (CurrUnit->GetHP() <= 0) {
//                 std::cout << std::endl << "You breaked the structure!" << std::endl;
//                 CurrCell->RemoveUnit();
//             }
//         } else if (key == 'n') {
//             std::cout << std::endl << "Then move to another cell!" << std::endl;
//         } else {
//             std::cout << std::endl << "Invalid command!" << std::endl;
//         }
//     } else {
//         //some interaction
//     }
// }

// ChooseEvent::ChooseEvent()
// {
//     //SetEvent();
// }

// ChooseEvent::~ChooseEvent()
// {
//     if (NewEvent != nullptr)
//         delete NewEvent;
// }

// //void ChooseEvent::SetEvent(Event *Event1)
// //{
// //    NewEvent = Event1;
// //}

// void ChooseEvent::HandleEvent()
// {
//     NewEvent->HandleEvent();
// }
