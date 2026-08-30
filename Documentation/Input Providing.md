Input is provided to Character Action Component using the following method 
```c++
void Input(FName Input, int32 Complexity);
```
* `FName Input` - name of the input that will be matched to requested Inputs from *Combo Input Notifies*.
* `int32 Complexity` - relative complexity of the input.

### Understanding Input Complexity

![Input Complexity Imagery](Input%20Complexity%20Imagery.png)

Single button inputs are usually marked as `Complexity = 0`. Inputs that are comprized only of single button inputs (0 complexity) and do not include any inputs of higher complexity, are marked as `Complexity = 1`. If an input includes only inputs of complexity 1 and below, then it is marked as `Complexity = 2` and so on.