// To do: The facet detection in this file may not work for non-homogeneous ideals since facets pass the test even if they do not contain a positive vector. Check if this is the case and fix the bug.

#include "breadthfirstsearch.h"

#include "buchberger.h"
#include "wallideal.h"
#include "printer.h"
#include "polyhedralcone.h"
#include "polyhedralfan.h"
#include "lp.h"
#include "log.h"

#include <iostream>

bool findPermutationTakingVectorToCone(SymmetryGroup const &s, PolyhedralCone const &cone, IntegerVector const &w, IntegerVector &perm, IntegerVector const &facetNormal)
{//Assume full dimensional
  log3 AsciiPrinter(Stderr)<<"Find perm called on, w" <<w << "facet normal"<<"\n";

  IntegerVectorList inequalities=cone.getHalfSpaces();
  //  unsigned char *table=s.getByteTable();
  int n=s.sizeOfBaseSet();
  /*  if(table)
    {
      IntegerVector w2=w;
      int tableHeight=s.getByteTableHeight();
      for(int i=0;i<tableHeight;i++)
	{
	  bool inCone=true;
	  for(int j=0;j<n;j++)w2[j]=w[table[j+n*i]];
	  for(IntegerVectorList::const_iterator k=inequalities.begin();k!=inequalities.end();k++)
	    if(dot(w2,*k)<0)
	      {
		inCone=false;
		break;
	      }
	  if(inCone)
	    {
	      perm=IntegerVector(n);
	      for(int j=0;j<n;j++)perm[j]=table[j+n*i];
	      return true;
	    }
	}
    }
    else*/
  IntegerVector relInt=cone.getRelativeInteriorPoint();
log3   AsciiPrinter(Stderr)<<"Inequalities"<<inequalities<<"\n";
  log3 AsciiPrinter(Stderr)<<"Rel int"<<relInt<<"\n";
  log3 AsciiPrinter(Stderr)<<"Omega"<<w<<"\n";
  log3 AsciiPrinter(Stderr)<<"Facet normal"<< facetNormal<<"\n";
    {
      for(SymmetryGroup::ElementContainer::const_iterator j=s.elements.begin();j!=s.elements.end();j++)
	{
	  if(dotLong(relInt,SymmetryGroup::compose(*j,facetNormal))<0)
	  if(cone.contains(SymmetryGroup::compose(*j,w)))
	    {
	      perm=*j;
	      log3 AsciiPrinter(Stderr)<<"TRUE\n";
	      return true;	
	    }
	}
    }
    log3 AsciiPrinter(Stderr)<<"FALSE\n";
  return false;
}




PolyhedralCone coneFromMarkedBasis(PolynomialSet const &g)
{
  int n=g.getRing().getNumberOfVariables();
    
  //	    log0 fprintf(Stderr,"B\n");
  IntegerVectorList normals=fastNormals(wallInequalities(g));

  //  log0 AsciiPrinter(Stderr)<<normals

  //	    log0 fprintf(Stderr,"Z\n");
  
  IntegerVectorList empty;
  return PolyhedralCone(normals,empty,n);
  //   cone.findFacets();
}

BreadthFirstSearch::BreadthFirstSearch(const SymmetryGroup &symmetryGroup_, bool minkowski_):
  numberOfVertices(0),
  numberOfEdges(0),
  symmetryGroup(symmetryGroup_),
  minkowski(minkowski_)
{
}

class Orbit{
  static list<int> computePolynomialLengths(const PolynomialSet &s)
  {
    list<int> l;
    for(PolynomialSet::const_iterator i=s.begin();i!=s.end();i++)
      l.push_back(i->numberOfTerms());
    l.sort();
    return l;
  }
public:
  class Summary{
    int numberOfPolynomials;
    list<int> polynomialLengths;
    IntegerVector sortedExponentsSum;
  public:
    Summary(PolynomialSet const &g)
    {
      polynomialLengths=computePolynomialLengths(g);
      numberOfPolynomials=g.size();
      PolynomialSet p=g.markedTermIdeal();
      sortedExponentsSum=p.exponentsSum();
      sortedExponentsSum.sort();
    }
    bool operator==(Summary const &b)const
    {
      if(b.numberOfPolynomials!=numberOfPolynomials)return false;
      if(b.sortedExponentsSum!=sortedExponentsSum)return false;

      list<int>::const_iterator i=polynomialLengths.begin();
      for(list<int>::const_iterator j=b.polynomialLengths.begin();j!=b.polynomialLengths.end();j++)
	{
	  if(*j!=*i)return false;
	  i++;
	}
      return true;
    }
  };
private:
  const SymmetryGroup &s;
  PolynomialSet const *originalG;
  PolynomialSet g;
  //  PolynomialSet initialIdeal;
  IntegerVectorList markedFacets;
  PolyhedralCone cone;
  Summary theSummary;
public:
  IntegerVector stableRay;
  Orbit(const PolynomialSet &g_, const SymmetryGroup &s_, PolynomialSet const *originalG_=0):
    s(s_),
    g(g_),
    //    initialIdeal(g_.markedTermIdeal()),
    cone(g_.getRing().getNumberOfVariables()),
    theSummary(g_),
    originalG(originalG_)
    //g(g_.markedTermIdeal())    //monomialideal
  {
    g.sort_();
    //initialIdeal.sort_();//added 27.02.2008
    cone=coneFromMarkedBasis(g);
    stableRay=PolyhedralFan::stableRay(cone,&s);
    //    log0 fprintf(Stderr,"Stable ray found\n");

    if(originalG)g=PolynomialSet(g.getRing());// Forget basis if Minkowskisum
  }
  const PolynomialSet representative()const
  {
    if(originalG)// Reconstruct basis if Minkowskisum
      {
	PolynomialSet gret=*originalG;
	WeightTermOrder T(stableRay);
	gret.markAndScale(T);
	return gret;
      }
    return g;
  }
  const IntegerVectorList &getMarkedFacets()const
  {
    return markedFacets;
  }
  IntegerVectorList getFacets()const
  {
    return cone.getHalfSpaces();
  }
  void markFacet(const IntegerVector &facet)
  {
    markedFacets.push_back(facet);
  }
  bool containsAndMark(const PolynomialSet &p_, Summary const &theSummary, IntegerVector const &w, const IntegerVector &v)
  {
    //	      log0 fprintf(stderr,"containsAndMark\n");
    //PolynomialRing theRing=p_.getRing();
    //    PolynomialSet p=p_.markedTermIdeal();

    if(!(theSummary==this->theSummary))return false;
    {
      /*      PolynomialSet &g=initialIdeal;
      // simple tests
      if(p.size()!=g.size())return false;
      
      {
	list<int> P=polynomialLengths(p);
	list<int> G=polynomialLengths(g);
	list<int>::const_iterator i=P.begin();
	for(list<int>::const_iterator j=G.begin();j!=G.end();j++)
	  {
	    if(*j!=*i)return false;
	    i++;
	  }
      }
      {
	vector<int> a;
	
	//      sort(a.begin(),a.end());
	
	IntegerVector P=p.exponentsSum();
	IntegerVector G=g.exponentsSum();
	P.sort();
	G.sort();
	if(P!=G)return false;
      }
    */
    // checking all elements
      
      IntegerVector perm;
      if(findPermutationTakingVectorToCone(s,cone,w,perm,v))
	{
	  markFacet(SymmetryGroup::compose(perm,v));
	  return true;	
	}
      /*      
      for(SymmetryGroup::ElementContainer::const_iterator j=s.elements.begin();j!=s.elements.end();j++)
	{
	  if(cone.contains(SymmetryGroup::compose(*j,w)))
	    {
	      markFacet(SymmetryGroup::compose(*j,v));
	      return true;	
	    }
	    }*/
    }
    //    log0 fprintf(stderr,"ret\n");
    return false;
  }
  bool permutationFixesInitialIdeal(IntegerVector const &v)
  {
    /*    PolynomialSet G=g.markedTermIdeal();
    G.sort_();
    
    PolynomialSet q(G.getRing());
    for(PolynomialSet::const_iterator i=G.begin();i!=G.end();i++)
      {
	q.push_back(SymmetryGroup::permutePolynomial(*i,v));
      }
    q.sort_();
    return (q==G);
    */
    return SymmetryGroup::compose(v,stableRay)==stableRay;
  }
  int orbitSize()
  {
    int groupSize=s.elements.size();

    int numFixed=0;
    for(SymmetryGroup::ElementContainer::const_iterator j=s.elements.begin();j!=s.elements.end();j++)
      {
	//	fprintf(Stderr,"1a\n");
	if(permutationFixesInitialIdeal(*j))numFixed++;
	//	fprintf(Stderr,"1b\n");
      }

    log2 fprintf(Stderr,"numFixed = %i\n",numFixed);
    return groupSize/numFixed;
  }
};

typedef list<Orbit> OrbitList;

class OrbitContainer{
public:
  int theSize;
  OrbitList l;
  OrbitContainer():
    theSize(0)
  {
  }
  void push_back(const Orbit &orbit)
  {
    theSize++;
        l.push_back(orbit); // breadth first
	//    l.push_front(orbit); // depth first
  }
  bool empty()
  {
    return theSize==0;
    //    return l.empty();
  }
  Orbit &front()
  {
    return *l.begin();
  }
  void pop_front()
  {
    l.pop_front();
    theSize--;
  }
  bool containsAndMark(const PolynomialSet &g, IntegerVector const &w, const IntegerVector &v)
  {
    Orbit::Summary theSummary(g);
    for(OrbitList::iterator i=l.begin();i!=l.end();i++)
      {
	log3 AsciiPrinter(Stderr)<<"loopin\n";
	if(i->containsAndMark(g,theSummary,w,v))return true;
      }
    return false;
  }
  void print(FILE *f)
  {
    AsciiPrinter p(f);
    p.printString("<\n");
    for(OrbitList::const_iterator i=l.begin();i!=l.end();i++)
      {
	p.printVector(i->stableRay);
	p.printPolynomialSet(i->representative());
	p.printVectorList(i->getMarkedFacets());
      }
    p.printString(">\n");
  }
  int size()
  {    
    return theSize;
  }
};


void BreadthFirstSearch::setSubspace(IntegerVectorList const &subspacePerp_)
{
  subspacePerp=subspacePerp_;
}


void BreadthFirstSearch::enumerate(const PolynomialSet &groebnerBasis)
{
  int n=groebnerBasis.getRing().getNumberOfVariables();
  int numberOfClosedVertices=0;
  int numberOfVertices=0;

  targetBeginEnumeration(groebnerBasis);


  OrbitContainer active;

  if(minkowski)
    active.push_back(Orbit(groebnerBasis,symmetryGroup,&groebnerBasis));
  else
    active.push_back(Orbit(groebnerBasis,symmetryGroup));
    
  while(!active.empty())
    {
   

      if(!subspacePerp.empty())
	{
	  IntegerVectorList inequalities=wallInequalities(active.front().representative());
	  for(IntegerVectorList::const_iterator i=subspacePerp.begin();i!=subspacePerp.end();i++)
	    inequalities.push_front(*i);
	  IntegerVector equalitySet(inequalities.size());
	  for(int i=0;i<subspacePerp.size();i++)
	    equalitySet[i]=1;
	  if(!hasInteriorPoint(inequalities,true,&equalitySet))
	    {
	      active.pop_front();
	      continue;
	    }
	}

      {
	static int n;
	n++;
	if(!(n%10))
	  log2 fprintf(Stderr,"%i\n",n);
      }
       log3  fprintf(Stderr,"Active set:\n");
       log3 active.print(Stderr);
       log3 fprintf(Stderr,"end active set\n");
       /*       fgetc(Stdin);
      */
      //      OrbitList::iterator currentIter=active.l.begin();
      Orbit &current=active.front();

      PolynomialSet g=current.representative();

      //log0 AsciiPrinter(Stderr)<<"Processing"<<g<<"\n";
      

      if(!targetBasis(g))break;

      //      IntegerVectorList normals=wallInequalities(g);
      //     normals=normalizedWithSumsAndDuplicatesRemoved(normals);

      //      AsciiPrinter(Stderr).printVectorList(normals);
      
      IntegerVectorList normals=current.getFacets();

      //      log0 fprintf(stderr,"Startloop\n");

      // log0 AsciiPrinter(Stderr)<<normals;

      for(IntegerVectorList::iterator i=normals.begin();i!=normals.end();i++)
	{
	  //log0 fprintf(stderr,"looping\n");
	  
	  //log0 AsciiPrinter(Stderr)<<"checking"<<*i<<"\n";

	    //  if(isFacet(normals,i))
	    {
	      if(minkowski || wallContainsPositiveVector(*i))
		{
		  /*		  fprintf(Stderr,"Possible flip:\n");
		  AsciiPrinter(Stderr).printVector(*i);
		  AsciiPrinter(Stderr).printPolynomialSet(flip(g,*i));
		  */
		  bool found=false;
		  const IntegerVectorList &marked=current.getMarkedFacets();
		  //log0 fprintf(stderr,"A\n");
		  for(SymmetryGroup::ElementContainer::const_iterator j=symmetryGroup.elements.begin();j!=symmetryGroup.elements.end() &&!found;j++)
		    if(current.permutationFixesInitialIdeal(*j))
		      for(IntegerVectorList::const_iterator k=marked.begin();k!=marked.end();k++)
			if(dependent(*k,SymmetryGroup::compose(*j,*i))){
			  /*  fprintf(Stderr,"Was marked with vector:");
			      AsciiPrinter(Stderr).printVector(*k);*/
			  found=true;goto terminateLoop;
			}
		terminateLoop:
		  //log0 fprintf(stderr,"B\n");
		  if(!found)
		    {
		      PolynomialSet neighbour=(minkowski)?flipMinkowski(g,*i):flip(g,*i);

		      /*fprintf(Stderr,"current:\n");
		      AsciiPrinter(Stderr).printPolynomialSet(g);
		      fprintf(Stderr,"flipped:\n");
		      AsciiPrinter(Stderr).printPolynomialSet(neighbour);
		      */
		      //log0 fprintf(Stderr,"--");
		      IntegerVector w;

		      //	  log0 fprintf(Stderr,"A\n");
		      /*		      {
			IntegerVectorList normals=wallInequalities(neighbour);
			normals=normalizedWithSumsAndDuplicatesRemoved(normals);
			IntegerVectorList empty;
			PolyhedralCone c(normals,empty,n);
			w=c.getRelativeInteriorPoint();
			}*/
		      {
			IntegerVectorList temp;
			//temp.push_back(*i);
			IntegerVectorList::iterator t=i;
			t++;
			temp.splice(temp.begin(),normals,i,t);
			PolyhedralCone c(normals,temp,n);
			/*AsciiPrinter P(Stderr);
			P.printString("::::::\n");
			P.printVectorList(normals);
			P.printVectorList(temp);
			c.print(&P);
			P.printString("::::::\n");*/
			normals.splice(t,temp);
			t--;
			//P.printVectorList(normals);
			i=t;
			w=c.getRelativeInteriorPoint();

		      }
		      //log0 fprintf(Stderr,"C\n");
		      //log0 AsciiPrinter(Stderr)<<w<<"\n";
		      //log0       active.print(Stderr);


		      if(!active.containsAndMark(neighbour,w,*i))
			{
			  //log0 fprintf(Stderr,"-------------------------adding\n");
			  if(minkowski)
			    active.push_back(Orbit(neighbour,symmetryGroup,&groebnerBasis));
			  else
			    active.push_back(Orbit(neighbour,symmetryGroup));
			  active.containsAndMark(neighbour,w,*i);
			}
		      //else
			//log0 fprintf(Stderr,"---------------------------not adding\n");
		      //log0 fprintf(Stderr,"D\n");

		    }
		  else
		    {
		      // log2 fprintf(Stderr,"-- marked\n");
		    }
		}
	    }
	}
      //      fprintf(Stderr,"New active set:\n");
      //    active.print(Stderr);
      // fprintf(Stderr,"end active set\n");

      //      log0 fprintf(Stderr,"Looping\n");

      numberOfVertices+=current.orbitSize();

      active.pop_front();  //breadth first
      //active.l.erase(currentIter); //depth first

      numberOfClosedVertices++;

      log1 fprintf(Stderr,"Number of active vertices  %i\n",active.size());
      log1 fprintf(Stderr,"Number of closed vertices: %i\n",numberOfClosedVertices);
      log1 fprintf(Stderr,"Number of vertices  %i\n",numberOfVertices);

    }

  targetEndEnumeration();
}
