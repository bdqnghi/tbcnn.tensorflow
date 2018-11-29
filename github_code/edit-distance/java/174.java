package uk.ac.manchester.dstoolkit.service.impl.morphisms.matching;

import java.util.List;
import java.util.Map;

import org.apache.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowire;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Configurable;
import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Service;

import uk.ac.manchester.dstoolkit.domain.models.canonical.CanonicalModelConstruct;
import uk.ac.manchester.dstoolkit.domain.models.morphisms.matching.Matching;
import uk.ac.manchester.dstoolkit.domain.provenance.ControlParameter;
import uk.ac.manchester.dstoolkit.domain.provenance.ControlParameterType;
import uk.ac.manchester.dstoolkit.service.morphisms.matching.MatchingProducerService;

/**
 * @author klitos
 *
 * Levenshtein distance (LD) a.k.a edit-distance is a measure of the similarity between two strings, the source string (s) 
 * and the target string (t). The distance is the number of deletions, insertions, or substitutions required to transform s into t.
 *
 * The algorithm uses dynamic programming i.e., Construct a matrix d[m][n] with sizes s.length() and t.length(). Instead of recursive calls,
 * the algorithm uses a matrix lookup which will store the smallest current cost to change a smaller i into j.
 * 
 * Complexity of algorithm: O(mn) where m and n are the sizes of the strings. 
 * 
 * The similarity of editDistance for two strings s and t is given by the formula :
 * 
 * sim(s,t) = 1 / (1 + editDistance(s,t))
 * 
 *  //TODO: send normalisation techniques as control parameters for the matchers
 *
 */

@Scope("prototype")
@Service
@Configurable(autowire = Autowire.BY_NAME)
public class LevenshteinMatcherServiceImpl extends StringBasedMatcherServiceImpl {
	
	private static Logger logger = Logger.getLogger(LevenshteinMatcherServiceImpl.class);
	
	@Autowired
	private MatchingProducerService matchingProducerService;
	
	/**
	 * Constructor
	 */
	public LevenshteinMatcherServiceImpl() {
		logger.debug("in LevenshteinMatcherServiceImpl");
		this.setName("LevenshteinMatcher");
		this.setMatcherType(MatcherType.LEVENSHTEIN);
	}//end constructor	

	
	/***
	 * 
	 * Note: Override match() from superClass (ConstructBasedMatcherServiceImpl)
	 * 
	 * The schemaServiceImpl schemaService.match() returns the final Matching after aggregate and selection
	 * 
	 * @return - a similarity matrix
	 */
	
	//this method is a hack according to my notes to be deleted soon. The method that needs to be called is float[][] match always.
	@Override
	public Matching match(CanonicalModelConstruct construct1, CanonicalModelConstruct construct2,
			Map<ControlParameterType, ControlParameter> controlParameters) {
		logger.debug("call override match in [LevenshteinMatcherServiceImpl]");
		logger.debug("construct1: " + construct1);
		logger.debug("construct2: " + construct2);
		float similarity = this.match(construct1.getName(), construct2.getName());
		logger.debug("similarity: " + similarity);
		return matchingProducerService.produceSingleMatching(similarity, construct1, construct2, controlParameters, this);
	}//end match()	
	
	/***
	 * 
	 * Note: Override match() from abstract class (StringBasedMatcherServiceImpl)
	 * 
	 * @return - a similarity matrix
	 */
	@Override
	public float[][] match(List<CanonicalModelConstruct> constructs1, List<CanonicalModelConstruct> constructs2) {
		logger.debug("in match (return float[][])");
		
		if (this.getChildMatchers() != null && this.getChildMatchers().size() > 0) {
			logger.error("This is a Primitive matcher cannot have child matchers.");
			logger.error("Levenshtein matcher has child matcher - shouldn't be the case - TODO sort this");
			return null;
		}
		
		/*Construct a similarity matrix that will hold the match similarity scores
		 *   - contructs1 (source constructs at the rows)
		 *   - contructs2 (target constructs at the columns)
		 */
		float[][] simMatrix = new float[constructs1.size()][constructs2.size()];
		logger.info("constructs1.size(): " + constructs1.size());
		logger.info("constructs2.size(): " + constructs2.size());
		/*Monitor the time to start the construction of the similarity matrix*/
		logger.info("Primitive matcher is : Levenshtein");
		long startTime = System.nanoTime();
		logger.info("start matching all constructs with StringBasedMatcher: " + startTime);
		for (CanonicalModelConstruct construct1 : constructs1) {		
			for (CanonicalModelConstruct construct2 : constructs2) {				
				logger.debug("construct1: " + construct1);
				logger.debug("construct2: " + construct2);
				logger.debug("construct1.getName: " + construct1.getName());
				logger.debug("construct2.getName: " + construct2.getName());
				long startTimeSingleMatch = System.nanoTime();
				logger.info("start matching two constructs with StringBasedMatcher: " + startTimeSingleMatch);
				//simMatrix[constructs1.indexOf(construct1)][constructs2.indexOf(construct2)] = this.match(construct1, construct2);
				simMatrix[constructs1.indexOf(construct1)][constructs2.indexOf(construct2)] = this.match(construct1.getName(), construct2.getName());
				long endTimeSingleMatch = System.nanoTime();
				logger.info("finished matching two constructs with StringBasedMatcher: " + endTimeSingleMatch);
				logger.info("duration for matching two constructs (in seconds): " + (endTimeSingleMatch - startTimeSingleMatch) / 1.0e9);
				logger.info("simMatrix[constructs1.indexOf(construct1)][constructs2.indexOf(construct2)]: "
						+ simMatrix[constructs1.indexOf(construct1)][constructs2.indexOf(construct2)]);
				logger.info("construct1.getName: " + construct1.getName());
				logger.info("construct2.getName: " + construct2.getName());
				logger.info("construct1.getName().length(): " + construct1.getName().length());
				logger.info("construct2.getName().length(): " + construct2.getName().length());
			}
		}
		long endTime = System.nanoTime();
		logger.info("constructs1.size(): " + constructs1.size());
		logger.info("constructs2.size(): " + constructs2.size());
		logger.info("finished matching all constructs with StringBasedMatcher: " + endTime);
		logger.info("duration for matching all constructs (in seconds): " + (endTime - startTime) / 1.0e9);
		return simMatrix;
	}//end match	

	/**
	 * Match two strings and obtain a sim score. This score will be stored in a
	 * similarity matrix later on.
	 * 
	 * @return float - similarity score
	 */
	@Override
	protected float match(String string1, String string2) {
		logger.debug("in match");
		logger.debug("string1: " + string1);
		logger.debug("string2: " + string2);
		
		if (this.getChildMatchers() != null && this.getChildMatchers().size() > 0) {
			logger.error("Edit-distance matcher has child matcher - shoudn't be the case - TODO sort this");
		}//end if

		/*Return 0 if strings are null*/
		if ((string1 == null) || (string2 == null) || (string1.length() == 0) || (string2.length() == 0)) {
			return 0.0F;
		}//end if
		
		/*Call method to calculate edit-distance*/
		int editDist = calcEditDistance(string1, string2);
		
		/*Normalise similarity*/
		float sim = calculateSimilarity(string1.length(), string2.length(), editDist);
		logger.debug("edit-distance is: " + editDist);
		logger.debug("sim: " + sim);
		return sim;	
	}//end match	
	
	/**
	 * The normalised Levenshtein distance given by:
	 * 
	 * 	sim = ( max(s,t) - editDis(x,y) ) / max(s,t)
	 * 
	 * @param editDistance
	 * @return - the normalised Levenshtein  
	 */
	protected float calculateSimilarity(int sourceSize, int targetSize, int editDistance) {
		logger.debug("in calculateSimilarity");
		float sim = ( Math.max(sourceSize, targetSize) - editDistance ) / (float) Math.max(sourceSize, targetSize);
		return sim;
	}//calculateSimilarity()	
	
	/**
	 * Calculate Levenshtein distance.
	 * 
	 * @param source - String
	 * @param target - String
	 * @return the edit-distance (Levenshtein distance)
	 */
	protected int calcEditDistance(String source, String target) {
		logger.debug("in calcEditDistance");
		logger.debug("source str: " + source);
		logger.debug("target str: " + target);
	    int sourceSize = source.length();
	    int targetSize = target.length();
	    int[][] matrix = new int[sourceSize+1][targetSize+1];
	    for(int i=0; i<=sourceSize; i++) {
	    	matrix[i][0] = i;
	    }
	    for(int j=0; j<=targetSize; j++) {
	       	matrix[0][j] = j;
	    }
	    for(int j=1; j<=targetSize; j++) {
	      for(int i=1; i<=sourceSize; i++) {
	        if (source.charAt(i-1) == target.charAt(j-1)) {
	        	matrix[i][j] = matrix[i-1][j-1];
	        } else {
	        	matrix[i][j] = findMin((matrix[i-1][j]+1), (matrix[i][j-1]+1), (matrix[i-1][j-1]+1));
	        }
	      }//end inner for
	    }//end for
	    return(matrix[sourceSize][targetSize]);
	}//end calcEditDistance()
	
	/***
	 * Find the minimum cost between operations (deleting, inserting, or changing)
	 */
	protected int findMin(int a, int b, int c) {
		return ( Math.min(Math.min(a,b),c) );
	}//end findMin()	
	
	
	/***
	 * Test 
	 */
	public static void main(String [] args) {
				
		//String source_construct = "MusicGroup";
		//String target_sontruct  = "Group"; 
		
		String source_construct = "SoloMusicArtist";
		String target_sontruct  = "Person";
		
		LevenshteinMatcherServiceImpl editDist = new LevenshteinMatcherServiceImpl();
		float simScore = editDist.match(source_construct, target_sontruct);
		
		logger.debug("simScore: " + simScore);
		
	}
	
	
	
}//end LevenshteinMatcherServiceImpl
