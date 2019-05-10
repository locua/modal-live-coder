# finalproject2k19

final project various mini projects and bits and bobs

Tested on ubuntu linux. It should work on windows to if ofxMaxim is working. On Windows the code may have to be edited in the ofApp.cpp file to give change all references to file paths to the absolute directorys (eg. C://User/), this may be the case on Mac OS too.

## Usage

Up to 100 samples can be loaded into the /bin/data/samples folder and will be automaticallyloaded into the program, indexed from 0 to 99. This index can then be used by the functions to reference and play the samples.

## Functions

### Random function


```c
// This would play a random pattern of sample 11
r11r
// This would play a random pattern of sample 1
r01r 
```

## Pattern function

```c
// This would pass the given pattern to the sample 14
p14p01010101000111p

```
