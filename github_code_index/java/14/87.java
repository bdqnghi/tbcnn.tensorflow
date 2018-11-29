package service.faulttree.MainTransformer;
import service.faulttree.BoolTree;
public class MainTransformerfaultBool {
	
	//冷却器故障
	public double getCoolerFailure(long time,int No){
		if(No == 1){
			BoolTree bool1424 = new BoolTree();
			double p1 = bool1424.BooleanTree(1424, time);
			BoolTree bool1427= new BoolTree();
			double p2 = bool1427.BooleanTree(1427, time);
			BoolTree bool1430 = new BoolTree();
			double p3 = bool1430.BooleanTree(1430, time);
			BoolTree bool1433 = new BoolTree();
			double p4 = bool1433.BooleanTree(1433, time);
			p1 = p1 + p2+p3+p4;
			if (p1 > 1) {
				p1 = 0.99;
			}
			return p1;
		}else if (No == 2){
			BoolTree bool1463 = new BoolTree();
			double p1 = bool1463.BooleanTree(1463, time);
			BoolTree bool1466= new BoolTree();
			double p2 = bool1466.BooleanTree(1466, time);
			BoolTree bool1469 = new BoolTree();
			double p3 = bool1469.BooleanTree(1469, time);
			BoolTree bool1472= new BoolTree();
			double p4 = bool1472.BooleanTree(1472, time);
			p1 = p1 + p2+p3+p4;
			if (p1 > 1) {
				p1 = 0.99;
			}
			return p1;
	}else if (No == 3){
		BoolTree bool1543 = new BoolTree();
		double p1 = bool1543.BooleanTree(1543, time);
		BoolTree bool1546= new BoolTree();
		double p2 = bool1546.BooleanTree(1546, time);
		BoolTree bool1549 = new BoolTree();
		double p3 = bool1549.BooleanTree(1549, time);
		BoolTree bool1552= new BoolTree();
		double p4 = bool1552.BooleanTree(1552, time);
		p1 = p1 + p2+p3+p4;
		if (p1 > 1) {
			p1 = 0.99;
		}
		return p1;
	}else if (No == 4){
		BoolTree bool1503 = new BoolTree();
		double p1 = bool1503.BooleanTree(1503, time);
		BoolTree bool1506= new BoolTree();
		double p2 = bool1506.BooleanTree(1506, time);
		BoolTree bool1509 = new BoolTree();
		double p3 = bool1509.BooleanTree(1509, time);
		BoolTree bool1512= new BoolTree();
		double p4 = bool1512.BooleanTree(1512, time);
		p1 = p1 + p2+p3+p4;
		if (p1 > 1) {
			p1 = 0.99;
		}
		return p1;
	}else {
		double p1 = 0;
		return p1;
	}
	}
	
	//交流电源故障
	public double getACPowerFailure(long time,int No){
		if (No == 1) {
		    BoolTree bool1441= new BoolTree();
			double p1 = bool1441.BooleanTree(1441, time);
			BoolTree bool1446 = new BoolTree();
			double p2 = bool1446.BooleanTree(1446, time);
			p1 = p1 + p2;
			if (p1 > 1) {
				p1 = 0.99;
			}
			return p1;
		} else if(No == 2){
			BoolTree bool1481= new BoolTree();
			double p1 = bool1481.BooleanTree(1481, time);
			BoolTree bool1486 = new BoolTree();
			double p2 = bool1486.BooleanTree(1486, time);
			p1 = p1 + p2;
			if (p1 > 1) {
				p1 = 0.99;
			}
			return p1;
		}else if(No == 3){
			BoolTree bool1557= new BoolTree();
			double p1 = bool1557.BooleanTree(1557, time);
			BoolTree bool1562 = new BoolTree();
			double p2 = bool1562.BooleanTree(1562, time);
			p1 = p1 + p2;
			if (p1 > 1) {
				p1 = 0.99;
			}
			return p1;
		}else if(No == 4){
			BoolTree bool1521= new BoolTree();
			double p1 = bool1521.BooleanTree(1521, time);
			BoolTree bool1526 = new BoolTree();
			double p2 = bool1526.BooleanTree(1526, time);
			p1 = p1 + p2;
			if (p1 > 1) {
				p1 = 0.99;
			}
			return p1;
		}else {
			double p1 = 0;
			return p1;
		}
	}
	
	//冷却水泄露报警
	public double CoolingWaterLeak(long time,int No){
		if(No == 1){
			BoolTree bool1423 = new BoolTree();
			double p1 = bool1423.BooleanTree(1423, time);
			BoolTree bool1426= new BoolTree();
			double p2 = bool1426.BooleanTree(1426, time);
			BoolTree bool1429 = new BoolTree();
			double p3 = bool1429.BooleanTree(1429, time);
			BoolTree bool1432 = new BoolTree();
			double p4 = bool1432.BooleanTree(1432, time);
			p1 = p1 + p2+p3+p4;
			if (p1 > 1) {
				p1 = 0.99;
			}
			return p1;
		}else if (No == 2){
			BoolTree bool1462 = new BoolTree();
			double p1 = bool1462.BooleanTree(1462, time);
			BoolTree bool1465= new BoolTree();
			double p2 = bool1465.BooleanTree(1465, time);
			BoolTree bool1468 = new BoolTree();
			double p3 = bool1468.BooleanTree(1468, time);
			BoolTree bool1471= new BoolTree();
			double p4 = bool1471.BooleanTree(1471, time);
			p1 = p1 + p2+p3+p4;
			if (p1 > 1) {
				p1 = 0.99;
			}
			return p1;
	}else if (No == 3){
		BoolTree bool1542 = new BoolTree();
		double p1 = bool1542.BooleanTree(1542, time);
		BoolTree bool1545= new BoolTree();
		double p2 = bool1545.BooleanTree(1545, time);
		BoolTree bool1548 = new BoolTree();
		double p3 = bool1548.BooleanTree(1548, time);
		BoolTree bool1551= new BoolTree();
		double p4 = bool1551.BooleanTree(1551, time);
		p1 = p1 + p2+p3+p4;
		if (p1 > 1) {
			p1 = 0.99;
		}
		return p1;
	}else if (No == 4){
		BoolTree bool1502 = new BoolTree();
		double p1 = bool1502.BooleanTree(1502, time);
		BoolTree bool1505= new BoolTree();
		double p2 = bool1505.BooleanTree(1505, time);
		BoolTree bool1508 = new BoolTree();
		double p3 = bool1508.BooleanTree(1508, time);
		BoolTree bool1511= new BoolTree();
		double p4 = bool1511.BooleanTree(1511, time);
		p1 = p1 + p2+p3+p4;
		if (p1 > 1) {
			p1 = 0.99;
		}
		return p1;
	}else {
		double p1 = 0;
		return p1;
	}
	}
	
}
