package Project3.Part2;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

import Project3.CityData;
import Project3.CityInfo;
import Project3.CostEdge;
import java.util.PriorityQueue;

/**
 * CS6423 Algorithmic Processes Summer 2014 Project 3: MinimumSpanningTree -
 * prints the minimum spanning tree starting in each city Daniel Kerr and
 * Charles So Date: 08/01/2014 File: MinimumSpanningTree.java
 */
public class MinimumSpanningTree {

	private CityInfo[] cityInfo;
	private float[][] costMatrix;

	/**
	 * This is where the edge costs are computed. It will compute the round trip
	 * cost and assign that for an edge. If there is not a round trip (IE edge
	 * from A to B, but no edge from B to A, then it will set the cost to be the
	 * lone AB edge
	 * 
	 * @param edgeList List of Edges
	 * @param startCity Where the starting city is
	 * @param cityInfo All the city in the list
	 */
	public void openCity(PriorityQueue<CostEdge> edgeList, CityInfo startCity,
			CityInfo[] cityInfo) {
		for (CityInfo connectedCity : cityInfo) {
			int startIndex = CityInfo.CitySet.getCityOrdinal(startCity.getCityName());
			int endIndex = CityInfo.CitySet.getCityOrdinal(connectedCity.getCityName());
			if (startIndex != endIndex
					&& (costMatrix[startIndex][endIndex] >= 0 
					|| costMatrix[endIndex][startIndex] >= 0)) {
				CostEdge newEdge = new CostEdge();
				newEdge.setStartCity(startCity);
				newEdge.setEndCity(connectedCity);
				float initialCost = 0;
				if (costMatrix[startIndex][endIndex] > -1) {
					initialCost += costMatrix[startIndex][endIndex];
				}
				float returnCost = 0;
				if (costMatrix[endIndex][startIndex] > -1) {
					returnCost += costMatrix[endIndex][startIndex];
				}
				newEdge.setCost(initialCost + returnCost);
				edgeList.add(newEdge);
			}
		}
	}

	/**
	 * A Prim like implementation
	 * 
	 */
	public MinimumSpanningTree() {
		CityData newCityData = new CityData("routes.txt");

		cityInfo = newCityData.getListOfCities();
		costMatrix = newCityData.getMatrixTravel().getTravelMatrix();

		System.out.println("We chose to treat the case of a city connected to another "
						+ "city, but with no return connection as having a return connection"
						+ "\n of cost 0.");
		for (CityInfo curCity : cityInfo) {
			// Let's traverse the cities and add items
			String startCity = curCity.getCityName();
			int startCityCount = CityInfo.CitySet.getCityOrdinal(startCity);
			CostComparator costComparator = new CostComparator();

			PriorityQueue<CostEdge> possibleEdges = new PriorityQueue<CostEdge>(
					newCityData.getListOfCities().length, costComparator);
			ArrayList<Integer> cityAddedIn = new ArrayList<Integer>();
			ArrayList<CostEdge> minimumTreeList = new ArrayList<CostEdge>();

			cityAddedIn.add(startCityCount);
			openCity(possibleEdges, curCity, cityInfo);

			// repeat until all cities are part of the tree
			while (cityAddedIn.size() < cityInfo.length) {
				float minimum = Long.MAX_VALUE;
				int minimumCity = -1;

				// get the current least cost edge from the set of
				// cities that are currently part of the solution
				// tree
				CostEdge minimumEdge = possibleEdges.poll();
				// Only add if the end city is not already part of the solution tree
				if (minimumEdge != null
						&& !cityAddedIn.contains(
								CityInfo.CitySet.getCityOrdinal(
										minimumEdge.getEndCity().getCityName()))) {
					minimumTreeList.add(minimumEdge);
					int endCityCount = CityInfo.CitySet.getCityOrdinal(
							minimumEdge.getEndCity().getCityCode());
					cityAddedIn.add(endCityCount);
					openCity(possibleEdges, minimumEdge.getEndCity(), cityInfo);
				}
			}

			System.out.println("Printing minimum cost spanning tree from "
					+ curCity.getCityName());

			float totalCost = 0.0f;
			for (CostEdge curCostEdge : minimumTreeList) {
				System.out.println(curCostEdge.toString());
				totalCost += curCostEdge.getCost();
			}

			System.out.println("Total cost: " + totalCost);
			System.out.println("===== End of the tree =====");
		}
	}

	public static void main(String[] args) {
		MinimumSpanningTree testTree = new MinimumSpanningTree();
	}

}
