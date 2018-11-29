package org.rcsb.mmtf.benchmark;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 *
 * @author Antonin Pavelka
 */
public class Bucket {

	private final double lo, hi;
	private final List<PdbEntry> entries = new ArrayList<>();

	public Bucket(double lo, double hi) {
		this.lo = lo;
		this.hi = hi;
	}

	public void add(PdbEntry pe) {
		entries.add(pe);
	}

	public void sort() {
		Collections.sort(entries);
	}

	public PdbEntry get(int i) {
		return entries.get(i);
	}

	public int size() {
		return entries.size();
	}

	public void remove(int i) {
		entries.remove(i);
	}

	public List<PdbEntry> getAll() {
		return entries;
	}

	public double getLo() {
		return lo;
	}

	public double getHi() {
		return hi;
	}
}
