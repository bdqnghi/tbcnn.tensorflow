#include "hmm.hpp"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>

HMM::HMM(PlaceCell *pc, GLfloat start_time, GLfloat end_time) {

	// define markov model
	// Good for Frank data
	p_outfield_to_infield = 0.2f;
	p_infield_to_outfield = 0.4f;
	p_infield_spike = 0.95f;
	p_outfield_spike = 0.4f;
	alpha_infield = 1.0f * p_infield_spike; // assume we're in the field to begin with
	alpha_outfield = 0.0f;
	bin_size = 0.1f;

	// Good for figure 8 data
	// p_outfield_to_infield = 0.1f;
	// p_infield_to_outfield = 0.3f;
	// p_infield_spike = 0.9f;
	// p_outfield_spike = 0.7f;
	// alpha_infield = 1.0f * p_infield_spike; // assume we're in the field to begin with
	// alpha_outfield = 0.0f;
	// bin_size = 30.0f;

	std::ofstream output(pc->getOutputFilename());

	GLfloat current_time = start_time;
	std::vector<GLfloat> spikes = std::vector<GLfloat>();
	spikes.push_back(current_time);
	int max_spikes = 0;

	while (current_time < end_time) {
		if ((*pc->getCurrentTime()) < current_time + bin_size && pc->getNextTime()) {
			spikes.push_back((*pc->getCurrentTime()));
		}
		else {
			if(spikes.size() > max_spikes)
				max_spikes = spikes.size();

			//printf("%f : [%i]\n", current_time, spikes.size());
			spike_obs.push_back(spikes);
			spikes = std::vector<GLfloat>();
			current_time += bin_size;
		}
	}

	spike_model.push_back(spike_obs[0]);

	for (int i = 1; i < spike_obs.size(); i++) {
		GLfloat spike_multiplier = 0.3f + ((float)spike_obs[i].size() / (float)max_spikes);
		if (spike_obs[i].size() > 0) { // we observe a spike
			alpha_infield = ((1.0f-p_infield_to_outfield) * (p_infield_spike*spike_multiplier) * alpha_infield) +
											(p_outfield_to_infield * (p_infield_spike*spike_multiplier) * alpha_outfield);
			alpha_outfield = (p_infield_to_outfield * p_outfield_spike * alpha_infield) +
											((1.0f-p_outfield_to_infield) * p_outfield_spike * alpha_outfield);
		} else { //no spike observed
			alpha_infield = ((1.0f-p_infield_to_outfield) * (1.0f-p_infield_spike) * alpha_infield) +
											(p_outfield_to_infield * (1.0f-p_infield_spike) * alpha_outfield);
			alpha_outfield = (p_infield_to_outfield * (1.0f-p_outfield_spike) * alpha_infield) +
											((1.0f-p_outfield_to_infield) * (1.0f-p_outfield_spike) * alpha_outfield);
		}

		alpha_infield = alpha_infield / (alpha_infield + alpha_outfield);
		alpha_outfield = alpha_outfield / (alpha_infield + alpha_outfield);

		GLfloat prob_infield = alpha_infield / (alpha_infield + alpha_outfield);
		GLfloat prob_outfield = alpha_outfield / (alpha_infield + alpha_outfield);

		spike_model.push_back( (prob_infield >= prob_outfield) ? spike_obs[i] : std::vector<GLfloat>());
		//spike_model.push_back(spike_obs[i]);
	}

	for ( int i=0; i<spike_model.size(); i++) {
		output << (float)spike_model[i].size() << "\n";
	}

	output.flush();
	output.close();
}

std::deque<GLfloat> HMM::getSpikeTimes() {
	std::deque<GLfloat> times;

	for (int i = 1; i < spike_model.size(); i++) {
			times.insert(times.end(), spike_model[i].begin(), spike_model[i].end() );
	}

	return times;
}
