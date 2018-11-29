package dynamicProgramming;


import org.apache.log4j.Logger;

/*
 * @desc
 * @author lirb
 * @datetime 2017/10/22,12:04
 */
public class MainAlg {
    private static final Logger logger = Logger.getLogger(MainAlg.class);
    private RodCutting rodCutting;

    public void doAlg(RodCutting rodCutting){
        try{
            this.rodCutting = rodCutting;
            long startTime = System.currentTimeMillis();
            int optimalPrice = rodCutting.getOptimalPrice();
            long endTime = System.currentTimeMillis();
            System.out.println();
            logger.info("RodLenth: "+ rodCutting.getRodLength()+", Optimal Price:" + optimalPrice+"; TimeCost:"+(endTime-startTime)/1000);
        }catch (Exception e){
            logger.error(e.getMessage());
        }

    }
}
