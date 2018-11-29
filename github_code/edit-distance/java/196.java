/*
 * Copyright (C) 2016 Takuya KOUMURA
 * https://github.com/takuya-koumura/birdsong-recognition
 *
 * This file is part of Birdsong Recognition.
 * 
 * Birdsong Recognition is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Birdsong Recognition is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Birdsong Recognition.  If not, see <http://www.gnu.org/licenses/>.
 */
package errorcomputation;

import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

import computation.Sequence;
import computation.Sequence.Note;
import utils.ArrayUtils;
import utils.CollectionUtils;

/**
 * A class to compute Levenshtein errors.
 * @author koumura
 *
 */
public class Levenshtein
{
	private static <T> Result compute(ArrayList<T> sequence0, ArrayList<T> sequence1)
	{
		int[] distance=new int[sequence1.size()+1];
		int[] prevDistance=new int[distance.length];
		ArrayList<int[]> source=new ArrayList<>(sequence0.size());
		prevDistance[0]=0;
		for(int i1=0; i1<sequence1.size(); ++i1) prevDistance[i1+1]=i1+1;
		for(int i0=0; i0<sequence0.size(); ++i0)
		{
			distance[0]=i0+1;
			int[] src=new int[sequence1.size()];
			source.add(src);
			for(int i1=0; i1<sequence1.size(); ++i1)
			{
				int min=prevDistance[i1];
				src[i1]=0;
				if(!sequence0.get(i0).equals(sequence1.get(i1))) ++min;
				if(prevDistance[i1+1]+1<min)
				{
					min=prevDistance[i1+1]+1;
					src[i1]=1;
				}
				if(distance[i1]+1<min)
				{
					min=distance[i1]+1;
					src[i1]=2;
				}
				distance[i1+1]=min;
			}
			int[] tmp=distance;
			distance=prevDistance;
			prevDistance=tmp;
		}
		//backtrack
		LinkedList<int[]> alignedIndex=new LinkedList<int[]>();
		int i0=sequence0.size()-1, i1=sequence1.size()-1;
		while(i0>=0||i1>=0)
		{
			int s;
			if(i0>=0&&i1>=0) s=source.get(i0)[i1];
			else if(i0>=0) s=1;
			else s=2;
			switch(s)
			{
			case 0:
				alignedIndex.add(new int[]{i0, i1});
				--i0;
				--i1;
				break;
			case 1:
				alignedIndex.add(new int[]{i0, -1});
				--i0;
				break;
			case 2:
				alignedIndex.add(new int[]{-1, i1});
				--i1;
				break;
			}
		}
		Collections.reverse(alignedIndex);
		int finalDistance=ArrayUtils.last(prevDistance);
		Result result=new Result(alignedIndex, finalDistance);
		return result;
	}
	
	/**
	 * @param noteSequence0
	 * @param noteSequence1
	 * @return Levenshtein distance.
	 */
	public static int computeDistance(List<Note> noteSequence0, List<Note> noteSequence1)
	{
		ArrayList<String> labelSeq0=noteSequence0.stream().map(n->n.getLabel()).collect(CollectionUtils.arrayListCollector());
		ArrayList<String> labelSeq1=noteSequence1.stream().map(n->n.getLabel()).collect(CollectionUtils.arrayListCollector());
		return compute(labelSeq0, labelSeq1).distance;
	}

	/**
	 * @param outputSequence Map of correct sequences to output intervals.
	 * @return Levenshtein error.
	 */
	public static double computeError(Map<Sequence, ArrayList<Note>> outputSequence)
	{
		int numLabel=0, distance=0;
		for(Sequence seq: outputSequence.keySet())
		{
			numLabel+=seq.getNote().size();
			distance+=computeDistance(seq.getNote(), outputSequence.get(seq));
		}
		return (double)distance/numLabel;
	}
	
	private static class Result
	{
		private LinkedList<int[]> alignedIndex;
		private int distance;

		private Result(LinkedList<int[]> alignedIndex, int distance)
		{
			this.alignedIndex = alignedIndex;
			this.distance = distance;
		}

		private LinkedList<int[]> getAlignedIndex(){return alignedIndex;}

		private int getDistance(){return distance;}
	}
}
