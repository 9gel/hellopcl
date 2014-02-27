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
 *
 */

#ifndef PCL_HARRIS_KEYPOINT_3D_H_
#define PCL_HARRIS_KEYPOINT_3D_H_

#include <pcl/pcl/keypoints/keypoint.h>

namespace pcl
{
  /** \brief HarrisKeypoint3D uses the idea of 2D Harris keypoints, but instead of using image gradients, it uses
    * surface normals.
    *
    * \author Suat Gedikli
    * \ingroup keypoints
    */
  template <typename PointInT, typename PointOutT, typename NormalT = pcl::Normal>
  class HarrisKeypoint3D : public Keypoint<PointInT, PointOutT>
  {
    public:
      typedef typename Keypoint<PointInT, PointOutT>::PointCloudIn PointCloudIn;
      typedef typename Keypoint<PointInT, PointOutT>::PointCloudOut PointCloudOut;
      typedef typename Keypoint<PointInT, PointOutT>::KdTree KdTree;
      typedef typename PointCloudIn::ConstPtr PointCloudInConstPtr;

      using Keypoint<PointInT, PointOutT>::name_;
      using Keypoint<PointInT, PointOutT>::input_;
      using Keypoint<PointInT, PointOutT>::indices_;
      using Keypoint<PointInT, PointOutT>::surface_;
      using Keypoint<PointInT, PointOutT>::tree_;
      using Keypoint<PointInT, PointOutT>::k_;
      using Keypoint<PointInT, PointOutT>::search_radius_;
      using Keypoint<PointInT, PointOutT>::search_parameter_;
      using Keypoint<PointInT, PointOutT>::initCompute;

      typedef enum {HARRIS = 1, NOBLE, LOWE, TOMASI, CURVATURE} ResponseMethod;

      /** \brief Constructor
        * \param[in] method the method to be used to determine the corner responses
        * \param[in] radius the radius for normal estimation as well as for non maxima suppression
        * \param[in] threshold the threshold to filter out weak corners
        */
      HarrisKeypoint3D (ResponseMethod method = HARRIS, float radius = 0.01f, float threshold = 0.0f)
      : threshold_ (threshold)
      , refine_ (true)
      , nonmax_ (true)
      , method_ (method)
      , normals_ (new pcl::PointCloud<NormalT>)
      , threads_ (1)
      {
        name_ = "HarrisKeypoint3D";
        search_radius_ = radius;
      }

      /** \brief set the method of the response to be calculated.
        * \param[in] type
        */
      void setMethod (ResponseMethod type);

      /** \brief set the radius for normal estimation and non maxima supression.
        * \param[in] radius
        */
      void setRadius (float radius);

      /** \brief set the threshold value for detecting corners. This is only evaluated if non maxima suppression is turned on.
        * \brief note non maxima suppression needs to be activated in order to use this feature.
        * \param[in] threshold
        */
      void setThreshold (float threshold);

      /** \brief whether non maxima suppression should be applied or the response for each point should be returned
        * \note this value needs to be turned on in order to apply thresholding and refinement
        * \param[in] nonmax default is false
        */
      void setNonMaxSupression (bool = false);

      /** \brief whether the detected key points should be refined or not. If turned of, the key points are a subset of the original point cloud. Otherwise the key points may be arbitrary.
        * \brief note non maxima supression needs to be on in order to use this feature.
        * \param[in] do_refine
        */
      void setRefine (bool do_refine);

      /**
        * \brief set normals if precalculated normals are available.
        * \param normals
        */
      void setNormals (boost::shared_ptr<pcl::PointCloud<NormalT> > normals ) const;


      virtual void
      setSearchSurface (const PointCloudInConstPtr &cloud) { surface_ = cloud; normals_->clear (); }

      /** \brief Initialize the scheduler and set the number of threads to use.
        * \param nr_threads the number of hardware threads to use (-1 sets the value back to automatic)
        */
      inline void
      setNumberOfThreads (int nr_threads)
      {
        if (nr_threads == 0)
          nr_threads = 1;
        threads_ = nr_threads;
      }
    protected:
      bool
      initCompute ();
      void detectKeypoints (PointCloudOut &output);
      /** \brief gets the corner response for valid input points*/
      void responseHarris (PointCloudOut &output) const;
      void responseNoble (PointCloudOut &output) const;
      void responseLowe (PointCloudOut &output) const;
      void responseTomasi (PointCloudOut &output) const;
      void responseCurvature (PointCloudOut &output) const;
      void refineCorners (PointCloudOut &corners) const;
      /** \brief calculates the upper triangular part of unnormalized covariance matrix over the normals given by the indices.*/
      void calculateNormalCovar (const std::vector<int>& neighbors, float* coefficients) const;
    private:
      float threshold_;
      bool refine_;
      bool nonmax_;
      ResponseMethod method_;
      boost::shared_ptr<pcl::PointCloud<NormalT> > normals_;
      int threads_;
  };
}

#include <pcl/pcl/keypoints/impl/harris_keypoint3D.hpp>

#endif // #ifndef PCL_HARRIS_KEYPOINT_3D_H_

