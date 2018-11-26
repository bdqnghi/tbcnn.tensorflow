package com.example.przemek.controller;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import com.example.przemek.model.BubbleSortModel;
import com.example.przemek.view.BubbleSortView;

public class BubbleSortController {
	
	BubbleSortModel bubbleSortModel = new BubbleSortModel();
	BubbleSortView bubbleSortView = new BubbleSortView();
	int sortMethod = 0;
	
	public BubbleSortController(BubbleSortModel model, BubbleSortView view) {
		this.bubbleSortModel = model;
		this.bubbleSortView = view;
		
		this.bubbleSortView.addAscendingListener(new listenerForAscend());
		this.bubbleSortView.addDescendingListener(new listenerForDescend());
		this.bubbleSortView.addSortListener(new listenerForSort());
		
	}
	class listenerForAscend implements ActionListener {

		@Override
		public void actionPerformed(ActionEvent e) {
			sortMethod = 0;	
		}}
	
	class listenerForDescend implements ActionListener {

		@Override
		public void actionPerformed(ActionEvent e) {
			sortMethod = 1;	
		}}
	
	
	
	class listenerForSort implements ActionListener {

		@Override
		public void actionPerformed(ActionEvent e) {
		int [] numbersArray = new int [7]; 	
		try {
			numbersArray [0] = bubbleSortView.getNumberOne();
			numbersArray [1] = bubbleSortView.getNumberTwo();
			numbersArray [2] = bubbleSortView.getNumberThree();
			numbersArray [3] = bubbleSortView.getNumberFour();
			numbersArray [4] = bubbleSortView.getNumberFive();
			numbersArray [5] = bubbleSortView.getNumberSix();
			numbersArray [6] = bubbleSortView.getNumberSeven();
		}
		catch(NumberFormatException ex) {
			bubbleSortView.DisplayError("all spaces must be filled with numbers");
			return;
		}
		
		if (sortMethod == 0) {
		bubbleSortModel.SortAscending(numbersArray, 7);
		}
		else if (sortMethod == 1) {
			bubbleSortModel.SortDescending(numbersArray, 7);	
		}
		
		bubbleSortView.setSortedOne(numbersArray[0]);
		bubbleSortView.setSortedTwo(numbersArray[1]);
		bubbleSortView.setSortedThree(numbersArray[2]);
		bubbleSortView.setSortedFour(numbersArray[3]);
		bubbleSortView.setSortedFive(numbersArray[4]);
		bubbleSortView.setSortedSix(numbersArray[5]);
		bubbleSortView.setSortedSeven(numbersArray[6]);
		}
		
	}
}
