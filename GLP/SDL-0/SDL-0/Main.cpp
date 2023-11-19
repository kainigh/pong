#include <iostream>
#include <SDL.h>
#include <glew.h>
#include <fstream>
#include <string>
#include <gl/GL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Game.h"



using namespace std;
//#define GLEW_STATIC


string LoadShader(string fileName);


Game Pong;

int main(int argc, char* argv[])
{
	

	Pong.Init();	
		
	Pong.Loop();



	//cin.get();
	return 0;
}

string LoadShader(string fileName) {

	ifstream myFile;

	myFile.open(fileName);

	if (myFile.fail()) {

		cerr << "Error - failed to open " << fileName << endl;

	}

	string fileText = "";

	string line = "";

	while (getline(myFile, line)) {

		fileText += line + '\n';

	}



	myFile.close();

	return fileText;



}