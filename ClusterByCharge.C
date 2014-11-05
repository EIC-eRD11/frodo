#include "ClusterByCharge.h"
#include "frodo.h"
#include "ABlob.h"
#include "ACluster.h"

void ClusterByCharge()
{

  frodo *av = frodo::instance();
  av->theClusters.clear();

  for (unsigned int i=0; i<av->theXBlobs.size(); i++)
    {
      for (unsigned int j=0; j<av->theYBlobs.size(); j++)
	{
	  for (unsigned int k=0; k<av->theUBlobs.size(); k++)
	    {

	      if ((av->theXBlobs[i].CorrectedQ() == av->theYBlobs[j].CorrectedQ()) &&
		  (av->theXBlobs[i].CorrectedQ() == av->theUBlobs[k].CorrectedQ()) )
		{
		  av->theClusters.push_back ( ACluster(&(av->theXBlobs[i]),
						       &(av->theYBlobs[j]),
						       &(av->theUBlobs[k])));
		}
	    }
	}
    }

}
