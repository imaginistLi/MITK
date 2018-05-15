/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/

// Blueberry
#include <berryISelectionService.h>
#include <berryIWorkbenchWindow.h>

// Qmitk
#include "PAUSMotionCompensation.h"

// Qt
#include <QMessageBox>

// mitk image
#include <mitkImage.h>

const std::string PAUSMotionCompensation::VIEW_ID = "org.mitk.views.pausmotioncompensation";

void PAUSMotionCompensation::SetFocus()
{
  m_Controls.buttonPerformImageProcessing->setFocus();
}

void PAUSMotionCompensation::CreateQtPartControl(QWidget *parent)
{
  // create GUI widgets from the Qt Designer's .ui file
  m_Controls.setupUi(parent);
  connect(
    m_Controls.buttonPerformImageProcessing, &QPushButton::clicked, this, &PAUSMotionCompensation::DoImageProcessing);
}

void PAUSMotionCompensation::OnSelectionChanged(berry::IWorkbenchPart::Pointer /*source*/,
                                                const QList<mitk::DataNode::Pointer> &nodes)
{
  // Make sure that there are exactle 2 nodes selected
  if (nodes.size() == 2)
  {
    // iterate all selected objects, adjust warning visibility
    foreach (mitk::DataNode::Pointer node, nodes)
    {
      if (node.IsNotNull() && dynamic_cast<mitk::Image *>(node->GetData()))
      {
        m_Controls.labelWarning->setVisible(false);
        m_Controls.buttonPerformImageProcessing->setEnabled(true);
        return;
      }
    }
  }
  m_Controls.labelWarning->setVisible(true);
  m_Controls.buttonPerformImageProcessing->setEnabled(false);
}

void PAUSMotionCompensation::DoImageProcessing()
{
  QList<mitk::DataNode::Pointer> nodes = this->GetDataManagerSelection();

  // Make sure that there are two images selected
  if (nodes.empty() || nodes.size() != 2)
  {
    QMessageBox::information(nullptr, "Warning", "Please select two images before starting image processing.");
    return;
  }

  //TODO: I need to process two nodes and get the BaseData.
  mitk::DataNode *node = nodes.front();

  if (!node)
  {
    // Nothing selected. Inform the user and return
    QMessageBox::information(nullptr, "Template", "Please load and select 2 images before starting image processing.");
    return;
  }

  // here we have a valid mitk::DataNode

  // a node itself is not very useful, we need its data item (the image)
  mitk::BaseData *data = node->GetData();
  if (data)
  {
    // test if this data item is an image or not (could also be a surface or something totally different)
    mitk::Image *image = dynamic_cast<mitk::Image *>(data);
    if (image)
    {
      std::stringstream message;
      std::string name;
      message << "Performing image processing for image ";
      if (node->GetName(name))
      {
        // a property called "name" was found for this DataNode
        message << "'" << name << "'";
      }
      message << ".";
      MITK_INFO << message.str();

      // actually do something here...
      m_Filter->SetInput(0, image);
      m_Filter->SetInput(1, image);
      m_Filter->Update();
      // node->SetData(m_Filter->GetOutput(0));
      // mitk::Image *test = m_Filter->GetOutput(0);
      m_Filter->GetOutput(0);
      m_Filter->GetOutput(1);
      // node->SetData(test);

      MITK_INFO << "We are back in the plugin.";

      auto newNode = mitk::DataNode::New();
      // newNode->SetData(test);
      newNode->SetName("Test");

      this->GetDataStorage()->Add(newNode);

      mitk::RenderingManager::GetInstance()->RequestUpdateAll();
    }
  }
}
