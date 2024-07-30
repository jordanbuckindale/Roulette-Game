# Project Structure

## Overview
The goal is to create a structure for organizing this large project. The diagram shows the modular design I have created to make the code more manageable. The goal is to make it so the project can be built incrementally, allowing for testing of each component as needed.

### Goals:
* Modularity: Each component is seperate, allowing it to be easier to develop and maintain.
* Reuseability: Functions and structures can be reused across different aspects of the project.
* Scalability: Easy implementation and modification of new features without disrupting entire codebase.
* Concision: Clear and concise implemenation to make it easier for navigation and understanding of codebase.


## Diagram
![roulette-game - Frame 3 (1)](https://github.com/user-attachments/assets/5dddfcc0-f5bc-4e0c-ba07-35eb78322a56)

##
## Components

- **Entry Point (yellow)**
  - _main.c_: This is the entry point of the application, responsible for initializing and running the game.

- **Header File (orange)**
  - _roulette_ui.h_: The header file that declares the main structures and functions used across the project.

- **Core Functionality Files (blue)**
  - _roulette_ui.c_: Manages the overall UI structure and integration.
  - _roulette_logic.c_: Handles the game rules and logic.
  - _animations.c_: Manages all animations in the game.
  - _drawings.c_: Responsible for rendering all visual elements.

- **Structure Files (light yellow)**
  - _wheel structure_: Defines the roulette wheel properties.
  - _betting table structure_: Defines the betting table layout.
  - _chips structure_: Defines chip properties and behaviors.
  - _buttons structure_: Defines UI button properties.

- **Drawing Implementation Files (light yellow, bottom)**
  - _wheel drawing_: Implements wheel drawing.
  - _betting_table drawing_: Implements betting table drawing.
  - _chips drawing_: Implements chip drawing.
  - _buttons drawing_: Implements button drawing.

- **Animation Specific Files (light yellow, right)**
  - _chip animation_: Handles chip movement animations.
  - _wheel animation_: Manages wheel spinning animation.
  - _button bet_: Possibly will handle betting button interactions and animations.
