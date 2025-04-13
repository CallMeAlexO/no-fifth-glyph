# No Fifth Glyph
This program looks at your input and prints “WOW!” if it finds no sign of that notorious fifth Latin symbol.

## How to Run

First, build it with GCC. 
```
gcc main.c -o fifth
```

Now launch it. You can pick from two ways to run:

1. Input right away: `./fifth "This is good input"`
2. With -f flag: `./fifth -f main.c story.txt story2.txt`

## Constraints
As part of this constraint, you can’t bring in standard library (stdlib) in a usual way (that typical starting word with a hash and that glyph). To scan and work on an input, typical functions from your OS would normally play a part. But, with our glyph ban, I had to go with syscall. This limits portability — still, it works on Linux. 

## Inspirations
* [Gadsby](https://en.wikipedia.org/wiki/Gadsby_(novel))
* [Tsoding](https://github.com/rexim)
* My pals said this task was absurd and couldn’t possibly work