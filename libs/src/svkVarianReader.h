/*
 *  Copyright © 2009 The Regents of the University of California.
 *  All Rights Reserved.
 *
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions are met:
 *  •   Redistributions of source code must retain the above copyright notice, 
 *      this list of conditions and the following disclaimer.
 *  •   Redistributions in binary form must reproduce the above copyright notice, 
 *      this list of conditions and the following disclaimer in the documentation 
 *      and/or other materials provided with the distribution.
 *  •   None of the names of any campus of the University of California, the name 
 *      "The Regents of the University of California," or the names of any of its 
 *      contributors may be used to endorse or promote products derived from this 
 *      software without specific prior written permission.
 *  
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
 *  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 *  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
 *  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
 *  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 *  OF SUCH DAMAGE.
 */



/*
 *  $URL$
 *  $Rev$
 *  $Author$
 *  $Date$
 *
 *  Authors:
 *      Jason C. Crane, Ph.D.
 *      Beck Olson
 */


#ifndef SVK_VARIAN_READER_H
#define SVK_VARIAN_READER_H


#include <vtkObjectFactory.h>
#include <vtkImageData.h>
#include <vtkInformation.h>
#include <vtkUnsignedCharArray.h>
#include <vtkUnsignedShortArray.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkGlobFileNames.h>
#include <vtkSortFileNames.h>
#include <vtkStringArray.h>
#include <vtkDebugLeaks.h>

#include <svkImageReader2.h>
#include <svkIOD.h>
#include <svkMRIIOD.h>

#include <sys/stat.h>
#include <map>


namespace svk {


using namespace std;


/*! 
 *  Varian reader base class. 
 */
class svkVarianReader : public svkImageReader2 
{

    public:

        vtkTypeRevisionMacro( svkVarianReader, svkImageReader2);


    protected:

        svkVarianReader();
        ~svkVarianReader();


        //  Methods:
        int                              GetNumPixelsInVol();
        int                              GetNumSlices();
        void                             ParseProcpar( string path );
        void                             GetProcparKeyValuePair();
        void                             ReadLine(ifstream* fs, istringstream* iss);
        long                             GetFileSize(ifstream* fs);
        void                             ParseAndSetProcparStringElements(
                                            string key, 
                                            string valueArray1, 
                                            string valueArray2
                                         );
        void                             PrintProcparKeyValuePairs();
        int                              GetNumberOfProcparElements( string* valueString );
        void                             GetProcparValueArray( string* valueString );
        void                             RemoveStringQuotes(string* input); 
        void                             AssignProcparVectorElements( 
                                            vector<string>* procparVector, 
                                            string valueArray
                                            );
        void                             AcqToLPS(float* acq, float* lps, double dcos[3][3]); 

        //  Members:
        ifstream*                                   procparFile;
        map <string, vector < vector<string> > >    procparMap; 
        int                                         numFrames; 
        long                                        procparFileSize; 
        svkDcmHeader::DcmDataOrderingDirection      dataSliceOrder;

};


}   //svk


#endif //SVK_VARIAN_READER_H

