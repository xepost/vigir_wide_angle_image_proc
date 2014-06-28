#ifndef OCAMLIB_CAMERA_MODEL_H
#define OCAMLIB_CAMERA_MODEL_H

//#include <opencv2/core/core.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/calib3d/calib3d.hpp>
//#include <stdexcept>
#include <boost/shared_ptr.hpp>

#include "omni_camera.h"
#include <opencv2/opencv.hpp>

struct ocam_model
{
  double pol[MAX_POL_LENGTH];    // the polynomial coefficients: pol[0] + x"pol[1] + x^2*pol[2] + ... + x^(N-1)*pol[N-1]
  int length_pol;                // length of polynomial
  double invpol[MAX_POL_LENGTH]; // the coefficients of the inverse polynomial
  int length_invpol;             // length of inverse polynomial
  double xc;         // row coordinate of the center
  double yc;         // column coordinate of the center
  double c;          // affine parameter
  double d;          // affine parameter
  double e;          // affine parameter
  int width;         // image width
  int height;        // image height
};

namespace ocamlib_image_geometry{


class OcamlibCameraModelCV1
{
public:

  OcamlibCameraModelCV1(const std::string& ocamlib_calibration_data_file);

  void rectifyImage(const cv::Mat& raw, cv::Mat& rectified,
                    int interpolation = CV_INTER_LINEAR) const;

  void updateUndistortionLUT(int width, int height);
  void create_perspective_undistortion_LUT( cv::Mat *mapx, cv::Mat *mapy, float sf) const;

  void world2cam(double point2D[2], double point3D[3], struct ocam_model *myocam_model);
  void create_perspective_undistortion_LUT( CvMat *mapx, CvMat *mapy, struct ocam_model *ocam_model, float sf);
protected:
  //boost::shared_ptr<vk::OmniCamera> omni_camera_;

  int get_ocam_model(struct ocam_model *myocam_model, const char *filename);

  CvMat* mapx_persp;
  CvMat* mapy_persp;

  ocam_model o;

};

}

#endif