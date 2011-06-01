/*=========================================================================

Program:   Medical Imaging & Interaction Toolkit
Language:  C++
Date:      $Date: $
Version:   $Revision: $

Copyright (c) German Cancer Research Center, Division of Medical and
Biological Informatics. All rights reserved.
See MITKCopyright.txt or http://www.mitk.org/copyright.html for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.

=========================================================================*/


#ifndef MITKNavigationDataHandEyeCalibrationFilter_H_HEADER_INCLUDED_
#define MITKNavigationDataHandEyeCalibrationFilter_H_HEADER_INCLUDED_

#include "mitkNavigationDataToNavigationDataFilter.h"
#include "mitkNavigationData.h"
#include "mitkBaseData.h"
#include "itkQuaternionRigidTransform.h"

namespace mitk {

  /**
  * \brief Class that reads NavigationData from input and transfers the information to the geometry of the associated BaseData
  *
  * Derived from NavigationDataToNavigationDataFilter
  *
  * \ingroup IGT
  */
  class MitkIGT_EXPORT NavigationDataHandEyeCalibrationFilter : public NavigationDataToNavigationDataFilter
  {
  public:
    mitkClassMacro(NavigationDataHandEyeCalibrationFilter, NavigationDataToNavigationDataFilter);

    itkNewMacro(Self);

    /*!
    \brief transformation type for itk::QuaternionRigidTransforms
    */
    typedef itk::QuaternionRigidTransform<ScalarType> QuaternionRigidTransformType;
    /** 
    * \brief Set the object that will be transformed to tracking coordinates using the current NavigationData 
    *        and the given transformation of the HandEyeCalibration
    * 
    * \param index index corresponding to the NavigationData and hand-eye transformation to be applied to this BaseData
    * \param data BaseData to be associated to the index 
    */
    void SetObjectToTransform(unsigned int index, BaseData::Pointer data);

    /**
    * \brief Set the transformation of the HandEyeCalibration that should be applied to the BaseData
    *        with the current transformation of the Navigation Data
    *
    * \param index index corresponding to the NavigationData applied with this hand-eye transformation
    * \param handEyeTransform transformation of a previously performed hand-eye calibration corresponding to the NavigationData
    *                         at index
    */
    void SetHandEyeTransformation(unsigned int index, QuaternionRigidTransformType::Pointer handEyeTransform);
    /*
    * \brief Transfer the information from the input to the associated BaseData
    */
    virtual void GenerateData();


  protected:
    /**
    * \brief Constructor
    **/
    NavigationDataHandEyeCalibrationFilter();

    /**
    * \brief Destructor
    **/
    ~NavigationDataHandEyeCalibrationFilter();

    /** 
    * \brief Map of the BaseDatas that should be transformed. 
    */
    std::map<int,BaseData::Pointer> m_ObjectsToTransform;
    /** 
    * \brief Map of the hand-eye transformations that should be applied to the BaseDatas 
    */
    std::map<int,QuaternionRigidTransformType::Pointer> m_HandEyeTransformations;
  };
} // namespace mitk
#endif /* MITKNavigationDataHandEyeCalibrationFilter_H_HEADER_INCLUDED_ */
