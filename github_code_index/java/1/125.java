package edu.iscas.expdroid.strategy;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

import edu.iscas.expdroid.model.TEdge;
import edu.iscas.expdroid.model.TEdge.EdgeType;
import edu.iscas.expdroid.model.TEvent;
import edu.iscas.expdroid.model.TState;
import edu.iscas.expdroid.tools.Config;
import edu.iscas.expdroid.tools.Statistic;
import edu.iscas.expdroid.utils.UtilE;

public class BFS extends StrategyImpl{
    public Queue<TState> stateQueue;
    
	@Override
	public void startExp() {
		// TODO Auto-generated method stub
		//do manual
		if(Config.g().doManualExp){
			 Strategy manual=new Manual();
			 manual.startExp();
	         //copyGraphInfo(manual);
		}
		
		//do BFS
	    if(null==curState){  //no explore has been done before
	    	//start initial activity
	    	startLauchActivity();
	    	initialGraph();
	    	cmd.takeScreenshot("0");
	    	stateQueue=new LinkedList<TState>();
	    }
	    while(true){
	    	if(isFinishedExp(curState)){
	    	     if(null!=stateQueue&&stateQueue.isEmpty()){
	    	    	 //Notify  statistic Thread
	    	    	  Statistic.end();
	    	    	 break;
	    	     }else{
	    	    	 curState=stateQueue.poll();
	    	    	 goTargetState(curState);
	    	     }
	    	}
	    	System.out.println("exit flag="+Statistic.expExit);
	    	if(Statistic.expExit) {
	    		Statistic.end();
	    		break;
	    	}
	    	
	    	TEvent event=ehelper.selectBFSEvent(curState);
	    	if(null!=event){
	    	   eventSerial.add(event);
	    	   boolean r=ehelper.executeEvent(event);
	    	   if(r) {
	    		  // eventSerial.add(event);
	    		   extendGraph(event);
	    	   }else {
	    		   eventSerial.remove(eventSerial.size()-1);
	    		   System.out.println("trigger event fail! event:"+event);
	    	   }
	    	}else {
	    		System.out.println("select event fail in state "+curState);
	    	}
	    	System.out.println("exit flag="+Statistic.expExit);
	    	if(Statistic.expExit){
	    		Statistic.end();
	    		break;
	    	}
	    }
	    
	}


	@Override
	protected void extendGraph(TEvent event) {
		// TODO Auto-generated method stub
		TState cState=ehelper.getCurState();
		 if(isLastState(cState)){
			 System.out.println("old state");
			// eventSerial.add(event);
		 }else{
		   if(isNewState(cState)){
			 System.out.println("new  state");
			 cState.No=stateGraph.allState.size();
			 cState.preTrace.addAll(new ArrayList<TEvent>(curState.preTrace));
			 cState.preTrace.addAll(new ArrayList<TEvent>(eventSerial));
			 stateGraph.allState.add(cState);
			 TEdge edge=new TEdge(EdgeType.auto,cState,new ArrayList<TEvent>(eventSerial));
			 curState.edges.add(edge);
			 //collect state of activityInfo later
			 
			 //save screenshot
			 cmd.takeScreenshot(cState.No+"");
			 //add new state to queue
			 if(isInPackage(cState)) {//checke new State is in tested package
		         System.out.println("in Package");
				 stateQueue.offer(cState);
			 }else{
				 System.out.println("out Package");
			 }
			 
		   }else{  //state has been before 
			   TState ccState=searchState(stateGraph,cState);
			   if(ccState==null) return ;
			   TEdge edge=new TEdge(EdgeType.auto,ccState,new ArrayList<TEvent>(eventSerial));
			   curState.edges.add(edge);
		   }
		   eventSerial.clear();
		   goTargetState(curState);
		} 
	}
	
	private boolean isFinishedExp(TState state){
	     if(state==null) return true;
	     boolean result=state.events.size()==state.eventExpCount.size();
	     return result;
	}

	
}
