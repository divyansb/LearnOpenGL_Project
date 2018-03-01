#include "file_IO.h"

void WriteToFile(const char* fileName, const char* text)
{
	std::ofstream file;
	file.open( fileName );
	file << text;
	file.close();
}

void ReadFromFile( const char* fileName, std::string &text )
{
	// The >> operator on an ifstream object gets only one word and nothing beyond that.

	std::ifstream file;
	file.open( fileName );
	std::string fileLine;

	while( getline( file, fileLine ) )
	{
		text.append( fileLine );
		text.append( "\n" );
	}

	
	file.close();

}