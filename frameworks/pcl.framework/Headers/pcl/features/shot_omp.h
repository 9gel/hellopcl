/*
  * Software License Agreement (BSD License)
  *
  *  Copyright (c) 2009, Willow Garage, Inc.
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
  *
  */

#ifndef PCL_SHOT_OMP_H_
#define PCL_SHOT_OMP_H_

#include <pcl/pcl/point_types.h>
#include <pcl/pcl/features/feature.h>
#include <pcl/pcl/features/shot.h>

namespace pcl
{
  /** \brief SHOTEstimation estimates the Signature of Histograms of OrienTations (SHOT) descriptor for a given point cloud dataset
    * containing points and normals, in parallel, using the OpenMP standard.
    *
    * \note If you use this code in any academic work, please cite:
    *
    *   - F. Tombari, S. Salti, L. Di Stefano
    *     Unique Signatures of Histograms for Local Surface Description.
    *     In Proceedings of the 11th European Conference on Computer Vision (ECCV),
    *     Heraklion, Greece, September 5-11 2010.
    *   - F. Tombari, S. Salti, L. Di Stefano
    *     A Combined Texture-Shape Descriptor For Enhanced 3D Feature Matching.
    *     In Proceedings of the 18th International Conference on Image Processing (ICIP),
    *     Brussels, Belgium, September 11-14 2011.
    *
    * \author Samuele Salti
    * \ingroup features
    */

  template <typename PointInT, typename PointNT, typename PointOutT = pcl::SHOT352, typename PointRFT = pcl::ReferenceFrame>
  class SHOTEstimationOMP : public SHOTEstimation<PointInT, PointNT, PointOutT, PointRFT>
  {
    public:
      using Feature<PointInT, PointOutT>::feature_name_;
      using Feature<PointInT, PointOutT>::getClassName;
      using Feature<PointInT, PointOutT>::input_;
      using Feature<PointInT, PointOutT>::indices_;
      using Feature<PointInT, PointOutT>::k_;
      using Feature<PointInT, PointOutT>::search_parameter_;
      using Feature<PointInT, PointOutT>::search_radius_;
      using Feature<PointInT, PointOutT>::surface_;
      using Feature<PointInT, PointOutT>::fake_surface_;
      using FeatureFromNormals<PointInT, PointNT, PointOutT>::normals_;
      using FeatureWithLocalReferenceFrames<PointInT, PointRFT>::frames_;
      using SHOTEstimation<PointInT, PointNT, PointOutT, PointRFT>::descLength_;
      using SHOTEstimation<PointInT, PointNT, PointOutT, PointRFT>::nr_grid_sector_;
      using SHOTEstimation<PointInT, PointNT, PointOutT, PointRFT>::nr_shape_bins_;
      using SHOTEstimation<PointInT, PointNT, PointOutT, PointRFT>::sqradius_;
      using SHOTEstimation<PointInT, PointNT, PointOutT, PointRFT>::radius3_4_;
      using SHOTEstimation<PointInT, PointNT, PointOutT, PointRFT>::radius1_4_;
      using SHOTEstimation<PointInT, PointNT, PointOutT, PointRFT>::radius1_2_;

      typedef typename Feature<PointInT, PointOutT>::PointCloudOut PointCloudOut;
      typedef typename Feature<PointInT, PointOutT>::PointCloudIn PointCloudIn;

      /** \brief Empty constructor. */
      SHOTEstimationOMP (unsigned int nr_threads = - 1) : SHOTEstimation<PointInT, PointNT, PointOutT, PointRFT> (), threads_ ()
      {
        setNumberOfThreads (nr_threads);
      }

      /** \brief Initialize the scheduler and set the number of threads to use.
        * \param nr_threads the number of hardware threads to use (-1 sets the value back to automatic)
        */
      inline void
      setNumberOfThreads (unsigned int nr_threads)
      {
        if (nr_threads == 0)
          nr_threads = 1;
        threads_ = nr_threads;
      }

    protected:

      /** \brief Estimate the Signatures of Histograms of OrienTations (SHOT) descriptors at a set of points given by
        * <setInputCloud (), setIndices ()> using the surface in setSearchSurface () and the spatial locator in
        * setSearchMethod ()
        * \param output the resultant point cloud model dataset that contains the SHOT feature estimates
        */
      void
      computeFeature (PointCloudOut &output);

      /** \brief This method should get called before starting the actual computation. */
      bool
      initCompute ();

      /** \brief The number of threads the scheduler should use. */
      int threads_;
  };

  template <typename PointInT, typename PointNT, typename PointOutT = pcl::SHOT1344, typename PointRFT = pcl::ReferenceFrame>
  class SHOTColorEstimationOMP : public SHOTColorEstimation<PointInT, PointNT, PointOutT, PointRFT>
  {
    public:
      using Feature<PointInT, PointOutT>::feature_name_;
      using Feature<PointInT, PointOutT>::getClassName;
      using Feature<PointInT, PointOutT>::input_;
      using Feature<PointInT, PointOutT>::indices_;
      using Feature<PointInT, PointOutT>::k_;
      using Feature<PointInT, PointOutT>::search_parameter_;
      using Feature<PointInT, PointOutT>::search_radius_;
      using Feature<PointInT, PointOutT>::surface_;
      using Feature<PointInT, PointOutT>::fake_surface_;
      using FeatureFromNormals<PointInT, PointNT, PointOutT>::normals_;
      using FeatureWithLocalReferenceFrames<PointInT, PointRFT>::frames_;
      using SHOTColorEstimation<PointInT, PointNT, PointOutT, PointRFT>::descLength_;
      using SHOTColorEstimation<PointInT, PointNT, PointOutT, PointRFT>::nr_grid_sector_;
      using SHOTColorEstimation<PointInT, PointNT, PointOutT, PointRFT>::nr_shape_bins_;
      using SHOTColorEstimation<PointInT, PointNT, PointOutT, PointRFT>::sqradius_;
      using SHOTColorEstimation<PointInT, PointNT, PointOutT, PointRFT>::radius3_4_;
      using SHOTColorEstimation<PointInT, PointNT, PointOutT, PointRFT>::radius1_4_;
      using SHOTColorEstimation<PointInT, PointNT, PointOutT, PointRFT>::radius1_2_;
      using SHOTColorEstimation<PointInT, PointNT, PointOutT, PointRFT>::b_describe_shape_;
      using SHOTColorEstimation<PointInT, PointNT, PointOutT, PointRFT>::b_describe_color_;
      using SHOTColorEstimation<PointInT, PointNT, PointOutT, PointRFT>::nr_color_bins_;

      typedef typename Feature<PointInT, PointOutT>::PointCloudOut PointCloudOut;
      typedef typename Feature<PointInT, PointOutT>::PointCloudIn PointCloudIn;

      /** \brief Empty constructor. */
      SHOTColorEstimationOMP (bool describe_shape = true,
                              bool describe_color = true,
                              unsigned int nr_threads = - 1)
        : SHOTColorEstimation<PointInT, PointNT, PointOutT, PointRFT> (describe_shape, describe_color), threads_ ()
      {
        setNumberOfThreads (nr_threads);
      }

      /** \brief Initialize the scheduler and set the number of threads to use.
        * \param nr_threads the number of hardware threads to use (-1 sets the value back to automatic)
        */
      inline void
      setNumberOfThreads (unsigned int nr_threads)
      {
        if (nr_threads == 0)
          nr_threads = 1;
        threads_ = nr_threads;
      }

    protected:

      /** \brief Estimate the Signatures of Histograms of OrienTations (SHOT) descriptors at a set of points given by
        * <setInputCloud (), setIndices ()> using the surface in setSearchSurface () and the spatial locator in
        * setSearchMethod ()
        * \param output the resultant point cloud model dataset that contains the SHOT feature estimates
        */
      void
      computeFeature (PointCloudOut &output);

      /** \brief This method should get called before starting the actual computation. */
      bool
      initCompute ();

      /** \brief The number of threads the scheduler should use. */
      int threads_;
  };

  template <typename PointInT, typename PointNT, typename PointRFT>
  class PCL_DEPRECATED_CLASS (SHOTEstimationOMP, "SHOTEstimationOMP<..., pcl::SHOT, ...> IS DEPRECATED, USE SHOTEstimationOMP<..., pcl::SHOT352, ...> INSTEAD")
    <PointInT, PointNT, pcl::SHOT, PointRFT>
    : public SHOTEstimation<PointInT, PointNT, pcl::SHOT, PointRFT>
  {
    public:
      using Feature<PointInT, pcl::SHOT>::feature_name_;
      using Feature<PointInT, pcl::SHOT>::getClassName;
      using Feature<PointInT, pcl::SHOT>::input_;
      using Feature<PointInT, pcl::SHOT>::indices_;
      using Feature<PointInT, pcl::SHOT>::k_;
      using Feature<PointInT, pcl::SHOT>::search_parameter_;
      using Feature<PointInT, pcl::SHOT>::search_radius_;
      using Feature<PointInT, pcl::SHOT>::surface_;
      using Feature<PointInT, pcl::SHOT>::fake_surface_;
      using FeatureFromNormals<PointInT, PointNT, pcl::SHOT>::normals_;
      using FeatureWithLocalReferenceFrames<PointInT, PointRFT>::frames_;
      using SHOTEstimation<PointInT, PointNT, pcl::SHOT, PointRFT>::descLength_;
      using SHOTEstimation<PointInT, PointNT, pcl::SHOT, PointRFT>::nr_grid_sector_;
      using SHOTEstimation<PointInT, PointNT, pcl::SHOT, PointRFT>::nr_shape_bins_;
      using SHOTEstimation<PointInT, PointNT, pcl::SHOT, PointRFT>::sqradius_;
      using SHOTEstimation<PointInT, PointNT, pcl::SHOT, PointRFT>::radius3_4_;
      using SHOTEstimation<PointInT, PointNT, pcl::SHOT, PointRFT>::radius1_4_;
      using SHOTEstimation<PointInT, PointNT, pcl::SHOT, PointRFT>::radius1_2_;

      typedef typename Feature<PointInT, pcl::SHOT>::PointCloudOut PointCloudOut;
      typedef typename Feature<PointInT, pcl::SHOT>::PointCloudIn PointCloudIn;

      /** \brief Empty constructor. */
      SHOTEstimationOMP (unsigned int nr_threads = - 1, int nr_shape_bins = 10)
        : SHOTEstimation<PointInT, PointNT, pcl::SHOT, PointRFT> (nr_shape_bins), threads_ ()
      {
        setNumberOfThreads (nr_threads);
      }

      /** \brief Initialize the scheduler and set the number of threads to use.
        * \param nr_threads the number of hardware threads to use (-1 sets the value back to automatic)
        */
      inline void
      setNumberOfThreads (unsigned int nr_threads)
      {
        if (nr_threads == 0)
          nr_threads = 1;
        threads_ = nr_threads;
      }

    protected:

      /** \brief Estimate the Signatures of Histograms of OrienTations (SHOT) descriptors at a set of points given by
        * <setInputCloud (), setIndices ()> using the surface in setSearchSurface () and the spatial locator in
        * setSearchMethod ()
        * \param output the resultant point cloud model dataset that contains the SHOT feature estimates
        */
      void
      computeFeature (PointCloudOut &output);

      /** \brief This method should get called before starting the actual computation. */
      bool
      initCompute ();

      /** \brief The number of threads the scheduler should use. */
      int threads_;
  };

  template <typename PointNT, typename PointRFT>
  class PCL_DEPRECATED_CLASS (SHOTEstimationOMP, "SHOTEstimationOMP<pcl::PointXYZRGBA,...,pcl::SHOT,...> IS DEPRECATED, USE SHOTEstimationOMP<pcl::PointXYZRGBA,...,pcl::SHOT352,...> FOR SHAPE AND SHOTColorEstimationOMP<pcl::PointXYZRGBA,...,pcl::SHOT1344,...> FOR SHAPE+COLOR INSTEAD")
    <pcl::PointXYZRGBA, PointNT, pcl::SHOT, PointRFT>
    : public SHOTEstimation<pcl::PointXYZRGBA, PointNT, pcl::SHOT, PointRFT>
  {
    public:
      using SHOTEstimation<pcl::PointXYZRGBA, PointNT, pcl::SHOT, PointRFT>::feature_name_;
      using SHOTEstimation<pcl::PointXYZRGBA, PointNT, pcl::SHOT, PointRFT>::getClassName;
      using SHOTEstimation<pcl::PointXYZRGBA, PointNT, pcl::SHOT, PointRFT>::input_;
      using SHOTEstimation<pcl::PointXYZRGBA, PointNT, pcl::SHOT, PointRFT>::indices_;
      using SHOTEstimation<pcl::PointXYZRGBA, PointNT, pcl::SHOT, PointRFT>::k_;
      using SHOTEstimation<pcl::PointXYZRGBA, PointNT, pcl::SHOT, PointRFT>::search_parameter_;
      using SHOTEstimation<pcl::PointXYZRGBA, PointNT, pcl::SHOT, PointRFT>::search_radius_;
      using SHOTEstimation<pcl::PointXYZRGBA, PointNT, pcl::SHOT, PointRFT>::surface_;
      using FeatureFromNormals<pcl::PointXYZRGBA, PointNT, pcl::SHOT>::normals_;
      using FeatureWithLocalReferenceFrames<pcl::PointXYZRGBA, PointRFT>::frames_;
      using SHOTEstimation<pcl::PointXYZRGBA, PointNT, pcl::SHOT, PointRFT>::descLength_;
      using SHOTEstimation<pcl::PointXYZRGBA, PointNT, pcl::SHOT, PointRFT>::nr_grid_sector_;
      using SHOTEstimation<pcl::PointXYZRGBA, PointNT, pcl::SHOT, PointRFT>::nr_shape_bins_;
      using SHOTEstimation<pcl::PointXYZRGBA, PointNT, pcl::SHOT, PointRFT>::sqradius_;
      using SHOTEstimation<pcl::PointXYZRGBA, PointNT, pcl::SHOT, PointRFT>::radius3_4_;
      using SHOTEstimation<pcl::PointXYZRGBA, PointNT, pcl::SHOT, PointRFT>::radius1_4_;
      using SHOTEstimation<pcl::PointXYZRGBA, PointNT, pcl::SHOT, PointRFT>::radius1_2_;
      using SHOTEstimation<pcl::PointXYZRGBA, PointNT, pcl::SHOT, PointRFT>::b_describe_shape_;
      using SHOTEstimation<pcl::PointXYZRGBA, PointNT, pcl::SHOT, PointRFT>::b_describe_color_;
      using SHOTEstimation<pcl::PointXYZRGBA, PointNT, pcl::SHOT, PointRFT>::nr_color_bins_;

      typedef typename Feature<pcl::PointXYZRGBA, pcl::SHOT>::PointCloudOut PointCloudOut;
      typedef typename Feature<pcl::PointXYZRGBA, pcl::SHOT>::PointCloudIn PointCloudIn;

      /** \brief Empty constructor. */
      SHOTEstimationOMP (bool describeShape = true,
                         bool describeColor = false,
                         unsigned int nr_threads = - 1,
                         const int nr_shape_bins = 10,
                         const int nr_color_bins = 30)
        : SHOTEstimation<pcl::PointXYZRGBA, PointNT, pcl::SHOT, PointRFT> (describeShape, describeColor, nr_shape_bins, nr_color_bins),
          threads_ ()
      {
        setNumberOfThreads (nr_threads);
      }

      /** \brief Initialize the scheduler and set the number of threads to use.
        * \param nr_threads the number of hardware threads to use (-1 sets the value back to automatic)
        */
      inline void
      setNumberOfThreads (unsigned int nr_threads)
      {
        if (nr_threads == 0)
          nr_threads = 1;
        threads_ = nr_threads;
      }

    private:

      /** \brief Estimate the Signatures of Histograms of OrienTations (SHOT) descriptors at a set of points given by
        * <setInputCloud (), setIndices ()> using the surface in setSearchSurface () and the spatial locator in
        * setSearchMethod ()
        * \param output the resultant point cloud model dataset that contains the SHOT feature estimates
        */
      void
      computeFeature (PointCloudOut &output);

      /** \brief The number of threads the scheduler should use. */
      int threads_;
  };
}

#endif  //#ifndef PCL_SHOT_OMP_H_


