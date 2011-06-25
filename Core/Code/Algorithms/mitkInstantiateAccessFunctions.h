/*=========================================================================

Program:   Medical Imaging & Interaction Toolkit
Language:  C++
Date:      $Date$
Version:   $Revision$

Copyright (c) German Cancer Research Center, Division of Medical and
Biological Informatics. All rights reserved.
See MITKCopyright.txt or http://www.mitk.org/copyright.html for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.

=========================================================================*/


#ifndef MITKINSTANTIATEACCESSFUNCTIONS_H_HEADER_INCLUDED
#define MITKINSTANTIATEACCESSFUNCTIONS_H_HEADER_INCLUDED
 
#include <itkCastImageFilter.h>
#include <mitkImageToItk.h>
#include <mitkConfig.h>

#include <mitkPPSeqForEach.h>
#include <mitkPPSeqForEachProduct.h>
#include <mitkPPSeqToTuple.h>
#include <mitkPPCat.h>
#include <mitkPPExpand.h>
#include <mitkPPTupleRem.h>

#ifndef DOXYGEN_SKIP

#define InstantiateAccessFunctionImpl(r, itkImgFunc, type) \
  MITK_PP_CAT(InstantiateAccessFunction_, itkImgFunc) type

// product is of the form (itkImgFunc)(short)(2)
#ifdef _MSC_VER
#define InstantiateAccessFunctionProductImpl(r, product) \
  MITK_PP_CAT(InstantiateAccessFunction_, MITK_PP_SEQ_HEAD(product)) \
  MITK_PP_EXPAND(MITK_PP_SEQ_TO_TUPLE(MITK_PP_SEQ_TAIL(product)))
#else
#define InstantiateAccessFunctionProductImpl(r, product) \
  MITK_PP_EXPAND(MITK_PP_CAT(InstantiateAccessFunction_, MITK_PP_SEQ_HEAD(product)) \
                 MITK_PP_SEQ_TO_TUPLE(MITK_PP_SEQ_TAIL(product)))
#endif

#endif // DOXYGEN_SKIP


//--------------------------------- instantiation functions  ------------------------------

/**
 * \brief Instantiate access function for the given pixel types and dimensions.
 *
 * Iteratively calls a macro named InstantiateAccessFunction_itkImgFunc
 * which you must define and which usually explicitly instantiates your access function.
 *
 * A call to InstantiateAccessFunctionForFixedPixelType(T, (a)(b), (d)(e)) results in calls
 *
 *   InstantiateAccessFunction_T(a, d)
 *   InstantiateAccessFunction_T(a, e)
 *   InstantiateAccessFunction_T(b, d)
 *   InstantiateAccessFunction_T(b, e)
 *
 * That is, InstantiateAccessFunction_T is called for the cartesian product of the sequences pixelTypeSeq
 * and dimSeq.
 *
 * Example:
 * \code
 * template<typename TPixel, typename VDimension>
 * void MyImageAccessFunction(itk::Image<TPixel, VImageDimension>* itkImage)
 * { ... }
 *
 * #define InstantiateAccessFunction_MyImageAccessFunction(pixelType, dim) \\
 *   template void MyImageAccessFunction(itk::Image<pixelType,dim>*);
 *
 * InstantiateAccessFunctionForFixedPixelType(MyImageAccessFunction, (int), (3))
 * \endcode
 *
 * Use this macro once after the definition of your access function.
 * Some compilers have memory problems without the explicit instantiation.
 * You may need to move the access function to a separate file. The CMake macro
 * MITK_MULTIPLEX_PICTYPE can help you with that. See \c mitk/CMake/mitkMacroMultiplexPicType.cmake
 * for documentation.
 *
 * \param pixelTypeSeq a sequence of types, like (int)(short)(char).
 * \param dimSeq a sequence of dimensions, like (2)(3).
 *
 * \ingroup Adaptor
 */
#define InstantiateAccessFunctionForFixedType(itkImgFunc, pixelTypeSeq, dimSeq)                           \
  MITK_PP_SEQ_FOR_EACH_PRODUCT(InstantiateAccessFunctionProductImpl, ((itkImgFunc))(pixelTypeSeq)(dimSeq))

/**
 * \brief Instantiate access function for all datatypes and dimensions.
 *
 * \sa InstantiateAccessFunctionForFixedType
 *
 * \ingroup Adaptor
 */
#define InstantiateAccessFunction(itkImgFunc)                                                             \
  InstantiateAccessFunctionForFixedDimension(itkImgFunc, 2)                                               \
  InstantiateAccessFunctionForFixedDimension(itkImgFunc, 3)

/**
 * \brief Instantiate access function for all datatypes and a specific dimension.
 *
 * \sa InstantiateAccessFunctionForFixedType
 *
 * \ingroup Adaptor
 */
#define InstantiateAccessFunctionForFixedDimension(itkImgFunc, dim)                                       \
  MITK_PP_SEQ_FOR_EACH(InstantiateAccessFunctionImpl, itkImgFunc, MITK_ACCESSBYITK_TYPES_DIMN_SEQ(dim))

/**
 * \brief Instantiate access function for all given pixel types and all dimensions.
 *
 * \sa InstantiateAccessFunctionForFixedType
 *
 * \ingroup Adaptor
 */
#define InstantiateAccessFunctionForFixedPixelType(itkImgFunc, pixelTypeSeq)                              \
  InstantiateAccessFunctionForFixedType(itkImgFunc, pixelTypeSeq, (2)(3))

/**
 * \brief Instantiate access function for integral datatypes and all dimensions.
 *
 * \sa InstantiateAccessFunctionForFixedType
 *
 * \ingroup Adaptor
 */
#define InstantiateAccessFunctionForIntegralPixelTypes(itkImgFunc)                                        \
  InstantiateAccessFunctionForFixedType(itkImgFunc, MITK_ACCESSBYITK_INTEGRAL_PIXEL_TYPES_SEQ, (2)(3))

/**
 * \brief Instantiate access function for floating point datatypes and all dimensions.
 *
 * \sa InstantiateAccessFunctionForFixedType
 *
 * \ingroup Adaptor
 */
#define InstantiateAccessFunctionForFloatingPixelTypes(itkImgFunc)                                        \
  InstantiateAccessFunctionForFixedType(itkImgFunc, MITK_ACCESSBYITK_FLOATING_PIXEL_TYPES_SEQ, (2)(3))


#endif // of MITKINSTANTIATEACCESSFUNCTIONS_H_HEADER_INCLUDED
