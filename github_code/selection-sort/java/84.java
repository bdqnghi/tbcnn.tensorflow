package mx.gob.cofepris.cos.deds.traceability.view.wirers.sort_filterPanelsWirer;

import java.awt.event.*;
import java.time.*;
import java.util.*;
import java.util.function.*;
import javax.swing.*;
import mx.gob.cofepris.cos.deds.traceability.model.sortAndFilterPanel.sort_filterPanel.*;
import mx.gob.cofepris.cos.deds.traceability.view.sortAndFilterPanel.*;
import mx.gob.cofepris.cos.deds.traceability.view.sortAndFilterPanel.itemsListFactories.*;
import mx.gob.cofepris.cos.deds.traceability.view.wirers.sort_filterPanelsWirer.filterFieldEffectsManager.*;


public class SortFilterPanelMVCAssemblerFactory {
	
	
	private SortFilterPanelMVCAssemblerFactory() {}
	
	
	public static Sort_FilterPanelView buildTextMultiChoiceSort_FilterPanelView(String panelName, 
			Sort_FilterPanelModel<String> sort_filterPanelModel) {
		TextMultiSelectionPanelViewAssembler textMultiSelectionPanelViewAssembler = 
				new TextMultiSelectionPanelViewAssembler(panelName, sort_filterPanelModel);
		return textMultiSelectionPanelViewAssembler.buildSort_FilterPanelView();
	}
	
	
	public static Sort_FilterPanelView buildTextSingleChoiceSort_FilterPanelView(String panelName, 
			Sort_FilterPanelModel<String> sort_filterPanelModel) {	
		TextSingleSelectionPanelViewAssembler textSingleSelectionPanelViewAssembler = 
				new TextSingleSelectionPanelViewAssembler(panelName, sort_filterPanelModel);
		return textSingleSelectionPanelViewAssembler.buildSort_FilterPanelView();
	}	

	
	public static Sort_FilterPanelView buildDateSort_FilterPanelView(String panelName, 
			Sort_FilterPanelModel<LocalDate> sort_filterPanelModel) {
		DatePanelViewAssembler datePanelViewAssembler = new DatePanelViewAssembler(panelName, sort_filterPanelModel);
		return datePanelViewAssembler.buildSort_FilterPanelView();
	}
	
	
	private static abstract class PanelViewAssembler<T> {
		private String panelName;
		Sort_FilterPanelModel<T> sort_filterPanelModel;
		
		
		public PanelViewAssembler(String panelName, Sort_FilterPanelModel<T> sort_filterPanelModel) {
			if (panelName == null) {
				throw new IllegalStateException("panelName cannot be null");
			} else if (sort_filterPanelModel == null) {
				throw new IllegalStateException("panelModel cannot be null");
			}
			this.panelName = panelName;	
			this.sort_filterPanelModel = sort_filterPanelModel;			
		}
		
		
		public abstract Sort_FilterPanelView buildSort_FilterPanelView();


		Sort_FilterPanelView buildBaseSort_FilterPanelView(SelectionItemsFactory<T> selectionItemsFactory, 
				Supplier<ArrayList<T>> selectedItemsSupplier) {
			Sort_FilterPanelView sort_FilterPanelView = new Sort_FilterPanelView(panelName);
			Sort_FilterPanelController<T> sort_filterPanelController = 
					new Sort_FilterPanelController.Builder<T>()
					.setSelectionItemsFactory(selectionItemsFactory)
					.setSort_FilterPanelModel(sort_filterPanelModel)
					.setSort_FilterPanelView(sort_FilterPanelView)
					.setViewSelectedItemsSupplier(selectedItemsSupplier)
					.build();
			sort_FilterPanelView.addSort_FilterPanelViewEventListener(sort_filterPanelController);
			sort_FilterPanelView.addListenerOnSelectAllCheckBox(buildSelectAllCheckBoxListener(selectionItemsFactory));
			sort_FilterPanelView.getPopupMenu().addPopupMenuListener(sort_filterPanelController);		
			sort_filterPanelModel.addS_FPanelModelConfigEventListener(sort_filterPanelController);		
			sort_filterPanelModel.addS_FPanelModelFilterEventListener(sort_filterPanelController);
			sort_filterPanelModel.addSortEventListener(sort_filterPanelController);
			return sort_FilterPanelView;
		}		
		
		
		private ActionListener buildSelectAllCheckBoxListener(SelectionItemsFactory<?> selectionItemsFactory) {
			return (e) -> {
				AbstractButton selectAllButton = (AbstractButton) e.getSource();
				boolean selectAll = selectAllButton.isSelected();
				SelectionModel<?> selectionModel = selectionItemsFactory.getSelectionModel();			
				selectionModel.setFullItemsSelectionState(selectAll);			
			};
		}
	}
	
	
	private static class DatePanelViewAssembler extends PanelViewAssembler<LocalDate> {

		public DatePanelViewAssembler(String panelName, Sort_FilterPanelModel<LocalDate> sort_filterPanelModel) {
			super(panelName, sort_filterPanelModel);			
		}
		
		
		@Override
		public Sort_FilterPanelView buildSort_FilterPanelView() {
			SelectionItemsFactory<LocalDate> selectionItemsFactory = new CheckBoxDateSelectionItemsFactory();
			SelectionModel<LocalDate> selectionModel = selectionItemsFactory.getSelectionModel();
			Supplier<ArrayList<LocalDate>> selectedItemsSupplier = selectionModel::retrieveSelectedValues;
			Sort_FilterPanelView panelView = buildBaseSort_FilterPanelView(selectionItemsFactory, 
					selectedItemsSupplier);
			panelView.displaySearchPanel(false);
			return panelView;
		}		
	}
	
	
	private static class TextMultiSelectionPanelViewAssembler extends PanelViewAssembler<String> {

		public TextMultiSelectionPanelViewAssembler(String panelName, 
				Sort_FilterPanelModel<String> sort_filterPanelModel) {
			super(panelName, sort_filterPanelModel);			
		}
		
		
		@Override
		public Sort_FilterPanelView buildSort_FilterPanelView() {
			SelectedItemsRetriever selectedItemsRetriever = new SelectedItemsRetriever();
			Supplier<ArrayList<String>> selectedItemsSupplier = selectedItemsRetriever.retrieveSelectedItemsSupplier();
			SelectionItemsFactory<String> selectionItemsFactory = new CheckBoxTextSelectionItemsFactory();			
			Sort_FilterPanelView sort_FilterPanelView = buildBaseSort_FilterPanelView(selectionItemsFactory, 
					selectedItemsSupplier);
			FilterFieldDocumentListener filterFieldDocumentListener = new VolatileItemsSelectionStateKeeper.Builder()
					.setSelectedItemsRetriever(selectedItemsRetriever)
					.setSort_FilterPanelView(sort_FilterPanelView)
					.setSourceSelectionItemsFactory(selectionItemsFactory)
					.setSourceSort_FilterPanelModel(sort_filterPanelModel)
					.build();	
			sort_FilterPanelView.addDocumentListenerOnFilterTextField(filterFieldDocumentListener);
			sort_FilterPanelView.getPopupMenu().addPopupMenuListener(filterFieldDocumentListener);		
			return sort_FilterPanelView;
		}
	}
	
	
	private static class TextSingleSelectionPanelViewAssembler extends PanelViewAssembler<String> {

		public TextSingleSelectionPanelViewAssembler(String panelName, 
				Sort_FilterPanelModel<String> sort_filterPanelModel) {
			super(panelName, sort_filterPanelModel);			
		}
		
		
		@Override
		public Sort_FilterPanelView buildSort_FilterPanelView() {
			SelectionItemsFactory<String> selectionItemsFactory = new RadioButtonTextSelectionItemsFactory();			
			SelectionModel<String> selectionModel = selectionItemsFactory.getSelectionModel();	
			Supplier<ArrayList<String>> selectedItemsSupplier = selectionModel::retrieveSelectedValues;
			Sort_FilterPanelView sort_FilterPanelView = buildBaseSort_FilterPanelView(selectionItemsFactory, 
					selectedItemsSupplier);
			FilterFieldDocumentListener filterFieldDocumentListener = new FilterFieldDocumentListener.Builder()
					.setSort_FilterPanelView(sort_FilterPanelView)
					.setSourceSelectionItemsFactory(selectionItemsFactory)
					.setSourceSort_FilterPanelModel(sort_filterPanelModel)
					.build();
			sort_FilterPanelView.addDocumentListenerOnFilterTextField(filterFieldDocumentListener);
			sort_FilterPanelView.getPopupMenu().addPopupMenuListener(filterFieldDocumentListener);
			sort_FilterPanelView.displaySelectAllItemsCheckBox(false);
			return sort_FilterPanelView;
		}		
	}
}
