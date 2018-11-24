#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Classfic
{
private:
    string gender;
    float weight, height;
    string _class;

public:
    void SetGender(string A)
    {gender=A;}
    void SetHeight(float q)
    {height=q;}
    void SetWeight(float t)
    {weight=t;}
    void SetClass(string B)
    {_class=B;}

    string GetGender()
    {return gender;}
    float GetHeight()
    {return height;}
    float GetWeight()
    {return weight;}
    string GetClass()
    {return _class;}
};

class MeanVar
{
private:
    float htmean, htvar;
    float wtmean, wtvar;
public:
    MeanVar()
    {
        htmean=0;htvar=0;wtmean=0;wtvar=0;
    }
    void SetHtMean(float q)
    {htmean=q;}
    void SetHtVar(float t)
    {htvar=t;}
    void SetWtMean(float p)
    {wtmean=p;}
    void SetWtVar(float v)
    {wtvar=v;}

    float GetHtMean()
    {return htmean;}
    float GetHtVar()
    {return htvar;}
    float GetWtMean()
    {return wtmean;}
    float GetWtVar()
    {return wtvar;}
};

MeanVar Under, Normal, Over;

void CalculateMean(Classfic cal[], int limit);
float CalculateVar(float mean, Classfic _data[], string _classed, int total, int totalloop, char ch);
float Probab(float ht, float wt, char cht);
void ResultMain(float, float, float, float, float, float);

int main()
{
    Classfic Buildd[62];
	string input_file_name;
	int COUNTER=0;
	float UnderWeightProb, NormalWeightProb, OverWeightProb;
	float UnderWtCon, NormalWtCon, OverWtCon;
	float UserINPUTHt, UserINPUTWt;

	cout << "Give name of input file : ";
	cin >> input_file_name;

	ifstream input_stream(input_file_name.c_str());

	if(input_stream == '\0')
    {
        cout<<"Could not open file";
        exit(0);
    }

    string tempt[4];
	string buffer;
    string line;

    while(getline(input_stream,line))
    {
        int countme=0;
        stringstream  lineStream(line);
        string        cell;

        while(getline(lineStream,cell,','))
        {
            tempt[countme]=cell;
            countme++;
        }
        if(COUNTER>0)
        {
            Buildd[COUNTER].SetGender(tempt[0]);
            Buildd[COUNTER].SetHeight(atof(tempt[1].c_str()));
            Buildd[COUNTER].SetWeight(atof(tempt[2].c_str()));
            Buildd[COUNTER].SetClass(tempt[3]);
        }
        COUNTER++;
    }

    //Proir
    int CU=0, CN=0, CO=0;
    for(int i=1; i<=COUNTER; i++)
    {
       // cout<<Buildd[i].GetClass();
        if(Buildd[i].GetClass()=="underweight")
                CU++;
        else if(Buildd[i].GetClass()=="normal")
            CN++;
        else if(Buildd[i].GetClass()=="overweight")
            CO++;
        else
        {}
    }
    UnderWeightProb=float(CU)/60;
    NormalWeightProb=float(CN)/60;
    OverWeightProb=float(CO)/60;
    //PriorEnd

    CalculateMean(Buildd, COUNTER);

    input_stream.close();
    cout<<"Success";
    //MOCK_DATA.csv
    //Main Program
    cout<<"Enter Height";
    cin>>UserINPUTHt;
    cout<<"Enter Weight";
    cin>>UserINPUTWt;

    UnderWtCon= Probab(UserINPUTHt, UserINPUTWt, 'u');
    NormalWtCon= Probab(UserINPUTHt, UserINPUTWt, 'n');
    OverWtCon= Probab(UserINPUTHt, UserINPUTWt, 'o');

    //nowthefinaaley
    ResultMain(UnderWeightProb, NormalWeightProb, OverWeightProb, UnderWtCon, NormalWtCon, OverWtCon);

	return 0;
}

void ResultMain(float a, float b, float c, float x, float y, float z)
{
    float tmpUnder, tmpNormal, tmpOver;

    float total=0;
    total=(a*x)+(b*y)+(c*z);
    tmpUnder=(a*x)/total;
    tmpNormal=(b*y)/total;
    tmpOver=(c*z)/total;
    cout<<tmpNormal;
    cout<<tmpOver;
    cout<<tmpUnder;
  /*  if(tmpUnder > tmpOver && tmpUnder > tmpNormal)
        cout<<"It is underweight";
    else if(tmpOver > tmpNormal)
        cout<<"It is overweight";
    else
        cout<<"It is underweight";*/
}

float Probab(float UserINPUTHt,float UserINPUTWt, char cht)
{
    float meanht, varianceht, meanwt, variancewt;
    if(cht=='u')
    {
        meanht=Under.GetHtMean();
        varianceht=Under.GetHtVar();
        meanwt=Under.GetWtMean();
        variancewt=Under.GetWtVar();
    }
    else if(cht=='n')
    {
        meanht=Normal.GetHtMean();
        varianceht=Normal.GetHtVar();
        meanwt=Normal.GetWtMean();
        variancewt=Normal.GetWtVar();
    }
    else if(cht=='o')
    {
        meanht=Over.GetHtMean();
        varianceht=Over.GetHtVar();
        meanwt=Over.GetWtMean();
        variancewt=Over.GetWtVar();
    }
    else{}

    cout<<Normal.GetHtMean()<<endl;
    cout<<Normal.GetHtVar()<<endl;
    cout<<Normal.GetWtMean()<<endl;
    cout<<Normal.GetWtVar()<<endl;
    cout<<Over.GetHtMean()<<endl;
    cout<<Over.GetHtVar()<<endl;
    cout<<Over.GetWtMean()<<endl;
    cout<<Over.GetWtVar()<<endl;
    cout<<Under.GetHtMean()<<endl;
    cout<<Under.GetHtVar()<<endl;
    cout<<Under.GetWtMean()<<endl;
    cout<<Under.GetWtVar()<<endl;

    float PHt=exp(-0.5f * float((pow((UserINPUTHt-meanht),2))/varianceht));
    float PWt=exp(-0.5f * float((pow((UserINPUTWt-meanht),2))/variancewt));
    float RPHt=pow((2 * 3.14159f * varianceht), -0.5f);
    float RPWt=pow((2 * 3.14159f * variancewt), -0.5f);
    float tmp = PHt * RPHt * PWt * RPWt;

    return tmp;
}

void CalculateMean(Classfic A[], int limit)
{
    int CU=0, CN=0, CO=0;
    float SUh=0, SNh=0, SOh=0;
    float SUw=0, SNw=0, SOw=0;
    for(int i=1; i<=limit; i++)
    {
        if(A[i].GetClass()=="underweight")
        {
            CU++;
            SUh+=A[i].GetHeight();
            SUw+=A[i].GetWeight();
        }
        else if(A[i].GetClass()=="normal")
        {
            CN++;
            SNh+=A[i].GetHeight();
            SNw+=A[i].GetWeight();
        }
        else if(A[i].GetClass()=="overweight")
        {
             CO++;
             SOh+=A[i].GetHeight();
             SOw+=A[i].GetWeight();
        }
        else
        {}
    }
    Under.SetHtMean(SUh/float(CU));
    Under.SetHtVar(CalculateVar(Under.GetHtMean(), A, "underweight", CU, limit,'h'));
    Under.SetWtMean(SUw/float(CU));
    Under.SetWtVar(CalculateVar(Under.GetWtMean(), A, "underweight", CU, limit,'w'));

    Normal.SetHtMean(SNh/float(CN));
    Normal.SetHtVar(CalculateVar(Normal.GetHtMean(), A, "normal", CU, limit,'h'));
    Normal.SetWtMean(SNw/float(CN));
    Normal.SetWtVar(CalculateVar(Normal.GetWtMean(), A, "normal", CU, limit,'w'));

    Over.SetHtMean(SOh/float(CO));
    Over.SetHtVar(CalculateVar(Over.GetHtMean(), A, "overweight", CU, limit,'h'));
    Over.SetWtMean(SOw/float(CO));
    Over.SetWtVar(CalculateVar(Over.GetWtMean(), A, "overweight", CU, limit,'w'));
    cout<<"Success";
}

float CalculateVar(float mean, Classfic _data[], string _classed, int total, int totalloop, char ch)
{
    float tempSum=0;
    float temphold;
    for(int i=1; i<=totalloop; i++)
    {
        if(_data[i].GetClass()==_classed)
        {
            if(ch=='h')
            {
                tempSum+= pow((_data[i].GetHeight() - mean),2.0);
            }
            else
            {
                tempSum+= pow((_data[i].GetWeight() - mean),2.0);
            }

        }
    }
    temphold=tempSum/float(total);

    return temphold;
}
