#include "ResourceManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

Shaders ResourceManager::getShadersCode(const char* vertex, const char* fragment)
{
    // create two ifstream objects
    ifstream vertexfile;
    ifstream fragmentfile;
    // make sure both files can throw exceptions
    vertexfile.exceptions(ifstream::failbit | ifstream::badbit);
    fragmentfile.exceptions(ifstream::failbit | ifstream::badbit);

    try {
        // read in the files via ifstream objects
        vertexfile.open(vertex);
        fragmentfile.open(fragment);
        // create stringstream objects to read in the files
        stringstream vstream, fstream;
        vstream << vertexfile.rdbuf();
        fstream << fragmentfile.rdbuf();
        // close the ifstream objects
        vertexfile.close();
        fragmentfile.close();
        string temp1 = vstream.str();
        string temp2 = fstream.str();

        return {temp1, temp2};
    }
    catch (ifstream::failure& f) {
        cout << "the reading of the files failed. " << endl;
    }
}
