# Project Boomerang
Welcome to the root of the project!

## Table Of Contents
- [Summary](#Summary)
- [Project Features](#Project-Features)
- [Project Goals](#Project-Goals)
- [Quick Tour](#Quick-Tour)
- [Repository Hierarchy](#Folder-Hierarchy)

## Summary
__Project Boomerang__ is an upcoming 2D fighter game that pits people against each other in a (TBD) environment. The main gimmick of the game is the weapons that players will use to attack each other. Instead of guns, fists, swords, or even magic, players must use their trusty boomerang to attack their opponents! A boomerang offers a unique attack style where players can angle them in unique directions to attack opponents at a wide varitiy of angles.

This game takes some inspiration from an indie game called [TowerFall](http://www.towerfall-game.com/) as well as a small mechanic that was present as a character skill in the [Kirby](https://kirby.fandom.com/wiki/Cutter) series.

## Project Features
- Created in Unreal Engine 4
- Local/Online Multiplayer
- Simple gameplay that encourages replayability and depth
- An accompanying third party app that can remotely interact with the game server (WIP)

## Project Goals
- An environment where one can learn how to use UE4 and learn both the ins and outs of it as well as some C++
- Experience creating an external app (WIP) that can connect and interact with the game via plugins and/or APIs
- Understand basic game networking and the relationship between game and server

## Quick Tour
This project will span __two__ repositories:
- __Project_Brng__: This repository will contain the vast majority of the work. This includes the game itself, the code used to deploy the infrastructure for the game server, and documentation for both.
- __Project_Brng_App__: This repository will contain code for the external app and relevant documentation for said app.

> For more details regarding __Project_Brng_App__, please refer to that [repository](https://github.com/maishiroma/Project_Brng_App).

## Repository Hierarchy
- [Docs](./Docs): Contains documention on how to deploy the server as well as some technical documentation on the game itself.
- [Game](./Game): Source folder for the UE4 project
- [ServerInfra](./ServerInfra): Terraform code that will be used to deploy a simple server to host the game