/*******************************************************************************************
* En fonction des fonctions

* Romain Larramendy, Lucas Bremard, Killian Baert, Valentin Hecht, Thomas Tissier, Maxence Dhaynaut, Benjamin Chane, Louis-Marie Brossard 

* FISA-TI23 Copyright 2020-2020
********************************************************************************************/

#include "pbPlots.h"
#include "supportLib.h"

int main(){
	double xs [] = {-2000, -1, 0, 1, 2000};
	double ys [] = {10, 100, 0, -100, -10};

	RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
	DrawScatterPlot(canvasReference, 600, 400, xs, 5, ys, 5);

	size_t length;
	
	double *pngdata = ConvertToPNG(&length, canvasReference->image);
	WriteToFile(pngdata, length, "example1.png");
	DeleteImage(canvasReference->image);
	

	return 0;
}