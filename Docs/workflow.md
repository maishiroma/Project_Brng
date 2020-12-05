# Workflow

## Table of Contents
- [Board](#Board)
- [Project Source](#Project-Source)
- [Code](#Code)
- [Art](#Art)

## Board
The board for this project can be found [here](https://github.com/maishiroma/Project_Brng/projects/1)

On this board we have established the following columns:
- __Backlog__: List of all tasks that have yet to be completed
- __Ready__: Tasks that are ready to be worked on
- __In Progress__: Tasks that are in progress
- __Blocked__: Tasks that cannot be done due to some external reasons (another issue blocking progress, needing more reqs, etc)
- __Review__: Tasks that are ready to be reviewed, usually in the form of a PR (otherwise noted)
- __Done__: Tasks that are completed

The general rule of thumb when doing work:
1. Create/Find an issue that needs to be solved
2. Once all pre-reqs for it are complete, drag it into __Ready__.
3. To start working on it, drag it into __In Progress__ and create an issue from it.
    - This can be done by hovering over the three dots and selecting convert to an issue.
4. Work on it in a seperate branch.
5. Once the branch is ready to be merged (aks the feature is done), open a PR for it and drag the ticket into __Review__
6. Once it gets approved and/or confirmed it working as expected, PR is merged and ticket is now under __Done__

## Project Source
The game project source is layed out from the root as follows: (May change as we work on this)
```
|-----Game
        |
        |-----MiscFolders
        |
        |-----Content
            |
            |-----Source
            |
            |-----Animations
            |
            |-----BlueprintClasses
            |
            |-----Blueprints
            |
            |-----Maps
            |
            |-----Sprites
            |
            |-----Materials
            |
            |-----UI
            |
            |-----Tilemaps
```

## Code
The project will be a mixture of Blueprints and C++ code writing, with all of the code going under the `Source` folder.

Standard coding practices will abid for those source C++ files with the following guidelines:
- CamelCasing for Class Names and Methods
- camelCasing for variables
- ALL_CAPS for constants

## Art
All Art should be placed in the proper folder in the `Game` root directory. Example when creating 2D art:
```
|-----Game
        |-----Content
            |
            |-----Sprites
                |
                |-----Character
                |
                |-----Map
                |
                |-----UI
                |
                |------Items
```

Within those directories, proper sub directories can be made to further organize the type of sprite. I.E. player sprites can go under `Character/Player`.

A standard for all art should be defined in the README.md of that directory, which should include the dimensions and/or theme of the game graphics.