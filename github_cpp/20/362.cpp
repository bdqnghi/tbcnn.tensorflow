/*

Copyright (C) 1998,1999,2000,2001  Franz Josef Och (RWTH Aachen - Lehrstuhl fuer Informatik VI)

This file is part of GIZA++ ( extension of GIZA ).

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, 
USA.

*/
#include "hmm.h"
#include "Globals.h"
#include "utility.h"
#include "HMMTables.h"
#include "ForwardBackward.h"
#include "Parameter.h"

#define CLASSIFY(i,empty,ianf) bool empty=(i>=l); unsigned int ianf=(i%l);
#define CLASSIFY2(i,ianf) unsigned int ianf=(i%l);

extern float step_k; 
short PredictionInAlignments=0;
short UniformEntryExit=3;
short HMMTrainingSpecialFlags=0;

GLOBAL_PARAMETER2(int,ModelH_Dump_Freq,"HMM DUMP FREQUENCY","th","dump frequency of HMM",PARLEV_OUTPUT,0);

GLOBAL_PARAMETER(short,CompareAlDeps,"emAlignmentDependencies",
		 "lextrain: dependencies in the HMM alignment model. "
		 " &1: sentence length; &2: previous class; &4: previous position; "
		 " &8: French position; &16: French class"
		 ,PARLEV_MODELS,1);
GLOBAL_PARAMETER(double,GLOBALProbabilityForEmpty,"emProbForEmpty",
		 "f-b-trn: probability for empty word",PARLEV_MODELS,0.4);
GLOBAL_PARAMETER(short,SmoothHMM,"emSmoothHMM",
		 "f-b-trn: smooth HMM model &1: modified counts; &2:perform smoothing with -emAlSmooth",PARLEV_SPECIAL,2);
GLOBAL_PARAMETER(double,HMMAlignmentModelSmoothFactor,"emAlSmooth",
		 "f-b-trn: smoothing factor for HMM alignment model (can be ignored by -emSmoothHMM)",PARLEV_SMOOTH,0.2);


/*template<class T>
void smooth_standard(T*a,T*b,double p)
{
  int n=b-a;
  if( n==0 ) 
    return;
  double pp=p/n;
  for(T*i=a;i!=b;++i)
    *i = (1.0-p)*(*i)+pp;
}*/


hmm::hmm(model2& m)
  : model2(m),counts(GLOBALProbabilityForEmpty,ewordclasses,fwordclasses),
    probs(GLOBALProbabilityForEmpty,ewordclasses,fwordclasses)
{  }

void hmm::initialize_table_uniformly(sentenceHandler&){}
/*cerr << (CompareAlDeps&1) << endl; // = 1
cerr << (CompareAlDeps&2) << endl; // = 0
cerr << (CompareAlDeps&4) << endl; // =0 
cerr << (CompareAlDeps&8) << endl; // = 0
cerr << (CompareAlDeps&16) << endl; // = 0 */

int hmm::em_with_tricks(int noIterations, string& alignFile)
{
  double minErrors=1.0;int minIter=0;
  string modelName="Hmm",shortModelName="hmm";
  int dumpFreq=ModelH_Dump_Freq;
  time_t it_st, st, it_fn, fn;
  string tfile, afile,afileh, number, alignfile, test_alignfile;
  int pair_no = 0;
  bool dump_files = false ;
  st = time(NULL) ;
  sHandler1.rewind();
  cout << "\n==========================================================\n";
  cout << modelName << " Training Started at: " << ctime(&st);
  for(int it=1; it <= noIterations ; it++){
    pair_no = 0;
    srcHits_.clear();
    it_st = time(NULL) ;
    cout << endl << "-----------\n" << modelName << ": Iteration " << it << '\n';
    dump_files = (dumpFreq != 0) && ((it % dumpFreq) == 0) && !NODUMPS;
    number = "";
    int n = it;
    do{
      number.insert((size_t)0, 1, (char)(n % 10 + '0'));
    } while((n /= 10) > 0);
    tfile = Prefix + ".t" + shortModelName + "." + number ;
    afile = Prefix + ".aa" + shortModelName + "." + number ;
    afileh = Prefix + ".h" + shortModelName + "." + number ;
    alignfile = Prefix + ".A" + shortModelName + "." + number ;
    test_alignfile = Prefix + ".tst.A" + shortModelName + "." + number ;
    // batch EM: each iteration gets a new count table 
    if(step_k == 0)
      counts=HMMTables<int,WordClasses>(GLOBALProbabilityForEmpty,ewordclasses,fwordclasses);
    aCountTable.clear();
    initAL();
    em_loop(perp, sHandler1,  dump_files , alignfile.c_str(), trainViterbiPerp, false,it==1,it);
    if( errorsAL()<minErrors )
      {
	minErrors=errorsAL();
        minIter=it;
      }
    if (testPerp && testHandler)
      em_loop(*testPerp, *testHandler, dump_files, test_alignfile.c_str(), *testViterbiPerp,  true,it==1,it); 
    //if (dump_files&&OutputInAachenFormat==1)
      //tTable.printCountTable(tfile.c_str(),Elist.getVocabList(),Flist.getVocabList(),1);
    if(step_k != 0) tTable.interpolateStepCounts(); // interpolate stepcounts and full counts here
    tTable.normalizeTable(Elist, Flist, &srcHits_, it != noIterations);
    aCountTable.normalize(aTable); // IGNORE -- updates model2 alignment probs
    probs=counts;  // not needed when using online EM since counts aren't cleared 
    /*Longer note for my memory: 'probs' holds last iterations expected counts since
     * in batch EM you clear counts between iterations and counts are needed for HMM
     * network initialization. For online EM the probs only hold the last steps expected
     * counts so much more minimal effect for small step sizes. */
    cout << modelName << ": ("<<it<<") TRAIN CROSS-ENTROPY " << perp.cross_entropy()
	 << " PERPLEXITY " << perp.perplexity() << '\n';
     if (testPerp && testHandler)
       cout << modelName << ": ("<<it<<") TEST CROSS-ENTROPY " << (*testPerp).cross_entropy()
	    << " PERPLEXITY " << (*testPerp).perplexity() 
	    << '\n';
     cout << modelName << ": ("<<it<<") VITERBI TRAIN CROSS-ENTROPY " << trainViterbiPerp.cross_entropy()
	 << " PERPLEXITY " << trainViterbiPerp.perplexity() << '\n';
    if (testPerp && testHandler)
       cout << modelName << ": ("<<it<<") VITERBI TEST CROSS-ENTROPY " << testViterbiPerp->cross_entropy()
	    << " PERPLEXITY " << testViterbiPerp->perplexity() 
	    << '\n';
    if (dump_files && (!run_giza_server)) { 
      tTable.printProbTable(tfile.c_str(),Elist.getVocabList(),Flist.getVocabList(),OutputInAachenFormat);
      ofstream afilestream(afileh.c_str());
      cerr << "Printing jumps to file = " << afileh << endl;
      probs.writeJumps2(afilestream);
      afilestream.close();
      aCountTable.printTable(afile.c_str());
    }
    it_fn = time(NULL) ;
    cout << "\n" << modelName << " Iteration: " << it<< " took: " <<
      difftime(it_fn, it_st) << " seconds\n";
  } // end of iterations 
  fn = time(NULL) ;
  cout << endl << "Entire " << modelName << " Training took: " << difftime(fn, st) << " seconds\n";
  //cout << "tTable contains " << tTable.getHash().bucket_count() 
  //     << " buckets and  " << tTable.getHash().size() << " entries." ;
  cout << "==========================================================\n";
  alignFile = alignfile;
  return minIter;
}

void hmm::load_table(const char* aname){
  cerr << "Loading HMM alignments from file.\n";
  ifstream anamefile(aname);
  probs.readJumps(anamefile);
  counts = probs; // use old aligne
}

HMMNetwork *hmm::makeHMMNetwork(const Vector<WordIndex>& es,const Vector<WordIndex>&fs,bool doInit)const
{
  unsigned int i,j;
  unsigned int l = es.size() - 1;
  unsigned int m = fs.size() - 1;
  unsigned int I=2*l,J=m;
  int IJ=I*J;
  bool DependencyOfJ=(CompareAlDeps&(16|8))||(PredictionInAlignments==2);
  bool DependencyOfPrevAJ=(CompareAlDeps&(2|4))||(PredictionInAlignments==0);
  HMMNetwork *net = new HMMNetwork(I,J);
  fill(net->alphainit.begin(),net->alphainit.end(),0.0);
  fill(net->betainit.begin(),net->betainit.end(),0.0);
  for(j=1;j<=m;j++)
    {
      for(i=1;i<=l;i++) {
	net->n(i-1,j-1)=tTable.getProb(es[i], fs[j]) ;
      }
      double emptyContribution=0;  
      emptyContribution=tTable.getProb(es[0],fs[j]) ;
      for(i=1;i<=l;i++)
	net->n(i+l-1,j-1)=emptyContribution;
      net->finalMultiply*=max(normalize_if_possible_with_increment(&net->n(0,j-1),&net->n(0,j-1)+IJ,J),double(1e-12));
    }
  if( DependencyOfJ )
    net->e.resize(m-1);
  else
    net->e.resize(J>1);
  // below where the (jump,alignment,transition) counts are calculated????
  for(j=0;j<net->e.size();j++) // for each source (cols)
    {
      //int frenchClass=fwordclasses.getClass(fs[1+min(int(m)-1,int(j)+1)]);
      net->e[j].resize(I,I,0);
      for(unsigned int i1=0;i1<I;++i1) {  // l is length of source sentence
	Array<double> al(l);
	CLASSIFY2(i1,i1real);
	for(unsigned int i2=0;i2<l;i2++) { 
          //cerr << "Finding al prob here: istrich = " << i1real << " k = " << i2 << " sentLength = " << l << " J = " << m;
          //cerr << "  classes = 0 0  j+1 = " << (j+1);
          //cerr << "  int pos=istrich-k; = " << int(i1real - i2) << endl;
	  al[i2]=probs.getAlProb(i1real, i2, l, m, 0, 0, j+1);
          //cerr << al[i2] << endl;
	  //al[i2]=probs.getAlProb(i1real,i2,l,m,ewordclasses.getClass(es[1+i1real]),frenchClass,j+1);
        }
        // 22 Oct, 2009 may need to normalise with interpolation here
	normalize_if_possible(conv<double>(al.begin()),conv<double>(al.end()));
	if( SmoothHMM&2 )
	  smooth_standard(conv<double>(al.begin()),conv<double>(al.end()),HMMAlignmentModelSmoothFactor);
	for(unsigned int i2=0;i2<I;i2++) {
	  CLASSIFY(i2,empty_i2,i2real);
	  net->e[j](i1,i2) = al[i2real];
	  
	  if( empty_i2 )
	    if(i1real!=i2real)
	      {
		net->e[j](i1,i2)=0;
	      }
	    else
	      {
		net->e[j](i1,i2)=doInit?al[0]:(probs.getProbabilityForEmpty()); // make first HMM iteration like IBM-1
	      }
	}
	normalize_if_possible(&net->e[j](i1,0),&net->e[j](i1,0)+I);
      }
    }
  if( doInit )
    {
      for(unsigned int i=0;i<I;++i)  //initializes alpha start probs and beta "start" probs
	{
	  net->alphainit[i]=net->betainit[i]=(i<I/2)?1:(2.0/I);
	  net->betainit[i]=1.0;
	}
    }
  else
    {
      if( DependencyOfPrevAJ==0 )
	{
	  for(i=0;i<I;i++)
	    {
	      CLASSIFY2(i,ireal);
	      net->alphainit[i]=probs.getAlProb(-1,ireal,l,m,0,fwordclasses.getClass(fs[1+0]),0);
	    }
	}
      else
	{
	  if( UniformEntryExit&2 )probs.getBetaInit(I,net->betainit);
	  if( UniformEntryExit&1 )probs.getAlphaInit(I,net->alphainit);
	}
    }
  massert( net->alphainit.size()==I );massert( net->betainit.size()==I );
  normalize_if_possible(conv<double>(net->alphainit.begin()),conv<double>(net->alphainit.end()));
  normalize_if_possible(conv<double>(net->betainit.begin()),conv<double>(net->betainit.end()));
  transform(net->betainit.begin(),net->betainit.end(),net->betainit.begin(),bind1st(multiplies<double>(),2*l));
  return net;
}
extern float MINCOUNTINCREASE;

void hmm::em_loop(Perplexity& perp, sentenceHandler& sHandler1, 
		  bool dump_alignment, const char* alignfile, Perplexity& viterbi_perp, 
		     bool test,bool doInit,int)
{
  WordIndex i, j, l, m ;
  double cross_entropy;
  int pair_no=0 ;
  perp.clear();
  viterbi_perp.clear();
  ofstream of2;
  // for each sentence pair in the "corpus"
  if (dump_alignment||FEWDUMPS )
    of2.open(alignfile);
  sentPair sent ;
  sHandler1.rewind();
  while(sHandler1.getNextSentence(sent)){
    const Vector<WordIndex>& es = sent.get_eSent();
    const Vector<WordIndex>& fs = sent.get_fSent();
    const float so  = sent.getCount();
    if(so != 1.0) { cerr << "NOT!!!!!!!!!!\n"; exit(1);};
    l = es.size() - 1;
    m = fs.size() - 1;
    cross_entropy = log(1.0);
    Vector<WordIndex> viterbi_alignment(fs.size());

    unsigned int I=2*l,J=m; // I = 2*l bc it extends targets to include null word
    bool DependencyOfJ=(CompareAlDeps&(16|8))||(PredictionInAlignments==2);
    bool DependencyOfPrevAJ=(CompareAlDeps&(2|4))||(PredictionInAlignments==0);
    HMMNetwork *net=makeHMMNetwork(es,fs,doInit);
    Array<double> gamma;
    Array<Array2<double> > epsilon(DependencyOfJ?(m-1):1);
    double trainProb;
    trainProb=ForwardBackwardTraining(*net,gamma,epsilon);
    srcHits_.insert(es[0]);
    if( !test )
      {
	double *gp=conv<double>(gamma.begin());
	for(unsigned int i2=0;i2<J;i2++)  // for all target 
          for(unsigned int i1=0;i1<I;++i1,++gp)  // for source + nulls
            if( *gp>MINCOUNTINCREASE )
              {
                COUNT add= *gp*so;
                if( i1>=l )
                  {
                    if(step_k == 0) tTable.incCount(es[0],fs[1+i2],add);
                    else tTable.stepCounts_[wordPairIds(es[0] ,fs[1+i2])] += add; 
                    aCountTable.getRef(0,i2+1,l,m)+=add;
                  }
                else
                  {
                    if(step_k == 0) tTable.incCount(es[1+i1],fs[1+i2],add);
                    else {
                      tTable.stepCounts_[wordPairIds(es[1+i1] ,fs[1+i2])] += add; 
                      srcHits_.insert(es[1+i1]);
                    }
                    aCountTable.getRef(1+i1,1+i2,l,m)+=add;
                  }
              }
	double p0c=0.0,np0c=0.0;
	for(unsigned int jj=0;jj<epsilon.size();jj++)
	  {
	    int frenchClass=fwordclasses.getClass(fs[1+min(int(m)-1,int(jj)+1)]);
	    double *ep=epsilon[jj].begin();
	    if( ep )
	      {
		double mult=1.0;
		mult*=l;
		for(i=0;i<I;i++)
		  {
		    for(unsigned int i_bef=0;i_bef<I;i_bef++,ep++)
		      {
			CLASSIFY(i,i_empty,ireal);
			CLASSIFY2(i_bef,i_befreal);
			if( i_empty )
			  p0c+=*ep * mult;
			else
			  {
                            /*cerr << "Adding to addAlCount here: i_befreal = " << i_befreal;
                            cerr << "  ireal = " << ireal << " l = " << l << " m = " << m;
                            cerr << " eWordClass = " << ewordclasses.getClass(es[1+i_befreal]);
                            cerr << " frenchClass = " << frenchClass;
                            cerr << " jj+1 = " << (jj+1) << " value = " << (*ep * mult) << endl;*/
			    counts.addAlCount(i_befreal,ireal,l,m, 0, 0, jj+1,*ep * mult,0.0);
			    //counts.addAlCount(i_befreal,ireal,l,m,ewordclasses.getClass(es[1+i_befreal]),
			//		      frenchClass ,jj+1,*ep * mult,0.0);
			    np0c+=*ep * mult; 
			  }
			massert( &epsilon[jj](i,i_bef)== ep);
		      }
		  }
	      }
	  }
	double *gp1=conv<double>(gamma.begin()),*gp2=conv<double>(gamma.end())-I;
	Array<double>&ai=counts.doGetAlphaInit(I);
	Array<double>&bi=counts.doGetBetaInit(I);
	int firstFrenchClass=(fs.size()>1)?(fwordclasses.getClass(fs[1+0])):0;
	for(i=0;i<I;i++,gp1++,gp2++)
	  {
	    CLASSIFY(i,i_empty,ireal);
	    ai[i]+= *gp1;
	    bi[i]+= *gp2;
	    if( DependencyOfPrevAJ==0 )
	      {
		if( i_empty )
		  p0c+=*gp1;
		else
		  {
		    //counts.addAlCount(-1,ireal,l,m,0,firstFrenchClass,0,*gp1,0.0);
		    counts.addAlCount(-1,ireal,l,m,0,0,0,*gp1,0.0);
		    np0c+=*gp1;
		  }
	      }
	  }
    if( Verbose )
      cout << "l: " << l << "m: " << m << " p0c: " << p0c << " np0c: " << np0c << endl;
      }
    cross_entropy+=log(max(trainProb,1e-100))+log(max(net->finalMultiply,1e-100));
    Array<int>vit;
    double viterbi_score=1.0;
    if( (HMMTrainingSpecialFlags&1) )
      HMMViterbi(*net,gamma,vit);
    else
      viterbi_score=HMMRealViterbi(*net,vit);
    for(j=1;j<=m;j++)
      {
	viterbi_alignment[j]=vit[j-1]+1;
	if( viterbi_alignment[j]>l)
	  viterbi_alignment[j]=0;
      }
    sHandler1.setProbOfSentence(sent,cross_entropy);
    perp.addFactor(cross_entropy, so, l, m,1);
    viterbi_perp.addFactor(log(viterbi_score)+log(max(net->finalMultiply,1e-100)), so, l, m,1);
    if( Verbose )
      cout << "Viterbi-perp: " << log(viterbi_score) << ' ' << log(max(net->finalMultiply,1e-100)) << ' ' << viterbi_score << ' ' << net->finalMultiply << ' ' << *net << "gamma: " << gamma << endl;
    delete net;net=0;
    if (dump_alignment||(FEWDUMPS&&sent.getSentenceNo()<1000) )
      printAlignToFile(es, fs, Elist.getVocabList(), Flist.getVocabList(), of2, viterbi_alignment, sent.getSentenceNo(), viterbi_score);
    addAL(viterbi_alignment,sent.getSentenceNo(),l);    
    pair_no++;
  } /* of while */
  if(of2.is_open()) 
    of2.close();
  sHandler1.rewind();
  perp.record("HMM");
  viterbi_perp.record("HMM");
  errorReportAL(cout,"HMM");
}

#include "HMMTables.cpp"
template class HMMTables<int,WordClasses>;
 
