package service.faulttree.MainTransformer;
import service.faulttree.BoolTree;
public class MainTransformerfaultBoolDay {
	
	//冷却器故障
	public int getCoolerFailure(long time,int No){
		int flag = 0;
		if (No == 1) {
			BoolTree bool1424 = new BoolTree();
			int p1 = bool1424.BooleanTreeDay(1424, time);
			BoolTree bool1427 = new BoolTree();
			int p2 = bool1427.BooleanTreeDay(1427, time);
			BoolTree bool1430 = new BoolTree();
			int p3 = bool1430.BooleanTreeDay(1430, time);
			BoolTree bool1433 = new BoolTree();
			int p4 = bool1433.BooleanTreeDay(1433, time);
			p1 = p1 + p2+p3+p4;
			if (p1 >= 1) {
				flag = 1;
			}
		}else if (No == 2) {
			BoolTree bool1463 = new BoolTree();
			int p1 = bool1463.BooleanTreeDay(1463, time);
			BoolTree bool1466 = new BoolTree();
			int p2 = bool1466.BooleanTreeDay(1466, time);
			BoolTree bool1469= new BoolTree();
			int p3 = bool1469.BooleanTreeDay(1469, time);
			BoolTree bool1472 = new BoolTree();
			int p4 = bool1472.BooleanTreeDay(1472, time);
			p1 = p1 + p2+p3+p4;
			if (p1 >= 1) {
				flag = 1;
			}
		}else if (No == 3) {
			BoolTree bool1543 = new BoolTree();
			int p1 = bool1543.BooleanTreeDay(1543, time);
			BoolTree bool1546 = new BoolTree();
			int p2 = bool1546.BooleanTreeDay(1546, time);
			BoolTree bool1549= new BoolTree();
			int p3 = bool1549.BooleanTreeDay(1549, time);
			BoolTree bool1552 = new BoolTree();
			int p4 = bool1552.BooleanTreeDay(1552, time);
			p1 = p1 + p2+p3+p4;
			if (p1 >= 1) {
				flag = 1;
			}
		}else if (No == 4) {
			BoolTree bool1503 = new BoolTree();
			int p1 = bool1503.BooleanTreeDay(1503, time);
			BoolTree bool1506 = new BoolTree();
			int p2 = bool1506.BooleanTreeDay(1506, time);
			BoolTree bool1509= new BoolTree();
			int p3 = bool1509.BooleanTreeDay(1509, time);
			BoolTree bool1512 = new BoolTree();
			int p4 = bool1512.BooleanTreeDay(1512, time);
			p1 = p1 + p2+p3+p4;
			if (p1 >= 1) {
				flag = 1;
			}
		}else {
			flag = 0;
		}
		return flag;
	}
	
	//交流电源故障
	public int getACPowerFailure(long time, int No){
		int flag = 0;
		if (No == 1) {
			BoolTree bool1441 = new BoolTree();
			int p1 = bool1441.BooleanTreeDay(1441, time);
			BoolTree bool1446= new BoolTree();
			int p2 = bool1446.BooleanTreeDay(1446, time);
			p1 = p1 + p2;
			if (p1 >= 1) {
				flag = 1;
			}
	}else if (No == 2){
		BoolTree bool1481 = new BoolTree();
		int p1 = bool1481.BooleanTreeDay(1481, time);
		BoolTree bool1486= new BoolTree();
		int p2 = bool1486.BooleanTreeDay(1486, time);
		p1 = p1 + p2;
		if (p1 >= 1) {
			flag = 1;
		}
	}else if (No == 3){
		BoolTree bool1557 = new BoolTree();
		int p1 = bool1557.BooleanTreeDay(1557, time);
		BoolTree bool1562= new BoolTree();
		int p2 = bool1562.BooleanTreeDay(1562, time);
		p1 = p1 + p2;
		if (p1 >= 1) {
			flag = 1;
		}
	}else if (No == 4){
		BoolTree bool1521 = new BoolTree();
		int p1 = bool1521.BooleanTreeDay(1521, time);
		BoolTree bool1526= new BoolTree();
		int p2 = bool1526.BooleanTreeDay(1526, time);
		p1 = p1 + p2;
		if (p1 >= 1) {
			flag = 1;
		}
	}else {
		flag = 0;
	}
	return flag;
}
	
	//冷却水泄露报警
	public int CoolingWaterLeak(long time,int No){
		int flag = 0;
		if (No == 1) {
			BoolTree bool1423 = new BoolTree();
			int p1 = bool1423.BooleanTreeDay(1423, time);
			BoolTree bool1426 = new BoolTree();
			int p2 = bool1426.BooleanTreeDay(1426, time);
			BoolTree bool1429 = new BoolTree();
			int p3 = bool1429.BooleanTreeDay(1429, time);
			BoolTree bool1432 = new BoolTree();
			int p4 = bool1432.BooleanTreeDay(1432, time);
			p1 = p1 + p2+p3+p4;
			if (p1 >= 1) {
				flag = 1;
			}
		}else if (No == 2) {
			BoolTree bool1462 = new BoolTree();
			int p1 = bool1462.BooleanTreeDay(1462, time);
			BoolTree bool1465 = new BoolTree();
			int p2 = bool1465.BooleanTreeDay(1465, time);
			BoolTree bool1468= new BoolTree();
			int p3 = bool1468.BooleanTreeDay(1468, time);
			BoolTree bool1471 = new BoolTree();
			int p4 = bool1471.BooleanTreeDay(1471, time);
			p1 = p1 + p2+p3+p4;
			if (p1 >= 1) {
				flag = 1;
			}
		}else if (No == 3) {
			BoolTree bool1542 = new BoolTree();
			int p1 = bool1542.BooleanTreeDay(1542, time);
			BoolTree bool1545 = new BoolTree();
			int p2 = bool1545.BooleanTreeDay(1545, time);
			BoolTree bool1548= new BoolTree();
			int p3 = bool1548.BooleanTreeDay(1548, time);
			BoolTree bool1551 = new BoolTree();
			int p4 = bool1551.BooleanTreeDay(1551, time);
			p1 = p1 + p2+p3+p4;
			if (p1 >= 1) {
				flag = 1;
			}
		}else if (No == 4) {
			BoolTree bool1502 = new BoolTree();
			int p1 = bool1502.BooleanTreeDay(1502, time);
			BoolTree bool1505 = new BoolTree();
			int p2 = bool1505.BooleanTreeDay(1505, time);
			BoolTree bool1508= new BoolTree();
			int p3 = bool1508.BooleanTreeDay(1508, time);
			BoolTree bool1511 = new BoolTree();
			int p4 = bool1511.BooleanTreeDay(1511, time);
			p1 = p1 + p2+p3+p4;
			if (p1 >= 1) {
				flag = 1;
			}
		}else {
			flag = 0;
		}
		return flag;
	}
	}

