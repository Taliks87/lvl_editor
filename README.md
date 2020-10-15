# 2d Level Editor (made by QT 5.13.0)
![Alt text](/screen.PNG?raw=true "2d Level Editor")

All game item call `pawn`

Editor create/save/load levels in folder `<level editor's root>/data`.
When the project started trying open `<level editor's root>/data/config.json`.
If it does not exist, it'll be created. Also tries to open `<level editor's root>/data/test.lvl` map at startup.

To add elements to the map use the drag-drop method from the pawn type's list(on the left).
Also it is possible to move a pawn by mouse on the map.
To remove the pawn use the middle mouse button.
You can edit fields of pawns in the panel information(on the right).

For adding a new pawn type and setup rules use `<level editor's root>/data/config.json`.
You can see `example of data folder` in `data-example.zip`.