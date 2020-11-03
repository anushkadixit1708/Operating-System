import java.io.BufferedReader;

import java.io.IOException;

import java.io.InputStreamReader;

// Class ClockReplacementAlogrithem definition

public class ClockReplacementAlogrithem

{

// main method definition

public static void main(String[] args) throws IOException

{

BufferedReader read = new BufferedReader(new InputStreamReader(System.in));

int framesAvalable, pointer = 0, hitCounter = 0, faultCounter = 0, referenceStringLength;

int temp[][];

int referenceString[];

int memoryLayout[][];

int usedLayout[][];

  

// Accepts number of frames

System.out.print("\n Enter the number of Frames: ");

framesAvalable = Integer.parseInt(read.readLine());

  

  

// Enter number of strings

System.out.println("\n Enter the length of the Reference string: ");

referenceStringLength = Integer.parseInt(read.readLine());

  

// Dynamically allocates memory to reference string array of size referenceStringLength entered by the user  

referenceString = new int[referenceStringLength];

// Dynamically allocates memory to matrix memoryLayout with row size as referenceStringLength (number of strings)

// and column size as framesAvalable (number of frames)

memoryLayout = new int[referenceStringLength][framesAvalable];

// Dynamically allocates memory to matrix usedLayout with row size as referenceStringLength (number of strings)

// and column size as framesAvalable (number of frames)

usedLayout = new int[referenceStringLength][framesAvalable];

// Dynamically allocates memory to matrix temp with row size as referenceStringLength (number of strings)

// and column size as 2

temp = new int[framesAvalable][2];

  

// Loops till number of frames

for(int counter = 0; counter < framesAvalable; counter++)

{

// Initialize each row 0 column position to -1 value

temp[counter][0] = -1;

// Initialize each row 0 column position to 0 value

temp[counter][1] = 0;

}// End of for loop

  

// Accepts the reference strings

System.out.print("\n Enter the reference string: ");

// Loops till number of strings

for(int counter = 0; counter < referenceStringLength; counter++)

referenceString[counter] = Integer.parseInt(read.readLine());

  

System.out.println();

  

// Loops till length of the reference string

for(int r = 0; r < referenceStringLength; r++)

{

// Initializes the search page status to -1

int searchStatus = -1;

// Loops till number of frames available

for(int c = 0; c < framesAvalable; c++)

{

// Checks if the current row and zero column of temp data is equals to the current position data of reference sting for page

if(temp[c][0] == referenceString[r])

{

// Assigns the c value as search status

searchStatus = c;

// Increase the hit counter by one

hitCounter++;

// Assigns one to the current row and column one position to one

temp[c][1] = 1;

// Come out of the loop

break;

}// End of if condition

}// End of inner for loop

// Checks if the current search status is -1

if(searchStatus == -1)

{

// Loops till temp matrix pointer position as row and one column position data is one

while(temp[pointer][1] == 1)

{

// Assigns zero to pointer as row index position and one column position of temp matrix

temp[pointer][1] = 0;

// Increase the pointer value by one

pointer++;

// Checks if the pointer value is equals to the number of frames

if(pointer == framesAvalable)

// Reset the pointer to zero

pointer = 0;

}// End of while loop

// Assigns r index position reference string to temp matrix pointer row index position and zero column index position

temp[pointer][0] = referenceString[r];

// Assign one to pointer row index position and one column index position of tem matrix

temp[pointer][1] = 1;

// Increase the fault counter by one

faultCounter++;

// Increase the pointer by one

pointer++;

// Checks if the pointer value is equals to number of frames

if(pointer == framesAvalable)

// Reset the pointer to zero

pointer = 0;

}// End of if condition

// Loops till number of frames

for(int c = 0; c < framesAvalable; c++)

{

// Assigns temp data to memory layout

memoryLayout[r][c] = temp[c][0];

// Assigns temp data to used layout

usedLayout[r][c] = temp[c][1];

}// End of inner for loop

}// End of outer for loop

  

// Loops till number of frames

for(int r = 0; r < framesAvalable; r++)

{

// Loops till number of strings

for(int c = 0; c < referenceStringLength; c++)

// Displays data

System.out.printf("%3d %d ", memoryLayout[c][r], usedLayout[c][r]);

System.out.println();

}// End of for loop

  

// Displays result

System.out.println("The number of Hits: " + hitCounter);

System.out.println("Hit Ratio: " + (float)((float)hitCounter/referenceStringLength));

System.out.println("The number of Faults: " + faultCounter);

}// End of main method  

}// End of class