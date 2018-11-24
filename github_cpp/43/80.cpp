/*
 * BucketSort.cpp
 *
 *  Created on: 22 Oct 2012
 *      Author: robinsonm
 */

#include "BucketSort.h"
#include <boost/foreach.hpp>

namespace Tyche {

void BucketSort::reset(const Vect3d& _low, const Vect3d& _high, double _max_interaction_radius) {
	LOG(2,"Resetting bucketsort data structure:");
	LOG(2,"\tMax interaction radius = "<<_max_interaction_radius);
	high = _high;
	low = _low;
	max_interaction_radius = _max_interaction_radius;
	Vect3i num_cells_without_ghost = ((high-low)/max_interaction_radius).cast<int>();
	Vect3d new_high = high;
	for (int i = 0; i < 3; ++i) {
		if (num_cells_without_ghost[i]==0) {
			LOG(2,"\tNote: Dimension "<<i<<" has no length, setting cell side equal to interaction radius.");
			new_high[i] = low[i] + max_interaction_radius;
			num_cells_without_ghost[i] = 1;
		}
	}
	num_cells_along_axes = num_cells_without_ghost + Vect3i(3,3,3);
	LOG(2,"\tNumber of cells along each axis = "<<num_cells_along_axes);
	cell_size = (new_high-low).cwiseQuotient(num_cells_without_ghost.cast<double>());
	LOG(2,"\tCell sizes along each axis = "<<cell_size);
	inv_cell_size = Vect3d(1,1,1).cwiseQuotient(cell_size);
	num_cells_along_yz = num_cells_along_axes[2]*num_cells_along_axes[1];
	const unsigned int num_cells = num_cells_along_axes.prod();
	cells.assign(num_cells, CELL_EMPTY);
	//TODO: assumed 3d
	surrounding_cell_offsets.clear();
	for (int i = -1; i < 2; ++i) {
		for (int j = -1; j < 2; ++j) {
			for (int k = -1; k < 2; ++k) {
				surrounding_cell_offsets.push_back(vect_to_index(Vect3i(i,j,k)));
			}
		}
	}


	ghosting_indices_pb.assign(num_cells, std::vector<int>());
	ghosting_indices_cb.clear();
	for (int i = 0; i < NDIM; ++i) {
		if (!periodic[i]) continue;
		int j,k;
		switch (i) {
			case 0:
				j = 1;
				k = 2;
				break;
			case 1:
				j = 0;
				k = 2;
				break;
			case 2:
				j = 0;
				k = 1;
				break;
			default:
				break;
		}

		Vect3i tmp;
		const int n = num_cells_along_axes[i];
		for (int jj = 0; jj < num_cells_along_axes[j]-2; ++jj) {
			tmp[j] = jj;
			for (int kk = 0; kk < num_cells_along_axes[k]-2; ++kk) {
				tmp[k] = kk;
				tmp[i] = n-3;
				const int index_from1 = vect_to_index(tmp);
				tmp[i] = 0;
				const int index_to1 = vect_to_index(tmp);
				ghosting_indices_pb[index_from1].push_back(index_to1);
				ghosting_indices_cb.push_back(std::pair<int,int>(index_to1,index_from1));
				tmp[i] = 1;
				const int index_from2 = vect_to_index(tmp);
				tmp[i] = n-2;
				const int index_to2 = vect_to_index(tmp);
				ghosting_indices_pb[index_from2].push_back(index_to2);
				ghosting_indices_cb.push_back(std::pair<int,int>(index_to2,index_from2));
			}
		}
	}
}

void BucketSort::embed_points(std::vector<Vect3d>& positions) {
	const unsigned int n = positions.size();
	linked_list.assign(n, CELL_EMPTY);
	const bool particle_based = dirty_cells.size() < cells.size();
	if (particle_based) {
		BOOST_FOREACH(int i, dirty_cells) {
			cells[i] = CELL_EMPTY;
		}
	} else {
		cells.assign(cells.size(), CELL_EMPTY);
	}

	dirty_cells.clear();
	for (int i = 0; i < n; ++i) {
		const int celli = find_cell_index(positions[i]);
		const int cell_entry = cells[celli];

		// Insert into own cell
		cells[celli] = i;
		dirty_cells.push_back(celli);
		linked_list[i] = cell_entry;

		// Insert into ghosted cells
		if (particle_based) {
			BOOST_FOREACH(int j, ghosting_indices_pb[celli]) {
				const int cell_entry = cells[j];
				cells[j] = i;
				dirty_cells.push_back(j);
				linked_list[i] = cell_entry;
			}
		}
	}

	if (!particle_based) {
		for (std::vector<std::pair<int,int> >::iterator index_pair = ghosting_indices_cb.begin(); index_pair != ghosting_indices_cb.end(); ++index_pair) {
			//BOOST_FOREACH(std::pair<int,int> index_pair, ghosting_indices) {
			cells[index_pair->first] = cells[index_pair->second];
		}
	}
}

std::vector<int>& BucketSort::find_broadphase_neighbours(const Vect3d& r, const int my_index, const bool self) {
	const int cell_i = find_cell_index(r);
	neighbr_list.clear();
	int n = surrounding_cell_offsets.size();
	if (self) n = (n-1)/2;
	for (int i = 0; i < n; ++i) {
		const int offset = surrounding_cell_offsets[i];
		int entry = cells[cell_i + offset];
		while (entry != CELL_EMPTY) {
			neighbr_list.push_back(entry);
			entry = linked_list[entry];
		}
	}
	if (self) {
		int entry = cells[cell_i];
		bool found_self = false;
		while (entry != CELL_EMPTY) {
			if (found_self) {
				neighbr_list.push_back(entry);
			} else if (my_index==entry) {
				found_self = true;
			}
			entry = linked_list[entry];
		}
	}
	return neighbr_list;
}


Vect3d BucketSort::correct_position_for_periodicity(const Vect3d& source_r, const Vect3d& to_correct_r) {
	Vect3d corrected_r = to_correct_r - source_r;
	for (int i = 0; i < NDIM; ++i) {
		if (!periodic[i]) continue;
		if (corrected_r[i] > cell_size[i]) corrected_r[i] -= domain_size[i];
		if (corrected_r[i] < -cell_size[i]) corrected_r[i] += domain_size[i];
	}
	return corrected_r + source_r;
}

Vect3d BucketSort::correct_position_for_periodicity(const Vect3d& to_correct_r) {
	Vect3d corrected_r = to_correct_r;
	for (int i = 0; i < NDIM; ++i) {
		if (!periodic[i]) continue;
		while (corrected_r[i] >= high[i]) corrected_r[i] -= domain_size[i];
		while (corrected_r[i] < low[i]) corrected_r[i] += domain_size[i];
	}
	return corrected_r;
}


}


