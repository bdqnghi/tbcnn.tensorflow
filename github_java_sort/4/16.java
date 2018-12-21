package logic.stockShowInfobl;

import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.regex.Pattern;

import data.sqlImpl.StockDataSQL;
import dataservice.StockListDataservice;
import enums.SortType;
import exception.StatusNotOKException;
import logic.utils.CreatSortDataStructure;
import logic.utils.FilterUtils;
import logic.utils.HeapSort;
import logic.utils.SortByTime;
import logicservice.showInfoblservice.StockListLogicservice;
import po.NStockPO;
import utils.Filter;
import utils.StopDeal;
import utils.WHICHIMP;
import utils.changeRateFormate;
import vo.NStockVO;
import vo.SortVO;

public class StockListLogic implements StockListLogicservice {
	private StockListDataservice socklistService ;
	public StockListLogic(){
	if(WHICHIMP.isSQL){
	
	socklistService = new StockDataSQL();
	}
	
	}
		
	public void setService(StockListDataservice ser) {
		this.socklistService = ser;
	}

	@Override
	public ArrayList<NStockVO> getResultListAll(String year, String exchange) {
		ArrayList<NStockVO> voList = new ArrayList<NStockVO>();
		try {
			ArrayList<NStockPO> poList = socklistService.getResultListAll(exchange);
			for (int i = 0; i < poList.size(); i++) {
				
				if(!StopDeal.isStopDeal(poTOvo(poList.get(i)))){
					voList.add(poTOvo(poList.get(i)));
				}
			}



		} catch (StatusNotOKException e) {
			System.out.println(e.message);
		}

		return sortStockList(voList, SortType.dateDown);
	}

	@Override
	public ArrayList<NStockVO> search(String searchstr) throws StatusNotOKException {
		ArrayList<NStockPO> poList = socklistService.getResultListAll("sz+sh");
		String trueExpression = ".*" + searchstr + ".*";
		ArrayList<NStockVO> vol = new ArrayList<NStockVO>();
		for (int i = 0; i < poList.size(); i++) {
			if (Pattern.matches(trueExpression, poList.get(i).getName())) {
				vol.add(poTOvo(poList.get(i)));
			}
		}
		return vol;
	}

	@Override
	public ArrayList<NStockVO> getResultList(ArrayList<NStockVO> vo, Filter filter) {
		return FilterUtils.filter(vo, filter);

	}

	@Override
	public ArrayList<NStockVO> sortStockList(ArrayList<NStockVO> vo, SortType sortType) {
		ArrayList<SortVO> stockSortList = new ArrayList<SortVO>();
		
		try {
			if (sortType.equals(SortType.openAscend)) {
				stockSortList = HeapSort.AntiHeapSort(CreatSortDataStructure.sortByOpen(vo));
			} else if (sortType.equals(SortType.openDown)) {
				stockSortList = HeapSort.heapSort(CreatSortDataStructure.sortByOpen(vo));
			} else if (sortType.equals(SortType.closeAscend)) {
				stockSortList = HeapSort.AntiHeapSort(CreatSortDataStructure.sortByClose(vo));
			} else if (sortType.equals(SortType.closeDown)) {
				stockSortList = HeapSort.heapSort(CreatSortDataStructure.sortByClose(vo));
			} else if (sortType.equals(SortType.adj_priceAscent)) {
				stockSortList = HeapSort.AntiHeapSort(CreatSortDataStructure.sortByAdjPrice(vo));
			} else if (sortType.equals(SortType.adj_priceDown)) {
				stockSortList = HeapSort.heapSort(CreatSortDataStructure.sortByAdjPrice(vo));
			} else if (sortType.equals(SortType.highAscend)) {
				stockSortList = HeapSort.AntiHeapSort(CreatSortDataStructure.sortByHigh(vo));
			} else if (sortType.equals(SortType.highDown)) {
				stockSortList = HeapSort.heapSort(CreatSortDataStructure.sortByHigh(vo));
			} else if (sortType.equals(SortType.lowAscend)) {
				stockSortList = HeapSort.AntiHeapSort(CreatSortDataStructure.sortByLow(vo));
			} else if (sortType.equals(SortType.lowDown)) {
				stockSortList = HeapSort.heapSort(CreatSortDataStructure.sortByLow(vo));
			} else if (sortType.equals(SortType.pbAscent)) {
				stockSortList = HeapSort.AntiHeapSort(CreatSortDataStructure.sortByPb(vo));
			} else if (sortType.equals(SortType.pbDown)) {
				stockSortList = HeapSort.heapSort(CreatSortDataStructure.sortByPb(vo));
			} else if (sortType.equals(SortType.peAscent)) {
				stockSortList = HeapSort.AntiHeapSort(CreatSortDataStructure.sortByPe(vo));
			} else if (sortType.equals(SortType.peDown)) {
				stockSortList = HeapSort.heapSort(CreatSortDataStructure.sortByPe(vo));
			} else if (sortType.equals(SortType.turnoverAscent)) {
				stockSortList = HeapSort.AntiHeapSort(CreatSortDataStructure.sortByTurnOver(vo));
			} else if (sortType.equals(SortType.turnoverDown)) {
				stockSortList = HeapSort.heapSort(CreatSortDataStructure.sortByTurnOver(vo));
			} else if (sortType.equals(SortType.volumeAscent)) {
				stockSortList = HeapSort.AntiHeapSort(CreatSortDataStructure.sortByVolume(vo));
			} else if (sortType.equals(SortType.volumeDown)) {
				stockSortList = HeapSort.heapSort(CreatSortDataStructure.sortByVolume(vo));
			} else if (sortType.equals(SortType.dateAscent)) {
				stockSortList = SortByTime.sortByTimeup(CreatSortDataStructure.sortByDate(vo));
			} else if(sortType.equals(SortType.dateDown)){
				stockSortList = SortByTime.sortByTime(CreatSortDataStructure.sortByDate(vo));
			}else if(sortType.equals(SortType.changeRateAscent)){
				stockSortList = HeapSort.AntiHeapSort(CreatSortDataStructure.sortByChangeRate(vo));
			}else {
				stockSortList = HeapSort.heapSort(CreatSortDataStructure.sortByChangeRate(vo));
			}
		} catch (NullPointerException e) {
			e.printStackTrace();
		}

		ArrayList<NStockVO> trading_info = new ArrayList<NStockVO>();
		for (int i = 0; i < stockSortList.size(); i++) {
			trading_info.add(stockSortList.get(i).getStockVO());
		}

		return trading_info;

	}

	@Override
	public ArrayList<NStockVO> click(String name) {
		ArrayList<NStockVO> vo = new ArrayList<NStockVO>();
		try {
			ArrayList<NStockPO> po = socklistService.getByName(name, null, null);
			
			for (int i = 0; i < po.size(); i++) {
				vo.add(poTOvo(po.get(i)));
			}
			
			
			
			for (int i = 1; i < po.size(); i++) {
				NStockVO af=vo.get(i);
				NStockVO be=vo.get(i-1);
				BigDecimal afclose=af.getClose();
				BigDecimal beclose=be.getClose();
				
				BigDecimal changeRate;
				if(beclose.compareTo(BigDecimal.ZERO)==0){
					
					changeRate=new BigDecimal(0);
					vo.get(i).setRate("停牌");
				}else{
					changeRate=afclose.subtract(beclose).divide(beclose,5,BigDecimal.ROUND_HALF_UP);
					vo.get(i).setRate(changeRateFormate.formate(changeRate));

				}
				vo.get(i).setChangeRate(changeRate);

			}
			if(vo.size()>=1){
				vo.remove(0);
			}
		} catch (StatusNotOKException e) {
			e.getMessage();
		}
		return sortStockList(vo, SortType.dateDown);
	}

	private NStockVO poTOvo(NStockPO po) {

		return new NStockVO(po.getName(), po.getDate(), po.getOpen(), po.getHigh(), po.getLow(), po.getClose(),
				po.getAdj_price(), po.getVolume(), po.getTurnover(), po.getPe_ttm(), po.getPb());

	}

	@Override
	public ArrayList<NStockVO> getResultDetail(ArrayList<NStockVO> vo, Filter filter) {
		




		if(vo.size()>0){
			return FilterUtils.filterDetail(vo.get(0).getName(),vo, filter);
		}
		else
			return FilterUtils.filterDetail(vo, filter);
	}









}
