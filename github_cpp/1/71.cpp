

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
{
  log3 AsciiPrinter(Stderr)<<"Find perm called on, w" <<w << "facet normal"<<"\n";

  IntegerVectorList inequalities=cone.getHalfSpaces();
  
  int n=s.sizeOfBaseSet();
  
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
    
  
  IntegerVectorList normals=fastNormals(wallInequalities(g));

  

  
  
  IntegerVectorList empty;
  return PolyhedralCone(normals,empty,n);
  
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
  
  IntegerVectorList markedFacets;
  PolyhedralCone cone;
  Summary theSummary;
public:
  IntegerVector stableRay;
  Orbit(const PolynomialSet &g_, const SymmetryGroup &s_, PolynomialSet const *originalG_=0):
    s(s_),
    g(g_),
    
    cone(g_.getRing().getNumberOfVariables()),
    theSummary(g_),
    originalG(originalG_)
    
  {
    g.sort_();
    
    cone=coneFromMarkedBasis(g);
    stableRay=PolyhedralFan::stableRay(cone,&s);
    

    if(originalG)g=PolynomialSet(g.getRing());
  }
  const PolynomialSet representative()const
  {
    if(originalG)
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
    
    
    

    if(!(theSummary==this->theSummary))return false;
    {
      
    
      
      IntegerVector perm;
      if(findPermutationTakingVectorToCone(s,cone,w,perm,v))
	{
	  markFacet(SymmetryGroup::compose(perm,v));
	  return true;	
	}
      
    }
    
    return false;
  }
  bool permutationFixesInitialIdeal(IntegerVector const &v)
  {
    
    return SymmetryGroup::compose(v,stableRay)==stableRay;
  }
  int orbitSize()
  {
    int groupSize=s.elements.size();

    int numFixed=0;
    for(SymmetryGroup::ElementContainer::const_iterator j=s.elements.begin();j!=s.elements.end();j++)
      {
	
	if(permutationFixesInitialIdeal(*j))numFixed++;
	
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
        l.push_back(orbit); 
	
  }
  bool empty()
  {
    return theSize==0;
    
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
       
      
      Orbit &current=active.front();

      PolynomialSet g=current.representative();

      
      

      if(!targetBasis(g))break;

      
      

      
      
      IntegerVectorList normals=current.getFacets();

      

      

      for(IntegerVectorList::iterator i=normals.begin();i!=normals.end();i++)
	{
	  
	  
	  

	    
	    {
	      if(minkowski || wallContainsPositiveVector(*i))
		{
		  
		  bool found=false;
		  const IntegerVectorList &marked=current.getMarkedFacets();
		  
		  for(SymmetryGroup::ElementContainer::const_iterator j=symmetryGroup.elements.begin();j!=symmetryGroup.elements.end() &&!found;j++)
		    if(current.permutationFixesInitialIdeal(*j))
		      for(IntegerVectorList::const_iterator k=marked.begin();k!=marked.end();k++)
			if(dependent(*k,SymmetryGroup::compose(*j,*i))){
			  
			  found=true;goto terminateLoop;
			}
		terminateLoop:
		  
		  if(!found)
		    {
		      PolynomialSet neighbour=(minkowski)?flipMinkowski(g,*i):flip(g,*i);

		      
		      
		      IntegerVector w;

		      
		      
		      {
			IntegerVectorList temp;
			
			IntegerVectorList::iterator t=i;
			t++;
			temp.splice(temp.begin(),normals,i,t);
			PolyhedralCone c(normals,temp,n);
			
			normals.splice(t,temp);
			t--;
			
			i=t;
			w=c.getRelativeInteriorPoint();

		      }
		      
		      
		      


		      if(!active.containsAndMark(neighbour,w,*i))
			{
			  
			  if(minkowski)
			    active.push_back(Orbit(neighbour,symmetryGroup,&groebnerBasis));
			  else
			    active.push_back(Orbit(neighbour,symmetryGroup));
			  active.containsAndMark(neighbour,w,*i);
			}
		      
			
		      

		    }
		  else
		    {
		      
		    }
		}
	    }
	}
      
      
      

      

      numberOfVertices+=current.orbitSize();

      active.pop_front();  
      

      numberOfClosedVertices++;

      log1 fprintf(Stderr,"Number of active vertices  %i\n",active.size());
      log1 fprintf(Stderr,"Number of closed vertices: %i\n",numberOfClosedVertices);
      log1 fprintf(Stderr,"Number of vertices  %i\n",numberOfVertices);

    }

  targetEndEnumeration();
}
