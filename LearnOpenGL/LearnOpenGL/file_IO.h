#ifndef DB_FILE_IO
#define  DB_FILE_IO

#include <iostream>
#include <fstream>
#include <string>

void WriteToFile( const char* fileName, const char* text );

void ReadFromFile( const char* fileName, std::string &text );


#endif // !DB_FILE_IO
