/*
Caleb Hemmestad
C++ 2021
Due: 11/10/21
Lab 6 Binary to Decimal Conversion

Description: Write a C++ program that reads characters representing binary (base 2) 
numbers from a data file called BinaryIn.dat and translates them to decimal (base 10) 
numbers. The binary and decimal numbers should be output in two columns with 
appropriate headings.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath> 
#include <string>

using namespace std ;

//precondition - values are changing during the process and arent right
//postcondition - resets values to be used again
void reset ( bool &startWithZero , bool &invalid , 
	bool &breakCheck , string &binaryNumber , 
	unsigned int &decimal , int &binaryPos , int &y , int &x ) ;

//precondition - checking to see if inputs are valid
//postcondition - changing bools so nothing is outputted if input was invalid
void conditionCheck ( bool &breakCheck , 
	bool &invalid , char file ) ;

//precondition - cant do math chars
//postcondition - converts chars to ints , adds to string for output , calculates decimal
void binaryConversion ( char &binary , int binaryPos , 
	int &oneZero , bool &startWithZero , unsigned int &decimal , 
	string &binaryNumber , int &y , ifstream &secondfile ) ;

//precondition - nothing is centered when outputted
//postcondition - centers output
void centering ( bool invalid , unsigned int decimal , 
	int &x , int y , string binaryNumber ) ;

//precondition - dont know how many binary numbers there are for calculating decimal
//postcondition - counts binary numbers if valid
void binaryPosition ( char file , int &oneZero , 
	int &binaryPos) ;

//precondition - dont know which column is for what when outputted
//postcondition - displays a header telling what each column is
void header ( ) ;

/*
					=============================================
												 BEGINNING OF MAIN
					=============================================
*/
int main(int argc, char **argv)
{
	system ( "clear" ) ; cout << "\n\n\n" ;
	
	//opening files
	ifstream firstfile ;
	firstfile.open ( "BinaryIn.dat" ) ;
	ifstream secondfile ;
	secondfile.open ( "BinaryIn.dat" ) ;
	
	//declaring variables
	char file ; char binary ; //for storing chars from the files (file is for the first. binary is for the second)
	string binaryNumber = "\0" ; //builds string to make centering easier when outputting
	bool startWithZero = true ; bool invalid = true ; bool breakCheck = true ; //bools for checking condition of input and if its useable
	int oneZero ; //converts char to int so we can do math with it
	int decimal = 0 ; //used for adding calculations as it goes through the binary and then used to display decimal equivalent
	int binaryPos = 0 ; //used for counting how many numbers there are and then use for power
	int y = 0 ; int x = 18 ; //basic numbers for centering
	
	header ( ) ; //displaying header
	//going through file
	do {
		firstfile.get ( file ) ; //getting info from file
		conditionCheck ( breakCheck , invalid , file ) ; //checking the condition of input
		if ( file == '\n' || !firstfile ) {
			if ( binaryPos == 0 ) { //skipping if input was just a bunch of spaces or \n
				continue ;
			}
			//doing calculations and outputs
			binaryConversion ( binary , binaryPos , oneZero , startWithZero , decimal , binaryNumber , y , secondfile ) ;
			centering ( invalid , decimal , x , y , binaryNumber ) ;
			reset ( startWithZero , invalid , breakCheck , binaryNumber , decimal , binaryPos , y , x ) ;
		} else {
			//counting binary numbers for calculations
			binaryPosition ( file , oneZero , binaryPos) ;
		} 
	}
	while ( firstfile ) ;
	
	//closing files
	firstfile.close ( ) ;
	secondfile.close ( ) ;
	return 0 ;
}
/*
					=============================================
														   END OF MAIN
					=============================================
*/

void header ( ) {
	cout << setw (30) << "Binary Number" << "\t\tDecimal Equivalent" << endl << endl ;
}

void reset ( bool &startWithZero , bool &invalid , bool &breakCheck , string &binaryNumber , unsigned int &decimal , int &binaryPos , int &y , int &x ) {
	startWithZero = true ;
	invalid = true ;
	breakCheck = true ;
	binaryNumber = '\0' ;
	decimal = 0 ;
	binaryPos = 0 ;
	y = 0 ;
	x = 18 ;
	cout << endl ;
}

void conditionCheck ( bool &breakCheck , bool &invalid , char file ) {
	if ( file == '0' || file == '1' ) {
		breakCheck = false ;
	}
	if ( file != '0' && file != '1' && file != '\n' && file != ' ' && file != '_' ) {
		invalid = false ;
	}
	if ( breakCheck == false && ( file == '_' || file == ' ' )) {
		invalid = false ;
	}
}

void binaryConversion ( char &binary , int binaryPos , int &oneZero , bool &startWithZero , unsigned int &decimal , string &binaryNumber , int &y , ifstream &secondfile )  {
	for ( int x = binaryPos-1 ; x >= 0 ; x-- ) {
		secondfile.get ( binary ) ; //getting information again for calculations
		if ( binary == '0' ) {
			oneZero = 0 ; //changing to int for math
		} else if ( binary == '1' ) {
			oneZero = 1 ; //changing to int for math
			startWithZero = false ; //doesnt add to string for output until the first number isnt zero
		} else {
			x++ ;
			continue ;
		}
		if ( !startWithZero ) {
			binaryNumber = binaryNumber + binary ; //adding to string for output
			y++ ; //for centering later
		}
		decimal += oneZero*(pow( 2 , x )) ; //calculating decimal equivalent
	}
}

void centering ( bool invalid , unsigned int decimal , int &x , int y , string binaryNumber ) {
	if ( !invalid ) {
		cout << setw (33) << "Bad digit on input" ;
	}
	if ( decimal > 99 ) {
		x = 19 ;
	} 
	if ( invalid ) {
		cout << setw (25+(round(y/2))) << binaryNumber ;
		cout << "\t" << setw (x) << decimal ;
	}
}

void binaryPosition ( char file , int &oneZero , int &binaryPos) {
	if ( file == '0' ) {
		oneZero = 0 ;
		binaryPos++ ;
	} else if ( file == '1' ) {
		oneZero = 1 ;
		binaryPos++ ;
	}
}
