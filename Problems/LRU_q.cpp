//.h file code:

#include <string>
#include <vector>
#include <iostream>
#include "rectangularvectors.h"

using IOException = java::io::IOException;


// Class ClockReplacementAlogrithem definition

class ClockReplacementAlogrithem

{

// main method definition

public:
static void main(std::vector<std::wstring> &args);

}; // End of class

//Helper class added by Java to C++ Converter:

#include <string>
#include <vector>

int main(int argc, char **argv)
{
    std::vector<std::wstring> args(argv + 1, argv + argc);
    ClockReplacementAlogrithem::main(args);
}


#include <vector>

class RectangularVectors
{
public:
    static std::vector<std::vector<int>> RectangularIntVector(int size1, int size2)
    {
        std::vector<std::vector<int>> newVector(size1);
        for (int vector1 = 0; vector1 < size1; vector1++)
        {
            newVector[vector1] = std::vector<int>(size2);
        }

        return newVector;
    }
};

//.cpp file code:

#include "snippet.h"

using BufferedReader = java::io::BufferedReader;
using IOException = java::io::IOException;
using InputStreamReader = java::io::InputStreamReader;

void ClockReplacementAlogrithem::main(std::vector<std::wstring> &args)

{

InputStreamReader tempVar(System::in);
BufferedReader *read = new BufferedReader(&tempVar);

int framesAvalable, pointer = 0, hitCounter = 0, faultCounter = 0, referenceStringLength;

std::vector<std::vector<int>> temp;

std::vector<int> referenceString;

std::vector<std::vector<int>> memoryLayout;

std::vector<std::vector<int>> usedLayout;



// Accepts number of frames

std::wcout << L"\n Enter the number of Frames: ";

framesAvalable = static_cast<int>(read->readLine());





// Enter number of strings

std::wcout << L"\n Enter the length of the Reference string: " << std::endl;

referenceStringLength = static_cast<int>(read->readLine());



// Dynamically allocates memory to reference string array of size referenceStringLength entered by the user  

referenceString = std::vector<int>(referenceStringLength);

// Dynamically allocates memory to matrix memoryLayout with row size as referenceStringLength (number of strings)

// and column size as framesAvalable (number of frames)

//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: memoryLayout = new int[referenceStringLength][framesAvalable];
memoryLayout = RectangularVectors::RectangularIntVector(referenceStringLength, framesAvalable);

// Dynamically allocates memory to matrix usedLayout with row size as referenceStringLength (number of strings)

// and column size as framesAvalable (number of frames)

//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: usedLayout = new int[referenceStringLength][framesAvalable];
usedLayout = RectangularVectors::RectangularIntVector(referenceStringLength, framesAvalable);

// Dynamically allocates memory to matrix temp with row size as referenceStringLength (number of strings)

// and column size as 2

//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: temp = new int[framesAvalable][2];
temp = RectangularVectors::RectangularIntVector(framesAvalable, 2);



// Loops till number of frames

for (int counter = 0; counter < framesAvalable; counter++)

{

// Initialize each row 0 column position to -1 value

temp[counter][0] = -1;

// Initialize each row 0 column position to 0 value

temp[counter][1] = 0;

} // End of for loop



// Accepts the reference strings

std::wcout << L"\n Enter the reference string: ";

// Loops till number of strings

for (int counter = 0; counter < referenceStringLength; counter++)
{

referenceString[counter] = static_cast<int>(read->readLine());
}



std::wcout << std::endl;



// Loops till length of the reference string

for (int r = 0; r < referenceStringLength; r++)

{

// Initializes the search page status to -1

int searchStatus = -1;

// Loops till number of frames available

for (int c = 0; c < framesAvalable; c++)

{

// Checks if the current row and zero column of temp data is equals to the current position data of reference sting for page

if (temp[c][0] == referenceString[r])

{

// Assigns the c value as search status

searchStatus = c;

// Increase the hit counter by one

hitCounter++;

// Assigns one to the current row and column one position to one

temp[c][1] = 1;

// Come out of the loop

break;

} // End of if condition

} // End of inner for loop

// Checks if the current search status is -1

if (searchStatus == -1)

{

// Loops till temp matrix pointer position as row and one column position data is one

while (temp[pointer][1] == 1)

{

// Assigns zero to pointer as row index position and one column position of temp matrix

temp[pointer][1] = 0;

// Increase the pointer value by one

pointer++;

// Checks if the pointer value is equals to the number of frames

if (pointer == framesAvalable)
{

// Reset the pointer to zero

pointer = 0;
}

} // End of while loop

// Assigns r index position reference string to temp matrix pointer row index position and zero column index position

temp[pointer][0] = referenceString[r];

// Assign one to pointer row index position and one column index position of tem matrix

temp[pointer][1] = 1;

// Increase the fault counter by one

faultCounter++;

// Increase the pointer by one

pointer++;

// Checks if the pointer value is equals to number of frames

if (pointer == framesAvalable)
{

// Reset the pointer to zero

pointer = 0;
}

} // End of if condition

// Loops till number of frames

for (int c = 0; c < framesAvalable; c++)

{

// Assigns temp data to memory layout

memoryLayout[r][c] = temp[c][0];

// Assigns temp data to used layout

usedLayout[r][c] = temp[c][1];

} // End of inner for loop

} // End of outer for loop



// Loops till number of frames

for (int r = 0; r < framesAvalable; r++)

{

// Loops till number of strings

for (int c = 0; c < referenceStringLength; c++)
{

// Displays data

printf(L"%3d %d ", memoryLayout[c][r], usedLayout[c][r]);
}

std::wcout << std::endl;

} // End of for loop



// Displays result

std::wcout << L"The number of Hits: " << hitCounter << std::endl;

std::wcout << L"Hit Ratio: " << static_cast<float>(static_cast<float>(hitCounter) / referenceStringLength) << std::endl;

std::wcout << L"The number of Faults: " << faultCounter << std::endl;

	delete read;
} // End of main method
