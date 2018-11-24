#include "HMM.hpp"

#include <algorithm>
#include <cstddef>
#include <tuple>

#include "linalg.hpp"
#include "utils.hpp"

/// @file HMM.cpp
/// @brief Partial implementation of the pure virtual HMM base class.

namespace linearham {


HMM::HMM(const std::string& yaml_path, int cluster_ind,
         const std::string& hmm_param_dir) {
  // Parse the `flexbounds` and `relpos` YAML data.
  yaml_root_ = YAML::LoadFile(yaml_path);
  flexbounds_ = yaml_root_["events"][cluster_ind]["flexbounds"]
                    .as<std::map<std::string, std::pair<int, int>>>();
  relpos_ = yaml_root_["events"][cluster_ind]["relpos"]
                .as<std::map<std::string, int>>();

  // Create the map holding (germline name, GermlineGene) pairs.
  ggenes_ = CreateGermlineGeneMap(hmm_param_dir);

  // Initialize the nucleotide alphabet.
  alphabet_ = ggenes_.begin()->second.germ_ptr->alphabet() + "N";

  // Initialize the state space.
  InitializeStateSpace();

  // Initialize the transition probability matrices.
  InitializeTransition();

  // Initialize the "germline" scaler counts.
  vgerm_init_scaler_count_ = 0;
  dgerm_init_scaler_count_ = 0;
  jgerm_init_scaler_count_ = 0;
};


// Initialization functions


void HMM::InitializeStateSpace() {
  // Iterate across the relpos map from left to right.
  for (auto it = relpos_.begin(); it != relpos_.end(); ++it) {
    // This map has germline gene names as keys and relpos as values.
    const std::string& gname = it->first;
    int relpos = it->second;

    // Cache the "germline" and "junction" states.
    const GermlineGene& ggene = ggenes_.at(gname);

    if (ggene.type == GermlineType::V) {
      // Cache the V "padding" state.
      CachePaddingStates(ggene.germ_ptr, flexbounds_.at("v_l"), relpos, true,
                         vpadding_ggene_ranges_, vpadding_naive_bases_,
                         vpadding_site_inds_);

      // Cache the V "germline" state.
      CacheGermlineStates(
          ggene.germ_ptr, flexbounds_.at("v_l"), flexbounds_.at("v_r"), relpos,
          true, false, vgerm_state_strs_, vgerm_ggene_ranges_,
          vgerm_naive_bases_, vgerm_germ_inds_, vgerm_site_inds_);

      // Cache the V-D "junction" states.
      CacheJunctionStates(ggene.germ_ptr, flexbounds_.at("v_r"),
                          flexbounds_.at("d_l"), relpos, false,
                          vd_junction_state_strs_, vd_junction_ggene_ranges_,
                          vd_junction_naive_bases_, vd_junction_germ_inds_,
                          vd_junction_site_inds_);
    } else if (ggene.type == GermlineType::D) {
      // Cache the V-D "junction" states.
      CacheJunctionStates(ggene.germ_ptr, flexbounds_.at("v_r"),
                          flexbounds_.at("d_l"), relpos, true,
                          vd_junction_state_strs_, vd_junction_ggene_ranges_,
                          vd_junction_naive_bases_, vd_junction_germ_inds_,
                          vd_junction_site_inds_);

      // Cache the D "germline" state.
      CacheGermlineStates(
          ggene.germ_ptr, flexbounds_.at("d_l"), flexbounds_.at("d_r"), relpos,
          false, false, dgerm_state_strs_, dgerm_ggene_ranges_,
          dgerm_naive_bases_, dgerm_germ_inds_, dgerm_site_inds_);

      // Cache the D-J "junction" states.
      CacheJunctionStates(ggene.germ_ptr, flexbounds_.at("d_r"),
                          flexbounds_.at("j_l"), relpos, false,
                          dj_junction_state_strs_, dj_junction_ggene_ranges_,
                          dj_junction_naive_bases_, dj_junction_germ_inds_,
                          dj_junction_site_inds_);
    } else {
      assert(ggene.type == GermlineType::J);

      // Cache the D-J "junction" states.
      CacheJunctionStates(ggene.germ_ptr, flexbounds_.at("d_r"),
                          flexbounds_.at("j_l"), relpos, true,
                          dj_junction_state_strs_, dj_junction_ggene_ranges_,
                          dj_junction_naive_bases_, dj_junction_germ_inds_,
                          dj_junction_site_inds_);

      // Cache the J "germline" state.
      CacheGermlineStates(
          ggene.germ_ptr, flexbounds_.at("j_l"), flexbounds_.at("j_r"), relpos,
          false, true, jgerm_state_strs_, jgerm_ggene_ranges_,
          jgerm_naive_bases_, jgerm_germ_inds_, jgerm_site_inds_);

      // Cache the J "padding" state.
      CachePaddingStates(ggene.germ_ptr, flexbounds_.at("j_r"), relpos, false,
                         jpadding_ggene_ranges_, jpadding_naive_bases_,
                         jpadding_site_inds_);
    }
  }
};


void HMM::InitializeTransition() {
  ComputePaddingTransition(vpadding_ggene_ranges_, ggenes_,
                           vpadding_transition_);
  ComputeGermlineJunctionTransition(
      vgerm_state_strs_, vgerm_ggene_ranges_, vgerm_germ_inds_,
      vgerm_site_inds_, vd_junction_state_strs_, vd_junction_ggene_ranges_,
      vd_junction_germ_inds_, vd_junction_site_inds_, GermlineType::V,
      GermlineType::D, ggenes_, vgerm_vd_junction_transition_);
  ComputeJunctionTransition(vd_junction_state_strs_, vd_junction_ggene_ranges_,
                            vd_junction_germ_inds_, vd_junction_site_inds_,
                            GermlineType::V, GermlineType::D, ggenes_,
                            vd_junction_transition_);
  ComputeJunctionGermlineTransition(
      vd_junction_state_strs_, vd_junction_ggene_ranges_,
      vd_junction_germ_inds_, vd_junction_site_inds_, dgerm_state_strs_,
      dgerm_ggene_ranges_, dgerm_germ_inds_, dgerm_site_inds_, GermlineType::V,
      GermlineType::D, ggenes_, vd_junction_dgerm_transition_);
  ComputeGermlineJunctionTransition(
      dgerm_state_strs_, dgerm_ggene_ranges_, dgerm_germ_inds_,
      dgerm_site_inds_, dj_junction_state_strs_, dj_junction_ggene_ranges_,
      dj_junction_germ_inds_, dj_junction_site_inds_, GermlineType::D,
      GermlineType::J, ggenes_, dgerm_dj_junction_transition_);
  ComputeJunctionTransition(dj_junction_state_strs_, dj_junction_ggene_ranges_,
                            dj_junction_germ_inds_, dj_junction_site_inds_,
                            GermlineType::D, GermlineType::J, ggenes_,
                            dj_junction_transition_);
  ComputeJunctionGermlineTransition(
      dj_junction_state_strs_, dj_junction_ggene_ranges_,
      dj_junction_germ_inds_, dj_junction_site_inds_, jgerm_state_strs_,
      jgerm_ggene_ranges_, jgerm_germ_inds_, jgerm_site_inds_, GermlineType::D,
      GermlineType::J, ggenes_, dj_junction_jgerm_transition_);
  ComputePaddingTransition(jpadding_ggene_ranges_, ggenes_,
                           jpadding_transition_);
};


// Auxiliary functions


void HMM::InitializeForwardProbabilities() {
  vgerm_forward_.setZero(vgerm_state_strs_.size());

  int i = 0;
  for (auto it = vgerm_ggene_ranges_.begin(); it != vgerm_ggene_ranges_.end();
       ++it, i++) {
    // Obtain the (key, value) pairs from the "germline" state index map.
    const std::string& gname = it->first;
    int range_start, range_end;
    std::tie(range_start, range_end) = it->second;

    // Extract the "germline" state information.
    const GermlineGene& ggene = ggenes_.at(gname);
    int germ_ind_start = vgerm_germ_inds_[range_start];

    // Compute the forward probability for the current "germline" state.
    vgerm_forward_[i] = ggene.germ_ptr->gene_prob();
    vgerm_forward_[i] *= vpadding_transition_[i];
    vgerm_forward_[i] *= vpadding_emission_[i];
    vgerm_forward_[i] *=
        ggene.germ_ptr->transition()
            .segment(germ_ind_start, range_end - range_start - 1)
            .prod();
    vgerm_forward_[i] *= vgerm_emission_[i];
  }

  // Scale the forward probabilities.
  vgerm_scaler_count_ = vgerm_init_scaler_count_ + ScaleMatrix(vgerm_forward_);
};


// Forward/backward traversal functions


double HMM::LogLikelihood() {
  InitializeForwardProbabilities();
  ComputeJunctionForwardProbabilities(
      vgerm_forward_, vgerm_scaler_count_, vgerm_vd_junction_transition_,
      vd_junction_transition_, vd_junction_emission_, vd_junction_forward_,
      vd_junction_scaler_counts_);
  ComputeGermlineForwardProbabilities(
      vd_junction_forward_, vd_junction_scaler_counts_,
      vd_junction_dgerm_transition_, dgerm_emission_,
      Eigen::RowVectorXd::Ones(dgerm_state_strs_.size()),
      Eigen::RowVectorXd::Ones(dgerm_state_strs_.size()), dgerm_forward_,
      dgerm_init_scaler_count_, dgerm_scaler_count_);
  ComputeJunctionForwardProbabilities(
      dgerm_forward_, dgerm_scaler_count_, dgerm_dj_junction_transition_,
      dj_junction_transition_, dj_junction_emission_, dj_junction_forward_,
      dj_junction_scaler_counts_);
  ComputeGermlineForwardProbabilities(
      dj_junction_forward_, dj_junction_scaler_counts_,
      dj_junction_jgerm_transition_, jgerm_emission_, jpadding_transition_,
      jpadding_emission_, jgerm_forward_, jgerm_init_scaler_count_,
      jgerm_scaler_count_);

  return std::log(jgerm_forward_.sum()) -
         jgerm_scaler_count_ * std::log(SCALE_FACTOR);
};


// Auxiliary functions


void CacheGermlineStates(
    GermlinePtr germ_ptr, std::pair<int, int> left_flexbounds,
    std::pair<int, int> right_flexbounds, int relpos, bool left_end,
    bool right_end, std::vector<std::string>& state_strs_,
    std::map<std::string, std::pair<int, int>>& ggene_ranges_,
    std::vector<int>& naive_bases_, std::vector<int>& germ_inds_,
    std::vector<int>& site_inds_) {
  // Compute the site positions that correspond to the start/end of the germline
  // gene in the "germline" region.
  int site_start = left_end ? std::max(relpos, left_flexbounds.first)
                            : left_flexbounds.second;
  int site_end =
      right_end ? std::min(relpos + germ_ptr->length(), right_flexbounds.second)
                : right_flexbounds.first;

  // Calculate the start/end indices that map to the current "germline" state.
  int range_start = naive_bases_.size();
  int range_end = naive_bases_.size() + (site_end - site_start);
  ggene_ranges_.emplace(germ_ptr->name(),
                        std::pair<int, int>({range_start, range_end}));

  // Store the germline-related state information.
  state_strs_.push_back(germ_ptr->name());

  for (int i = site_start; i < site_end; i++) {
    naive_bases_.push_back(germ_ptr->bases()[i - relpos]);
    germ_inds_.push_back(i - relpos);
    site_inds_.push_back(i);
  }
};


void CacheJunctionStates(
    GermlinePtr germ_ptr, std::pair<int, int> left_flexbounds,
    std::pair<int, int> right_flexbounds, int relpos, bool left_end,
    std::vector<std::string>& state_strs_,
    std::map<std::string, std::pair<int, int>>& ggene_ranges_,
    std::vector<int>& naive_bases_, std::vector<int>& germ_inds_,
    std::vector<int>& site_inds_) {
  // Compute the site positions that correspond to the start/end of the germline
  // gene in the "junction" region.
  int site_start = left_end ? std::max(relpos, left_flexbounds.first)
                            : left_flexbounds.first;
  int site_end =
      left_end ? right_flexbounds.second
               : std::min(relpos + germ_ptr->length(), right_flexbounds.second);

  // Calculate the start/end indices that map to the "junction" states
  // associated with the current germline gene.
  int range_start = naive_bases_.size();
  int range_end = naive_bases_.size() + (site_end - site_start);
  if (left_end) range_end += germ_ptr->alphabet().size();
  ggene_ranges_.emplace(germ_ptr->name(),
                        std::pair<int, int>({range_start, range_end}));

  // If necessary, cache the NTI-related state information.
  if (left_end) {
    for (std::size_t i = 0; i < germ_ptr->alphabet().size(); i++) {
      state_strs_.push_back(germ_ptr->name() + ":N_" + germ_ptr->alphabet()[i]);
      naive_bases_.push_back(i);
      germ_inds_.push_back(-1);
      site_inds_.push_back(-1);
    }
  }

  // Store the germline-related state information.
  for (int i = site_start; i < site_end; i++) {
    state_strs_.push_back(germ_ptr->name() + ":" + std::to_string(i - relpos));
    naive_bases_.push_back(germ_ptr->bases()[i - relpos]);
    germ_inds_.push_back(i - relpos);
    site_inds_.push_back(i);
  }
};


void CachePaddingStates(
    GermlinePtr germ_ptr, std::pair<int, int> leftright_flexbounds, int relpos,
    bool left_end, std::map<std::string, std::pair<int, int>>& ggene_ranges_,
    std::vector<int>& naive_bases_, std::vector<int>& site_inds_) {
  // Compute the site positions that correspond to the start/end of the padding
  // state in the "germline" region.
  int site_start = left_end ? leftright_flexbounds.first
                            : std::min(relpos + germ_ptr->length(),
                                       leftright_flexbounds.second);
  int site_end = left_end ? std::max(relpos, leftright_flexbounds.first)
                          : leftright_flexbounds.second;

  // Calculate the start/end indices that map to the "padding" state associated
  // with the current germline gene.
  int range_start = naive_bases_.size();
  int range_end = naive_bases_.size() + (site_end - site_start);
  ggene_ranges_.emplace(germ_ptr->name(),
                        std::pair<int, int>({range_start, range_end}));

  // Store the padding-related state information.
  for (int i = site_start; i < site_end; i++) {
    naive_bases_.push_back(germ_ptr->alphabet().size());
    site_inds_.push_back(i);
  }
};


void ComputeGermlineJunctionTransition(
    const std::vector<std::string>& germ_state_strs_,
    const std::map<std::string, std::pair<int, int>>& germ_ggene_ranges_,
    const std::vector<int>& germ_germ_inds_,
    const std::vector<int>& germ_site_inds_,
    const std::vector<std::string>& junction_state_strs_,
    const std::map<std::string, std::pair<int, int>>& junction_ggene_ranges_,
    const std::vector<int>& junction_germ_inds_,
    const std::vector<int>& junction_site_inds_, GermlineType left_gtype,
    GermlineType right_gtype,
    const std::unordered_map<std::string, GermlineGene>& ggenes_,
    Eigen::MatrixXd& germ_junction_transition_) {
  germ_junction_transition_.setZero(germ_state_strs_.size(),
                                    junction_state_strs_.size());

  int from_i = 0;
  for (auto from_it = germ_ggene_ranges_.begin();
       from_it != germ_ggene_ranges_.end(); ++from_it, from_i++) {
    // Obtain the (key, value) pairs from the "germline" state index map.
    const std::string& from_gname = from_it->first;
    int from_range_start, from_range_end;
    std::tie(from_range_start, from_range_end) = from_it->second;

    // Extract the "germline" state information.
    const GermlineGene& from_ggene = ggenes_.at(from_gname);
    int from_germ_ind_start = germ_germ_inds_[from_range_end - 1];
    int from_site_ind_start = germ_site_inds_[from_range_end - 1];

    for (auto to_it = junction_ggene_ranges_.begin();
         to_it != junction_ggene_ranges_.end(); ++to_it) {
      // Obtain the (key, value) pairs from the "junction" state index map.
      const std::string& to_gname = to_it->first;
      int to_range_start, to_range_end;
      std::tie(to_range_start, to_range_end) = to_it->second;

      // Extract the "junction" state information.
      const GermlineGene& to_ggene = ggenes_.at(to_gname);
      int nti_col_length = (to_ggene.type == right_gtype)
                               ? to_ggene.germ_ptr->alphabet().size()
                               : 0;
      int germ_col_start = to_range_start + nti_col_length;
      int germ_col_length = to_range_end - germ_col_start;
      int to_germ_ind_start =
          (germ_col_length > 0) ? junction_germ_inds_[germ_col_start] : -1;
      int to_site_ind_start =
          (germ_col_length > 0) ? junction_site_inds_[germ_col_start] : -1;

      // Fill the "germline"-to-"junction" transition probability matrix.
      Eigen::Ref<Eigen::MatrixXd> germ_junction_transition_row =
          germ_junction_transition_.block(from_i, 0, 1,
                                          germ_junction_transition_.cols());

      FillTransition(from_ggene, to_ggene, left_gtype, right_gtype,
                     from_germ_ind_start, to_germ_ind_start,
                     from_site_ind_start, to_site_ind_start, 0, to_range_start,
                     0, nti_col_length, 0, germ_col_start, 1, germ_col_length,
                     germ_junction_transition_row);
    }
  }
};


void ComputeJunctionTransition(
    const std::vector<std::string>& junction_state_strs_,
    const std::map<std::string, std::pair<int, int>>& junction_ggene_ranges_,
    const std::vector<int>& junction_germ_inds_,
    const std::vector<int>& junction_site_inds_, GermlineType left_gtype,
    GermlineType right_gtype,
    const std::unordered_map<std::string, GermlineGene>& ggenes_,
    Eigen::MatrixXd& junction_transition_) {
  junction_transition_.setZero(junction_state_strs_.size(),
                               junction_state_strs_.size());

  for (auto from_it = junction_ggene_ranges_.begin();
       from_it != junction_ggene_ranges_.end(); ++from_it) {
    // Obtain the (key, value) pairs from the "junction" state index map.
    const std::string& from_gname = from_it->first;
    int from_range_start, from_range_end;
    std::tie(from_range_start, from_range_end) = from_it->second;

    // Extract the "junction" state information.
    const GermlineGene& from_ggene = ggenes_.at(from_gname);
    int nti_row_length = (from_ggene.type == right_gtype)
                             ? from_ggene.germ_ptr->alphabet().size()
                             : 0;
    int germ_row_start = from_range_start + nti_row_length;
    int germ_row_length = from_range_end - germ_row_start;
    int from_germ_ind_start =
        (germ_row_length > 0) ? junction_germ_inds_[germ_row_start] : -1;
    int from_site_ind_start =
        (germ_row_length > 0) ? junction_site_inds_[germ_row_start] : -1;

    for (auto to_it = junction_ggene_ranges_.begin();
         to_it != junction_ggene_ranges_.end(); ++to_it) {
      // Obtain the (key, value) pairs from the "junction" state index map.
      const std::string& to_gname = to_it->first;
      int to_range_start, to_range_end;
      std::tie(to_range_start, to_range_end) = to_it->second;

      // Extract the "junction" state information.
      const GermlineGene& to_ggene = ggenes_.at(to_gname);
      int nti_col_length = (to_ggene.type == right_gtype)
                               ? to_ggene.germ_ptr->alphabet().size()
                               : 0;
      int germ_col_start = to_range_start + nti_col_length;
      int germ_col_length = to_range_end - germ_col_start;
      int to_germ_ind_start =
          (germ_col_length > 0) ? junction_germ_inds_[germ_col_start] : -1;
      int to_site_ind_start =
          (germ_col_length > 0) ? junction_site_inds_[germ_col_start] : -1;

      // Fill the "junction" transition probability matrix.
      FillTransition(from_ggene, to_ggene, left_gtype, right_gtype,
                     from_germ_ind_start, to_germ_ind_start,
                     from_site_ind_start, to_site_ind_start, from_range_start,
                     to_range_start, nti_row_length, nti_col_length,
                     germ_row_start, germ_col_start, germ_row_length,
                     germ_col_length, junction_transition_);
    }
  }
};


void ComputeJunctionGermlineTransition(
    const std::vector<std::string>& junction_state_strs_,
    const std::map<std::string, std::pair<int, int>>& junction_ggene_ranges_,
    const std::vector<int>& junction_germ_inds_,
    const std::vector<int>& junction_site_inds_,
    const std::vector<std::string>& germ_state_strs_,
    const std::map<std::string, std::pair<int, int>>& germ_ggene_ranges_,
    const std::vector<int>& germ_germ_inds_,
    const std::vector<int>& germ_site_inds_, GermlineType left_gtype,
    GermlineType right_gtype,
    const std::unordered_map<std::string, GermlineGene>& ggenes_,
    Eigen::MatrixXd& junction_germ_transition_) {
  junction_germ_transition_.setZero(junction_state_strs_.size(),
                                    germ_state_strs_.size());

  for (auto from_it = junction_ggene_ranges_.begin();
       from_it != junction_ggene_ranges_.end(); ++from_it) {
    // Obtain the (key, value) pairs from the "junction" state index map.
    const std::string& from_gname = from_it->first;
    int from_range_start, from_range_end;
    std::tie(from_range_start, from_range_end) = from_it->second;

    // Extract the "junction" state information.
    const GermlineGene& from_ggene = ggenes_.at(from_gname);
    int nti_row_length = (from_ggene.type == right_gtype)
                             ? from_ggene.germ_ptr->alphabet().size()
                             : 0;
    int germ_row_start = from_range_start + nti_row_length;
    int germ_row_length = from_range_end - germ_row_start;
    int from_germ_ind_start =
        (germ_row_length > 0) ? junction_germ_inds_[germ_row_start] : -1;
    int from_site_ind_start =
        (germ_row_length > 0) ? junction_site_inds_[germ_row_start] : -1;

    int to_i = 0;
    for (auto to_it = germ_ggene_ranges_.begin();
         to_it != germ_ggene_ranges_.end(); ++to_it, to_i++) {
      // Obtain the (key, value) pairs from the "germline" state index map.
      const std::string& to_gname = to_it->first;
      int to_range_start, to_range_end;
      std::tie(to_range_start, to_range_end) = to_it->second;

      // Extract the "germline" state information.
      const GermlineGene& to_ggene = ggenes_.at(to_gname);
      int to_germ_ind_start = germ_germ_inds_[to_range_start];
      int to_site_ind_start = germ_site_inds_[to_range_start];

      // Fill the "junction"-to-"germline" transition probability matrix.
      // (Note: `FillTransition` does not account for the transitions within the
      // "germline" region.)
      Eigen::Ref<Eigen::MatrixXd> junction_germ_transition_col =
          junction_germ_transition_.block(0, to_i,
                                          junction_germ_transition_.rows(), 1);

      FillTransition(from_ggene, to_ggene, left_gtype, right_gtype,
                     from_germ_ind_start, to_germ_ind_start,
                     from_site_ind_start, to_site_ind_start, from_range_start,
                     0, nti_row_length, 0, germ_row_start, 0, germ_row_length,
                     1, junction_germ_transition_col);

      junction_germ_transition_col.block(
          from_range_start, 0, from_range_end - from_range_start, 1) *=
          to_ggene.germ_ptr->transition()
              .segment(to_germ_ind_start, to_range_end - to_range_start - 1)
              .prod();
    }
  }
};


void ComputePaddingTransition(
    const std::map<std::string, std::pair<int, int>>& ggene_ranges_,
    const std::unordered_map<std::string, GermlineGene>& ggenes_,
    Eigen::RowVectorXd& transition_) {
  transition_.setZero(ggene_ranges_.size());

  // Loop through the "padding" states and cache the associated transition
  // probabilities.
  int i = 0;
  for (auto it = ggene_ranges_.begin(); it != ggene_ranges_.end(); ++it, i++) {
    // Obtain the (key, value) pairs from the "padding" state index map.
    const std::string& gname = it->first;
    int range_start, range_end;
    std::tie(range_start, range_end) = it->second;

    // Extract the "padding" state information.
    const GermlineGene& ggene = ggenes_.at(gname);
    double n_transition = (ggene.type == GermlineType::V)
                              ? ggene.VGermlinePtrCast()->n_transition()
                              : ggene.JGermlinePtrCast()->n_transition();

    transition_[i] =
        (1.0 - n_transition) * std::pow(n_transition, range_end - range_start);
  }
};


void FillTransition(const GermlineGene& from_ggene,
                    const GermlineGene& to_ggene, GermlineType left_gtype,
                    GermlineType right_gtype, int germ_ind_row_start,
                    int germ_ind_col_start, int site_ind_row_start,
                    int site_ind_col_start, int nti_row_start,
                    int nti_col_start, int nti_row_length, int nti_col_length,
                    int germ_row_start, int germ_col_start, int germ_row_length,
                    int germ_col_length,
                    Eigen::Ref<Eigen::MatrixXd> transition_) {
  // Are we transitioning within the same gene?
  // [i.e. V_i -> V_i; (N, D_i) -> (N, D_i); D_i -> D_i; (N, J_i) -> (N, J_i)]
  if (from_ggene.germ_ptr->name() == to_ggene.germ_ptr->name()) {
    // Are we transitioning from a NTI state in (N, D_i) or (N, J_i)?
    if (from_ggene.type == right_gtype) {
      // Are we in the V-D or D-J "junction" region?
      if (nti_col_length > 0) {
        // Fill in the N -> N transition probabilities.
        const Eigen::MatrixXd& nti_transition =
            (from_ggene.type == GermlineType::D)
                ? from_ggene.DGermlinePtrCast()->nti_transition()
                : from_ggene.JGermlinePtrCast()->nti_transition();
        transition_.block(nti_row_start, nti_col_start, nti_row_length,
                          nti_col_length) = nti_transition;
      }

      // Are the N -> D or N -> J transitions possible?
      if (germ_col_length > 0) {
        // Fill in the N -> D or N -> J transition probabilities.
        const Eigen::MatrixXd& nti_landing_out =
            (from_ggene.type == GermlineType::D)
                ? from_ggene.DGermlinePtrCast()->nti_landing_out()
                : from_ggene.JGermlinePtrCast()->nti_landing_out();
        transition_.block(nti_row_start, germ_col_start, nti_row_length,
                          germ_col_length) =
            nti_landing_out.block(0, germ_ind_col_start, nti_landing_out.rows(),
                                  germ_col_length);
      }
    }

    // Are the V -> V, D -> D, or J -> J transitions possible?
    if (germ_row_length > 0 && germ_col_length > 0) {
      // Fill in the V -> V, D -> D, or J -> J transition probabilities.
      Eigen::Ref<Eigen::MatrixXd> transition_block = transition_.block(
          germ_row_start, germ_col_start, germ_row_length, germ_col_length);

      // Are we in the V-D or D-J "junction" region?
      if (germ_ind_row_start == germ_ind_col_start) {
        transition_block.diagonal(1) =
            from_ggene.germ_ptr->transition().segment(germ_ind_row_start,
                                                      germ_row_length - 1);
      } else {
        transition_block.diagonal(-(germ_row_length - 1)) =
            from_ggene.germ_ptr->transition().diagonal(
                -(germ_ind_row_start + germ_row_length - 1));
      }
    }
  }

  // Are we transitioning across different genes?
  // [i.e. V_i -> (N, D_j) or D_i -> (N, J_j)]
  if (from_ggene.type == left_gtype && to_ggene.type == right_gtype) {
    // Are we in or transitioning to the V-D or D-J "junction" region?
    if (germ_row_length > 0 && nti_col_length > 0) {
      // Fill in the V -> N or D -> N transition probabilities.
      const Eigen::VectorXd& nti_landing_in =
          (to_ggene.type == GermlineType::D)
              ? to_ggene.DGermlinePtrCast()->nti_landing_in()
              : to_ggene.JGermlinePtrCast()->nti_landing_in();
      Eigen::Ref<Eigen::MatrixXd> transition_block = transition_.block(
          germ_row_start, nti_col_start, germ_row_length, nti_col_length);

      transition_block.setOnes();
      ColVecMatCwise(from_ggene.germ_ptr->landing_out().segment(
                         germ_ind_row_start, germ_row_length),
                     transition_block, transition_block);
      transition_block *= to_ggene.germ_ptr->gene_prob();
      RowVecMatCwise(nti_landing_in, transition_block, transition_block);
    }

    // Are the V -> D or D -> J transitions possible?
    if (germ_row_length > 0 && germ_col_length > 0) {
      // Is there a match region between the two genes?
      int match_row_diff, match_col_diff;
      bool match_found = false;

      for (int from_site_ind = site_ind_row_start;
           from_site_ind < site_ind_row_start + germ_row_length && !match_found;
           from_site_ind++) {
        // Can we find the start index of the potential match region?
        if (from_site_ind == site_ind_col_start - 1) {
          match_row_diff = from_site_ind - site_ind_row_start;
          match_col_diff = 0;
          match_found = true;
        }
      }

      for (int to_site_ind = site_ind_col_start + 1;
           to_site_ind < site_ind_col_start + germ_col_length && !match_found;
           to_site_ind++) {
        // Can we find the start index of the potential match region?
        if (site_ind_row_start == to_site_ind - 1) {
          match_row_diff = 0;
          match_col_diff = to_site_ind - site_ind_col_start;
          match_found = true;
        }
      }

      if (match_found) {
        // Fill in the V -> D or D -> J transition probabilities.
        Eigen::Ref<Eigen::MatrixXd> transition_block = transition_.block(
            germ_row_start + match_row_diff, germ_col_start + match_col_diff,
            germ_row_length - match_row_diff, germ_col_length - match_col_diff);
        int match_length = transition_block.diagonal().size();

        transition_block.diagonal().array() =
            from_ggene.germ_ptr->landing_out()
                .segment(germ_ind_row_start + match_row_diff, match_length)
                .array() *
            to_ggene.germ_ptr->gene_prob() *
            to_ggene.germ_ptr->landing_in()
                .segment(germ_ind_col_start + match_col_diff, match_length)
                .array();
      }
    }
  }
};


void ComputeJunctionForwardProbabilities(
    const Eigen::RowVectorXd& germ_forward_, int germ_scaler_count_,
    const Eigen::MatrixXd& germ_junction_transition_,
    const Eigen::MatrixXd& junction_transition_,
    const Eigen::MatrixXd& junction_emission_,
    Eigen::MatrixXd& junction_forward_,
    std::vector<int>& junction_scaler_counts_) {
  junction_forward_.setZero(junction_emission_.rows(),
                            junction_emission_.cols());
  junction_scaler_counts_.resize(junction_emission_.rows(), 0);

  for (std::size_t i = 0; i < junction_emission_.rows(); i++) {
    Eigen::Ref<Eigen::MatrixXd> junction_forward_row =
        junction_forward_.block(i, 0, 1, junction_forward_.cols());
    int prev_scaler_count;

    // Are we transitioning from a "germline" state?
    if (i == 0) {
      junction_forward_row = germ_forward_ * germ_junction_transition_;
      prev_scaler_count = germ_scaler_count_;
    } else {
      junction_forward_row =
          junction_forward_.row(i - 1) * junction_transition_;
      prev_scaler_count = junction_scaler_counts_[i - 1];
    }

    junction_forward_row.array() *= junction_emission_.row(i).array();

    // Scale the forward probabilities.
    junction_scaler_counts_[i] =
        prev_scaler_count + ScaleMatrix(junction_forward_row);
  }
};


void ComputeGermlineForwardProbabilities(
    const Eigen::MatrixXd& junction_forward_,
    const std::vector<int>& junction_scaler_counts_,
    const Eigen::MatrixXd& junction_germ_transition_,
    const Eigen::RowVectorXd& germ_emission_,
    const Eigen::RowVectorXd& padding_transition_,
    const Eigen::RowVectorXd& padding_emission_,
    Eigen::RowVectorXd& germ_forward_, int& germ_init_scaler_count_,
    int& germ_scaler_count_) {
  // Compute the forward probabilities for the "germline" states.
  germ_forward_ = junction_forward_.bottomRows(1) * junction_germ_transition_;
  germ_forward_.array() *= germ_emission_.array();
  germ_forward_.array() *= padding_transition_.array();
  germ_forward_.array() *= padding_emission_.array();

  // Scale the forward probabilities.
  germ_scaler_count_ = germ_init_scaler_count_ +
                       junction_scaler_counts_.back() +
                       ScaleMatrix(germ_forward_);
};


int ScaleMatrix(Eigen::Ref<Eigen::MatrixXd> m) {
  int n = 0;

  while ((0 < m.array() && m.array() < SCALE_THRESHOLD).any()) {
    m *= SCALE_FACTOR;
    n += 1;
  }

  return n;
};


Eigen::RowVectorXi ConvertSeqToInts(const std::string& seq_str,
                                    const std::string& alphabet) {
  Eigen::RowVectorXi seq(seq_str.size());

  for (std::size_t i = 0; i < seq_str.size(); i++) {
    seq[i] = GetAlphabetIndex(alphabet, seq_str[i]);
  }

  return seq;
};


std::string ConvertIntsToSeq(const Eigen::RowVectorXi& seq,
                             const std::string& alphabet) {
  std::string seq_str(seq.size(), ' ');

  for (std::size_t i = 0; i < seq.size(); i++) {
    seq_str[i] = alphabet.at(seq[i]);
  }

  return seq_str;
};


}  // namespace linearham
