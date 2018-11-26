package simsim.graphs;

import java.util.* ;

/**
 * @author  Sérgio Duarte (smd@di.fct.unl.pt)
 *
 * Computes a minimum spanning tree for a graph.
 * @param <T>
 */
public class MinimumSpanningTree<T> extends SpanningTree<T> {
        
    /**
     * @param nc - Collection of nodes of the graph.
     * @param ec - Collection of edges of the graph.
     */
    public MinimumSpanningTree( Collection<T> nc, Collection<Link<T>> ec ) {
        super( new ArrayList<T>(nc), new ArrayList<Link<T>>()) ;
        calcTree( nc, ec ) ;
    }
    
    //-------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------
    private void calcTree( Collection<T> nc, Collection<Link<T>> ne ) {
        
        TreeSet<Link<T>> sortedLinks = new TreeSet<Link<T>>( ne ) ;
         
        Hashtable<T, Link<T>> reps = new Hashtable<T, Link<T>>() ;

        int L = nc.size() ;
        for( Link<T> i : sortedLinks )
        	if( L >= 0 && belongsToMst( reps, i ) )
        		links.add(i) ;
    }
    
    private boolean belongsToMst( Hashtable<T, Link<T>> reps, Link<T> l ) {
       Link<T> repV = reps.get( l.v ) ;
        Link<T> repW = reps.get( l.w ) ;
        if( repV == null && repW == null ) {
            reps.put( l.v, l ) ;
            reps.put( l.w, l ) ;
            return true ;
        }
        if( repV == null && repW != null ) {
            reps.put( l.v, repW ) ;
            return true ;
        }
        if( repV != null && repW == null ) {
            reps.put( l.w, repV ) ;
            return true ;
        }
        if( repV.equals( repW ) ) return false ;
        replaceReps( reps, repV, repW ) ;
        return true ;
    }
    
    private void replaceReps( Hashtable<T, Link<T>> reps, Link<T> rS, Link<T> rD ) {
    	for( Map.Entry<T, Link<T>> i : reps.entrySet() )
    		if( i.getValue().equals(rD) )
    			i.setValue(rS ) ;
    }
}
