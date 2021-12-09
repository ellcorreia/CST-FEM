#ifndef Unit1H
#define Unit1H
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <vector>

typedef std::vector<double> vec1D ;
typedef std::vector<vec1D> vec2D ;



//NO - COORDENADAS E CONDICOES DE CONTORNO
class CNO
{
 public:
	int I;          ///< Indice
	int VINX;      	///< Condicao de Contorno ==0 (livre) e ==1 (engastado)
	int VINY;
	double X;	    ///< No em X
	double Y;       ///< No em Y
	double UX;      ///<  U - Deslocamento
	double UY;
	double PX;      ///<  P - Carga
	double PY;
	int grauLiberdade;

	CNO (const int& _I,const double& _X, const double& _Y,  const int& _VINX, const int& _VINY , const double& _UX, const double& _UY , const double& _PX, const double& _PY  );



	};
typedef std::vector<CNO> VCNO;

typedef CNO* PNO;
typedef std::vector<PNO> VPNO; // Vetor de ponteiros da classe No
//MATERIAIS - PROPRIEDADES
class CMATERIAL
{
 public:
	int I;
	double E;         ///< Modulo de elasticidade
	double poisson;   ///< Poisson

	CMATERIAL (const int& _I, const double& _E, const double& _poisson);
    
};
typedef std::vector<CMATERIAL> VCMATERIAL;

//ELEMENTOS - GEOMETRIA
class CELEMENTO
{
  public:

	int I;

	VPNO NO ;
	int EP;               ///< EPT = 1 e EPD = 0
	CMATERIAL* MAT;       ///< material
	vec2D KL;             /// Matriz de rigidez local
	vec1D FL;

	CELEMENTO ( const int& _I, CNO* _NO0,CNO* _NO1, CNO* _NO2, const int& _EP, CMATERIAL* _MAT );

    // CALCULADORAS
	void calK ();         /// retorna a matriz
	void calF ();
	void calA ();
	void calL () ;
};
typedef std::vector<CELEMENTO> VCELEMENTO;

void RESOLVE_GAUSS(vec1D& U ,vec2D& RIG, vec1D& F);

#endif
