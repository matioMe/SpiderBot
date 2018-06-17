#ifndef XML_H
#define XML_H

#include <iostream>
#include <fstream>


using namespace std;

class XML
{
public:
    XML(string fileName);
    ~XML();
    int generateFile(float values[], int nbColumn, int nbRaws);

private:
    string m_fileName;
    string m_fileString;
    ofstream* m_file;
};

#endif // XML_H
