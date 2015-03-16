# IMPSIM

The Integrated Mechanisms Program (IMP) is a "physics engine" that is capable of simulating the behavior of complex multi-body kinematically-constrained mechanical systems. It was originally fully implemented in C and runs using DOS but is capable of running on Windows XP through a built-in emulator. It implements a basic command-line user interface and is capable of generating simple graphical output (wireframe 3-D graphics, x-y plots and similar).

Imp in Java
Our team is currently refactoring IMP to realize a modular object-oriented architecture (implemented in Java) that consists of a core "engine" that exposes a public API. We have isolated this core so that it can be accessed by a client such as a user interface (we are also implementing an Eclipse-based UI; other UI's, such as bridges to CAD systems, are possible). The decision to use Java (and OpenGL in the user interface) was made to allow IMP to be deployed across various platforms, which has been a long-term goal of IMP's primary author, Dr. John J. Uicker, Jr., of the University of Wisconsin.

The Java version of IMP implements uses a new, streamlined IMP language designed to simplify the process of specifying a kinematic model. The language parser is also isolated from the core, and can potentially be substituted with another type of model definition mechanism.

Along with the core "engine" and parser modules, we have been working on a plugin for the Eclipse IDE that enables a user to model mechanisms in a graphical way (in addition to using the modelling language). We made it so even if you don't have any coding experience or don't know the IMP modelling language, you could still make a model in IMP through this graphical interface. This plugin also implements a means of executing the simulation, as well as capturing and displaying various results graphically. Our plugin of can import data from 3D modeling programs like AutoCAD and SolidWorks.

Thus far, we have implemented support for only revolute and prismatic joints; the original C version of IMP supports many additional joint types, but we are working in increments and have deferred additional joints for now. Similarly, we have only implemented kinematic analysis capabilities so far; the additional static equilibrium and dynamic modes of operation supported in the C version are also planned future developments.

Both versions of IMP are in the repository with the plugin being under the main java project.
