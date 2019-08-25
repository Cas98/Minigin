# Minigin
MINIGIN:
The engine is static library. So to run the engine you create an object from the minigin.h class and run it.
In this class the window gets created with SDL. All the neccesary components (like the renderer) get initialized and destroyed.
And the game loop gets runned. The game loop is fairly simple. It updates the scenemanager, renderer and inputmanager and time. 
If the inputmanager returns a false the gameloop will stop and the program will close.

SCENES:
1) Manager:
When you create a scene you ad it to the scene manager. 
You also set an active scene so the scene manager will only update the active scene.

2) Scene class:
This is a non final class. So if you want to create a scene create a new scene class that inherits from the Scene.h class and add it to the scenemanager.
The scene acts as a manager for gameobjects. You can add and remove gameobjects to the scene. Where the objects will be updated and rendered (if the scene is active).
You can add objects in two different ways. By using the Add or AddThreaded. 
If you use AddThreaded the game objects that are added here will be updated on a seperate thread.

GAMEOBJECT:
The game object uses the component pattern. You can add and remove components and check if a game object has a certain component.
It can only have one of each component. You can get component by type with a templated function.
The game object updates it's components.
It also holds a pointer to the scene it is part of.
The object also has a tag(string) you can set.

RENDERER:
Uses SDL to render images.
The renderer also creates render components at the start of the program and puts them in an inactive buffer.
When a render component is created it will take a component from the inactive buffer and place it in an active buffer. 
This active buffer will be rendered. 
And when a render component is deleted it wil be send back to the inactive buffer.
There are also buffers for inactive scenes that have gameobjects with render components.

INPUT:
1) Manager:
The input manager get the keystates from keyboard and controllers using XInput. It supports up to four controllers.
It also has functions to get states of keys (like up,down ,released,...).
It also can return the mouse position.


COMPONENTS:
1)Base:
Class all components inherit from.
Holds a pointer to its game object.
Has an enum disscribing the type of component it is.

2)Texture:
You create this componnet with a path to the image file and it creates a SDL texture for it.		

3)FPS:
A components that calculates the fps (also averages it out).
Then set the text component of its game object to the fps.	

4)Transform:
Hold the position, rotation and scale of an object.
Also provides functions to set and change these variables.

5)Input:
Uses the input manager to register input.
Holds a index for the controller that is used.
Also has a function to map keys to commands. The command is executed when the key is in the state its triggered.

6)Render:
Gets the texture from the texture component and renders them.
Also has new and delete operator overloaders to use the GetRenderComponent and SendRenderComponent from the renderer.

7)Script:
This component isn't final. You inherit from this component to create a script for game logic.
It provides a initialize and update function to override.

8)Subject:
Uses the observer pattern. And can send messages with the notify function to observers.
Can add and remove observers.

9)Text:
Takes in a string and path to a font file. 
Turns the string text into an image and stores it in its game objects texture component.
You  are also able to set the color of the text.

10)FSM:
Finite state machine component uses the state pattern. It Takes in a start state and updates it. 
When the state returns a new state the FSM switches the current state to this new state and deletes the old state.
When it return a nullptr it keeps the current state.
There is also a state class which can be inhereted from to create new states. 
The state class provides a HandleInput, Exit and Enter function to override.
These function get called in the FSM component.

11)Grid:
The grid component holds a 2D array of game object pointers.
You can set gameobjects at a certain index.
You can get the game object at a certain index.
You can remove a game object from the grid.
And you can set the gameobject pos to snap to the same pos as its index on the grid.

PENGO:
The game starts in the main menu where you can select the mode(Solo, Versus, Coop).
When started you first play the first level. When its completed you automatically start the next level. There are 3 levels.
The level ends when all snobees are dead or when one minute has passed. if all snobees are killed before the minute has past you get bonus points.
The game ends when all three levels are completed or when pengo runs out of lives. And you will be returned to the main menu.

Controls:
Player 1
W/A/S/D to move 
Q to push ice blocks (only pengo)

Player 2
arrow keys to move 
Enter to push ice blocks (only pengo)

Controller:
D-pad to move 
A to push ice blocks (only pengo)

Menu:
Mouse to interact with menu
ESC to activate pause menu in game

