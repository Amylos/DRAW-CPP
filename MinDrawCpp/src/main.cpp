/*
 * main.cpp
 *
 *  Created on: 2022
 *      Author: Garnier
 */


#include<iostream>
#include<CApp.h>
#include<CContainer.h>

#include<CArea.h>
#include<CCanvas.h>
#include"defines.h"

using namespace std;

int main(int argc,char*argv[]){

	cout << "<================== ENTRY APPLICATION ==============>" << endl;
	cout << " Move ToolBox  : M + mouse \n"
			" Change color  : LEFT Clic\n"
			" Create Shapes : LEFT + mouse\n"
			" Move Shapes	: RIGHT + mouse\n"
			" Copy Shapes 	: CTRL + LEFT\n"
			" Save Shapes   : S\n"
			" Flush Shapes	: F\n"
			" Load Shapes 	: U\n" << endl;


	CApp app(APP_WINDOW_TITLE,APP_WINDOW_WIDTH,APP_WINDOW_HEIGHT,APP_WINDOW_COLOR_BKGND);

	cout << "<================== EXIT APPLICATION ==============>" << endl;

	return EXIT_SUCCESS;
}
