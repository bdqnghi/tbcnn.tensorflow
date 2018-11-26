public class FordFulkerson {
	FlowNetwork network;		/** Represents the FlowNetwork problem. */
	Search searchMethod; /** Search method. */
	
	// construct instance to compute maximum flow accross given
	// network using given search method to find augmenting path.
	public ForFulkerson (FlowNetwork network, Search method) {
		this.network = network;
		this.searchMethod = method;
		}
	// Compute maximal flow for the flow network. rESULTS OF THE
	// computation are stored within the flow network object.
	public boolean compute (){
		boolean augmented = false;
		while (searchMethod.findAugmentingPath(network.vertices)) {
			processPath(network.vertices);
			augmented = true;
			}
			return augmented;
			}
			
			// Find edge in augmenting path with lowest potential to be increased
			// and augment flows qwithin path from source to sink by that amount.
			protected void processPath(VertexInfo []vertices) {
				int v = network.sinkIndex;
				int delta = Integer.MAX_VALUE;	//goal is to find smallest
				while (v!= network.sourceIndex) {
					int u = vertices[v].previous;
					int flow;
					if (vertices[v].forward) {
						//Forward edges can be adjusted by remaing capcaity on edge
						flow = network.edge(v,u).flow;
					}
					if (flow < delta) { delta = flow; } // smaller candiate flow
					v = u; // folow reverse path to source
				}
				
				// Adjust path (forward is added , backward is reduced) with delta.
				v = network.sinkIndex;
				while (v != network.sourceIndex) {
					int u = vertices[v].previous;
					if (vertices[v].forward) {
						network.edge(u,v).flow += delta;
						} else {
						network.edge(v,u).flow -= delta;
						}
						v=u; // follow reverse path to sourc
					}
					Arrays.fill(network.vertices, null); //reset for next iteration
					}
				}
				
					