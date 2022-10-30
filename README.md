# SmallPrixManager
Many, many, many years ago I keenly played [Grand Prix Manager](https://en.wikipedia.org/wiki/Grand_Prix_Manager).

It had nice overhead views of many famous racing tracks, with cars zipping around them during the races.

For a long time I could not guess how they move the cars around the track.
Pushing a sprite along a fixed curve is one thing. But a car? Which has to break, may skid off the track, can only go as fast as its engine allow?
A whole other thing.

To this day, I don't know how _they_ did it.

I can only show you how I tried, and failed, to do it.

![Screenshot](https://github.com/stefanos-86/SmallPrixManager/blob/main/ReadmeImage.png "")

## Danger: this is an old, old repo.
This project was born in 2013, progressed up to a given point, then it was abandoned.
It was found again while cleaning up the old computer it was originally developed on.

Then it was quickly, really quickly, ported to Visual Studio 2019, from Mercurial to Git and from SFML to SDL.

I have nothing against [SFML](https://www.sfml-dev.org/), but there are no pre-built versions of it for my current compiler as of now.
I had a look at the list of its build dependencies... and decided it was faster to simply switch over to SDL
(or maybe not - but what's done is done). The original code is still there, safe in the Git history.

There used to be unit tests. They are still there, but commented out. The porting did not require changing the testing 
logic. And, thanks to this "cop out", did not require GTest as well.

So, it is old, bad, half-commented-out, did not reach its goals.

But you can see some "odd" algorithms inside and a simple implementaion of Bezier curves.

## The math, the code, the crazyness.
_Disclaimer: I did not read all the 9 years old code to do the port. I am writing from memory!_

The core of the problem is to figure out how fast can a car go around any corner.

The core of the solution is some high scool math and a few derivatives.
- Max speed is limited by maximum tire grip force and cornering forces;
- tire grip is a known formula for friction;
- the cornering force depends on the radial acceleration;
- which depend on the radius of the car speed and curve tangent circle;
- for which there is a formula (which origin I forgot, I must have looked it up somewhere);
- that requires the derivatives of the curve (whish I could remember why);
- that I must have computed on pencil and paper from Bezier's formulas (...sooo much time ago).

Toss in a simple integration of engine power (plus some work with time and the car mass and approximation of air resistance) and you know
how fast the car can gain speed. Gives a better acceleration effect when coming out of corners, the car does not immediatly reach "warp speed"
as soon as the road is straight.

### Ok... where's the catch?

The brakes.

The bizzare algorithm I described does not account for braking. It just pins the car at the maximum speed it can get without skidding off the corners.

When it meets the hairpin at the end of a very fast straight... it just immediately go from 300km/h to 10km/h. No braking distance at all.

I could not invent nor look up a way to simulate a car slowing down to an appropriate speed _before_ the corner, within belivable limits
of tire grip and brakes' power. How to know how much force to apply on the brakes? How much distance before the corner? No clue.

I had to give up.

## Compiling
The Visual Studio project is included, it has only one external dependency on [SDL](https://www.libsdl.org/).
Check the inlcude and library paths - you will have to adapt them to your installation of SDL.

## ImGui pieces inside!
The project relies on [Dear ImGui](https://github.com/ocornut/imgui).

As per the instructions, I added their files to the projct.
I thank the Dear ImGui authors for their work, and I hope I am not breaking any license by embedding it there (please let me know if you know better).
