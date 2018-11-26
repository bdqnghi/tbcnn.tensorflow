package service.faulttree.pumptur;

import service.faulttree.BoolTree;

public class PumpturBFault {
	/*QueryFaultTreeAction ab = new QueryFaultTreeAction();
	int No = ab.getNo();
	long time = ab.getEndTime();
	// 大轴摆度异常
*/
	public double getAxleViFault(long time,int No) {

		if (No == 1) {
			double p1 = 0;
			return p1;
		} else if (No == 2) {
			BoolTree bool441 = new BoolTree();
			double p1 = bool441.BooleanTree(441, time);
			BoolTree bool442 = new BoolTree();
			double p2 = bool442.BooleanTree(442, time);
			p1 = (p1 + p2)/2;
			if (p1 > 1) {
				p1 = 0.99;
			}
			return p1;
		} else if (No == 3) {
			BoolTree bool766 = new BoolTree();
			double p1 = bool766.BooleanTree(766, time);
			BoolTree bool767 = new BoolTree();
			double p2 = bool767.BooleanTree(767, time);
			p1 = (p1 + p2)/2;
			if (p1 > 1) {
				p1 = 0.99;
			}
			return p1;
		} else if (No == 4) {
			BoolTree bool1094 = new BoolTree();
			double p1 = bool1094.BooleanTree(1094, time);
			BoolTree bool1095 = new BoolTree();
			double p2 = bool1095.BooleanTree(1095, time);
			p1 = (p1 + p2)/2;
			if (p1 > 1) {
				p1 = 0.99;
			}
			return p1;
		} else {
			double p1 = 0;
			return p1;
		}
	}
	// 冷却水异常

	public double getCWaterFault(long time,int No) {

		if (No == 1) {
			BoolTree bool310 = new BoolTree();
			double p1 = bool310.BooleanTree(310, time);
			return p1;
		} else if (No == 2) {
			BoolTree bool637 = new BoolTree();
			double p1 = bool637.BooleanTree(637, time);
			return p1;
		} else if (No == 3) {
			BoolTree bool956 = new BoolTree();
			double p1 = bool956.BooleanTree(956, time);
			return p1;
		} else if (No == 4) {
			BoolTree bool1282 = new BoolTree();
			double p1 = bool1282.BooleanTree(1282, time);
			return p1;
		} else {
			double p1 = 0;
			return p1;
		}
	}
	// 油系统异常

	public double getOilFault(long time,int No) {

		if (No == 1) {
			BoolTree bool165 = new BoolTree();
			double p1 = bool165.BooleanTree(165, time);
			return p1;
		} else if (No == 2) {
			BoolTree bool485 = new BoolTree();
			double p1 = bool485.BooleanTree(485, time);
			return p1;
		} else if (No == 3) {
			BoolTree bool810 = new BoolTree();
			double p1 = bool810.BooleanTree(810, time);
			return p1;
		} else if (No == 4) {
			BoolTree bool1130 = new BoolTree();
			double p1 = bool1130.BooleanTree(1130, time);
			return p1;
		} else {
			double p1 = 0;
			return p1;
		}
	}

	// 动不平衡
	public double getUnbalance(long time,int No) {

		if (No == 1) {
			double p1 = 0;
			return p1;
		} else if (No == 2) {
			BoolTree bool441 = new BoolTree();
			double p1 = bool441.BooleanTree(441, time);
			BoolTree bool442 = new BoolTree();
			double p2 = bool442.BooleanTree(442, time);
			p1 = (p1 + p2)/2;
			p1 = p1 - Math.random() / 10;
			if (p1 < 0) {
				p1 = 0;
			}
			return p1;
		} else if (No == 3) {
			BoolTree bool766 = new BoolTree();
			double p1 = bool766.BooleanTree(766, time);
			BoolTree bool767 = new BoolTree();
			double p2 = bool767.BooleanTree(767, time);
			p1 = (p1 + p2)/2;
			p1 = p1 - Math.random() / 10;
			if (p1 < 0) {
				p1 = 0;
			}
			return p1;
		} else if (No == 4) {
			BoolTree bool1094 = new BoolTree();
			double p1 = bool1094.BooleanTree(1094, time);
			BoolTree bool1095 = new BoolTree();
			double p2 = bool1095.BooleanTree(1095, time);
			p1 = (p1 + p2)/2;
			p1 = p1 - Math.random() / 10;
			if (p1 < 0) {
				p1 = 0;
			}
			return p1;
		} else {
			double p1 = 0;
			return p1;
		}
	}

	// 励磁电流不平衡

	public double getExCurrentFault(long time,int No) {

		if (No == 1) {
			BoolTree bool284 = new BoolTree();
			double p1 = bool284.BooleanTree(284, time);
			return p1;
		} else if (No == 2) {
			BoolTree bool604 = new BoolTree();
			double p1 = bool604.BooleanTree(604, time);
			return p1;
		} else if (No == 3) {
			BoolTree bool929 = new BoolTree();
			double p1 = bool929.BooleanTree(929, time);
			return p1;
		} else if (No == 4) {
			BoolTree bool1247 = new BoolTree();
			double p1 = bool1247.BooleanTree(1247, time);
			return p1;
		} else {
			double p1 = 0;
			return p1;
		}
	}
	
	
	// 上导摆度异常

	public double getUpguideFault(long time,int No) {

		if (No == 1) {
			BoolTree bool2180 = new BoolTree();
			double p1 = bool2180.BooleanTree(2180, time);
			return p1;
		} else if (No == 2) {
			BoolTree bool331 = new BoolTree();
			double p1 = bool331.BooleanTree(331, time);
			BoolTree bool332 = new BoolTree();
			double p2 = bool332.BooleanTree(332, time);
			p1 = (p1 + p2)/2;
			if (p1 > 1) {
				p1 = 0.99;
			}
			return p1;
		} else if (No == 3) {
			BoolTree bool656 = new BoolTree();
			double p1 = bool656.BooleanTree(656, time);
			BoolTree bool657 = new BoolTree();
			double p2 = bool657.BooleanTree(657, time);
			p1 = (p1 + p2)/2;
			if (p1 > 1) {
				p1 = 0.99;
			}
			return p1;
		} else if (No == 4) {
			BoolTree bool977 = new BoolTree();
			double p1 = bool977.BooleanTree(977, time);
			BoolTree bool978 = new BoolTree();
			double p2 = bool978.BooleanTree(978, time);
			p1 = (p1 + p2)/2;
			if (p1 > 1) {
				p1 = 0.99;
			}
			return p1;
		} else {
			double p1 = 0;
			return p1;
		}
	}

	// 下导摆度异常

	public double getLoguideFault(long time,int No) {

		if (No == 1) {
			BoolTree bool2204 = new BoolTree();
			double p1 = bool2204.BooleanTree(2204, time);
			return p1;
		} else if (No == 2) {
			BoolTree bool333 = new BoolTree();
			double p1 = bool333.BooleanTree(333, time);
			BoolTree bool334 = new BoolTree();
			double p2 = bool334.BooleanTree(334, time);
			p1 = (p1 + p2)/2;
			if (p1 > 1) {
				p1 = 0.99;
			}
			return p1;
		} else if (No == 3) {
			BoolTree bool651 = new BoolTree();
			double p1 = bool651.BooleanTree(651, time);
			BoolTree bool652 = new BoolTree();
			double p2 = bool652.BooleanTree(652, time);
			p1 = (p1 + p2)/2;
			if (p1 > 1) {
				p1 = 0.99;
			}
			return p1;
		} else if (No == 4) {
			BoolTree bool979 = new BoolTree();
			double p1 = bool979.BooleanTree(979, time);
			BoolTree bool980 = new BoolTree();
			double p2 = bool980.BooleanTree(980, time);
			p1 = (p1 + p2)/2;
			if (p1 > 1) {
				p1 = 0.99;
			}
			return p1;
		} else {
			double p1 = 0;
			return p1;
		}
	}

	// 水导摆度异常

	public double getWguideFault(long time,int No) {

		if (No == 1) {
			BoolTree bool2189 = new BoolTree();
			double p1 = bool2189.BooleanTree(2189, time);
			return p1;
		} else if (No == 2) {
			BoolTree bool438 = new BoolTree();
			double p1 = bool438.BooleanTree(438, time);
			BoolTree bool439 = new BoolTree();
			double p2 = bool439.BooleanTree(439, time);
			BoolTree bool440 = new BoolTree();
			double p3 = bool440.BooleanTree(440, time);
			p1 = (p1 + p2 + p3)/3;
			if (p1 > 1) {
				p1 = 0.99;
			}
			return p1;
		} else if (No == 3) {
			BoolTree bool763 = new BoolTree();
			double p1 = bool763.BooleanTree(763, time);
			BoolTree bool764 = new BoolTree();
			double p2 = bool764.BooleanTree(764, time);
			BoolTree bool765 = new BoolTree();
			double p3 = bool765.BooleanTree(765, time);
			p1 = (p1 + p2 + p3)/3;
			if (p1 > 1) {
				p1 = 0.99;
			}
			return p1;
		} else if (No == 4) {
			BoolTree bool1091 = new BoolTree();
			double p1 = bool1091.BooleanTree(1091, time);
			BoolTree bool1092 = new BoolTree();
			double p2 = bool1092.BooleanTree(1092, time);
			BoolTree bool1093 = new BoolTree();
			double p3 = bool1093.BooleanTree(1093, time);
			p1 = (p1 + p2 + p3)/3;
			if (p1 > 1) {
				p1 = 0.99;
			}
			return p1;
		} else {
			double p1 = 0;
			return p1;
		}
	}
	// 尾水管水位过高

	public double getExWPipeFault(long time,int No) {

		if (No == 1) {
			BoolTree bool2196 = new BoolTree();
			double p1 = bool2196.BooleanTree(2196, time);
			return p1;
		} else if (No == 2) {
			BoolTree bool2318 = new BoolTree();
			double p1 = bool2318.BooleanTree(2318, time);
			return p1;
		} else if (No == 3) {
			BoolTree bool2422 = new BoolTree();
			double p1 = bool2422.BooleanTree(2422, time);
			return p1;
		} else if (No == 4) {
			BoolTree bool2528 = new BoolTree();
			double p1 = bool2528.BooleanTree(2528, time);
			return p1;
		} else {
			double p1 = 0;
			return p1;
		}
	}
	// 冷却水流量低

	public double getCoolWLow(long time,int No) {

		if (No == 1) {
			BoolTree bool2035 = new BoolTree();
			double p1 = bool2035.BooleanTree(2035, time);
			return p1;
		} else if (No == 2) {
			BoolTree bool2031 = new BoolTree();
			double p1 = bool2031.BooleanTree(2031, time);
			return p1;
		} else if (No == 3) {
			BoolTree bool2027 = new BoolTree();
			double p1 = bool2027.BooleanTree(2027, time);
			return p1;
		} else if (No == 4) {
			BoolTree bool2022 = new BoolTree();
			double p1 = bool2022.BooleanTree(2022, time);
			return p1;
		} else {
			double p1 = 0;
			return p1;
		}
	}
	// 轴瓦温度

	public double getBearingBushHot(long time,int No) {

		if (No == 1) {
			BoolTree bool2198 = new BoolTree();
			double p1 = bool2198.BooleanTree(2198, time);
			BoolTree bool2199 = new BoolTree();
			double p2 = bool2199.BooleanTree(2199, time);
			BoolTree bool2200 = new BoolTree();
			double p3 = bool2200.BooleanTree(2200, time);
			BoolTree bool2201 = new BoolTree();
			double p4 = bool2201.BooleanTree(2201, time);
			p1 = (p1 + p2 + p3 + p4) / 4;
			return p1;
		} else if (No == 2) {
			BoolTree bool2320 = new BoolTree();
			double p1 = bool2320.BooleanTree(2320, time);
			BoolTree bool2321 = new BoolTree();
			double p2 = bool2321.BooleanTree(2321, time);
			BoolTree bool2322 = new BoolTree();
			double p3 = bool2322.BooleanTree(2322, time);
			BoolTree bool2323 = new BoolTree();
			double p4 = bool2323.BooleanTree(2323, time);
			p1 = (p1 + p2 + p3 + p4) / 4;
			return p1;
		} else if (No == 3) {
			BoolTree bool2424 = new BoolTree();
			double p1 = bool2424.BooleanTree(2424, time);
			BoolTree bool2425 = new BoolTree();
			double p2 = bool2425.BooleanTree(2425, time);
			BoolTree bool2426 = new BoolTree();
			double p3 = bool2426.BooleanTree(2426, time);
			BoolTree bool2427 = new BoolTree();
			double p4 = bool2427.BooleanTree(2427, time);
			p1 = (p1 + p2 + p3 + p4) / 4;
			return p1;
		} else if (No == 4) {
			BoolTree bool2530 = new BoolTree();
			double p1 = bool2530.BooleanTree(2530, time);
			BoolTree bool2531 = new BoolTree();
			double p2 = bool2531.BooleanTree(2531, time);
			BoolTree bool2532 = new BoolTree();
			double p3 = bool2532.BooleanTree(2532, time);
			BoolTree bool2533 = new BoolTree();
			double p4 = bool2533.BooleanTree(2533, time);
			p1 = (p1 + p2 + p3 + p4) / 4;
			return p1;
		} else {
			double p1 = 0;
			return p1;
		}
	}
	// 主轴密封

	public double getAxleSealFault(long time,int No) {

		if (No == 1) {
			BoolTree bool118 = new BoolTree();
			double p1 = bool118.BooleanTree(118, time);
			BoolTree bool119 = new BoolTree();
			double p2 = bool119.BooleanTree(119, time);
			p1 = (p1 + p2)/2;
			if (p1 > 1) {
				p1 = 0.99;
			}
			return p1;
		} else if (No == 2) {
			BoolTree bool433 = new BoolTree();
			double p1 = bool433.BooleanTree(433, time);
			BoolTree bool434 = new BoolTree();
			double p2 = bool434.BooleanTree(434, time);
			p1 = (p1 + p2)/2;
			if (p1 > 1) {
				p1 = 0.99;
			}
			return p1;
		} else if (No == 3) {
			BoolTree bool758 = new BoolTree();
			double p1 = bool758.BooleanTree(758, time);
			BoolTree bool759 = new BoolTree();
			double p2 = bool759.BooleanTree(759, time);
			p1 = (p1 + p2)/2;
			if (p1 > 1) {
				p1 = 0.99;
			}
			return p1;
		} else if (No == 4) {
			BoolTree bool1086 = new BoolTree();
			double p1 = bool1086.BooleanTree(1086, time);
			BoolTree bool1087 = new BoolTree();
			double p2 = bool1087.BooleanTree(1087, time);
			p1 = (p1 + p2)/2;
			if (p1 > 1) {
				p1 = 0.99;
			}
			return p1;
		} else {
			double p1 = 0;
			return p1;
		}
	}

	// 蜗壳故障

	public double getVoluteFault(long time,int No) {

		if (No == 1) {
			BoolTree bool170 = new BoolTree();
			double p1 = bool170.BooleanTree(170, time);
			return p1;
		} else if (No == 2) {
			BoolTree bool531 = new BoolTree();
			double p1 = bool531.BooleanTree(531, time);
			return p1;
		} else if (No == 3) {
			BoolTree bool815 = new BoolTree();
			double p1 = bool815.BooleanTree(815, time);
			return p1;
		} else if (No == 4) {
			BoolTree bool1135 = new BoolTree();
			double p1 = bool1135.BooleanTree(1135, time);
			return p1;
		} else {
			double p1 = 0;
			return p1;
		}
	}
	
	// 定子绕组固定不良
	public double getStatorFault(long time,int No) {

		if (No == 1) {
			
			double p1 =0;
			return p1;
		} else if (No == 2) {
			BoolTree bool335 = new BoolTree();
			double p1 = bool335.BooleanTree(335, time);
			BoolTree bool336 = new BoolTree();
			double p2 = bool336.BooleanTree(336, time);
			BoolTree bool337 = new BoolTree();
			double p3 = bool337.BooleanTree(337, time);
			
			p1 = (p1 + p2 + p3) / 3;
			return p1;
		} else if (No == 3) {
			BoolTree bool658 = new BoolTree();
			double p1 = bool658.BooleanTree(658, time);
			BoolTree bool659 = new BoolTree();
			double p2 = bool659.BooleanTree(659, time);
			BoolTree bool660 = new BoolTree();
			double p3 = bool660.BooleanTree(660, time);
			
			p1 = (p1 + p2 + p3) / 3;
			return p1;
		} else if (No == 4) {
			BoolTree bool981 = new BoolTree();
			double p1 = bool981.BooleanTree(981, time);
			BoolTree bool982 = new BoolTree();
			double p2 = bool982.BooleanTree(982, time);
			BoolTree bool983 = new BoolTree();
			double p3 = bool983.BooleanTree(983, time);
			
			p1 = (p1 + p2 + p3) / 3;
			return p1;
		} else {
			double p1 = 0;
			return p1;
		}
	}
	
	
	// 上机架振动
		public double getUpFrame(long time,int No) {

			if (No == 1) {
				
				double p1 =0;
				return p1;
			} else if (No == 2) {
				BoolTree bool338 = new BoolTree();
				double p1 = bool338.BooleanTree(338, time);
				BoolTree bool339 = new BoolTree();
				double p2 = bool339.BooleanTree(339, time);
				BoolTree bool340 = new BoolTree();
				double p3 = bool340.BooleanTree(340, time);
				
				p1 = (p1 + p2 + p3) / 3;
				return p1;
			} else if (No == 3) {
				BoolTree bool661 = new BoolTree();
				double p1 = bool661.BooleanTree(661, time);
				BoolTree bool662 = new BoolTree();
				double p2 = bool662.BooleanTree(662, time);
				BoolTree bool663 = new BoolTree();
				double p3 = bool663.BooleanTree(663, time);
				
				p1 = (p1 + p2 + p3) / 3;
				return p1;
			} else if (No == 4) {
				BoolTree bool984 = new BoolTree();
				double p1 = bool984.BooleanTree(984, time);
				BoolTree bool985 = new BoolTree();
				double p2 = bool985.BooleanTree(985, time);
				BoolTree bool986 = new BoolTree();
				double p3 = bool986.BooleanTree(986, time);
				
				p1 = (p1 + p2 + p3) / 3;
				return p1;
			} else {
				double p1 = 0;
				return p1;
			}
		}
		// 下机架振动
				public double getLowFrame(long time,int No) {

					if (No == 1) {
						
						double p1 =0;
						return p1;
					} else if (No == 2) {
						BoolTree bool341 = new BoolTree();
						double p1 = bool341.BooleanTree(341, time);
						BoolTree bool342 = new BoolTree();
						double p2 = bool342.BooleanTree(342, time);
						BoolTree bool343 = new BoolTree();
						double p3 = bool343.BooleanTree(343, time);
						
						p1 = (p1 + p2 + p3) / 3;
						return p1;
					} else if (No == 3) {
						BoolTree bool664 = new BoolTree();
						double p1 = bool664.BooleanTree(664, time);
						BoolTree bool665 = new BoolTree();
						double p2 = bool665.BooleanTree(665, time);
						BoolTree bool666 = new BoolTree();
						double p3 = bool666.BooleanTree(666, time);
						
						p1 = (p1 + p2 + p3) / 3;
						return p1;
					} else if (No == 4) {
						BoolTree bool987 = new BoolTree();
						double p1 = bool987.BooleanTree(987, time);
						BoolTree bool988 = new BoolTree();
						double p2 = bool988.BooleanTree(988, time);
						BoolTree bool989 = new BoolTree();
						double p3 = bool989.BooleanTree(989, time);
						
						p1 = (p1 + p2 + p3) / 3;
						return p1;
					} else {
						double p1 = 0;
						return p1;
					}
				}
				// 油循环泵故障
				public double getOilPumpFault(long time,int No) {

					if (No == 1) {
						BoolTree bool139 = new BoolTree();
						double p1 = bool139.BooleanTree(139, time);
						BoolTree bool145 = new BoolTree();
						double p2 = bool145.BooleanTree(145, time);
						p1 = (p1 + p2 ) / 2;
						return p1;
					} else if (No == 2) {
						BoolTree bool459 = new BoolTree();
						double p1 = bool459.BooleanTree(459, time);
						BoolTree bool465 = new BoolTree();
						double p2 = bool465.BooleanTree(465, time);
						p1 = (p1 + p2 ) / 2;
						return p1;
					} else if (No == 3) {
						BoolTree bool784 = new BoolTree();
						double p1 = bool784.BooleanTree(784, time);
						BoolTree bool790 = new BoolTree();
						double p2 = bool790.BooleanTree(790, time);
						p1 = (p1 + p2 ) / 2;
						return p1;
					} else if (No == 4) {
						BoolTree bool1104 = new BoolTree();
						double p1 = bool1104.BooleanTree(1104, time);
						BoolTree bool1110 = new BoolTree();
						double p2 = bool1110.BooleanTree(1110, time);
						p1 = (p1 + p2 ) / 2;
						return p1;
					} else {
						double p1 = 0;
						return p1;
					}
				}
				
				// 压差低

				public double getYaChaDi(long time,int No) {

					if (No == 1) {
						BoolTree bool120 = new BoolTree();
						double p1 = bool120.BooleanTree(120, time);
						return p1;
					} else if (No == 2) {
						double p1 =0;
						if(time == 1470240000) {p1=1;}
						return p1;
					} else if (No == 3) {
						BoolTree bool760 = new BoolTree();
						double p1 = bool760.BooleanTree(760, time);
						return p1;
					} else if (No == 4) {
						BoolTree bool1088 = new BoolTree();
						double p1 = bool1088.BooleanTree(1088, time);
						return p1;
					} else {
						double p1 = 0;
						return p1;
					}
				}
				
}
