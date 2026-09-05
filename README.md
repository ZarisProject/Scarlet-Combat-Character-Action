# Scarlet Combat: Character Action

Unreal Engine 5 toolkit for creating character action combat systems. The approach used in this system is entirely dependent on animations. Specify input windows and transition points using animation notifies and create branching combo sequences using Data Tables.

**Status: Preproduction**

## Principle
![](Documentation/Attachments/Screenshot%202026-08-28%20154600.png)
[Obsidian Diagram File](Documentation/Principle%20Diagram.canvas)

Scarlet Character Action is entirely based on animations. By adding special animation notifies to animation sequences one can specify combo branch windows, attack trace windows and other types of effects to each individual animation (later called "move").

### Move Set Library
A data table that contains data about every move and their relation to other moves - therefor it contains information about every available combo. 

Each entry contains following information:
* `MoveName` - name of the move, acts as a key value in the data table;
* `Animation` - animation montage corresponding to the move;
* `ComboBranches` - a dictionary (`TMap`) that maps *Combo Keys* to following moves.
* ... *Additional meta data that will be added later*.

### Character Action Component (`SC_CharacterAction`)
An actor component that handles incoming inputs, fetches combo information from *Move Set Libraries* (one component can look up moves from multiple libraries) and triggers new move animations.

### Input
Input is provided to Character Action Component using the following method 
```c++
void Input(FName Input, int32 Complexity);
```
Provided input is buffered up and served  to *Combo Input Notifies* on demand. To learn more about specifying input complexity see [Input Providing](Documentation/Input%20Providing.md).

#### Character Action Input System
Advanced input system implemented as a separate actor component. While non mandatory, this system acts as an important addition to the rest of the Character Action combat system, by providing easy means of capturing complex inputs from the player.

### Move Animation
Currently playing animation montage with special Animation Notifies attached to it.

### Animation Notifies

![](Documentation/Attachments/Screenshot%202026-08-28%20152549.png)
#### Combo Input Notify
A Notify State (notify acting over a duration), that represents a time window, in which a certain input will result in an execution of a new combo move. Actual execution of the next move will be delayed until the next *Combo Transition Notify*. 

Each *Combo Input Notify* is assigned a *Combo Key* value, that is mapped to the next move by Move Set Library (`ComboBranches`). This approach allows for reuse of animations in different combo sequences. If the correct input is served while the *Combo Input Notify* is active (and other conditions are met, if such are specified), this notify's *Combo Key* is cached, for *Combo Transition Notify* to handle triggering of the next move later on.  Depending on configuration, *Combo Input Notifies* may override each other.

To learn how input is served to *Combo Input Notifies* see [Serving Input to Notifies](Documentation/Serving%20Input%20to%20Notifies.md).

#### Combo Transition Notify
As specified in *Combo Input Notify* description, this notify specifies the point of transition between combo moves. Once the *Combo Transition Notify* is reached, the currently cached *Combo Key* (if such is present) is sent to Character Action Component, which handles animation switching.

*Combo Transition Notifies* come in two forms:
* Standard Notify (Transition point) - a single point of animation, at which a transition between moves is possible. *Combo Key* must be cached before reaching this point for transition to occur.
* Notify State (Transition Window) - a time window, during which any cached *Combo Key*  immediately results in a transition to a new move. *Combo Key* may be cached before or during the Transition Window. 

#### Other Notifies
 - Damage Trace Notify
 - Damage Negation Notify

## Code Design

![](Documentation/Attachments/Code%20Design%20Diagram.png)

