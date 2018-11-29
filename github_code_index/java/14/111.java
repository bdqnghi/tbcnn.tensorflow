package service.faulttree.pumptur;

import service.faulttree.BoolTree;

public class PumpturBFaultDay {

	public int getAxleViFault(long time, int No) {
		int flag = 0;
		if (No == 1) {
			flag = 0;
		} else if (No == 2) {
			BoolTree bool441 = new BoolTree();
			int p1 = bool441.BooleanTreeDay(441, time);
			BoolTree bool442 = new BoolTree();
			int p2 = bool442.BooleanTreeDay(442, time);
			p1 = p1 + p2;
			if (p1 >= 1) {
				flag = 1;
			}
		} else if (No == 3) {
			BoolTree bool766 = new BoolTree();
			double p1 = bool766.BooleanTreeDay(766, time);
			BoolTree bool767 = new BoolTree();
			double p2 = bool767.BooleanTreeDay(767, time);
			p1 = p1 + p2;
			if (p1 >= 1) {
				flag = 1;
			}
		} else if (No == 4) {
			BoolTree bool1094 = new BoolTree();
			double p1 = bool1094.BooleanTreeDay(1094, time);
			BoolTree bool1095 = new BoolTree();
			double p2 = bool1095.BooleanTreeDay(1095, time);
			p1 = p1 + p2;
			if (p1 >= 1) {
				flag = 1;
			}
		} else {
			flag = 0;
		}
		return flag;
	}
	// 冷却水异常

	public int getCWaterFault(long time, int No) {
		int flag = 0;
		if (No == 1) {
			BoolTree bool310 = new BoolTree();
			flag = bool310.BooleanTreeDay(310, time);
		} else if (No == 2) {
			BoolTree bool637 = new BoolTree();
			flag = bool637.BooleanTreeDay(637, time);
		} else if (No == 3) {
			BoolTree bool956 = new BoolTree();
			flag = bool956.BooleanTreeDay(956, time);
		} else if (No == 4) {
			BoolTree bool1282 = new BoolTree();
			flag = bool1282.BooleanTreeDay(1282, time);
		} else {
			flag = 0;
		}
		return flag;
	}

	// 油系统异常

	public int getOilFault(long time, int No) {
		int flag = 0;
		if (No == 1) {
			BoolTree bool165 = new BoolTree();
			flag = bool165.BooleanTreeDay(165, time);
		} else if (No == 2) {
			BoolTree bool485 = new BoolTree();
			flag = bool485.BooleanTreeDay(485, time);
		} else if (No == 3) {
			BoolTree bool810 = new BoolTree();
			flag = bool810.BooleanTreeDay(810, time);
		} else if (No == 4) {
			BoolTree bool1130 = new BoolTree();
			flag = bool1130.BooleanTreeDay(1130, time);
		} else {
			flag = 0;
		}
		return flag;
	}

	// 动不平衡
	public int getUnbalance(long time, int No) {
		int flag = 0;

		if (No == 1) {
			flag = 0;
		} else if (No == 2) {
			BoolTree bool441 = new BoolTree();
			int p1 = bool441.BooleanTreeDay(441, time);
			BoolTree bool442 = new BoolTree();
			int p2 = bool442.BooleanTreeDay(442, time);
			p1 = p1 + p2;

			if (p1 > 0) {
				flag = 1;
			}
		} else if (No == 3) {
			BoolTree bool766 = new BoolTree();
			int p1 = bool766.BooleanTreeDay(766, time);
			BoolTree bool767 = new BoolTree();
			int p2 = bool767.BooleanTreeDay(767, time);
			p1 = p1 + p2;

			if (p1 > 0) {
				flag = 1;
			}
		} else if (No == 4) {
			BoolTree bool1094 = new BoolTree();
			int p1 = bool1094.BooleanTreeDay(1094, time);
			BoolTree bool1095 = new BoolTree();
			int p2 = bool1095.BooleanTreeDay(1095, time);
			p1 = p1 + p2;

			if (p1 > 0) {
				flag = 1;
			}
		} else {
			flag = 0;
		}
		return flag;
	}

	// 励磁电流不平衡

	public int getExCurrentFault(long time, int No) {
		int flag = 0;
		if (No == 1) {
			BoolTree bool284 = new BoolTree();
			flag = bool284.BooleanTreeDay(284, time);
		} else if (No == 2) {
			BoolTree bool604 = new BoolTree();
			flag = bool604.BooleanTreeDay(604, time);
		} else if (No == 3) {
			BoolTree bool929 = new BoolTree();
			flag = bool929.BooleanTreeDay(929, time);
		} else if (No == 4) {
			BoolTree bool1247 = new BoolTree();
			flag = bool1247.BooleanTreeDay(1247, time);
		} else {
			flag = 0;
		}
		return flag;
	}
	// 剪断销故障

	public int getBreakpinFault(long time, int No) {
		int flag = 0;
		
		return flag;
	}
	// 上导摆度异常

	public int getUpguideFault(long time, int No) {
		int flag = 0;
		if (No == 1) {
			BoolTree bool2180 = new BoolTree();
			flag = bool2180.BooleanTreeDay(2180, time);
		} else if (No == 2) {
			BoolTree bool331 = new BoolTree();
			double p1 = bool331.BooleanTreeDay(331, time);
			BoolTree bool332 = new BoolTree();
			double p2 = bool332.BooleanTreeDay(332, time);
			p1 = p1 + p2;
			if (p1 > 0) {
				flag = 1;
			}
		} else if (No == 3) {
			BoolTree bool656 = new BoolTree();
			double p1 = bool656.BooleanTreeDay(656, time);
			BoolTree bool657 = new BoolTree();
			double p2 = bool657.BooleanTreeDay(657, time);
			p1 = p1 + p2;
			if (p1 > 0) {
				flag = 1;
			}
		} else if (No == 4) {
			BoolTree bool977 = new BoolTree();
			double p1 = bool977.BooleanTreeDay(977, time);
			BoolTree bool978 = new BoolTree();
			double p2 = bool978.BooleanTreeDay(978, time);
			p1 = p1 + p2;
			if (p1 > 0) {
				flag = 1;
			}
		} else {
			flag = 0;
		}
		return flag;
	}

	// 下导摆度异常

	public int getLoguideFault(long time, int No) {
		int flag = 0;
		if (No == 1) {
			BoolTree bool2204 = new BoolTree();
			flag = bool2204.BooleanTreeDay(2204, time);
		} else if (No == 2) {
			BoolTree bool333 = new BoolTree();
			double p1 = bool333.BooleanTreeDay(333, time);
			BoolTree bool334 = new BoolTree();
			double p2 = bool334.BooleanTreeDay(334, time);
			p1 = p1 + p2;
			if (p1 > 0) {
				flag = 1;
			}
		} else if (No == 3) {
			BoolTree bool651 = new BoolTree();
			double p1 = bool651.BooleanTreeDay(651, time);
			BoolTree bool652 = new BoolTree();
			double p2 = bool652.BooleanTreeDay(652, time);
			p1 = p1 + p2;
			if (p1 > 0) {
				flag = 1;
			}
		} else if (No == 4) {
			BoolTree bool979 = new BoolTree();
			double p1 = bool979.BooleanTreeDay(979, time);
			BoolTree bool980 = new BoolTree();
			double p2 = bool980.BooleanTreeDay(980, time);
			p1 = p1 + p2;
			if (p1 > 0) {
				flag = 1;
			}
		} else {
			flag = 0;
		}
		return flag;
	}

	// 水导摆度异常

	public int getWguideFault(long time, int No) {
		int flag = 0;
		if (No == 1) {
			BoolTree bool2189 = new BoolTree();
			flag = bool2189.BooleanTreeDay(2189, time);
		} else if (No == 2) {
			BoolTree bool438 = new BoolTree();
			double p1 = bool438.BooleanTreeDay(438, time);
			BoolTree bool439 = new BoolTree();
			double p2 = bool439.BooleanTreeDay(439, time);
			BoolTree bool440 = new BoolTree();
			double p3 = bool440.BooleanTreeDay(440, time);
			p1 = p1 + p2 + p3;
			if (p1 > 0) {
				flag = 1;
			}
		} else if (No == 3) {
			BoolTree bool763 = new BoolTree();
			double p1 = bool763.BooleanTreeDay(763, time);
			BoolTree bool764 = new BoolTree();
			double p2 = bool764.BooleanTreeDay(764, time);
			BoolTree bool765 = new BoolTree();
			double p3 = bool765.BooleanTreeDay(765, time);
			p1 = p1 + p2 + p3;
			if (p1 > 0) {
				flag = 1;
			}
		} else if (No == 4) {
			BoolTree bool1091 = new BoolTree();
			double p1 = bool1091.BooleanTreeDay(1091, time);
			BoolTree bool1092 = new BoolTree();
			double p2 = bool1092.BooleanTreeDay(1092, time);
			BoolTree bool1093 = new BoolTree();
			double p3 = bool1093.BooleanTreeDay(1093, time);
			p1 = p1 + p2 + p3;
			if (p1 > 0) {
				flag = 1;
			}
		} else {
			flag = 0;
		}
		return flag;
	}
	// 尾水管水位过高

	public int getExWPipeFault(long time, int No) {
		int flag = 0;
		if (No == 1) {
			BoolTree bool2196 = new BoolTree();
			flag = bool2196.BooleanTreeDay(2196, time);
		} else if (No == 2) {
			BoolTree bool2318 = new BoolTree();
			flag = bool2318.BooleanTreeDay(2318, time);
		} else if (No == 3) {
			BoolTree bool2422 = new BoolTree();
			flag = bool2422.BooleanTreeDay(2422, time);
		} else if (No == 4) {
			BoolTree bool2528 = new BoolTree();
			flag = bool2528.BooleanTreeDay(2528, time);
		} else {
			flag = 0;
		}
		return flag;
	}
	// 冷却水流量低

	public int getCoolWLow(long time, int No) {
		int flag = 0;
		if (No == 1) {
			BoolTree bool2035 = new BoolTree();
			flag = bool2035.BooleanTreeDay(2035, time);
		} else if (No == 2) {
			BoolTree bool2031 = new BoolTree();
			flag = bool2031.BooleanTreeDay(2031, time);
		} else if (No == 3) {
			BoolTree bool2027 = new BoolTree();
			flag = bool2027.BooleanTreeDay(2027, time);
		} else if (No == 4) {
			BoolTree bool2022 = new BoolTree();
			flag = bool2022.BooleanTreeDay(2022, time);
		} else {
			flag = 0;
		}
		return flag;
	}
	// 轴瓦温度

	public int getBearingBushHot(long time, int No) {
		int flag = 0;
		if (No == 1) {
			BoolTree bool2198 = new BoolTree();
			double p1 = bool2198.BooleanTreeDay(2198, time);
			BoolTree bool2199 = new BoolTree();
			double p2 = bool2199.BooleanTreeDay(2199, time);
			BoolTree bool2200 = new BoolTree();
			double p3 = bool2200.BooleanTreeDay(2200, time);
			BoolTree bool2201 = new BoolTree();
			double p4 = bool2201.BooleanTreeDay(2201, time);
			p1 = p1 + p2 + p3 + p4;
			if (p1 > 0) {
				flag = 1;
			}
		} else if (No == 2) {
			BoolTree bool2320 = new BoolTree();
			double p1 = bool2320.BooleanTreeDay(2320, time);
			BoolTree bool2321 = new BoolTree();
			double p2 = bool2321.BooleanTreeDay(2321, time);
			BoolTree bool2322 = new BoolTree();
			double p3 = bool2322.BooleanTreeDay(2322, time);
			BoolTree bool2323 = new BoolTree();
			double p4 = bool2323.BooleanTreeDay(2323, time);
			p1 = p1 + p2 + p3 + p4;
			if (p1 > 0) {
				flag = 1;
			}
		} else if (No == 3) {
			BoolTree bool2424 = new BoolTree();
			double p1 = bool2424.BooleanTreeDay(2424, time);
			BoolTree bool2425 = new BoolTree();
			double p2 = bool2425.BooleanTreeDay(2425, time);
			BoolTree bool2426 = new BoolTree();
			double p3 = bool2426.BooleanTreeDay(2426, time);
			BoolTree bool2427 = new BoolTree();
			double p4 = bool2427.BooleanTreeDay(2427, time);
			p1 = p1 + p2 + p3 + p4;
			if (p1 > 0) {
				flag = 1;
			}
		} else if (No == 4) {
			BoolTree bool2530 = new BoolTree();
			double p1 = bool2530.BooleanTreeDay(2530, time);
			BoolTree bool2531 = new BoolTree();
			double p2 = bool2531.BooleanTreeDay(2531, time);
			BoolTree bool2532 = new BoolTree();
			double p3 = bool2532.BooleanTreeDay(2532, time);
			BoolTree bool2533 = new BoolTree();
			double p4 = bool2533.BooleanTreeDay(2533, time);
			p1 = p1 + p2 + p3 + p4;
			if (p1 > 0) {
				flag = 1;
			}
		} else {
			flag = 0;
		}
		return flag;
	}
	// 主轴密封

	public int getAxleSealFault(long time, int No) {
		int flag = 0;
		if (No == 1) {
			BoolTree bool118 = new BoolTree();
			double p1 = bool118.BooleanTreeDay(118, time);
			BoolTree bool119 = new BoolTree();
			double p2 = bool119.BooleanTreeDay(119, time);
			p1 = p1 + p2;
			if (p1 > 0) {
				flag = 1;
			}
		} else if (No == 2) {
			BoolTree bool433 = new BoolTree();
			double p1 = bool433.BooleanTreeDay(433, time);
			BoolTree bool434 = new BoolTree();
			double p2 = bool434.BooleanTreeDay(434, time);
			p1 = p1 + p2;
			if (p1 > 0) {
				flag = 1;
			}
		} else if (No == 3) {
			BoolTree bool758 = new BoolTree();
			double p1 = bool758.BooleanTreeDay(758, time);
			BoolTree bool759 = new BoolTree();
			double p2 = bool759.BooleanTreeDay(759, time);
			p1 = p1 + p2;
			if (p1 > 0) {
				flag = 1;
			}
		} else if (No == 4) {
			BoolTree bool1086 = new BoolTree();
			double p1 = bool1086.BooleanTreeDay(1086, time);
			BoolTree bool1087 = new BoolTree();
			double p2 = bool1087.BooleanTreeDay(1087, time);
			p1 = p1 + p2;
			if (p1 > 0) {
				flag = 1;
			}
		} else {
			flag = 0;
		}
		return flag;
	}

	// 蜗壳故障

	public int getVoluteFault(long time, int No) {
		int flag = 0;
		if (No == 1) {
			BoolTree bool170 = new BoolTree();
			flag = bool170.BooleanTreeDay(170, time);
		} else if (No == 2) {
			BoolTree bool531 = new BoolTree();
			flag = bool531.BooleanTreeDay(531, time);
		} else if (No == 3) {
			BoolTree bool815 = new BoolTree();
			flag = bool815.BooleanTreeDay(815, time);
		} else if (No == 4) {
			BoolTree bool1135 = new BoolTree();
			flag = bool1135.BooleanTreeDay(1135, time);
		} else {
			flag = 0;
		}
		return flag;
	}
}
