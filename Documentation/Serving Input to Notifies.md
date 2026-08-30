The following diagram shows how input is received, requested and served during a single tick (frame):
![Tick Structure](Attachments/Tick%20Structure.png)

During each tick Character Action Component and every Combo Input Notify are updated exactly once, but the order of updates remains unknown (we can assume it is random). That is why it is useful to think about *Character Action Tick*, which begins and ends with Character Action Component updates.

Every tick when a Combo Input Notify is active it requests it's associated input from the Character Action Component using the following method:
```c++
void RequestInput(FName Input, SC_ComboInputNotify* RequestorNotify);
```
This method stores requested inputs and requestor notifies as pairs in the `InputRequestBuffer`.

Player inputs, that are provided using `Input(...)` are stored in `PlayerInputBuffer`, that is kept sorted by input complexity (from more complex to less complex).
```c++
void Input(FName Input, int32 Complexity);
```

At the end of every *Character Action Tick* requested inputs are served using the following algorithm:
1. Find the most complex player input (earliest in `PlayerInputBuffer`) that is also present in the `InputRequestBuffer`;
2. If found:
	1. Serve found input to the notify that requested it;
	2. if not successful:
		1.  remove found input from the `InputRequestBuffer` and go back to step 1.
3. Clear `PlayerInputBuffer` and `InputRequestBuffer`.

Character Action Component serves inputs back to Combo Input Notifies using
```c++
bool ServeInput(FName Input);
```
Return value of this method signifies success or failure of ADDITIONAL conditions. For example if a certain move requires the player to have a certain level of concentration (or stamina, or anything else), then the result of that check will be used as a return value for `ServeInput` method.
