/*
 * Copyright (c) 2013, Christian Gehring, Hannes Sommer, Paul Furgale, Remo Diethelm
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Autonomous Systems Lab, ETH Zurich nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Christian Gehring, Hannes Sommer, Paul Furgale,
 * Remo Diethelm BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#pragma once

#include <cmath>

#include <Eigen/Geometry>

#include "kindr/common/common.hpp"
#include "kindr/common/assert_macros_eigen.hpp"
#include "kindr/rotations/RotationBase.hpp"

namespace kindr {

/*! \class EulerAnglesZyx
 *  \brief Implementation of Euler angles (Z-Y'-X'' / yaw-pitch-roll) rotation based on Eigen::Matrix<Scalar, 3, 1>
 *
 *  The following typedefs are provided for convenience:
 *   - \ref EulerAnglesZyxAD "EulerAnglesZyxD" for active rotation and double primitive type
 *   - \ref EulerAnglesZyxAF "EulerAnglesZyxF" for active rotation and float primitive type
 *   - EulerAnglesYprD = EulerAnglesZyxD
 *   - EulerAnglesYprF = EulerAnglesZyxF
 *
 *  \tparam PrimType_ the primitive type of the data (double or float)
 *  \ingroup rotations
 */
template<typename PrimType_>
class EulerAnglesZyx : public RotationBase<EulerAnglesZyx<PrimType_>> {
 private:
  /*! \brief The base type.
   */
  typedef Eigen::Matrix<PrimType_, 3, 1> Base;

  /*! \brief vector of Euler angles [yaw; pitch; roll]
   */
  Base zyx_;
 public:
  /*! \brief The implementation type.
   *  The implementation type is always an Eigen object.
   */
  typedef Base Implementation;
  /*! \brief The primitive type.
   *  Float/Double
   */
  typedef PrimType_ Scalar;

  /*! \brief Euler angles as 3x1-matrix
   */
  typedef Base Vector;

  /*! \brief Default constructor using identity rotation.
   */
  EulerAnglesZyx()
    : zyx_(Base::Zero()) {
  }

  /*! \brief Constructor using three scalars.
   *  \param yaw      first rotation angle around Z axis
   *  \param pitch    second rotation angle around Y' axis
   *  \param roll     third rotation angle around X'' axis
   */
  EulerAnglesZyx(Scalar yaw, Scalar pitch, Scalar roll)
    : zyx_(yaw,pitch,roll) {
  }

  /*! \brief Constructor using Eigen::Matrix.
   *  \param other   Eigen::Matrix<PrimType_,3,1> [roll; pitch; yaw]
   */
  explicit EulerAnglesZyx(const Base& other)
    : zyx_(other) {
  }

  /*! \brief Constructor using another rotation.
   *  \param other   other rotation
   */
  template<typename OtherDerived_>
  inline explicit EulerAnglesZyx(const RotationBase<OtherDerived_>& other)
    : zyx_(internal::ConversionTraits<EulerAnglesZyx, OtherDerived_>::convert(other.derived()).toImplementation()) {
  }

  /*! \brief Assignment operator using another rotation.
   *  \param other   other rotation
   *  \returns referece
   */
  template<typename OtherDerived_>
  EulerAnglesZyx& operator =(const RotationBase<OtherDerived_>& other) {
    this->toImplementation() = internal::ConversionTraits<EulerAnglesZyx, OtherDerived_>::convert(other.derived()).toImplementation();
    return *this;
  }


  /*! \brief Parenthesis operator to convert from another rotation.
   *  \param other   other rotation
   *  \returns reference
   */
  template<typename OtherDerived_>
  EulerAnglesZyx& operator ()(const RotationBase<OtherDerived_>& other) {
    this->toImplementation() = internal::ConversionTraits<EulerAnglesZyx, OtherDerived_>::convert(other.derived()).toImplementation();
    return *this;
  }

  /*! \brief Returns the inverse of the rotation.
   *  \returns the inverse of the rotation
   */
  EulerAnglesZyx inverted() const {
    return EulerAnglesZyx(RotationQuaternion<PrimType_>(*this).inverted());
  }

  /*! \brief Inverts the rotation.
   *  \returns reference
   */
  EulerAnglesZyx& invert() {
    *this = this->inverted();
    return *this;
  }

  /*! \brief Returns the Euler angles in a vector.
   *  \returns  vector Eigen::Matrix<Scalar,3, 1>
   */
  inline const Vector vector() const {
    return this->toImplementation();
  }

  /*! \brief Cast to the implementation type.
   *  \returns the implementation for direct manipulation (recommended only for advanced users)
   */
  inline Base& toImplementation() {
    return static_cast<Base&>(zyx_);
  }

  /*! \brief Cast to the implementation type.
   *  \returns the implementation for direct manipulation (recommended only for advanced users)
   */
  inline const Base& toImplementation() const {
    return static_cast<const Base&>(zyx_);
  }

  /*! \brief Gets yaw (Z) angle.
   *  \returns yaw angle (scalar)
   */
  inline Scalar yaw() const {
    return zyx_(0);
  }

  /*! \brief Gets pitch (Y') angle.
   *  \returns pitch angle (scalar)
   */
  inline Scalar pitch() const {
    return zyx_(1);
  }

  /*! \brief Gets roll (X'') angle.
   *  \returns roll angle (scalar)
   */
  inline Scalar roll() const {
    return zyx_(2);
  }

  /*! \brief Sets yaw (Z) angle.
   */
  inline void setYaw(Scalar yaw) {
    zyx_(0) = yaw;
  }

  /*! \brief Sets pitch (Y') angle.
   */
  inline void setPitch(Scalar pitch) {
    zyx_(1) = pitch;
  }

  /*! \brief Sets roll (X'') angle.
   */
  inline void setRoll(Scalar roll) {
    zyx_(2) = roll;
  }

  /*! \brief Reading access to yaw (Z) angle.
   *  \returns yaw angle (scalar) with reading access
   */
  inline Scalar z() const {
    return zyx_(0);
  }

  /*! \brief Reading access to pitch (Y') angle.
   *  \returns pitch angle (scalar) with reading access
   */
  inline Scalar y() const {
    return zyx_(1);
  }

  /*! \brief Reading access to roll (X'') angle.
   *  \returns roll angle (scalar) with reading access
   */
  inline Scalar x() const {
    return zyx_(2);
  }

  /*! \brief Writing access to yaw (Z) angle.
   *  \returns yaw angle (scalar) with writing access
   */
  inline void setZ(Scalar z) {
    zyx_(0) = z;
  }

  /*! \brief Writing access to pitch (Y') angle.
   *  \returns pitch angle (scalar) with writing access
   */
  inline void setY(Scalar y) {
    zyx_(1) = y;
  }

  /*! \brief Writing access to roll (X'') angle.
   *  \returns roll angle (scalar) with writing access
   */
  inline void setX(Scalar x) {
    zyx_(2) = x;
  }

  /*! \brief Sets the rotation to identity.
   *  \returns reference
   */
  EulerAnglesZyx& setIdentity() {
    zyx_.setZero();
    return *this;
  }

  /*! \brief Returns a unique Euler angles rotation with angles in [-pi,pi),[-pi/2,pi/2),[-pi,pi).
   *  This function is used to compare different rotations.
   *  \returns copy of the Euler angles rotation which is unique
   */
  EulerAnglesZyx getUnique() const {
    Base zyx(kindr::common::floatingPointModulo(z()+M_PI,2*M_PI)-M_PI,
             kindr::common::floatingPointModulo(y()+M_PI,2*M_PI)-M_PI,
             kindr::common::floatingPointModulo(x()+M_PI,2*M_PI)-M_PI); // wrap all angles into [-pi,pi)

    const double tol = 1e-3;

    // wrap angles into [-pi,pi),[-pi/2,pi/2),[-pi,pi)
    if(zyx.y() < -M_PI/2 - tol)
    {
      if(zyx.z() < 0) {
        zyx.z() = zyx.z() + M_PI;
      } else {
        zyx.z() = zyx.z() - M_PI;
      }

      zyx.y() = -(zyx.y() + M_PI);

      if(zyx.x() < 0) {
        zyx.x() = zyx.x() + M_PI;
      } else {
        zyx.x() = zyx.x() - M_PI;
      }
    }
    else if(-M_PI/2 - tol <= zyx.y() && zyx.y() <= -M_PI/2 + tol)
    {
      zyx.z() += zyx.x();
      zyx.x() = 0;
    }
    else if(-M_PI/2 + tol < zyx.y() && zyx.y() < M_PI/2 - tol)
    {
      // ok
    }
    else if(M_PI/2 - tol <= zyx.y() && zyx.y() <= M_PI/2 + tol)
    {
      // todo: M_PI/2 should not be in range, other formula?
      zyx.z() -= zyx.x();
      zyx.x() = 0;
    }
    else // M_PI/2 + tol < zyx.y()
    {
      if(zyx.z() < 0) {
        zyx.z() = zyx.z() + M_PI;
      } else {
        zyx.z() = zyx.z() - M_PI;
      }

      zyx.y() = -(zyx.y() - M_PI);

      if(zyx.x() < 0) {
        zyx.x() = zyx.x() + M_PI;
      } else {
        zyx.x() = zyx.x() - M_PI;
      }
    }

    return EulerAnglesZyx(zyx);
  }

  /*! \brief Modifies the Euler angles rotation such that the angles lie in [-pi,pi),[-pi/2,pi/2),[-pi,pi).
   *  \returns reference
   */
  EulerAnglesZyx& setUnique() {  // wraps angles into [-pi,pi),[-pi/2,pi/2),[-pi,pi)
    *this = getUnique();
    return *this;
  }

  /*! \brief Concenation operator.
   *  This is explicitly specified, because Eigen::Matrix provides also an operator*.
   *  \returns the concenation of two rotations
   */
  using RotationBase<EulerAnglesZyx<PrimType_>>::operator*;

  /*! \brief Equivalence operator.
   *  This is explicitly specified, because Eigen::Matrix provides also an operator==.
   *  \returns true if two rotations are similar.
   */
  using RotationBase<EulerAnglesZyx<PrimType_>>::operator==;

  /*! \brief Used for printing the object with std::cout.
   *  \returns std::stream object
   */
  friend std::ostream& operator << (std::ostream& out, const EulerAnglesZyx& zyx) {
    out << zyx.toImplementation().transpose();
    return out;
  }
};

//! \brief Active Euler angles rotation (Z,Y',X'' / yaw,pitch,roll) with double primitive type
typedef EulerAnglesZyx<double>  EulerAnglesZyxD;
//! \brief Active Euler angles rotation (Z,Y',X'' / yaw,pitch,roll) with float primitive type
typedef EulerAnglesZyx<float>  EulerAnglesZyxF;
//! \brief Passive Euler angles rotation (Z,Y',X'' / yaw,pitch,roll) with double primitive type
typedef EulerAnglesZyx<double> EulerAnglesZyxPD;
//! \brief Passive Euler angles rotation (Z,Y',X'' / yaw,pitch,roll) with float primitive type
typedef EulerAnglesZyx<float> EulerAnglesZyxPF;

//! \brief Equivalent Euler angles rotation (Z,Y',X'' / yaw,pitch,roll) class
template <typename PrimType_>
using EulerAnglesYpr = EulerAnglesZyx<PrimType_>;

//! \brief Active Euler angles rotation (Z,Y',X'' / yaw,pitch,roll) with double primitive type
typedef EulerAnglesYpr<double>  EulerAnglesYprD;
//! \brief Active Euler angles rotation (Z,Y',X'' / yaw,pitch,roll) with float primitive type
typedef EulerAnglesYpr<float>  EulerAnglesYprF;
//! \brief Passive Euler angles rotation (Z,Y',X'' / yaw,pitch,roll) with double primitive type
typedef EulerAnglesYpr<double> EulerAnglesYprPD;
//! \brief Passive Euler angles rotation (Z,Y',X'' / yaw,pitch,roll) with float primitive type
typedef EulerAnglesYpr<float> EulerAnglesYprPF;



namespace internal {

template<typename PrimType_>
class get_scalar<EulerAnglesZyx<PrimType_>> {
 public:
  typedef PrimType_ Scalar;
};

template<typename PrimType_>
class get_matrix3X<EulerAnglesZyx<PrimType_>>{
 public:
  typedef int  IndexType;

  template <IndexType Cols>
  using Matrix3X = Eigen::Matrix<PrimType_, 3, Cols>;
};


/* -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * Conversion Traits
 * ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
template<typename DestPrimType_, typename SourcePrimType_>
class ConversionTraits<EulerAnglesZyx<DestPrimType_>, AngleAxis<SourcePrimType_>> {
 public:
  inline static EulerAnglesZyx<DestPrimType_> convert(const AngleAxis<SourcePrimType_>& aa) {
    return EulerAnglesZyx<DestPrimType_>(RotationQuaternion<DestPrimType_>(aa));
  }
};

template<typename DestPrimType_, typename SourcePrimType_>
class ConversionTraits<EulerAnglesZyx<DestPrimType_>, RotationVector<SourcePrimType_>> {
 public:
  inline static EulerAnglesZyx<DestPrimType_> convert(const RotationVector<SourcePrimType_>& rotationVector) {
    return EulerAnglesZyx<DestPrimType_>(AngleAxis<SourcePrimType_>(rotationVector));
  }
};

template<typename DestPrimType_, typename SourcePrimType_>
class ConversionTraits<EulerAnglesZyx<DestPrimType_>, RotationQuaternion<SourcePrimType_>> {
 public:
  inline static EulerAnglesZyx<DestPrimType_> convert(const RotationQuaternion<SourcePrimType_>& q) {
    return EulerAnglesZyx<DestPrimType_>((q.toImplementation().toRotationMatrix().eulerAngles(2, 1, 0)).template cast<DestPrimType_>());
  }
};

template<typename DestPrimType_, typename SourcePrimType_>
class ConversionTraits<EulerAnglesZyx<DestPrimType_>, RotationMatrix<SourcePrimType_>> {
 public:
  inline static EulerAnglesZyx<DestPrimType_> convert(const RotationMatrix<SourcePrimType_>& R) {

    const Eigen::Matrix<DestPrimType_,3,3> R_BI = R.toImplementation().transpose().template cast<DestPrimType_>();
    const DestPrimType_ r23 = R_BI(1,2);
    const DestPrimType_ r33 = R_BI(2,2);
    const DestPrimType_ r13 = R_BI(0,2);
    const DestPrimType_ r12 = R_BI(0,1);
    const DestPrimType_ r11 = R_BI(0,0);
    return EulerAnglesZyx<DestPrimType_>(Eigen::Matrix<DestPrimType_,3,1>(atan2(r12,r11), -asin(r13), atan2(r23,r33)));
    //  return  EulerAnglesZyx<DestPrimType_>((R_BI.eulerAngles(2, 1, 0)).template cast<DestPrimType_>()); // original
  }
};

template<typename DestPrimType_, typename SourcePrimType_>
class ConversionTraits<EulerAnglesZyx<DestPrimType_>, EulerAnglesXyz<SourcePrimType_>> {
 public:
  inline static EulerAnglesZyx<DestPrimType_> convert(const EulerAnglesXyz<SourcePrimType_>& xyz) {
    return EulerAnglesZyx<DestPrimType_>(RotationQuaternion<DestPrimType_>(xyz));
  }
};

template<typename DestPrimType_, typename SourcePrimType_>
class ConversionTraits<EulerAnglesZyx<DestPrimType_>, EulerAnglesZyx<SourcePrimType_>> {
 public:
  inline static EulerAnglesZyx<DestPrimType_> convert(const EulerAnglesZyx<SourcePrimType_>& zyx) {
    return EulerAnglesZyx<DestPrimType_>(zyx.toImplementation().template cast<DestPrimType_>());
  }
};

/* -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * Multiplication Traits
 * ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//template<typename PrimType_>
//class MultiplicationTraits<RotationBase<EulerAnglesZyx<PrimType_, RotationUsage::ACTIVE>, RotationUsage::ACTIVE>, RotationBase<EulerAnglesZyx<PrimType_, RotationUsage::ACTIVE>, RotationUsage::ACTIVE>> {
// public:
//  inline static EulerAnglesZyx<PrimType_, RotationUsage::ACTIVE> mult(const EulerAnglesZyx<PrimType_, RotationUsage::ACTIVE>& a, const EulerAnglesZyx<PrimType_, RotationUsage::ACTIVE>& b) {
//    return EulerAnglesZyx<PrimType_, RotationUsage::ACTIVE>(RotationQuaternion<PrimType_, RotationUsage::ACTIVE>(
//                                                                 RotationQuaternion<PrimType_, RotationUsage::ACTIVE>(a).toImplementation()*
//                                                                 RotationQuaternion<PrimType_, RotationUsage::ACTIVE>(b).toImplementation()));
//  }
//};
//
//template<typename PrimType_>
//class MultiplicationTraits<RotationBase<EulerAnglesZyx<PrimType_, RotationUsage::PASSIVE>, RotationUsage::PASSIVE>, RotationBase<EulerAnglesZyx<PrimType_, RotationUsage::PASSIVE>, RotationUsage::PASSIVE>> {
// public:
//  inline static EulerAnglesZyx<PrimType_, RotationUsage::PASSIVE> mult(const EulerAnglesZyx<PrimType_, RotationUsage::PASSIVE>& a, const EulerAnglesZyx<PrimType_, RotationUsage::PASSIVE>& b) {
//    return EulerAnglesZyx<PrimType_, RotationUsage::PASSIVE>(RotationQuaternion<PrimType_, RotationUsage::PASSIVE>(
//                                                                 RotationQuaternion<PrimType_, RotationUsage::PASSIVE>(a).toImplementation()*
//                                                                 RotationQuaternion<PrimType_, RotationUsage::PASSIVE>(b).toImplementation()));
//  }
//};

//template<typename PrimType_>
//class MultiplicationTraits<RotationBase<EulerAnglesZyx<PrimType_>>, RotationBase<EulerAnglesZyx<PrimType_>>> {
// public:
//  inline static EulerAnglesZyx<PrimType_> mult(const EulerAnglesZyx<PrimType_>& a, const EulerAnglesZyx<PrimType_>& b) {
//    return EulerAnglesZyx<PrimType_>(RotationQuaternion<PrimType_>(
//                                                                 RotationQuaternion<PrimType_>(a).toImplementation()*
//                                                                 RotationQuaternion<PrimType_>(b).toImplementation()));
//  }
//};



/* -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * Rotation Traits
 * ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */


/* -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * Comparison Traits
 * ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */


} // namespace internal
} // namespace kindr


