/*
 *  $URL$ 
 *  $Rev$
 *  $Author$
 *  $Date$
 *
 *  Authors:
 *      Jason C. Crane, Ph.D.
 *      Beck Olson
 *
 *  License: TBD
 *
 *
 *
 *  Test driver to check that topologcial features are placed in their 
 *  vtkCollection in an order matching their vtkId's from the original
 *  dataset.
 *
 */

#include <svkImageData.h>
#include <svkImageReader2.h>
#include <svkImageReaderFactory.h>
#include <vtkImageData.h>
#include <vtkCell.h>

using namespace svk;
    
svkImageData* LoadFile( char* fileName );

int main ( int argc, char** argv )
{
    char* fileName = NULL;
    int slice = 0;
    if( argc == 1 ) {
        cerr<<"Not enough input arguments."<<endl;
        return 1;
    } else if( argc == 3 ) {
        slice = atoi(argv[2]);
    } else if( argc > 3) {
        cerr<<"Too many input arguments."<<endl;
        return 1;
    } 
    
    fileName = argv[1];
    // Below is just a svkPlotGrid test

    svkImageData* data = LoadFile( fileName );
    vtkActorCollection* gridActors = data->GetTopoActorCollection(0); 
    vtkActor* tempActor;
    vtkCell* tempCell; 
    int* extent = vtkImageData::SafeDownCast( data )->GetExtent(); 
    int* index = new int[3]; 
    int ID;
    double* gridActorBounds;
    double* dataCellBounds;
    int colID;
    vtkImageData* data4D = vtkImageData::SafeDownCast( data );
    cout<< "data is: "<<*data<<endl;
    cout<< "data4D is: "<<*data4D<<endl;
    cout<<"Extent is:"<<extent[0]<<" "<<extent[1]<<" "<<extent[2]<<" "<<extent[3]<<" "<<extent[4]<<" "<<extent[5]<<endl; 
    for( index[2] = extent[4]; index[2] < extent[5]; index[2]++) {
        for( index[1] = extent[2]; index[1] < extent[3]; index[1]++) {
            for( index[0] = extent[0]; index[0] < extent[1]; index[0]++) {

                cout<<"index z="<<index[2]<<" x="<<index[0]<<" y="<<index[1]<<endl;
                ID = data4D->ComputeCellId( index );
                cout<<"ID is="<<ID<<endl;
                tempCell = data4D->GetCell(ID);
                dataCellBounds = tempCell->GetBounds();
                cout<<"Data bounds is:"<<dataCellBounds[0]<<" "<<dataCellBounds[1]<<" "
                                       <<dataCellBounds[2]<<" "<<dataCellBounds[3]<<" "
                                       <<dataCellBounds[4]<<" "<<dataCellBounds[5]<<endl; 
                tempActor = vtkActor::SafeDownCast( gridActors->GetItemAsObject( ID ) );
                gridActorBounds = tempActor->GetBounds();
                cout<<"Data bounds is:"<<gridActorBounds[0]<<" "<<gridActorBounds[1]<<" "
                                       <<gridActorBounds[2]<<" "<<gridActorBounds[3]<<" "
                                       <<gridActorBounds[4]<<" "<<gridActorBounds[5]<<endl; 
                colID = gridActors->IsItemPresent( tempActor );   
                cout<<"ID from collection is="<<colID<<endl;
                tempActor = vtkActor::New();
                colID = gridActors->IsItemPresent( tempActor );   
                cout<<"Item that is not present's ID is="<<colID<<endl;
                tempActor->Delete();
            }
        }
    }    
    fileName = NULL;
    delete[] index;
    gridActors->Delete(); 
    data->Delete();
    return 0;
    
}

svkImageData* LoadFile( char* fileName )
{
    svkImageData* myData;
    svkImageReaderFactory* readerFactory = svkImageReaderFactory::New();
    svkImageReader2* reader = readerFactory->CreateImageReader2(fileName);
    readerFactory->Delete();

    if (reader == NULL) {
        cerr << "Can not determine appropriate reader for: " << fileName << endl;
        exit(1);
    }

    reader->SetFileName( fileName );
    reader->Update();
    myData = reader->GetOutput();
    reader->Delete();
    return myData;
}
