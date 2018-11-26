//
// Author: Miguel González-Fierro <mgpalaci@ing.uc3m.es>, (C) 2011
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//


#include <iostream>
#include "DynamicsFunctions.h"
#include "Matrix.h"
#include "SpatialVectorArithmetic.h"
#include "ModelConstructors.h"
#include "ArrayRelease.h"

using namespace std;


void df::IDf(mc* model, float* Xfb, float* vfb, float* q_i, float* qd_i, float* qdd_i)
{
	int NBR = model[0].NB - 6;

	matrix matrix_aux;
	sva sva_aux;
	df* df_aux = new df [NBR];
	afb_idf = new float [NBR];
	tau_idf = new float [NBR];
	int* parent_r = new int [model[0].NB - 6];

	a_grav = NULL;
	a_grav_n = NULL;

	float a_grav_pos[6] = {0,0,0,0,0,-9.81};
	float a_grav_neg[6] = {0,0,0,0,0,9.81};
	a_grav = a_grav_pos;
	a_grav_n = a_grav_neg;

	for (i=0;i<model[0].NB - 6;i++)
	{
		int aux = model[i+6].parent - 6;
		parent_r[i] = aux;
	}


	vfb = matrix_aux.Multiplication(Xfb,6,6,vfb,0,6);
	afb_idf = matrix_aux.Multiplication(Xfb,6,6,a_grav_n,0,6);

	for (i=0;i<NBR;i++)
	{
		df_aux[i].jcalc(model[i+6].pitch,q_i[i]);
		df_aux[i].vJ = matrix_aux.ScalarMulti(df_aux[i].S,0,6,qd_i[i]);

		df_aux[i].Xup = matrix_aux.Multiplication(df_aux[i].Xj,6,6,model[i+6].Xtree,6,6);

		if (parent_r[i] == 0)
		{
			float* Xup_vfb = matrix_aux.Multiplication(df_aux[i].Xup,6,6,vfb,0,6);

			df_aux[i].v = matrix_aux.Sum(Xup_vfb,df_aux[i].vJ,4);

			float* Xup_afb_idf = matrix_aux.Multiplication(df_aux[i].Xup,6,6,afb_idf,0,6);
			float* S_qdd = matrix_aux.ScalarMulti(df_aux[i].S,0,6,qdd_i[i]);
			float* crm_vJ = matrix_aux.Multiplication(sva_aux.crm(df_aux[i].v),6,6,df_aux[i].vJ,0,6);

			float* Xup_afb_idf_S_qdd = matrix_aux.Sum(Xup_afb_idf,S_qdd,4);
			df_aux[i].a = matrix_aux.Sum(Xup_afb_idf_S_qdd,crm_vJ,4);

		}
		else
		{
			int temp = parent_r[i] - 1;

			float Xup_v[6];
			matrix_aux.Multiplication(Xup_v,df_aux[i].Xup,6,6,df_aux[temp].v,0,6);
			df_aux[i].v = matrix_aux.Sum(Xup_v,df_aux[i].vJ,4);

			float* asd = matrix_aux.Multiplication(df_aux[i].Xup,6,6,df_aux[temp].v,0,6);
			
			float* Xup_a = matrix_aux.Multiplication(df_aux[i].Xup,6,6,df_aux[temp].a,0,6);
			float* S_qdd = matrix_aux.ScalarMulti(df_aux[i].S,0,6,qdd_i[i]);
			float* crm_vJ = matrix_aux.Multiplication(sva_aux.crm(df_aux[i].v),6,6,df_aux[i].vJ,0,6);

			float* aux = matrix_aux.Sum(Xup_a,S_qdd,4);
			df_aux[i].a = matrix_aux.Sum(aux,crm_vJ,4);
		}

		df_aux[i].IC = model[i+6].I;

		float* IC_a = matrix_aux.Multiplication(df_aux[i].IC,6,6,df_aux[i].a,0,6);
		float* crm_v = sva_aux.crf(df_aux[i].v);
		float* crf_IC = matrix_aux.Multiplication(crm_v,6,6,df_aux[i].IC,6,6);
		float* crf_IC_v = matrix_aux.Multiplication(crf_IC,6,6,df_aux[i].v,0,6);

		df_aux[i].pC = matrix_aux.Sum(IC_a,crf_IC_v,4);
	}

	df_aux[0].ICfb = model[5].I;
	float* IC_afb_idf = matrix_aux.Multiplication(df_aux[0].ICfb,6,6,afb_idf,0,6);
	float* crf_vfb = sva_aux.crf(vfb);
	float* crf_IC = matrix_aux.Multiplication(crf_vfb,6,6,df_aux[0].ICfb,6,6);
	float* crf_IC_vfb = matrix_aux.Multiplication(crf_IC,6,6,vfb,0,6);

	df_aux[0].pCfb = matrix_aux.Sum(IC_afb_idf,crf_IC_vfb);

	for(i=NBR-1;i>=0;i--)
	{
		if (parent_r[i] == 0)
		{	

			float* Xup_t = matrix_aux.Transponse(df_aux[i].Xup,6,6);
			float* Xup_IC =  matrix_aux.Multiplication(Xup_t,6,6,df_aux[i].IC,6,6);
			float* Xup_IC_Xup = matrix_aux.Multiplication(Xup_IC,6,6,df_aux[i].Xup,6,6);
			float* Xup_t_pC = matrix_aux.Multiplication(Xup_t,6,6,df_aux[i].pC,0,6);

			df_aux[0].ICfb = matrix_aux.Sum(df_aux[0].ICfb,Xup_IC_Xup,3);
			df_aux[0].pCfb = matrix_aux.Sum(df_aux[0].pCfb,Xup_t_pC,4);
		}
		else
		{
			int temp = parent_r[i] - 1;

			float* Xup_t = matrix_aux.Transponse(df_aux[i].Xup,6,6);
			float* Xup_IC =  matrix_aux.Multiplication(Xup_t,6,6,df_aux[i].IC,6,6);
			float* Xup_IC_Xup = matrix_aux.Multiplication(Xup_IC,6,6,df_aux[i].Xup,6,6);
			float* Xup_t_pC = matrix_aux.Multiplication(Xup_t,6,6,df_aux[i].pC,0,6);

			df_aux[temp].IC = matrix_aux.Sum(df_aux[temp].IC,Xup_IC_Xup,3);
			df_aux[temp].pC = matrix_aux.Sum(df_aux[temp].pC,Xup_t_pC,4);
		}
	}

	float* ICfb_n = matrix_aux.ScalarMulti(df_aux[0].ICfb,6,6,-1);


	afb_idf = matrix_aux.LeftDiv(ICfb_n,6,df_aux[0].pCfb,0,6);

	for (i=0;i<NBR;i++)
	{
		if (parent_r[i] == 0)
		{
			df_aux[i].a = matrix_aux.Multiplication(df_aux[i].Xup,6,6,afb_idf,0,6);
		}
		else
		{
			int temp = parent_r[i] - 1;
			df_aux[i].a = matrix_aux.Multiplication(df_aux[i].Xup,6,6,df_aux[temp].a,0,6);
		}

		float* IC_a = matrix_aux.Multiplication(df_aux[i].IC,6,6,df_aux[i].a,0,6);
		float* IC_a_pC = matrix_aux.Sum(IC_a,df_aux[i].pC,4);

		float* temp = matrix_aux.Multiplication(df_aux[i].S,0,6,IC_a_pC,0,6);

		tau_idf[i] = temp[0];
	}

	afb_idf = matrix_aux.LeftDiv(Xfb,6,afb_idf,0,6);
}


void df::IDf(mc* model, float* Xfb, float* vfb, float* q_i, float* qd_i, float* qdd_i, df* f_ext, float* grav_accn)
{
	int NBR = model[0].NB - 6;

	matrix matrix_aux;
	sva sva_aux;
	df* df_aux = new df [NBR];
	afb_idf = new float [NBR];
	tau_idf = new float [NBR];
	int* parent_r = new int [model[0].NB - 6];

	a_grav = NULL;
	a_grav_n = NULL;

	if (grav_accn == 0)
	{
		float a_grav_pos[6] = {0,0,0,0,0,-9.81};
		float a_grav_neg[6] = {0,0,0,0,0,9.81};
		a_grav = a_grav_pos;
		a_grav_n = a_grav_neg;
	}
	else
	{
		float a_grav_pos[6] = {0,0,0,grav_accn[0],grav_accn[1],grav_accn[2]};
		float a_grav_neg[6] = {0,0,0,-1*grav_accn[0],-1*grav_accn[1],-1*grav_accn[2]};
		a_grav = a_grav_pos;
		a_grav_n = a_grav_neg;
	}

	for (i=0;i<model[0].NB - 6;i++)
	{
		int aux = model[i+6].parent - 6;
		parent_r[i] = aux;
	}


	vfb = matrix_aux.Multiplication(Xfb,6,6,vfb,0,6);
	afb_idf = matrix_aux.Multiplication(Xfb,6,6,a_grav_n,0,6);

	for (i=0;i<NBR;i++)
	{
		df_aux[i].jcalc(model[i+6].pitch,q_i[i]);
		df_aux[i].vJ = matrix_aux.ScalarMulti(df_aux[i].S,0,6,qd_i[i]);

		df_aux[i].Xup = matrix_aux.Multiplication(df_aux[i].Xj,6,6,model[i+6].Xtree,6,6);

		if (parent_r[i] == 0)
		{
			float* Xup_vfb = matrix_aux.Multiplication(df_aux[i].Xup,6,6,vfb,0,6);

			df_aux[i].v = matrix_aux.Sum(Xup_vfb,df_aux[i].vJ,4);

			float* Xup_afb_idf = matrix_aux.Multiplication(df_aux[i].Xup,6,6,afb_idf,0,6);
			float* S_qdd = matrix_aux.ScalarMulti(df_aux[i].S,0,6,qdd_i[i]);
			float* crm_vJ = matrix_aux.Multiplication(sva_aux.crm(df_aux[i].v),6,6,df_aux[i].vJ,0,6);

			float* Xup_afb_idf_S_qdd = matrix_aux.Sum(Xup_afb_idf,S_qdd,4);
			df_aux[i].a = matrix_aux.Sum(Xup_afb_idf_S_qdd,crm_vJ,4);

		}
		else
		{
			int temp = parent_r[i] - 1;

			float Xup_v[6];
			matrix_aux.Multiplication(Xup_v,df_aux[i].Xup,6,6,df_aux[temp].v,0,6);
			df_aux[i].v = matrix_aux.Sum(Xup_v,df_aux[i].vJ,4);

			float* asd = matrix_aux.Multiplication(df_aux[i].Xup,6,6,df_aux[temp].v,0,6);
			
			float* Xup_a = matrix_aux.Multiplication(df_aux[i].Xup,6,6,df_aux[temp].a,0,6);
			float* S_qdd = matrix_aux.ScalarMulti(df_aux[i].S,0,6,qdd_i[i]);
			float* crm_vJ = matrix_aux.Multiplication(sva_aux.crm(df_aux[i].v),6,6,df_aux[i].vJ,0,6);

			float* aux = matrix_aux.Sum(Xup_a,S_qdd,4);
			df_aux[i].a = matrix_aux.Sum(aux,crm_vJ,4);
		}

		df_aux[i].IC = model[i+6].I;

		float* IC_a = matrix_aux.Multiplication(df_aux[i].IC,6,6,df_aux[i].a,0,6);
		float* crm_v = sva_aux.crf(df_aux[i].v);
		float* crf_IC = matrix_aux.Multiplication(crm_v,6,6,df_aux[i].IC,6,6);
		float* crf_IC_v = matrix_aux.Multiplication(crf_IC,6,6,df_aux[i].v,0,6);

		df_aux[i].pC = matrix_aux.Sum(IC_a,crf_IC_v,4);

		if (f_ext[i].f_ext != 0)
		{
			df_aux[i].pC = matrix_aux.Sum(df_aux[i].pC,f_ext[i+6].f_ext,1);
		}
	}



	df_aux[0].ICfb = model[5].I;
	float* IC_afb_idf = matrix_aux.Multiplication(df_aux[0].ICfb,6,6,afb_idf,0,6);
	float* crf_vfb = sva_aux.crf(vfb);
	float* crf_IC = matrix_aux.Multiplication(crf_vfb,6,6,df_aux[0].ICfb,6,6);
	float* crf_IC_vfb = matrix_aux.Multiplication(crf_IC,6,6,vfb,0,6);

	df_aux[0].pCfb = matrix_aux.Sum(IC_afb_idf,crf_IC_vfb);

	if (f_ext[i].f_ext != 0)
	{
		df_aux[i].pC = matrix_aux.Sum(df_aux[i].pC,f_ext[5].f_ext,1);
	}

	for(i=NBR-1;i>=0;i--)
	{
		if (parent_r[i] == 0)
		{	

			float* Xup_t = matrix_aux.Transponse(df_aux[i].Xup,6,6);
			float* Xup_IC =  matrix_aux.Multiplication(Xup_t,6,6,df_aux[i].IC,6,6);
			float* Xup_IC_Xup = matrix_aux.Multiplication(Xup_IC,6,6,df_aux[i].Xup,6,6);
			float* Xup_t_pC = matrix_aux.Multiplication(Xup_t,6,6,df_aux[i].pC,0,6);

			df_aux[0].ICfb = matrix_aux.Sum(df_aux[0].ICfb,Xup_IC_Xup,3);
			df_aux[0].pCfb = matrix_aux.Sum(df_aux[0].pCfb,Xup_t_pC,4);
		}
		else
		{
			int temp = parent_r[i] - 1;

			float* Xup_t = matrix_aux.Transponse(df_aux[i].Xup,6,6);
			float* Xup_IC =  matrix_aux.Multiplication(Xup_t,6,6,df_aux[i].IC,6,6);
			float* Xup_IC_Xup = matrix_aux.Multiplication(Xup_IC,6,6,df_aux[i].Xup,6,6);
			float* Xup_t_pC = matrix_aux.Multiplication(Xup_t,6,6,df_aux[i].pC,0,6);

			df_aux[temp].IC = matrix_aux.Sum(df_aux[temp].IC,Xup_IC_Xup,3);
			df_aux[temp].pC = matrix_aux.Sum(df_aux[temp].pC,Xup_t_pC,4);
		}
	}

	float* ICfb_n = matrix_aux.ScalarMulti(df_aux[0].ICfb,6,6,-1);


	afb_idf = matrix_aux.LeftDiv(ICfb_n,6,df_aux[0].pCfb,0,6);


	for (i=0;i<NBR;i++)
	{
		if (parent_r[i] == 0)
		{
			df_aux[i].a = matrix_aux.Multiplication(df_aux[i].Xup,6,6,afb_idf,0,6);
		}
		else
		{
			int temp = parent_r[i] - 1;
			df_aux[i].a = matrix_aux.Multiplication(df_aux[i].Xup,6,6,df_aux[temp].a,0,6);
		}

		float* IC_a = matrix_aux.Multiplication(df_aux[i].IC,6,6,df_aux[i].a,0,6);
		float* IC_a_pC = matrix_aux.Sum(IC_a,df_aux[i].pC,4);

		float* temp = matrix_aux.Multiplication(df_aux[i].S,0,6,IC_a_pC,0,6);

		tau_idf[i] = temp[0];
	}
	afb_idf = matrix_aux.LeftDiv(Xfb,6,afb_idf,0,6);
}
