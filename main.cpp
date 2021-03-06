#pragma hdrstop
#pragma argsused
#include <math.h>

#include "main.h"


int main()
{
  VCNO No;
  VCMATERIAL Mat;
  VCELEMENTO Ele;
  int NM;      // Numero mat
  int NN;
  int NE;

  char s[1000];       ///< Variavel auxiliar
  std::ifstream Ent;  ///< Arquivo de leirura
  std::ofstream Sai;  /// sa�da de dados

  Ent.open("C:/CST/ENTRADA.txt");     //le arquivo entrada

  //PRINT ELEMENTOS
  Ent.getline(s,1000);
  std::cout<< s << std::endl;
  Ent >> NM;  Ent.getline(s,1000);
  Ent.getline(s,1000);
  Ent >> NN;  Ent.getline(s,1000);
  Ent.getline(s,1000);
  Ent >> NE;  Ent.getline(s,1000);
  std::cout<< NM << " \n" << NN << " \n" << NE << std::endl;

  //PRINT MATERIAL
  Ent.getline(s,1000);   //pula linha
  std::cout<< s << std::endl;
  Ent.getline(s,1000);   //pula linha
  std::cout<< s << std::endl;
  for (int I = 0; I<NM; I++)    //le
	{
	  int _I;
	  double _E,_poisson;
	  Ent >> _I  >> _E >> _poisson;   Ent.getline(s,1000);
	  Mat.push_back(CMATERIAL(_I,_E,_poisson));
	  std::cout<< Mat[I].I << " " << Mat[I].E << " " << Mat[I].poisson << std::endl;
	}

  //PRINT COORDENADA
  Ent.getline(s,1000);   //pula linha
  std::cout<< s << std::endl;
  Ent.getline(s,1000);   //pula linha
  std::cout<< s << std::endl;
  for (int I = 0; I<NN; I++)    //le
	{
	  int _I;
	  int _VINX;
	  int _VINY;
	  double _X;
	  double _Y;
	  double _UX;
	  double _UY;
	  double _PX;
	  double _PY;

	  Ent >> _I  >> _X >> _Y >> _VINX >> _VINY >> _UX >> _UY >> _PX >> _PY;   Ent.getline(s,1000);
	  No.push_back(CNO(_I,_X,_Y,_VINX,_VINY,_UX,_UY,_PX,_PY));   //No
	  std::cout<< No[I].I << " " << No[I].X << " " <<  " " << No[I].Y << " " << " " << No[I].VINX << " "  << No[I].VINY << " " << No[I].UX << " " << No[I].UY << " " << No[I].PX << " " << No[I].PY << std::endl;
	}



//PRINT CONECTIVIDADE
  Ent.getline(s,1000);   //pula linha
  std::cout<< s << std::endl;
  Ent.getline(s,1000);   //pula linha
  std::cout<< s << std::endl;
  for (int I = 0; I<NE; I++)    //le
	{
	  int _I;
	  int NO0;
	  int NO1;
	  int NO2;
	  int _EP;
	  int MAT;

	  Ent >> _I  >> NO0 >> NO1 >> NO2 >> _EP >> MAT ;   Ent.getline(s,1000);
	  Ele.push_back(CELEMENTO(_I,&No[NO0],&No[NO1],&No[NO2],_EP,&Mat[MAT] ));   //Ele
	  std::cout<< Ele[I].I << " " << Ele[I].NO[0]->I << " " << Ele[I].NO[1]->I << " " << Ele[I].NO[2]->I << " " << Ele[I].EP << " " << Ele[I].MAT->I << std::endl;

	}

  vec2D KG;
  KG.resize(2*NN,vec1D(2*NN,0.0));

  for (int I=0; I<NE; I++)
  {
   for (int J=0; J<3; J++)
   {
	for (int K=0; K<3; K++)
	{
	 KG[2*Ele[I].NO[J]->I][2*Ele[I].NO[K]->I]+=Ele[I].KL[2*J][2*K];
	 KG[2*Ele[I].NO[J]->I][2*Ele[I].NO[K]->I+1]+=Ele[I].KL[2*J][2*K+1];
	 KG[2*Ele[I].NO[J]->I+1][2*Ele[I].NO[K]->I]+=Ele[I].KL[2*J+1][2*K];
	 KG[2*Ele[I].NO[J]->I+1][2*Ele[I].NO[K]->I+1]+=Ele[I].KL[2*J+1][2*K+1];
	}
   }
  }


  std::cout << "MATRIZ GLOBAL" << std::endl;
  for ( int i = 0; i < NN*2; i++ )
  {
	for ( int j = 0; j < NN*2; j++ )
	{
	 // std::cout << "KG [" << i << "][" << j << "]: ";
	 std::cout << KG[i][j] << " " ;
	}
	std::cout << std::endl;
  }


 ///////////// VETOR FOR�A P 
  vec1D P;
  P.resize(2*NN, 0.0);
  std::cout << "\nVETOR DE CARGA \n" ;
   for (int j = 0; j<NN; j++)
   {

	 P[2*j] = No[j].PX;
	 P[2*j+1] = No[j].PY;
	 std::cout <<  P[2*j] << " " << P[2*j+1] << " ";

   }
	std::cout << "\n" ;

 //////////// VETOR FOR�A P ^^^^^^^^^^


 ///////////// COND. CONTORNO  vvvvvvvv

  for (int j = 0; j<NN; j++)
  {
	if (No[j].VINX== 1)
	{
	 for (int i = 0; i<2*NN; i++)
	 {
	  KG[2*j][i]=0;  // zera a linha inteira
	  KG[i][2*j]=0;  // zera a coluna inteira
	 }

	 KG[2*j][2*j]=1;
	 P[2*j]=No[j].UX;
	}
	if (No[j].VINY== 1)
	{
	 for (int i = 0; i<2*NN; i++)
	 {
	  KG[2*j+1][i]=0;  // zera a linha inteira
	  KG[i][2*j+1]=0;  // zera a coluna inteira
	 }

	 KG[2*j+1][2*j+1]=1;
	 P[2*j+1]=No[j].UY;
	}
  }

  std::cout << "MATRIZ GLOBAL" << std::endl;
  for ( int i = 0; i < NN*2; i++ )
  {
	for ( int j = 0; j < NN*2; j++ )
	{
	 // std::cout << "KG [" << i << "][" << j << "]: ";
	 std::cout << KG[i][j] << " " ;
	}
	std::cout << std::endl;
  }

  std::cout << "\nVETOR DE CARGA \n" ;
   for (int j = 0; j<NN; j++)
   {

	 std::cout <<  P[2*j] << " " << P[2*j+1] << " ";

   }
	std::cout << "\n" ;

  vec1D U;
  U.resize(2*NN, 0.0);
  RESOLVE_GAUSS(U , KG, P);
  for (int j = 0; j<NN; j++)
  {
	No[j].UX=U[2*j];
    No[j].UY=U[2*j+1];
  }
  std::cout << "\nVETOR DE DESLOCAMENTOS \n" ;
   for (int j = 0; j<NN; j++)
   {

	 std::cout <<  U[2*j] << " " << U[2*j+1] << " ";

   }
	std::cout << "\n" ;

  std::cout << "MATRIZ GLOBAL" << std::endl;
  for ( int i = 0; i < NN*2; i++ )
  {
	for ( int j = 0; j < NN*2; j++ )
	{
	 // std::cout << "KG [" << i << "][" << j << "]: ";
	 std::cout << KG[i][j] << " " ;
	}
	std::cout << std::endl;
  }

}
/// -------------------------------------------------------------

CMATERIAL::CMATERIAL (const int& _I, const double& _E, const double& _poisson)
{
  I=_I;
  E=_E;
  poisson=_poisson;
}

CNO::CNO (const int& _I,const double& _X, const double& _Y,  const int& _VINX, const int& _VINY , const double& _UX, const double& _UY , const double& _PX, const double& _PY   )
{
 I=_I;
 VINX = _VINX;
 VINY = _VINY;
 X=_X;
 Y=_Y;
 UX=_UX;
 UY=_UY;
 PX=_PX;
 PY=_PY;
}

CELEMENTO::CELEMENTO ( const int& _I, CNO* _NO0,CNO* _NO1, CNO* _NO2, const int& _EP, CMATERIAL* _MAT )
{
 I=_I;
 NO.push_back(_NO0);
 NO.push_back(_NO1);
 NO.push_back(_NO2);
 //NO0=_NO0;               ///< conectividade dos nos
 //NO1=_NO1;               ///< conectividade dos nos
 //NO2=_NO2;               ///< conectividade dos nos
 EP=_EP;                 ///< EPT = 1 e EPD = 0
 MAT=_MAT;
 calK();
 calF();
}

 void CELEMENTO::calK ()
 {

  double a1;
  double a2;
  double a3;
  double b1;
  double b2;
  double b3;
  double beta;
  double EL;  //E'
  double poissonL;  //POISSON'

  if (EP==1)
  {
   EL=MAT->E;
   poissonL=MAT->poisson;
   beta=(1-poissonL)/2;
  }
  else
  {
   EL=MAT->E/(1-(MAT->poisson)*(MAT->poisson));
   poissonL=MAT->poisson/(1-MAT->poisson);
   beta=(1-poissonL)/2;
  }

  //std::cout << " TESTE "  <<NO0->X  << "  "  << NO0->Y  << "\n";

  a1=NO[2]->X-NO[1]->X;
  a2=NO[0]->X-NO[2]->X;
  a3=NO[1]->X-NO[0]->X;
  b1=NO[1]->Y-NO[2]->Y;
  b2=NO[2]->Y-NO[0]->Y;
  b3=NO[0]->Y-NO[1]->Y;

  /*
  //IMPRIME A E B
  std::cout<< "a1 = " << a1 << "\n";
  std::cout<< "a2 = " << a2 << "\n";
  std::cout<< "a3 = " << a3 << "\n";
  std::cout<< "b1 = " << b1 << "\n";
  std::cout<< "b2 = " << b2 << "\n";
  std::cout<< "b3 = " << b3 << "\n";
  */

  // MATRIZ K - LOCAL
  KL.resize(6, vec1D(6,0.0));
  KL[0][0]=b1*b1+a1*a1*beta;
  KL[0][1]=a1*b1*(beta+poissonL);
  KL[0][2]=b1*b2+a1*a2*beta;
  KL[0][3]=a1*b2*beta+a2*b1*poissonL;
  KL[0][4]=b1*b3+a1*a3*beta;
  KL[0][5]=a1*b3*beta+a3*b1*poissonL;

  KL[1][0]=a1*b1*(beta+poissonL);
  KL[1][1]=a1*a1+b1*b1*beta;
  KL[1][2]=a2*b1*beta+a1*b2*poissonL;
  KL[1][3]=a1*a2+b1*b2*beta;
  KL[1][4]=a3*b1*beta+a1*b3*poissonL;
  KL[1][5]=a1*a3+b1*b3*beta;

  KL[2][0]=b1*b2+a1*a2*beta;
  KL[2][1]=a2*b1*beta+a1*b2*poissonL;
  KL[2][2]=b2*b2+a2*a2*beta;
  KL[2][3]=a2*b2*(beta+poissonL);
  KL[2][4]=b2*b3+a2*a3*beta;
  KL[2][5]=a2*b3*beta+a3*b2*poissonL;

  KL[3][0]=a1*b2*beta+a2*b1*poissonL;
  KL[3][1]=a1*a2+b1*b2*beta;
  KL[3][2]=a2*b2*(beta+poissonL);
  KL[3][3]=a2*a2+b2*b2*beta;
  KL[3][4]=a3*b2*beta+a2*b3*poissonL;
  KL[3][5]=a2*a3+b2*b3*beta;

  KL[4][0]=b1*b3+a1*a3*beta;
  KL[4][1]=a3*b1*beta+a1*b3*poissonL;
  KL[4][2]=b2*b3+a2*a3*beta;
  KL[4][3]=a3*b2*beta+a2*b3*poissonL;
  KL[4][4]=b3*b3+a3*a3*beta;
  KL[4][5]=a3*b3*(beta+poissonL);

  KL[5][0]=a1*b3*beta+a3*b1*poissonL;
  KL[5][1]=a1*a3+b1*b3*beta;
  KL[5][2]=a2*b3*beta+a3*b2*poissonL;
  KL[5][3]=a2*a3+b2*b3*beta;
  KL[5][4]=a3*b3*(beta+poissonL);
  KL[5][5]=a3*a3+b3*b3*beta;


  int i, j;

  //IMPRIME MATRIZ LOCAL
   for ( int j = 0; j < 6; j++ )
   { std::cout  << KL[0][j] << "  ";
   } std::cout << "\n";
   for ( int j = 0; j < 6; j++ )
   { std::cout  << KL[1][j] << "  ";
   } std::cout << "\n";
   for ( int j = 0; j < 6; j++ )
   { std::cout  << KL[2][j] << "  ";
   } std::cout << "\n";
   for ( int j = 0; j < 6; j++ )
   { std::cout  << KL[3][j] << "  ";
   } std::cout << "\n";
   for ( int j = 0; j < 6; j++ )
   { std::cout  << KL[4][j] << "  ";
   } std::cout << "\n";
   for ( int j = 0; j < 6; j++ )
   { std::cout  << KL[5][j] << "  ";
   } std::cout << "\n";

 }


  void CELEMENTO::calA()
 {

  double A;   /// AREA DO TRIANGULO

  A=(  NO[1]->X*NO[2]->Y
	 + NO[0]->X*NO[1]->Y
	 + NO[2]->X*NO[0]->Y
	 - NO[1]->X*NO[0]->Y
	 - NO[2]->X*NO[1]->Y
	 - NO[0]->X*NO[2]->Y)/2;
 }


 void CELEMENTO::calF()
 {

  FL.resize(6,0.0);
  FL[0]=0.0;
  FL[1]=0.0;
  FL[2]=0.0;
  FL[3]=0.0;
  FL[4]=0.0;
  FL[5]=0.0;

 }


 void RESOLVE_GAUSS(vec1D& U ,vec2D& RIG, vec1D& F) //solver
{
  int GL,SOL,NMAIOR;
  double AUX;
  int I;
  int NG;
  NG=F.size();
  SOL=1;
  I=0;
  GL=NG;
 // V1D U;
 // U.resize(F.size(),0.0);
// PIVOTEAMENTO

  while ((SOL==1)&(I<GL))
  {
    NMAIOR=I;
    for (int J=I+1; J<GL; J++)
    {
      if ((fabs(RIG[J][I]))>(fabs(RIG[NMAIOR][I])))
      {
        NMAIOR=J;
      }
    }
    if (NMAIOR!=I)
    {
      for (int J=I; J<GL; J++)
      {
        AUX=RIG[I][J];
        RIG[I][J]=RIG[NMAIOR][J];
        RIG[NMAIOR][J]=AUX;
      }
      AUX=F[I];
      F[I]=F[NMAIOR];
      F[NMAIOR]=AUX;
    }

// TRIANGULARIZA��O DA MATRIZ

    if (RIG[I][I]==0.0)
	{
	  //ShowMessage("sistema sem solu��o!!!!");
      std::cout <<"sistema sem solu��o!!!!" <<std::endl;
      SOL=0;
      break;
    }
    else
    {
      for (int J=I+1; J<GL; J++)
      {
        AUX=RIG[J][I]/RIG[I][I];
        RIG[J][I]=0.0;
        for  (int K=I+1;K<GL; K++)
        {
          RIG[J][K]=RIG[J][K]-RIG[I][K]*AUX;
        }
        F[J]=F[J]-F[I]*AUX;
      }
    }
    I=I+1;
  }

// RETRODISTRIBUI��O

  if(SOL==1)
  {
    U[GL-1]=F[GL-1]/RIG[GL-1][GL-1];
    for (int II= 2; II<GL+1; II++)
    {
      I=GL-II;
      AUX=0.0;
      for (int J=I+1; J<GL; J++)
      {
        AUX=AUX+RIG[I][J]*U[J];
      }
      U[I]=(F[I]-AUX)/RIG[I][I];
    }
  }
  
}


