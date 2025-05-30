#ifndef EVENT_H_DEFINED
#define EVENT_H_DEFINED

#include "AI.h"
#include "Cell.h"
#include "Map.h"
#include "Unit.h"
#include <iostream>
#include <string>

// class Event
// {
// protected:
//     Map *GameMap;
//     MainHero *Hero;

// public:
//     Event();
//     Event(Map *GameMap1, MainHero *Hero1);
//     virtual ~Event();
//     virtual void HandleEvent();
// };

// class KeyPressEvent : public Event
// {
// private:
//     char key;

// public:
//     KeyPressEvent(char key1, Map *GameMap1, MainHero *Hero1);
//     virtual ~KeyPressEvent();
//     virtual void HandleEvent() override;
// };

// class EncounterWithNPCEvent : public Event
// {
// protected:
//     Cell *CurrCell;
//     Unit *CurrUnit;

// public:
//     EncounterWithNPCEvent();
//     EncounterWithNPCEvent(Map *GameMap1, MainHero *Hero);
//     virtual ~EncounterWithNPCEvent();
//     virtual void HandleEvent() override;
// };

// class EncounterWithEnemy : public EncounterWithNPCEvent
// {
// public:
//     EncounterWithEnemy(Map *GameMap1, MainHero *Hero1);
//     virtual ~EncounterWithEnemy();
//     virtual void HandleEvent() override;
// };

// class EncounterWithFriendly : public EncounterWithNPCEvent
// {
// public:
//     EncounterWithFriendly(Map *GameMap1, MainHero *Hero1);
//     virtual ~EncounterWithFriendly();
//     virtual void HandleEvent() override;
// };

// class EncounterWithStruct : public EncounterWithNPCEvent
// {
// public:
//     EncounterWithStruct(Map *GameMap1, MainHero *Hero1);
//     virtual ~EncounterWithStruct();
//     virtual void HandleEvent() override;
// };

// class ChooseEvent
// {
// private:
//     Event *NewEvent;

// public:
//     ChooseEvent();
//     ~ChooseEvent();

//     void SetEvent(Event *Event1);
//     void HandleEvent();
// };

#endif //EVENT_H_DEFINED
