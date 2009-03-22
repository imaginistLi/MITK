/*=========================================================================

Program:   openCherry Platform
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

#include "cherryQtShowViewAction.h"

#include <cherryIWorkbenchPage.h>
#include <cherryUIException.h>

namespace cherry
{

QtShowViewAction::QtShowViewAction(IWorkbenchWindow::Pointer window,
    IViewDescriptor::Pointer desc) :
  QAction(0)
{
  this->setParent(static_cast<QWidget*>(window->GetShell()->GetControl()));
  this->setText(QString(desc->GetLabel().c_str()));
  this->setToolTip(QString(desc->GetLabel().c_str()));

  QIcon* icon = static_cast<QIcon*>(desc->GetImageDescriptor()->CreateImage());
  this->setIcon(*icon);
  desc->GetImageDescriptor()->DestroyImage(icon);

  m_Window = window;
  m_Desc = desc;

  this->connect(this, SIGNAL(triggered(bool)), this, SLOT(Run()));
}

void QtShowViewAction::Run()
{
  IWorkbenchPage::Pointer page = m_Window->GetActivePage();
  if (page.IsNotNull())
  {
    try
    {
      page->ShowView(m_Desc->GetId());
    }
    catch (PartInitException e)
    {
      std::cout << "Error: " << e.displayText() << std::endl;
    }
  }
}

}
