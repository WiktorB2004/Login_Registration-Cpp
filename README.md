# Login Registration System - C++ Practice Project

## Overview
- Start date: 19.09.2023
- Currently under development - many changes are about to be done.
- This is user login and register application which stores data in txt database file.

## Objective
This project is created to review newly acquired C++ language knowledge, practice usage of Visual Studio and to use "Pragmatic Programmer" tips on making good software.
The code may and most probably will not be perfect, because of my lack of experience with C++ language.
Through making and correcting mistakes + writing the code I can easily gain missing experience alongside with learning dos and don'ts
of C++ language.

## Project Phases
1. Write basic code:
	- ~~Basic logic and functionality~~
	- ~~Function documentation and comments~~
	- ~~Basic error handling~~

2. Analysis of the code and initial refactoring
	- ~~Check the code for bad practices and note/repair them~~
	- ~~Try to find better ways to solve problems - note them~~

3. Implement more features + Optimize
	- ~~Possibility of erasing current file data if name is taken~~
	- Optimize time and memory needed
	- ~~Manually test the program~~

4. Final changes
	- ~~Redesign project folder structure~~

## Video and Screenshoots

https://github.com/WiktorB2004/Login-Registration-Cpp/assets/62223421/a23696e4-d52a-4f83-8c06-fb21af80658a

This is how the database file looks after actions presented in the video:

![usersDBss](https://github.com/WiktorB2004/Login-Registration-Cpp/assets/62223421/884540ec-2bbd-40f7-8430-8aa50e676ab1)

## Conclusion

1. Each feature should be handled by dedicated class
	- User input should be handled by dedicated function/class instead of screen functions, so it wont be hard/impossible to write unit tests
	- Dedicated class for each functionality would make it easier to test/debug the code and understand the application logic
2. Handle data using classes
	- It would be easier and more efficient to handle user data if it was stored in the User class, and datbase would operate on the user class
3. Thinking about testing while designing/writing the code
	- Make code easy to test
4. Define class functions in className.cpp and only declare them in className.h

In the process of making the project I've learned:
	- Basic usage of CMake (single and cross-platform), GoogleTest
	- GitHub workflow - creating GitHub actions
	- Gained experience with using C++, Visual Studio and Git Version control

