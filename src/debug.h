#pragma once
#ifndef DEBUG_H
#define DEBUG_H

// #define ASSERT(x) if(!(x)) __debugbreak();
#define ASSERT(x) if(!(x)) PrintError(__LINE__, __FILE__);

#ifdef DEBUG
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall())
#else
#define GLCall(x) x
#endif

// Clear GL errors
void GLClearError();

// Check for GL errors
bool GLLogCall();

// Print an error, prints line and filename
void PrintError(int line, const char* file);

#endif