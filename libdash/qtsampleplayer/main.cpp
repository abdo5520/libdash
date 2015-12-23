/*
 * main.cpp
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include <QApplication>
#include "UI/DASHPlayer.h"

// Added by Abdallah Abdallah
#include "MultiThreading.h"
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <iostream>

using namespace sampleplayer;
using namespace std;


static void *AdaptDemo(void *data);



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtSamplePlayerGui w;
    DASHPlayer p(w);

    cout << "Modified By Abdallah Abdallah " << "\n";

    	  	/**
    	    	 *   Instead of updating through w>NotifySettingsChanged();
    	    	 *   we will use w->observers directly
    	    	 *
    	    	 */


    QtSamplePlayerGui *wPointer = &w;
    DASHPlayer 			*pPointer = &p;
    /**
     *  Initialize the Random function
     */
    /* initialize random seed: */
    srand (time(NULL));


     THREAD_HANDLE demoThreadHandle = CreateThreadPortable (AdaptDemo,&w);

 //   THREAD_HANDLE demoThreadHandle = (THREAD_HANDLE)malloc(sizeof(pthread_t));

    if (!demoThreadHandle)
    {
        std::cerr << "Error allocating thread." << std::endl;
        return false;
    }


	w.show();





    return a.exec();


}



static void *AdaptDemo(void *data)
{

	QtSamplePlayerGui *wPointer = (QtSamplePlayerGui *) data;

	int iSecret;
	sleep (5);
	  while (1)
	  {

		  /* generate secret number between 0 and 13: */
		  iSecret = rand() % 14;
		  wPointer->locking();
	    	wPointer->setIndexInternalClass(iSecret);
	    	wPointer->unlocking();
	    	 cout << "Abdallah demo Thread is On i =  " << iSecret <<"\n";

			sleep(5);

	    }




}




/**

void            QtSamplePlayerGui::NotifySettingsChanged                            ()
 {
     this->LockUI();

     int period              = this->ui->cb_period->currentIndex();
     int videoAdaptionSet    = this->ui->cb_video_adaptationset->currentIndex();
     int videoRepresentation = this->ui->cb_video_representation->currentIndex();
     int audioAdaptionSet    = this->ui->cb_audio_adaptationset->currentIndex();
     int audioRepresentation = this->ui->cb_audio_representation->currentIndex();

     for(size_t i = 0; i < this->observers.size(); i++)
         this->observers.at(i)->OnSettingsChanged(period, videoAdaptionSet, videoRepresentation, audioAdaptionSet, audioRepresentation);

     this->UnLockUI();
 }


*/
