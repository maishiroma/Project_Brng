# Game Design Document
This documentation will serve as the foundation that this game will be designed by.

## Table of Contents
- [Summary](#Summary)
- [Gameplay Basics](#Gameplay-Basics)
- [Multiplayer](#Multiplayer)
- [Accompany App Integration](#Accompanying-App-Integration)

## Summary
Players are pitted against each other in a 1 on 1 fight death match. Players can attack each other using special weapons, boomeranges. Players lost health when they collide into a hostile boomerange. A player dies when they lost all of their health. Games are in a round basis: once a player wins a specific number of rounds, the game is over and the player with the most round wins is the champion.

## Gameplay Basics
This section is divided up into smaller sections, each of which go over specific areas

### Movement
Players move in a 2D plane, meaning they can only move vertical and horizontally. Players can walk/run on the ground and jump once. Players can also duck, which is useful for avoiding specific boomerang throws.

### Attacking
Players can thrown an unlimited number of boomerangs. However, if the player throws too many boomeranges, the attack power of each one will substancially decrease and won't reset until the player stops throwing boomerangs. When throwing a boomerang, the player normally throws it straight in front of them, and after a set amount of disitance, the boomerage will then move back towards the player. However, in mid-throw can lightly affect the throw trajectory of it by either going slightly upwards or slightly downwards. This allows for the boomerange to continue __behind__ the player, where it _won't_ stop until it either hits a wall or another player.

#### Boomerange Types
Players have access to two different type of boomerangs: normal and power ones. Power ones are slightly different in that they are slightly larger and slower when moving. They also do slightly more damage compared to normal ones. These also have the property of bouncing off of walls, allowing for these boomeranges to continuously bounce back and forth an area until X times. However, to throw one of these, the player must hold down the attack button a set amount of time. And like what was mentioned earlier, the more this is used without breaks, the weaker the boomerang's power will be as well as the number of times it can bounce off of walls.

Here's a small chart diagraming each type of boomerang:

| __Attribute__  | __Normal Boomerang__ | __Power Boomerang__   |
| :------------- | :------------------: | --------------------: |
| __Deploy Speed__ | Fast (rapid press) | Slow (hold & release) |
| __Travel Speed__ | Fast | Slower |
| __Attack Strength__ | Weak | Stronger |
| __Wall Durability__ | Break upon single collision | Bounce off multiple times |

And here's a chart for describing collisions with each type of boomerang (aka what happens if a boomerang hits another boomerang)

| __Boomerang Type__ | __Normal__ | __Power__ |
| :----------------- | :--------: | --------: |
| __Normal__ | Both destroyed | Power destroys normal |
| __Power__ | Power destroys normal | Both destroyed |

In other words, when two boomerangs of the __same type__ collide, both attacks are _nullified_. Otherwise a power boomerange will always destroy a normal boomerange and still continue in its path.

## Multiplayer
This game will primarily be a multiplayer experience. As such, players will need to connect to a remote server which will be hosting games.

When connected, the player can then choose to either create a room or join a room. 

### Creating Room
When a room is created, the player is prompted to either set a password or not in the room. This password is to prevent randoms from joining a room if the player desires to play with a specific person.

Once the player creates a room, the game will then wait for a connection to come into the room, at which the player will then be requested by the game to accept the new challenger. Once so, the game will begin.

Once a game is concluded, the player will then either be presented with two options: rematch or quit. If the hosts quits, both players will be returned to the main menu for multiplayer matches.

### Join Room
The player is shown a list of available rooms. Rooms that have passcodes will be marked as such. When a player joing a room, a passcode prompt will be presented (if required). Otherwise, the player then waits for the game to begin.

All logic afterwards is the same as if the player created the room.

## Accompanying App Integration
> This section is a WIP

The game will also be sporting a connection to an external app. This external app will allow for some extra features in the game, primarly useful for those who are spectating.

Some of these features include:
- Voice Chats
- Game Stats
- In game Perks