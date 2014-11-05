#include "BlobMaker.h"
#include "frodo.h"
#include "AStrip.h"
#include "ABlob.h"

#include "Riostream.h"
#include <iostream>

void BlobMaker()
{

  frodo *av = frodo::instance();
  av->theXBlobs.clear();
  av->theYBlobs.clear();
  av->theUBlobs.clear();

  // X...
  for (unsigned int i=1; i<av->theXStrips.size()-1; i++)
    {
      if ( (av->theXStrips[i-1].Q() < av->theXStrips[i].Q()) &&
	   (av->theXStrips[i].Q() >=  av->theXStrips[i+1].Q()) )
	{
	  //cout << "XStrip " << i << " has local maximum chg: " << av->theXStrips[i].Q() << endl;

	  av->theXBlobs.push_back( ABlob(&(av->theXStrips[i-1]),  
					 &(av->theXStrips[i]),  
					 &(av->theXStrips[i+1])) );
	}
    }

  // Y...
  for (unsigned int i=1; i<av->theYStrips.size()-1; i++)
    {
      if ( (av->theYStrips[i-1].Q() < av->theYStrips[i].Q()) &&
	   (av->theYStrips[i].Q() >=  av->theYStrips[i+1].Q()) )
	{
	  //cout << "YStrip " << i << " has local maximum chg: " << av->theYStrips[i].Q()<< endl;

	  av->theYBlobs.push_back( ABlob(&(av->theYStrips[i-1]),  
					 &(av->theYStrips[i]),  
					 &(av->theYStrips[i+1])) );
	}
    }

  // U...
  for (unsigned int i=1; i<av->theUStrips.size()-1; i++)
    {
      if ( (av->theUStrips[i-1].Q() < av->theUStrips[i].Q()) &&
	   (av->theUStrips[i].Q() >=  av->theUStrips[i+1].Q()) )
	{
	  //cout <<"UStrip " << i << " has local maximum chg: " << av->theUStrips[i].Q() << endl;

	  av->theUBlobs.push_back( ABlob(&(av->theUStrips[i-1]),  
					 &(av->theUStrips[i]),  
					 &(av->theUStrips[i+1])) );
	}
    }



}
