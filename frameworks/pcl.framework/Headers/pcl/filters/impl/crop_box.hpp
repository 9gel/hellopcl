/*
 * Software License Agreement (BSD License)
 *
 *  Point Cloud Library (PCL) - www.pointclouds.org
 *  Copyright (c) 2009-2011, Willow Garage, Inc.
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
 * $Id: extract_indices.hpp 1897 2011-07-26 20:35:49Z rusu $
 *
 */

#ifndef PCL_FILTERS_IMPL_CROP_BOX_H_
#define PCL_FILTERS_IMPL_CROP_BOX_H_

#include <pcl/pcl/filters/crop_box.h>


///////////////////////////////////////////////////////////////////////////////
template<typename PointT>
void
pcl::CropBox<PointT>::applyFilter (PointCloud &output)
{
  output.resize (input_->points.size ());
  int indice_count = 0;

  // We filter out invalid points
  output.is_dense = true;

  Eigen::Affine3f transform = Eigen::Affine3f::Identity();
  Eigen::Affine3f inverse_transform = Eigen::Affine3f::Identity();

  if (rotation_ != Eigen::Vector3f::Zero ())
  {
    pcl::getTransformation (0, 0, 0,
                            rotation_ (0), rotation_ (1), rotation_ (2),
                            transform);
    inverse_transform = transform.inverse ();
  }

  for (size_t index = 0; index < indices_->size (); ++index)
  {
    if (!input_->is_dense)
      // Check if the point is invalid
      if (!isFinite (input_->points[index]))
        continue;

    // Get local point
    PointT local_pt = input_->points[(*indices_)[index]];

    // Transform point to world space
    if (!(transform_.matrix ().isIdentity ()))
      local_pt = pcl::transformPoint<PointT> (local_pt, transform_);

    if (translation_ != Eigen::Vector3f::Zero ())
    {
      local_pt.x -= translation_ (0);
      local_pt.y -= translation_ (1);
      local_pt.z -= translation_ (2);
    }

    // Transform point to local space of crop box
    if (!(inverse_transform.matrix ().isIdentity ()))
      local_pt = pcl::transformPoint<PointT> (local_pt, inverse_transform);

    if (local_pt.x < min_pt_[0] || local_pt.y < min_pt_[1] || local_pt.z < min_pt_[2])
      continue;
    if (local_pt.x > max_pt_[0] || local_pt.y > max_pt_[1] || local_pt.z > max_pt_[2])
      continue;

    output.points[indice_count++] = input_->points[(*indices_)[index]];
  }
  output.width = indice_count;
  output.height = 1;
  output.resize (output.width * output.height);
}

///////////////////////////////////////////////////////////////////////////////
template<typename PointT> void
pcl::CropBox<PointT>::applyFilter (std::vector<int> &indices)
{
  indices.resize (input_->points.size ());
  int indice_count = 0;

  Eigen::Affine3f transform = Eigen::Affine3f::Identity ();
  Eigen::Affine3f inverse_transform = Eigen::Affine3f::Identity ();

  if (rotation_ != Eigen::Vector3f::Zero ())
  {
    pcl::getTransformation (0, 0, 0,
                            rotation_ (0), rotation_ (1), rotation_ (2),
                            transform);
    inverse_transform = transform.inverse ();
  }

  for (size_t index = 0; index < indices_->size (); ++index)
  {
    if (!input_->is_dense)
      // Check if the point is invalid
      if (!isFinite (input_->points[index]))
        continue;

    // Get local point
    PointT local_pt = input_->points[(*indices_)[index]];

    // Transform point to world space
    if (!(transform_.matrix ().isIdentity ()))
      local_pt = pcl::transformPoint<PointT> (local_pt, transform_);

    if (translation_ != Eigen::Vector3f::Zero ())
    {
      local_pt.x -= translation_ (0);
      local_pt.y -= translation_ (1);
      local_pt.z -= translation_ (2);
    }

    // Transform point to local space of crop box
    if (!(inverse_transform.matrix ().isIdentity ()))
      local_pt = pcl::transformPoint<PointT> (local_pt, inverse_transform);

    if (local_pt.x < min_pt_[0] || local_pt.y < min_pt_[1] || local_pt.z < min_pt_[2])
      continue;
    if (local_pt.x > max_pt_[0] || local_pt.y > max_pt_[1] || local_pt.z > max_pt_[2])
      continue;

    indices[indice_count++] = (*indices_)[index];
  }
  indices.resize (indice_count);
}

#define PCL_INSTANTIATE_CropBox(T) template class PCL_EXPORTS pcl::CropBox<T>;

#endif    // PCL_FILTERS_IMPL_CROP_BOX_H_
