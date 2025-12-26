// Final working code
#include <stdio.h>
#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//Find the max value's index
static int findMaxIndex(double * Ywavelen, int YwavelenSize) {
    int maxIndex = 0;
    for (int i = 1; i < YwavelenSize; i++) {
        if (Ywavelen[i] > Ywavelen[maxIndex]) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

//find the FWHM
static void findHalfMaxIndices(double * Ywavelen, int YwavelenSize, double halfMax, int *leftIndex, int *rightIndex, int maxIndex) {
    *leftIndex = 0;
    *rightIndex = YwavelenSize - 1;

    // Search left from peak for the first value <= halfMax
    for (int i = maxIndex; i > 0; i--) {
        if (Ywavelen[i] <= halfMax) {
            *leftIndex = i;
            break;
        }
    }

    // Search right from peak for the first value <= halfMax
    for (int i = maxIndex; i < YwavelenSize; i++) {
        if (Ywavelen[i] <= halfMax) {
            *rightIndex = i;
            break;
        }
    }
}

static long calcFwhm(aSubRecord *precord){
    double *Xwavelength = NULL;
    double *Yintensity = NULL;
    double *fwhm_val = NULL;
    int i =0;

    Xwavelength = (double *)(precord->a);     //Wavelength values
    Yintensity = (double *)(precord->b);     //Intensity Values from ArrayData
    
    fwhm_val = (double *)(precord->vala);  // FWHM final value           

    int XwavelenSize = precord->noa; // No of elements in wavelength
    int YspctrumSize = precord->nob; // No of elements in spectrum
    
    //Find the max element in the array
    int maxIndex = findMaxIndex(Yintensity, YspctrumSize);
    double maxValue = Yintensity[maxIndex];

    // Calculate half of the maximum value
    double halfMax = maxValue / 2.0;

    // Find the index of the points closest to half the maximum value
    int leftIndex = 0;
    int rightIndex = 0;
    findHalfMaxIndices(Yintensity, YspctrumSize, halfMax, &leftIndex, &rightIndex, maxIndex);

    double reqrd_val = Xwavelength[rightIndex] - Xwavelength[leftIndex];
    *fwhm_val = reqrd_val;

    return 0;
}

epicsRegisterFunction(calcFwhm);
