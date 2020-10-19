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

    double x1 = MapXCoordinateAutoSettings(0, canvasReference, xs, 5);
    double y1 = MapYCoordinateAutoSettings(0, canvasReference, ys, 5);

    double x2 = MapXCoordinateAutoSettings(1, canvasReference, xs, 5);
    double y2 = MapYCoordinateAutoSettings(1, canvasReference, ys, 5);

    DrawLine(canvasReference, x1, y1, x2, y2, 2, GetGray(0.3));

	return 0;
}