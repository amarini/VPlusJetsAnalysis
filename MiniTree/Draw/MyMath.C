#include "TMath.h"
#include "TLorentzVector.h"

namespace MyMath{
	double deltaPhi(float phi1,float phi2){ float dphi=phi1-phi2; while(dphi>M_PI) dphi -= 2*M_PI; while (dphi<-M_PI) dphi+=2*M_PI; return dphi;};
	double AP1(float llPt,float j1Pt,float j2Pt, float j3Pt,
		  float llPhi,float j1Phi,float j2Phi,float j3Phi
		){if(j1Pt<30) return -10;
		  if(j2Pt<30) return -10;
		  if(j3Pt<30) return -10;
		  if(llPt<30) return -10;
		
		  float phi[10]; phi[0]=llPhi;phi[1]=j1Phi;phi[2]=j2Phi;phi[3]=j3Phi;
		
		 float A1=0;
		
		 for(int i=0;i<4;i++)
		  {
		  float min=10;
		  for(int j=0;j<4;j++)
			{
			float dphi=fabs( deltaPhi(phi[i],phi[j]-M_PI) );
			if(dphi<min) min=dphi;
			}
		 A1+=min;
		  }
		 return A1; 
		};
	double A1(float llPt,float j1Pt,float j2Pt, float j3Pt,
		  float llPhi,float j1Phi,float j2Phi,float j3Phi
		){if(j1Pt<30) return -10;
		  if(j2Pt<30) return -10;
		  if(j3Pt<30) return -10;
		  if(llPt<30) return -10;
		
		  float phi[10]; phi[0]=llPhi;phi[1]=j1Phi;phi[2]=j2Phi;phi[3]=j3Phi;
		  float pt[10]; pt[0]=llPt;pt[1]=j1Pt;pt[2]=j2Pt;pt[3]=j3Pt;
		
		 float A1=0;
		
		 for(int i=0;i<4;i++)
		  {
		  float min=10000;
		  for(int j=0;j<4;j++)
			{
			float dphi=fabs( deltaPhi(phi[i],phi[j]) );
			float ptS=TMath::Sqrt( pt[i]*pt[i] +pt[j]*pt[j] - 2*pt[i]*pt[j]*TMath::Cos(M_PI-dphi));
			if(ptS<min) min=ptS;
			}
		 A1+=min;
		  }
		 return A1; 
		};
};
