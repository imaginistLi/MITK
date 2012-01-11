/*=========================================================================

Program:   mbilog - logging for mitk / BlueBerry

Copyright (c) German Cancer Research Center, Division of Medical and
Biological Informatics. All rights reserved.
See MITKCopyright.txt or http://www.mitk.org/copyright.html for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef _mbilogAbstractBackend_H
#define _mbilogAbstractBackend_H

#include "mbilogExports.h"
#include "mbilogLogMessage.h"

namespace mbilog{


  /** Documentation
   *  \brief This class is an interface for logging backends that can be registered in the mbi logging mechanism.
   *
   *  \ingroup mbilog
   */
  struct MBILOG_DLL_API AbstractBackend //TODO: convert to class
  {
    virtual ~AbstractBackend()
	
	/** \brief This method is called by the mbi logging mechanism if the object is registered in 
	 *         the mbi logging mechanism and a logging message is emitted.
	 *
	 *  \param logMessage Logging message which was emitted.
	 *
	 */
    virtual void ProcessMessage(const mbilog::LogMessage& logMessage)=0;
  };
  
}


#endif