/*=========================================================================

  Library:   CTK

  Copyright (c) Kitware Inc. 
  All rights reserved.
  Distributed under a BSD License. See LICENSE.txt file.

  This software is distributed "AS IS" WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the above copyright notice for more information.

=========================================================================*/

// Qt includes
#include <QApplication>
#include <QPushButton>

// CTK includes
#include "ctkButtonGroup.h"
#include "ctkCollapsibleButton.h"

// STD includes
#include <cstdlib>
#include <iostream>

//-----------------------------------------------------------------------------
int ctkButtonGroupTest1(int argc, char * argv [] )
{
  QApplication app(argc, argv);

  QPushButton* button1 = new QPushButton(0);
  QPushButton* button2 = new QPushButton(0);
  QPushButton* button3 = new QPushButton(0);
  ctkCollapsibleButton* button4 = new ctkCollapsibleButton(0);

  button1->setCheckable(true);
  button2->setCheckable(true);
  button3->setCheckable(false);
  button4->setCheckable(true);
  
  button2->setChecked(true);
  button4->setChecked(true);
  
  ctkButtonGroup buttonGroup(0);
  //QButtonGroup buttonGroup(0);

  buttonGroup.addButton(button1);
  buttonGroup.addButton(button2);
  buttonGroup.addButton(button3);
  buttonGroup.addButton(button4);

  if (!button4->isChecked() || button2->isChecked())
    {
    std::cerr << "ctkButtonGroup::addButton failed"
              << button2->isChecked() << " " << button4->isChecked() 
              << std::endl;
    return EXIT_FAILURE;
    }

  // Click #1: check button1
  button1->click();
  
  if (!button1->isChecked() || button4->isChecked())
    {
    std::cerr << "ctkButtonGroup::click1 failed"
              << button1->isChecked() << " " << button4->isChecked() 
              << std::endl;
    return EXIT_FAILURE;
    }

  // Click #2: uncheck button1 
  button1->click();

  if (button1->isChecked() || button4->isChecked())
    {
    std::cerr << "ctkButtonGroup::click2 failed"
              << button1->isChecked() << " " << button4->isChecked() 
              << std::endl;
    return EXIT_FAILURE;
    }

  // Click #3: check button1 
  button1->click();

  if (!button1->isChecked() || button4->isChecked())
    {
    std::cerr << "ctkButtonGroup::click3 failed"
              << button1->isChecked() << " " << button4->isChecked() 
              << std::endl;
    return EXIT_FAILURE;
    }

  // Click #4: check button2 
  button2->click();

  if (!button2->isChecked() || button1->isChecked())
    {
    std::cerr << "ctkButtonGroup::click4 failed"
              << button2->isChecked() << " " << button1->isChecked() 
              << std::endl;
    return EXIT_FAILURE;
    }
  
  // Click #5: click button3 keep check on button2
  button3->click();

  if (!button2->isChecked() || button3->isChecked())
    {
    std::cerr << "ctkButtonGroup::click5 failed"
              << button2->isChecked() << " " << button3->isChecked() 
              << std::endl;
    return EXIT_FAILURE;
    }
  
  // Click #6: uncheck button2
  button2->click();

  if (button2->isChecked())
    {
    std::cerr << "ctkButtonGroup::click6 failed"
              << button2->isChecked() << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}

