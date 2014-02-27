/*
 * Software License Agreement (BSD License)
 *
 *  Point Cloud Library (PCL) - www.pointclouds.org
 *  Copyright (c) 2010-2011, Willow Garage, Inc.
 *
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef PCL_RECOGNITION_HYPOTHESIS_VERIFICATION_H_
#define PCL_RECOGNITION_HYPOTHESIS_VERIFICATION_H_

#include <pcl/pcl/pcl_macros.h>
#include "pcl/recognition/hv/occlusion_reasoning.h"
#include "pcl/recognition/impl/hv/occlusion_reasoning.hpp"
#include <pcl/pcl/common/common.h>
#include <pcl/pcl/search/kdtree.h>
#include <pcl/pcl/filters/voxel_grid.h>

namespace pcl
{

  /**
   * \brief Abstract class for hypotheses verification methods
   * \author Aitor Aldoma, Federico Tombari
   */

  template<typename ModelT, typename SceneT>
  class PCL_EXPORTS HypothesisVerification
  {

  protected:
    /*
     * \brief Boolean vector indicating if a hypothesis is accepted/rejected (output of HV stage)
     */
    std::vector<bool> mask_;
    /*
     * \brief Scene point cloud
     */
    typename pcl::PointCloud<SceneT>::ConstPtr scene_cloud_;

    /*
     * \brief Downsampled scene point cloud
     */
     typename pcl::PointCloud<SceneT>::Ptr scene_cloud_downsampled_;

    /*
     * \brief Scene tree of the downsampled cloud
     */
    typename pcl::search::KdTree<SceneT>::Ptr scene_downsampled_tree_;

    /*
     * \brief Vector of point clouds representing the 3D models after occlusion reasoning
	 * the 3D models are pruned of occluded points, and only visible points are left. 
	 * the coordinate system is that of the scene cloud
     */
    typename std::vector<typename pcl::PointCloud<ModelT>::ConstPtr> visible_models_;
    /*
     * \brief Vector of point clouds representing the complete 3D model (in same coordinates as the scene cloud)
     */
    typename std::vector<typename pcl::PointCloud<ModelT>::ConstPtr> complete_models_;
    /*
     * \brief Resolutions in pixel for the depth scene buffer
     */
    int zbuffer_scene_resolution_;
    /*
     * \brief Resolutions in pixel for the depth model self-occlusion buffer
     */
    int zbuffer_self_occlusion_resolution_;
    /*
     * \brief The resolution of models and scene used to verify hypotheses (in meters)
     */
    float resolution_;

    /*
     * \brief Threshold for inliers
     */
    float inliers_threshold_;

  public:

    HypothesisVerification ()
    {
      zbuffer_scene_resolution_ = 100;
      zbuffer_self_occlusion_resolution_ = 150;
      resolution_ = 0.005f;
      inliers_threshold_ = static_cast<float>(resolution_);
    }

    /*
     *  \brief Sets the resolution of scene cloud and models used to verify hypotheses
     *  mask r resolution
     */
    void
    setResolution(float r) {
      resolution_ = r;
    }

    /*
     *  \brief Sets the resolution of scene cloud and models used to verify hypotheses
     *  mask r resolution
     */
    void
    setInlierThreshold(float r) {
      inliers_threshold_ = r;
    }

    /*
     *  \brief Returns a vector of booleans representing which hypotheses have been accepted/rejected (true/false)
     *  mask vector of booleans
     */

    void
    getMask (std::vector<bool> & mask)
    {
      mask = mask_;
    }

    /*
     *  \brief Sets the 3D complete models. NOTE: If addModels is called with occlusion_reasoning=true, then
     *  there is no need to call this function.
     *  mask models Vector of point clouds representing the models (in same coordinates as the scene_cloud_)
     */

    void
    addCompleteModels (std::vector<const typename pcl::PointCloud<ModelT>::Ptr> & complete_models)
    {
      complete_models_ = complete_models;
    }

    /*
     *  \brief Sets the models (recognition hypotheses) - requires the scene_cloud_ to be set first if reasoning about occlusions
     *  mask models Vector of point clouds representing the models (in same coordinates as the scene_cloud_)
     */
    void
    addModels (std::vector<typename pcl::PointCloud<ModelT>::ConstPtr> & models, bool occlusion_reasoning = false)
    {

      mask_.clear();

      if (!occlusion_reasoning)
        visible_models_ = models;
      else
      {
        //we need to reason about occlusions before setting the model
        if (scene_cloud_ == 0)
        {
          PCL_ERROR("setSceneCloud should be called before adding the model if reasoning about occlusions...");
        }

        pcl::occlusion_reasoning::ZBuffering<ModelT, SceneT> zbuffer_scene (zbuffer_scene_resolution_, zbuffer_scene_resolution_, 1.f);
        if (!scene_cloud_->isOrganized ())
        {
          zbuffer_scene.computeDepthMap (scene_cloud_, true);
        }

        for (size_t i = 0; i < models.size (); i++)
        {

          //self-occlusions
          typename pcl::PointCloud<ModelT>::Ptr filtered (new pcl::PointCloud<ModelT> ());
          typename pcl::occlusion_reasoning::ZBuffering<ModelT, SceneT> zbuffer_self_occlusion (150, 150, 1.f);
          zbuffer_self_occlusion.computeDepthMap (models[i], true);
          zbuffer_self_occlusion.filter (models[i], filtered, 0.005f);

          typename pcl::PointCloud<ModelT>::ConstPtr const_filtered(new pcl::PointCloud<ModelT> (*filtered));

          //scene-occlusions
          if (scene_cloud_->isOrganized ())
          {
            filtered = pcl::occlusion_reasoning::filter<ModelT,SceneT> (scene_cloud_, const_filtered, 525.f, 0.01f);
          }
          else
          {
            zbuffer_scene.filter (const_filtered, filtered, 0.01f);
          }

          visible_models_.push_back (filtered);
        }

        complete_models_ = models;
      }
    }

    /*
     *  \brief Sets the scene cloud
     *  scene_cloud Point cloud representing the scene
     */

    void
    setSceneCloud (const typename pcl::PointCloud<SceneT>::Ptr & scene_cloud)
    {

      complete_models_.clear();
      visible_models_.clear();

      scene_cloud_ = scene_cloud;
      scene_cloud_downsampled_.reset(new pcl::PointCloud<SceneT>());

      pcl::VoxelGrid<SceneT> voxel_grid;
      voxel_grid.setInputCloud (scene_cloud);
      voxel_grid.setLeafSize (resolution_, resolution_, resolution_);
      voxel_grid.filter (*scene_cloud_downsampled_);

      //initialize kdtree for search
      scene_downsampled_tree_.reset (new pcl::search::KdTree<SceneT>);
      scene_downsampled_tree_->setInputCloud(scene_cloud_downsampled_);
    }

    /*
     *  \brief Function that performs the hypotheses verification, needs to be implemented in the subclasses
     *  This function modifies the values of mask_ and needs to be called after both scene and model have been added
     */

    virtual void
    verify ()=0;
  };

}

#endif /* PCL_RECOGNITION_HYPOTHESIS_VERIFICATION_H_ */
